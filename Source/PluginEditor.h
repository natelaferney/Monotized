/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
//==============================================================================
/**
*/
class MonotizedAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener
{
public:
    MonotizedAudioProcessorEditor (MonotizedAudioProcessor&, AudioProcessorValueTreeState&);
    ~MonotizedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void buttonClicked(Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MonotizedAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	ScopedPointer<TextButton> enabledButton;
	ScopedPointer<ButtonAttachment> enabledButtonAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonotizedAudioProcessorEditor)
};
