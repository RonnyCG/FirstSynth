/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"

//==============================================================================
/**
*/
class FirstSynthAudioProcessorEditor  : public AudioProcessorEditor 
									
{
public:
    FirstSynthAudioProcessorEditor (FirstSynthAudioProcessor&);
    ~FirstSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstSynthAudioProcessor& processor;

	Oscillator oscGUI;
	Envelope envGUI;
	Filter filterGUI;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSynthAudioProcessorEditor)
};
