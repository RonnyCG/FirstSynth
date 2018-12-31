/*
  ==============================================================================

    Envelope.cpp
    Created: 31 Dec 2018 3:46:57pm
    Author:  RonnyCG

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(FirstSynthAudioProcessor& p) : processor{ p }
{
	setSize(200, 200);

	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.1f, 5000.0f);
	attackSlider.setValue(0.1f);
	attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&attackSlider);
	attackSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);//linking editor with processor side

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(0.1f, 5000.0f);
	decaySlider.setValue(0.1f);
	decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&decaySlider);
	decaySliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.1f, 5000.0f);
	sustainSlider.setValue(0.1f);
	sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&sustainSlider);
	sustainSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);

	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f, 5000.0f);
	releaseSlider.setValue(0.1f);
	releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
	addAndMakeVisible(&releaseSlider);
	releaseSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
	g.fillAll(Colours::black);
}

void Envelope::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40); //reduce el tamaño del rectangulo por el valor dado en relacion al setSize del constructor

	//======================================= //REVISAR!!!!
	attackSlider.setBounds(10, 10, 40, 100);
	decaySlider.setBounds(56, 10, 40, 100);
	sustainSlider.setBounds(104, 10, 40, 100);
	releaseSlider.setBounds(150, 10, 40, 100);
}
