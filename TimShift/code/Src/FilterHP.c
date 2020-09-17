/*
 * FilterHP.c
 *
 *  Created on: 9 окт. 2018 г.
 *      Author: Artem
 */

#include "FIlterHP.h"

float p1Coeff[3] = {1, -2, 1};

float p2Coeff[2] = {-1.92894226325203, 0.9313816821269031};

float p3Coeff = 0.965080986344734;

float filtStates1[2];

float filtStates2[2];

float iir_Dopler1(float x)
{
  float stageIn = p3Coeff * x;
  stageIn -= p2Coeff[0] * filtStates1[0];
  stageIn -= p2Coeff[1] * filtStates1[1];
  float numAccum = p1Coeff[0] * stageIn;
  numAccum += p1Coeff[1] * filtStates1[0];
  numAccum += p1Coeff[2] * filtStates1[1];

  filtStates1[1] = filtStates1[0];
  filtStates1[0] = stageIn;

  return numAccum;
}

float iir_Dopler2(float x)
{
  float stageIn = p3Coeff * x;
  stageIn -= p2Coeff[0] * filtStates2[0];
  stageIn -= p2Coeff[1] * filtStates2[1];
  float numAccum = p1Coeff[0] * stageIn;
  numAccum += p1Coeff[1] * filtStates2[0];
  numAccum += p1Coeff[2] * filtStates2[1];

  filtStates2[1] = filtStates2[0];
  filtStates2[0] = stageIn;

  return numAccum;
}
