/*
  ==============================================================================

    Filter.cpp
    Created: 17 Jan 2019 11:47:42am
    Author:  RonnyCG

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(FirstSynthAudioProcessor& p) : processor{ p }
{
 	setSize(200, 200);

	filterMenu.addItem("Low Pass", 1);
	filterMenu.addItem("High Pass", 2);
	filterMenu.addItem("Band Pass", 3);
	filterMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterMenu);
	filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "filterType", filterMenu);
	
	filterCutOff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutOff.setRange(20.0f, 10000.0f); //Hz
	filterCutOff.setValue(400.0); //Hz
	filterCutOff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterCutOff);
	filterVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterCutOff", filterCutOff);
	filterCutOff.setSkewFactorFromMidPoint(1000.0f);//funcion para generar una forma logaritmica de incrementar el slider con el param como punto medio

	filterResonance.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterResonance.setRange(1, 5); 
	filterResonance.setValue(1); 
	filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterResonance);
	resVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filterRes", filterResonance);

}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0,10, getWidth(), 20);
	
	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);

	juce::Rectangle<float> area(25,25,150,150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);

	filterMenu.setBounds(area.removeFromTop(20));
	filterCutOff.setBounds(30, 100, 70, 70);
	filterResonance.setBounds(100, 100, 70, 70);
}
