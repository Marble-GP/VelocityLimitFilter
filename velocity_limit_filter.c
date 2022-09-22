#include "velocity_limit_filter.h"

void VLF_Init(velocity_limit_filter_t* handler, float max_velocity, float FB_Gain, float LPF_CutOffFreq, float ControlFreq)
{

    //auto LPF gain
    if(LPF_CutOffFreq < 0.0f)
    {
        float k = ControlFreq/max_velocity;
        if(k > 10.0f)
        {
            LPF_CutOffFreq = 10.0f * max_velocity;
            if(FB_Gain < 0.0f)
            {
                FB_Gain = 15.4f*max_velocity;
            }
        }
        else if(k > 5.0f)
        {
            LPF_CutOffFreq = 5.0f*max_velocity;
            if(FB_Gain < 0.0f)
            {
                FB_Gain = 7.82f*max_velocity;
            }
        }
        else if(k > 2.0f)
        {
            LPF_CutOffFreq = 2.0f*max_velocity;
            if(FB_Gain < 0.0f)
            {
                FB_Gain = 3.18f*max_velocity;
            }           
        }
        else
        {
            LPF_CutOffFreq = max_velocity;
            if(FB_Gain < 0.0f)
            {
                FB_Gain = 1.65f*max_velocity;
            }
        }

    }

    handler->max_velocity = max_velocity;
    handler->FB_Gain = FB_Gain;
    handler->LPF_Gain = (2.0f*VLF_FLOAT32_PI*LPF_CutOffFreq/ControlFreq)/(1.0f + (2.0f*VLF_FLOAT32_PI*LPF_CutOffFreq/ControlFreq));
    handler->Ts = 1.0f/ControlFreq;
    handler->output = 0.0f;
    handler->input_lpf_pre = 0.0f;
}

float VLF_Operate(velocity_limit_filter_t* handler, float input)
{
    float input_lpf = handler->LPF_Gain*input + (1.0f - handler->LPF_Gain)*handler->output;
    handler->output += VLF_limitter((input_lpf - handler->input_lpf_pre)/handler->Ts  -  handler->FB_Gain*(handler->output - input_lpf), handler->max_velocity)*handler->Ts;
    handler->input_lpf_pre = input_lpf;

    return handler->output;
}

void VLF_Reset(velocity_limit_filter_t* handler)
{
    handler->output = 0.0f;
    handler->input_lpf_pre = 0.0f;
}