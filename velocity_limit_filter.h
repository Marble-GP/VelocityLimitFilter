/**
 * @file velocity_limit_filter.h
 * @author  S.Watanabe (marble321done@gmail.com)
 * @brief This is a Library of Velocity Limit Filter with Feedback (Proposed by H.Okajima,et al., Kumamoto Univ.)
 * @ref https://www.jstage.jst.go.jp/article/sicetr/54/1/54_146/_pdf/-char/ja
 *      https://fragrant-rainforest-e05.notion.site/ecb6808ef9f348749128c61bf45e40c4
 * @version 0.2.2
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef VELOCITY_LIMIT_FILTER_H
#define VELOCITY_LIMIT_FILTER_H

#include <math.h>

#define VLF_FLOAT32_PI (3.1415927f)

#define VLF_limitter(x, limit_val) ((x) > (limit_val) ? (limit_val) : ((x) < -(limit_val) ? -(limit_val) : (x)))

#define VLF_AUTO (-1.0f)

typedef struct __velocity_limit_filter
{
    float max_velocity;
    float FB_Gain;
    float LPF_Gain;
    float Ts;
    float input_lpf_pre;
    float output;

} velocity_limit_filter_t;

/**
 * @brief Initilize function of Velocity Limit Filter.
 * 
 * @param handler Velocity Limit Filter Handler
 * @param max_velocity Limit value of gradient of output signal
 * @param FB_Gain Feedback gain (Setting the value to zero or a negative number automatically sets the optimum gain.)
 * @param LPF_CutOffFreq Cut-Off Frequency of IIR Digital Low-Pass Filter (Setting the value to zero or a negative number will automatically set the value.)
 * @param ControlFreq Input signal sampling frequency or digital control frequency (The filter should operate every (1/ControlFreq) second.)
 */
void VLF_Init(velocity_limit_filter_t* handler, float max_velocity, float FB_Gain, float LPF_CutOffFreq, float ControlFreq);

/**
 * @brief Calculate the Velocity Limit Filter.
 * 
 * @param handler Velocity Limit Filter Handler
 * @param input Input value
 * @return float Output value of the filter
 */
float VLF_Operate(velocity_limit_filter_t* handler, float input);

/**
 * @brief Rerset internal variables of the Velocity Limit Filter.
 * 
 * @param handler Velocity Limit Filter Handler
 */
void VLF_Reset(velocity_limit_filter_t* handler);

#endif