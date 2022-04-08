// Includes --------------------------------------------------------------------
#include "ADF4159.h"
#include "stm32g4xx.h"
#include "spi.h"
#include "gpio.h"
#include "stm32g4xx_ll_spi.h"
#include "assert.h"
#include "uart.h"
#include "debug.h"

// Private Typedef -------------------------------------------------------------
typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t msb_frac_value : 12;
    uint32_t int_value : 12;
    uint32_t mux_ctrl : 4;
    uint32_t ramp_on : 1;
} ADF4159_R0_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t phase_value : 12;
    uint32_t lsb_frac_value : 13;
    uint32_t phase_adjust : 1;
    uint32_t reserved : 3;
} ADF4159_R1_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t clk1_div_value : 12;
    uint32_t r_counter : 5;
    uint32_t ref_doubler : 1;
    uint32_t rdiv2 : 1;
    uint32_t prescaler : 1;
    uint32_t reserved : 1;
    uint32_t cp_current_setting : 4;
    uint32_t csr : 1;
    uint32_t reserved1 : 3;
} ADF4159_R2_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t counter_reset : 1;
    uint32_t cp_3state : 1;
    uint32_t power_down : 1;
    uint32_t pd_polarity : 1;
    uint32_t ldp : 1;
    uint32_t fsk : 1;
    uint32_t psk : 1;
    uint32_t ramp_mode : 2;
    uint32_t reserved : 2;
    uint32_t sd_reset : 1;
    uint32_t n_sel : 1;
    uint32_t lol : 1;
    uint32_t reserved1 : 4;
    uint32_t neg_bleed_en : 1;
    uint32_t neg_bleed_current : 3;
    uint32_t reserved2 : 7;
} ADF4159_R3_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t reserved : 3;
    uint32_t clk_div_sel : 1;
    uint32_t clk2_div_value : 12;
    uint32_t clk_div_mode : 2;
    uint32_t ramp_status : 5;
    uint32_t sigma_delta_mod_mode : 5;
    uint32_t le_sel : 1;
} ADF4159_R4_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t deviation_word : 16;
    uint32_t deviation_offset_word : 4;
    uint32_t dev_sel : 1;
    uint32_t dual_ramp : 1;
    uint32_t fsk_ramp : 1;
    uint32_t interrupt : 2;
    uint32_t parabolic_ramp : 1;
    uint32_t tx_ramp_clk : 1;
    uint32_t txdata_invert : 1;
    uint32_t reserved : 1;
} ADF4159_R5_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t step_word : 20;
    uint32_t step_sel : 1;
    uint32_t reserved : 6;
} ADF4159_R6_t;

typedef struct
{
    uint32_t ctrl_bits : 3;
    uint32_t delay_start_word : 12;
    uint32_t del_start_en : 1;
    uint32_t del_clk_sel : 1;
    uint32_t ramp_delay : 1;
    uint32_t ramp_delay_fl : 1;
    uint32_t fast_ramp : 1;
    uint32_t txdata_trigger : 1;
    uint32_t sing_full_tri : 1;
    uint32_t tri_delay : 1;
    uint32_t txdata_trigger_delay : 1;
    uint32_t reserved : 8;
} ADF4159_R7_t;

typedef struct
{
    ADF4159_R0_t r0;
    ADF4159_R1_t r1;
    ADF4159_R2_t r2;
    ADF4159_R3_t r3;
    ADF4159_R4_t r4;
    ADF4159_R5_t r5;
    ADF4159_R6_t r6;
    ADF4159_R7_t r7;
} ADF4159_REGS_t;

static_assert(sizeof(ADF4159_R0_t) == 4, "Error");
static_assert(sizeof(ADF4159_R1_t) == 4, "Error");
static_assert(sizeof(ADF4159_R2_t) == 4, "Error");
static_assert(sizeof(ADF4159_R3_t) == 4, "Error");
static_assert(sizeof(ADF4159_R4_t) == 4, "Error");
static_assert(sizeof(ADF4159_R5_t) == 4, "Error");
static_assert(sizeof(ADF4159_R6_t) == 4, "Error");
static_assert(sizeof(ADF4159_R7_t) == 4, "Error");
static_assert(sizeof(ADF4159_REGS_t) == 32, "Error");

// Private Macro ---------------------------------------------------------------

