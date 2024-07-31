#pragma once

#include "base/WDFToneStack.h"
#include "base/VAToneStack.h"
#include <memory>

class ToneStackProcessor 
{

public:

    ToneStackProcessor() {};
    ~ToneStackProcessor() {};

    // Resets the tone stack processor with sample rate and number of channels.
    // set bool to 0 for VA tone filtering and 1 for WDF filtering.
    void Reset(float sampleRate, int numChannels, bool vaorwdf); 
    void UpdateParameters(float Bass, float Treble, float inputlevel);
    void ProcessBuffer(std::vector<std::vector<float>>& buffer, int blockSize);

private:

    // DSP filters
    std::vector<std::unique_ptr<VAToneStack>> VAfilters;
    std::vector<std::unique_ptr<WDFToneStack>> WDFfilters;

    // False for VA model, true for WDF model. Assigned at reset.
    bool VAorWDF = false;

    // Object variables
    int NumChannels = 2;
    float InputLevel = 0.0f;
    
    double nonlinear_mapping(double x) {
        if (x < 0.5) {
            return 0.25 + 3 * (x / 0.5);
        }
        else {
            return 1 + 3 * ((x - 0.5) / 0.5);
        }
    }

};
