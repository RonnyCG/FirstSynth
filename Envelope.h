/*
  ==============================================================================

    Envelope.h
    Created: 31 Dec 2018 3:46:57pm
    Author:  RonnyCG

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(FirstSynthAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackSliderTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decaySliderTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainSliderTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseSliderTree;
	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	FirstSynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
