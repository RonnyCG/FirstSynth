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
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 20.0, 10.0);
	addAndMakeVisible(&attackSlider);
	attackSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);//linking editor with processor side

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(0.1f, 5000.0f);
	decaySlider.setValue(0.1f);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 20.0, 10.0);
	addAndMakeVisible(&decaySlider);
	decaySliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.1f, 5000.0f);
	sustainSlider.setValue(0.1f);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 20.0, 10.0);
	addAndMakeVisible(&sustainSlider);
	sustainSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);

	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f, 5000.0f);
	releaseSlider.setValue(0.1f);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 20.0, 10.0);
	addAndMakeVisible(&releaseSlider);
	releaseSliderTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Envelope", titleArea, Justification::centredTop);

	//static, should be dinamic
	g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
	g.drawText("D", 77, 150, 20, 20, Justification::centredTop);
	g.drawText("S", 103, 150, 20, 20, Justification::centredTop);
	g.drawText("R", 128, 150, 20, 20, Justification::centredTop);
	
	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(50); //reduce el tamaño del rectangulo por el valor dado en relacion al setSize del constructor

	int sliderWidth = 25;
	int sliderHeight = 175;

	attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));

	/*//======================================= //REVISAR!!!!
	attackSlider.setBounds(10, 10, 40, 100);
	decaySlider.setBounds(56, 10, 40, 100);
	sustainSlider.setBounds(104, 10, 40, 100);
	releaseSlider.setBounds(150, 10, 40, 100);*/
}
