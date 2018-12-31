/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSynthAudioProcessor::FirstSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
		),
	tree(*this, nullptr)

#endif
{
	//ADSR Sliders
	//===================================================================================================
	NormalisableRange<float> attackParam(50.f, 5000.0f);
	NormalisableRange<float> decayParam(50.0f, 5000.0f);
	NormalisableRange<float> sustainParam(0.0f, 1.0f);
	NormalisableRange<float> releaseParam(50.0f, 5000.0f);

	tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 100.0f, nullptr, nullptr);
	tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 100.0f, nullptr, nullptr);
	tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 1.0f, nullptr, nullptr);
	tree.createAndAddParameter("release", "Release", "Release", releaseParam, 100.0f, nullptr, nullptr);
	
	//===================================================================================================

	//OSC ComboBox
	//==========================================================================================
	NormalisableRange<float> wavetypeParam(0, 2);
	tree.createAndAddParameter("wavetype","WaveType","WaveType",wavetypeParam,0,nullptr, nullptr);
	//==========================================================================================

	tree.state = ValueTree("Foo");

	mySynth.clearVoices();

	for (int i = 0; i < 5; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}

	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

FirstSynthAudioProcessor::~FirstSynthAudioProcessor()
{
}

//==============================================================================
const String FirstSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String FirstSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FirstSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	ignoreUnused(samplesPerBlock); //ignora samples de la anterior tecla presionada, para q no quede basura
	lastSampleRate = sampleRate; //variable usada para q no haya problemas en varias tarjetas de sonido
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);


}

void FirstSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FirstSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
 
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
		{
			myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"), //Envelope
										tree.getRawParameterValue("decay"), 
										tree.getRawParameterValue("sustain"), 
										tree.getRawParameterValue("release"));

			myVoice->getOscType(tree.getRawParameterValue("wavetype"));		//Osc ComboBox
		}
	}

	buffer.clear();
	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool FirstSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FirstSynthAudioProcessor::createEditor()
{
    return new FirstSynthAudioProcessorEditor (*this);
}

//==============================================================================
void FirstSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstSynthAudioProcessor();
}
