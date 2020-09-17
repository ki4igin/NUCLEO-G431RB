#ifndef __AD9102_H
#define __AD9102_H

// Includes --------------------------------------------------------------------
#include "Init.h"
// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------
#define SPICONFIG          0x00  //SPI Control Register
#define SPICONFIG_RESET    0x2000
#define SPICONFIG_SPI3WIRE 0x4000

#define POWERCONFIG 0x01  // Power Status Register
#define DAC_SLEEP   0x08  // Disable DAC output current

#define DACRSET     0x0C    // FSADJ Register
#define DAC_RSET_EN 0x8000  // Enable the internal RSET resistor for the DAC
#define DAC_RSET    0x8     // Digital control to set the value of the RSET resistor in the DAC [4:0] (default 0x0A)

#define RAMUPDATE 0x1D  // Update Pattern Register
#define UPDATE    0x1   // Update all SPI settings with a new configuration (self-clearing)

#define PAT_STATUS 0x1E  // Command/Status Register
#define MEM_ACCESS 0x4   // Memory SPI access enable
#define RUN        0x1   // Allows the pattern generation, and stop pattern after trigger

#define DACDOF         0x25                               //DAC Digital Offset Register
#define DAC_DIG_OFFSET ((-647 * VCO_OFFSET / 1000) << 4)  //DAC digital offset CODE = -1396 * Usm + 3

#define WAV_CONFIG 0x27  // Wave Select Register
#define WAV_SEL    0x0   // 0 Waveform read from RAM between START_ADDR and STOP_ADDR
                         // 1 Restored waveform (default)                            
                         // 2 Prestored waveform using START_DELAY and PATTERN_PERIOD
                         // 3 Prestored waveform modulated by waveform from RAM

#define PAT_TIMEBASE      0x28
#define START_DELAY_BASE  1
#define PAT_PERIOD_BASE   1 << 4  //The number of DAC clock periods per PATTERN_PERIOD (default 1) [7:4] bit
#define PAT_TIMEBASE_HOLD 1 << 8

#define PAT_PERIOD     0x29  //Pattern period register
#define PATTERN_PERIOD 100   //Pattern period (default 0x8000) CODE = 150 MHz / Fout (CODE = 100: Fout = 1.5 MHz)

#define DAC_DGAIN    0x35                                  //DAC Digital Gain Register
#define DAC_DIG_GAIN ((-155 * VCO_RANGE / 1000 + 0) << 4)  //DAC digital gain 12 bits, range +2 to -2; CODE = -214 * dU + 20; dU = (CODE - 20) / -214

#define START_ADDR_REG 0x5D  //Start Address Register
#define START_ADDR     0x00  //RAM address where DAC starts to read waveform

#define STOP_ADDR_REG 0x5E                   //Stop Address Register
#define STOP_ADDR     (PATTERN_PERIOD << 4)  //RAM address where DAC stops to read waveform.
// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------
void AD9102Init(void);
// Inline Functions ------------------------------------------------------------

#endif
