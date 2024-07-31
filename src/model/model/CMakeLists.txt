cmake_minimum_required(VERSION 3.22)

project(RE201Model LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    RE201.cpp
    RE201.h
    dsp/base/AllPassFilter.h
    dsp/base/BiquadCascade.h
    dsp/base/Biquad.cpp
    dsp/base/Biquad.h
    dsp/base/CircularBuffer.cpp
    dsp/base/CircularBuffer.h
    dsp/base/FIRFilter.h
    dsp/base/ImpulseResponse.h
    dsp/base/OnePole.h
    dsp/base/Reverb.h
    dsp/base/TapeMag.h
    dsp/base/VAToneStack.h
    dsp/base/WaveguideSpringReverb.cpp
    dsp/base/WaveguideSpringReverb.h
    dsp/base/WDFToneStack.h
    dsp/base/WowFlutter.h
    dsp/ReverbProcessor.cpp
    dsp/ReverbProcessor.h
    dsp/TapeDelayProcessor.cpp
    dsp/TapeDelayProcessor.h
    dsp/TapeMagProcessor.cpp
    dsp/TapeMagProcessor.h
    dsp/ToneFilteringProcessor.cpp
    dsp/ToneFilteringProcessor.h
    dsp/WetDryProcessor.h
)

add_subdirectory(../../libs/chowdsp_wdf ${CMAKE_BINARY_DIR}/libs/chowdsp_wdf EXCLUDE_FROM_ALL)
add_subdirectory(../../libs/FFTConvolver ${CMAKE_BINARY_DIR}/libs/FFTConvolver EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PUBLIC chowdsp_wdf FFTConvolver)
target_include_directories(${PROJECT_NAME} PUBLIC .)
