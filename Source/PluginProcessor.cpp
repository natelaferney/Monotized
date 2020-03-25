/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonotizedAudioProcessor::MonotizedAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : parameters(*this, nullptr, Identifier("Monotized"),
		 {
			 std::make_unique<AudioParameterBool>("enabled", "Enabled", false)
		 }),
		
		AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	enabled = parameters.getRawParameterValue("enabled");
}

MonotizedAudioProcessor::~MonotizedAudioProcessor()
{
}

//==============================================================================
const String MonotizedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MonotizedAudioProcessor::acceptsMidi() const
{
    return false;
}

bool MonotizedAudioProcessor::producesMidi() const
{
    return false;
}

bool MonotizedAudioProcessor::isMidiEffect() const
{
    return false;
}

double MonotizedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MonotizedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MonotizedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MonotizedAudioProcessor::setCurrentProgram (int index)
{
}

const String MonotizedAudioProcessor::getProgramName (int index)
{
    return {};
}

void MonotizedAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MonotizedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MonotizedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MonotizedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MonotizedAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	const int bufferSize = buffer.getNumSamples();
	const bool enabledButtonValue = (*enabled < .5) ? false : true;

	float monoValue = 0.0f;

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	switch (enabledButtonValue)
	{
	case true:
		for (int i = 0; i < bufferSize; ++i)
		{
			switch (totalNumInputChannels)
			{
			case 2:
				monoValue = .5 * (buffer.getSample(0, i) + buffer.getSample(1, i));
				buffer.setSample(0, i, monoValue);
				buffer.setSample(1, i, monoValue);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}

}

//==============================================================================
bool MonotizedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MonotizedAudioProcessor::createEditor()
{
    return new MonotizedAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void MonotizedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	XmlElement* xml = new XmlElement("SimpleDoublerPreset");
	xml->setAttribute(Identifier("enabled"), (double)parameters.getParameter("enabled")->convertTo0to1(*enabled));
	copyXmlToBinary(*xml, destData);
	delete xml;
}

void MonotizedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState != nullptr)
	{
		const float enabledButtonValue = (float)xmlState->getDoubleAttribute("enabled", 0.0f);

		parameters.getParameter("enabled")->beginChangeGesture();
		parameters.getParameter("enabled")->setValueNotifyingHost(enabledButtonValue);
		parameters.getParameter("enabled")->endChangeGesture();
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MonotizedAudioProcessor();
}
