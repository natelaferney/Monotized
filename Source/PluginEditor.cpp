/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MonotizedAudioProcessorEditor::MonotizedAudioProcessorEditor (MonotizedAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);

	addAndMakeVisible(enabledButton = new TextButton("MONO ENABLE"));
	enabledButton->setBounds(100, 100, 100, 100);
	enabledButton->setClickingTogglesState(true);
	enabledButton->addListener(this);
	enabledButton->setColour(TextButton::buttonColourId, Colours::darkslategrey);
	enabledButton->setColour(TextButton::buttonOnColourId, Colours::limegreen);

	enabledButtonAttachment.reset(new ButtonAttachment(valueTreeState, "enabled", *enabledButton));
}

MonotizedAudioProcessorEditor::~MonotizedAudioProcessorEditor()
{

}

void MonotizedAudioProcessorEditor::buttonClicked(Button* button)
{

}

//==============================================================================
void MonotizedAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MonotizedAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
