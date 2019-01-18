/*
  ==============================================================================

    Filter.h
    Created: 17 Jan 2019 11:47:42am
    Author:  RonnyCG

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(FirstSynthAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:

	Slider filterCutOff;
	Slider filterResonance;
	ComboBox filterMenu;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;

	FirstSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
