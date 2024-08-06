/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <foleys_gui_magic/foleys_gui_magic.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_data_structures/juce_data_structures.h>

#include "RE201.h"

//==============================================================================
/**
*/
class JE201AudioProcessor : public foleys::MagicProcessor, juce::ValueTree::Listener
#if JucePlugin_Enable_ARA
    ,
                            public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    JE201AudioProcessor();
    ~JE201AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //This function will alert the listener of parameter changes
    void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged,
        const juce::Identifier& property) override;

private:
    // ------ Parameter storage variabels

    std::atomic<float>*InputLevel = nullptr, *WetDry = nullptr, *Bass = nullptr, *Treble = nullptr, *RepeatRate = nullptr, *Intensity = nullptr, *ReverbVolume = nullptr, *EchoVolume = nullptr;

    juce::AudioParameterChoice* DelaySetting = nullptr;

    juce::AudioParameterChoice* ReverbType = nullptr;

    //Keep for when fixed
    //, *OSAmount = nullptr;

    // ------ Plugin Objects

    // Space echo model
    RE201Model echomodel;

    // Valuetree objects and functions
    juce::AudioProcessorValueTreeState treestate;
    juce::AudioProcessorValueTreeState::ParameterLayout params();

    // -------

    // Functions for getting params from treestate and applying to DSP objects
    void populateParameters();
    void updateParameters();

    // Parameter thread safety flag
    std::atomic_flag changesApplied;

    // Current multi tap playhead state
    int playheadstates[3] = { 0, 0, 0 };

    // Arrays used to enable reverb or delay
    int reverbEnabled[12] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
    int delayEnabled[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };

    // OS amounts, Reintegrate in future updates
    //int OSamount[5] = { 2, 4, 6, 8, 16};
    //int previousOSamount = 0;

    // Function to apply playhead states based on mode selection
    void applyDelaySettings()
    {
        if (*DelaySetting == 0)
        {
            playheadstates[0] = 1;
            playheadstates[1] = 0;
            playheadstates[2] = 0;
        }

        if (*DelaySetting == 1)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 1;
            playheadstates[2] = 0;
        }

        if (*DelaySetting == 2)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 0;
            playheadstates[2] = 1;
        }

        if (*DelaySetting == 3)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 1;
            playheadstates[2] = 1;
        }

        if (*DelaySetting == 4)
        {
            playheadstates[0] = 1;
            playheadstates[1] = 0;
            playheadstates[2] = 0;
        }

        if (*DelaySetting == 5)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 1;
            playheadstates[2] = 0;
        }

        if (*DelaySetting == 6)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 0;
            playheadstates[2] = 1;
        }

        if (*DelaySetting == 7)
        {
            playheadstates[0] = 1;
            playheadstates[1] = 1;
            playheadstates[2] = 0;
        }

        if (*DelaySetting == 8)
        {
            playheadstates[0] = 0;
            playheadstates[1] = 1;
            playheadstates[2] = 1;
        }

        if (*DelaySetting == 9)
        {
            playheadstates[0] = 1;
            playheadstates[1] = 0;
            playheadstates[2] = 1;
        }

        if (*DelaySetting == 10)
        {
            playheadstates[0] = 1;
            playheadstates[1] = 1;
            playheadstates[2] = 1;
        }
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JE201AudioProcessor)
};
