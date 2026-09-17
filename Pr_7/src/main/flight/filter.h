/*******************************************************************************
 #  SPDX-License-Identifier: GPL-3.0-or-later                                  #
 #  SPDX-FileCopyrightText: 2025 Drona Aviation                                #
 #  -------------------------------------------------------------------------  #
 #  Copyright (c) 2025 Drona Aviation                                          #
 #  All rights reserved.                                                       #
 #  -------------------------------------------------------------------------  #
 #  Author: Ashish Jaiswal (MechAsh) <AJ>                                      #
 #  Project: MagisV2                                                           #
 #  File: \src\main\flight\filter.h                                            #
 #  Created Date: Sat, 22nd Feb 2025                                           #
 #  Brief:                                                                     #
 #  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  #
 #  Last Modified: Sun, 20th Apr 2025                                          #
 #  Modified By: AJ                                                            #
 #  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  #
 #  HISTORY:                                                                   #
 #  Date      	By	Comments                                                   #
 #  ----------	---	---------------------------------------------------------  #
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

typedef float filterStatePt1_t;

float filterApplyPt1 ( float input, filterStatePt1_t *state, uint8_t f_cut );

//!
//!  NEW : Bi-Quad Filter integration
//!

typedef struct {
  float b0, b1, b2, a1, a2;
  float x1, x2, y1, y2;
} biquad_t;

void biquadInitLPF ( biquad_t *filter, float cutoffFreq, float sampleRate );
float biquadApply ( biquad_t *filter, float x );

extern biquad_t accBiquad [ XYZ_AXIS_COUNT ];     // X, Y, Z
extern biquad_t gyroBiquad [ XYZ_AXIS_COUNT ];    // Optional, if you want to filter gyro too

#ifdef __cplusplus
}
#endif
