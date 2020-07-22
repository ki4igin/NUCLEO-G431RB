#ifndef __INIT_H
#define __INIT_H

// Includes --------------------------------------------------------------------

// Typedef ---------------------------------------------------------------------

// Macro -----------------------------------------------------------------------
// #define VCO_MIN 0
#define VCO_MAX 200
#ifdef VCO_MIN
  #define VCO_OFFSET ((VCO_MAX + VCO_MIN) / 2)
  #define VCO_RANGE  (VCO_MAX - VCO_MIN)
#else
  #define VCO_OFFSET 1600  // �������� �������� ���� � ��.
  #define VCO_RANGE  500   // ������ �������� ���� � ��.
// #define VCO_OFFSET 1000  // �������� �������� ���� � ��.
// #define VCO_RANGE  1500  // ������ �������� ���� � ��.
#endif
// Variables -------------------------------------------------------------------

// Function prototypes ---------------------------------------------------------

// Inline Functions ------------------------------------------------------------

#endif
