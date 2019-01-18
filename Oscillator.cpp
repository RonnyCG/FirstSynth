/*
  ==============================================================================

    Oscillator.cpp
    Created: 31 Dec 2018 11:33:22am
    Author:  RonnyCG

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(FirstSynthAudioProcessor& p) : processor{p}
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	setSize(200, 200);

	oscMenu.addItem("Sine", 1);
	oscMenu.addItem("Saw", 2);
	oscMenu.addItem("Square", 3);
	oscMenu.setJustificationType(Justification::centred);

	addAndMakeVisible(&oscMenu);
	oscMenu.addListener(this);

	oscMenuTree = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);

}
 
Oscillator::~Oscillator()
{
	
}

void Oscillator::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Oscillator", titleArea, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40); //reduce el tamaño del rectangulo por el valor dado en relacion al setSize del constructor
	oscMenu.setBounds(area.removeFromTop(20)); //dibuja el oscMenu 20 pixeles desde arriba del rectangulo
	
}

void Oscillator::comboBoxChanged(ComboBox* box)
{

}