// Private Variables -----------------------------------------------------------
// clang - format off
// REF: Doubler disabled, Use divide by 2, R-counter = 4
// Main divider: INT = 76, FRAC = 26954954
// Use divede
ADF4159_REGS_t reg_init = {
    .r0 = {
        .ctrl_bits = 0, 
        .ramp_on = 0, 
        .int_value = 300, 
        .msb_frac_value = 0, 
        .mux_ctrl = 0xE
    },
    .r1 = {
        .ctrl_bits = 1, 
        .lsb_frac_value = 0, 
        .phase_adjust = 0, 
        .phase_value = 0
    },    
    .r2 = {
        .ctrl_bits = 2, 
        .csr = 0, 
        .cp_current_setting = 0, 
        .prescaler = 0, 
        .rdiv2 = 0, 
        .ref_doubler = 0, 
        .r_counter = 8, 
        .clk1_div_value = 0
    },
    .r3 = {
        .ctrl_bits = 3, 
        .neg_bleed_en = 0, 
        .neg_bleed_current = 0, 
        .lol = 0, 
        .n_sel = 0, 
        .sd_reset = 0, 
        .ramp_mode = 0, 
        .pd_polarity = 0, 
        .power_down = 0, 
        .cp_3state = 0, 
        .counter_reset = 0
    },
    .r4 = {
        .ctrl_bits = 4, 
        .le_sel = 0, 
        .sigma_delta_mod_mode = 0, 
        .ramp_status = 0, 
        .clk_div_mode = 0, 
        .clk2_div_value = 0, 
        .clk_div_sel = 0
    },
    .r5 = {
        .ctrl_bits = 5, 
        .txdata_invert = 0, 
        .tx_ramp_clk = 0, 
        .parabolic_ramp = 0, 
        .interrupt = 0, 
        .fsk_ramp = 0, 
        .dual_ramp = 0, 
        .dev_sel = 0, 
        .deviation_offset_word = 0, 
        .deviation_word = 0
    },    
    .r6 = {
        .ctrl_bits = 6, 
        .step_sel = 0, 
        .step_word = 0
    },
    /* 
    .r6 = {
        .ctrl_bits = 6
    },*/
    .r7 = {
        .ctrl_bits = 7, 
        .txdata_trigger_delay = 0, 
        .tri_delay = 0, 
        .sing_full_tri = 0, 
        .txdata_trigger = 0, 
        .fast_ramp = 0, 
        .ramp_delay_fl = 0, 
        .ramp_delay = 0, 
        .del_clk_sel = 0, 
        .del_start_en = 0, 
        .delay_start_word = 0
    }
};
// clang-format on
static_assert(sizeof(reg_init) == 32, "Error");

// Private Function prototypes -------------------------------------------------
void ADF4159_WriteReg(uint32_t data);
void Delay_ms(uint32_t delay);

// Functions -------------------------------------------------------------------
void ADF4159_Init()
{
    // GPIO Init
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIOBEN;

    GpioSetMode(PLL_3STATE_GPIO_Port, PLL_3STATE_Pin, GPIO_MODE_OUTPUT);
    GpioSetMode(PLL_CE_GPIO_Port, PLL_CE_Pin, GPIO_MODE_OUTPUT);
    GpioSetMode(PLL_LE_GPIO_Port, PLL_LE_Pin, GPIO_MODE_OUTPUT);
    GpioSetMode(PLL_CLK_EN_GPIO_Port, PLL_CLK_EN_Pin, GPIO_MODE_OUTPUT);
    GpioSetMode(PLL_TXDATA_GPIO_Port, PLL_TXDATA_Pin, GPIO_MODE_OUTPUT);

    GpioOutReset(PLL_3STATE_GPIO_Port, PLL_3STATE_Pin);
    GpioOutSet(PLL_CLK_EN_GPIO_Port, PLL_CLK_EN_Pin);
    GpioOutSet(PLL_CE_GPIO_Port, PLL_CE_Pin);

    MX_SPI2_Init();
    LL_SPI_Enable(BOARD_SPI);

    ADF4159_R7_t r7 = {.ctrl_bits = 7};
    ADF4159_WriteReg(*(uint32_t*)&r7);

    ADF4159_R6_t r6 = {.ctrl_bits = 6};
    ADF4159_WriteReg(*(uint32_t*)&r6);
    r6.step_sel = 1;
    ADF4159_WriteReg(*(uint32_t*)&r6);

    ADF4159_R5_t r5 = {.ctrl_bits = 5};
    ADF4159_WriteReg(*(uint32_t*)&r5);
    r5.dev_sel = 1;
    ADF4159_WriteReg(*(uint32_t*)&r5);

    ADF4159_R4_t r4 = {.ctrl_bits = 4};
    ADF4159_WriteReg(*(uint32_t*)&r4);
    r4.clk_div_sel = 1;
    ADF4159_WriteReg(*(uint32_t*)&r4);

    ADF4159_R3_t r3 = {.ctrl_bits = 3};
    ADF4159_WriteReg(*(uint32_t*)&r3);

    ADF4159_R2_t r2 = {.ctrl_bits = 2};
    ADF4159_WriteReg(*(uint32_t*)&r2);

    ADF4159_R1_t r1 = {.ctrl_bits = 1};
    ADF4159_WriteReg(*(uint32_t*)&r1);
    DebugSendArray(&r1, 4);

    ADF4159_R0_t r0 = {.ctrl_bits = 0, .mux_ctrl = 0};
    ADF4159_WriteReg(*(uint32_t*)&r0);

    uint32_t* pointer = (uint32_t*)&reg_init.r7;
    for (uint32_t i = 0; i < 8; i++)
    {
        DebugSendArray(pointer--, 4);
        ADF4159_WriteReg(*pointer--);
    }
}

void ADF4159_WriteReg(uint32_t data)
{
    GpioOutReset(PLL_LE_GPIO_Port, PLL_LE_Pin);

    while (LL_SPI_IsActiveFlag_TXE(BOARD_SPI) == 0)
    {
        /* code */
    }

    LL_SPI_TransmitData16(BOARD_SPI, (uint16_t)(data >> 16));

    while (LL_SPI_IsActiveFlag_TXE(BOARD_SPI) == 0)
    {
        /* code */
    }

    LL_SPI_TransmitData16(BOARD_SPI, (uint16_t)data);

    while (LL_SPI_IsActiveFlag_BSY(BOARD_SPI) == 1)
    {
        /* code */
    }

    GpioOutSet(PLL_LE_GPIO_Port, PLL_LE_Pin);
}
