/*
  ==============================================================================

    SynthVoice.h
    Created: 29 Dec 2018 8:49:36pm
    Author:  RonnyCG

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound)
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	//=========================================

	void getOscType(float* selection)
	{
		theWave = *selection;//numero de seleccion del comboBox
	}
	//=========================================

	double setOscType() //funcion q usa el num de seleccion del comboBox para elegir el tipo de osc
	{
		if (theWave == 0)
		{
			return osc1.sinewave(frequency);
		}

		else if (theWave == 1)
		{
			return osc1.saw(frequency);
		}
		else if (theWave == 2)
		{
			return osc1.square(frequency);
		}
		else
		{
			return osc1.sinewave(frequency);
		}
		
	}
	//=========================================

	void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
	{

		env1.setAttack(double(*attack));
		env1.setDecay(double(*decay));
		env1.setSustain(double(*sustain));
		env1.setRelease(double(*release));
	}
	//=========================================

	double setEnvelopeParams()
	{
		return env1.adsr(setOscType(), env1.trigger);
	}
	//=========================================

	void getFilterParams(float* filterType, float* filterVal, float* filterRes)
	{
		filterChoice = *filterType;
		cutOff = *filterVal;
		resonance = *filterRes;
	}

	//=========================================

	double setFilter()
	{
		if (filterChoice == 0)
		{
			return filter1.lores(setEnvelopeParams(), cutOff, resonance);
		}
		else if (filterChoice == 1)
		{
			return filter1.hires(setEnvelopeParams(), cutOff, resonance);
		}
		else if (filterChoice == 2)
		{
			return filter1.bandpass(setEnvelopeParams(), cutOff, resonance);
		}
		else
		{
			return filter1.lores(setEnvelopeParams(), cutOff, resonance);
		}
	}

	//=========================================

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
	{
		env1.trigger = 1;// trigger (activa) el envelope cuando se empieza la nota
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		
		test = midiNoteNumber;	
	}

	//=========================================

	void stopNote(float velocity, bool allowTailOff)
	{
		env1.trigger = 0; 
		allowTailOff = true;
	
		if(velocity == 0)
			clearCurrentNote();
	}

	//=========================================

	void pitchWheelMoved(int newPitchWheelValue)
	{

	}

	//=========================================

	void controllerMoved(int controllerNumber, int newControllerValue)
	{

	}

	//=========================================

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
	{
			
		for (int sample = 0; sample < numSamples; sample++)
		{
			//double theWave = osc1.sinewave(frequency);

			//double theSound = env1.adsr(setOscType(), env1.trigger) * level;


			for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
			{
				outputBuffer.addSample(channel, startSample, /*theSound*/ setFilter()*level);
			}

			startSample++;
		}
	}

	//=========================================

private:
	double level;
	double frequency;
	int theWave;

	//Filtro
	int filterChoice;
	float cutOff;
	float resonance;
	//===============

	maxiOsc osc1;
	maxiEnv env1;
	maxiFilter filter1;

	int test;
};
