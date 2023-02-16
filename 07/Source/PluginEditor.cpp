/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SimpleDelayAudioProcessorEditor::~SimpleDelayAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff121212));

    g.setColour (juce::Colours::black);
    juce::Rectangle<float> backgroundRect = getLocalBounds().toFloat();
    int numBackgroundRects = 60;
    juce::Point<float> offset = backgroundRect.getBottomRight() / numBackgroundRects;

    for (int i = 0; i < numBackgroundRects; ++i)
    {
        g.drawRect (backgroundRect);
        backgroundRect += offset;
    }

    juce::Rectangle<int> bounds = getLocalBounds();
    juce::Rectangle<int> textArea = bounds.removeFromLeft ((bounds.getWidth() * 2) / 3)
                                          .removeFromBottom (bounds.getHeight() / 2)
                                          .reduced (10);

    juce::ColourGradient gradient (juce::Colour (0xffe62875),
                                   textArea.toFloat().getTopLeft(),
                                   juce::Colour (0xffe43d1b),
                                   textArea.toFloat().getTopRight(),
                                   false);
    g.setGradientFill (gradient);

    g.setFont (textArea.toFloat().getHeight());
    g.drawFittedText ("ADC", textArea, juce::Justification::centred, 1);
}

void SimpleDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
