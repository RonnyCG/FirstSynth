/*
  ==============================================================================

    Oscillator.h
    Created: 31 Dec 2018 11:33:22am
    Author:  RonnyCG

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator    : public Component, private ComboBox::Listener
{
public:
    Oscillator(FirstSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

	void comboBoxChanged(ComboBox*) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	FirstSynthAudioProcessor& processor;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oscMenuTree;
	ComboBox oscMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
