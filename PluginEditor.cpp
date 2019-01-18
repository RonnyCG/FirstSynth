/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
FirstSynthAudioProcessorEditor::FirstSynthAudioProcessorEditor (FirstSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

	addAndMakeVisible(&oscGUI);
	addAndMakeVisible(&envGUI);
	addAndMakeVisible(&filterGUI);
}

FirstSynthAudioProcessorEditor::~FirstSynthAudioProcessorEditor()
{
}

//==============================================================================
void FirstSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void FirstSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	juce::Rectangle<int> area = getLocalBounds();
	
	const int componentWidth = 200;
	const int componentHeigth = 200;

	oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeigth));
	filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeigth));
	envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeigth));//revisar!!!

	 
}


