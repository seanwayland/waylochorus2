/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


/***
 class MyComp : public juce::Component ; public Timer
 {
 public:
 MyComp()
 {
 startTimer(100)
 };
 
 void timerCallback() override
 {
 repaint()
 };
 
 void paint(Graphics &g) override
 {
 // paint here
 };
 
 };
 ***/

//==============================================================================
WaylodelayUdAudioProcessorEditor::WaylodelayUdAudioProcessorEditor (WaylodelayUdAudioProcessor& p)
:  AudioProcessorEditor (&p), audioProcessor (p)
{
    
    Timer::startTimerHz(5);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1400,800);
    auto& params = processor.getParameters();
    
    addAndMakeVisible (delaySettings);
    delaySettings.setBounds(1000,50, 200,50);
    delaySettings.addItem ("011 legend chorus 1",  1);
    delaySettings.addItem ("012 legend chorus 2",  2);
    delaySettings.addItem ("013 legend chorus 3", 3);
    delaySettings.addItem ("021 legend chorus 4",  4);
    delaySettings.addItem ("022 legend chorus 5",  5);
    delaySettings.addItem ("023 legend chorus 6", 6);
    delaySettings.addItem ("031 legend chorus 7",  7);
    delaySettings.addItem ("032 legend chorus 8",  8);
    delaySettings.addItem ("033 legend chorus 9", 9);
    delaySettings.addItem ("111 legend chorus 10",  10);
    delaySettings.addItem ("112 legend chorus 11",  11);
    delaySettings.addItem ("113 legend chorus 12", 12);
    delaySettings.addItem ("121 legend lead solo 1",  13);
    delaySettings.addItem ("122 legend lead solo 2",  14);
    delaySettings.addItem ("123 legend lead solo 3", 15);
    delaySettings.addItem ("131 legend lead solo 4",  16);
    delaySettings.addItem ("132 legend lead solo 5",  17);
    delaySettings.addItem ("133 legend lead solo 6", 18);
    delaySettings.addItem ("211 legend lead solo 7",  19);
    delaySettings.addItem ("212 legend lead solo 8",  20);
    delaySettings.addItem ("213 legend lead solo 9", 21);
    delaySettings.addItem ("221 legend swell FX 1",  22);
    delaySettings.addItem ("222 legend swell FX 2",  23);
    delaySettings.addItem ("223 legend point source plus echos", 24);
    delaySettings.addItem ("231 legend echo 1 ",  25);
    delaySettings.addItem ("232 legend echo 2",  26);
    delaySettings.addItem ("233 legend echo 3", 27);
    delaySettings.addItem ("Waylochorus 1", 28);
    delaySettings.addItem ("Waylolead 1", 29);
    
    
    delaySettings.onChange = [this] { getPreset(); };
    
    
    
    
    juce::AudioParameterFloat* delayTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);
    mDelayTimeSlider.setBounds(150, 80 , 150, 150);
    timeLabel.setBounds(10,50,200,200);
    timeLabel.setText("Delay Time", juce::dontSendNotification);
    timeLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible (timeLabel);
    addAndMakeVisible(timeLabel);
    
    
    
    
    mDelayTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTimeSlider.setRange(delayTimeParameter->range.start, delayTimeParameter->range.end);
    mDelayTimeSlider.setValue(*delayTimeParameter);
    addAndMakeVisible(mDelayTimeSlider);
    mDelayTimeSlider.onValueChange = [this, delayTimeParameter] { *delayTimeParameter = mDelayTimeSlider.getValue(); };
    mDelayTimeSlider.onDragStart = [delayTimeParameter] {delayTimeParameter->beginChangeGesture(); };
    mDelayTimeSlider.onDragEnd = [delayTimeParameter] {delayTimeParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* dryGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mDryGainSlider.setBounds(600, 0, 150, 150);
    dryGainLabel.setBounds(520,0,150,150);
    dryGainLabel.setText("Dry Gain", juce::dontSendNotification);
    dryGainLabel.setColour (juce::Label::textColourId, juce::Colours::lightseagreen);
    addAndMakeVisible(dryGainLabel);
    
    
    
    juce::AudioParameterFloat* wetGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(41);
    mWetGainSlider.setBounds(850, 0, 150, 150);
    wetGainLabel.setBounds(775,0,150,150);
    wetGainLabel.setText("Wet Gain", juce::dontSendNotification);
    wetGainLabel.setColour (juce::Label::textColourId, juce::Colours::lightseagreen);
    addAndMakeVisible(wetGainLabel);
    mWetGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mWetGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mWetGainSlider.setRange(wetGainParameter->range.start, wetGainParameter->range.end);
    mWetGainSlider.setValue(*wetGainParameter);
    addAndMakeVisible(mWetGainSlider);
    mWetGainSlider.onValueChange = [this, wetGainParameter] { *wetGainParameter = mWetGainSlider.getValue(); };
    mWetGainSlider.onDragStart = [wetGainParameter] {wetGainParameter->beginChangeGesture(); };
    mWetGainSlider.onDragEnd = [wetGainParameter] {wetGainParameter->endChangeGesture(); };
    
    
    juce::AudioParameterFloat* rateParameter = (juce::AudioParameterFloat*)params.getUnchecked(42);
    mRateSlider.setBounds(370, 0, 150, 150);
    rateLabel.setBounds(290,0,150,150);
    rateLabel.setText("More Beer", juce::dontSendNotification);
    rateLabel.setColour (juce::Label::textColourId, juce::Colours::lightseagreen);
    addAndMakeVisible(rateLabel);
    mRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mRateSlider.setRange(rateParameter->range.start, rateParameter->range.end);
    mRateSlider.setValue(*rateParameter);
    addAndMakeVisible(mRateSlider);
    mRateSlider.onValueChange = [this, rateParameter] { *rateParameter = mRateSlider.getValue(); };
    mRateSlider.onDragStart = [rateParameter] {rateParameter->beginChangeGesture(); };
    mRateSlider.onDragEnd = [rateParameter] {rateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* depthParameter = (juce::AudioParameterFloat*)params.getUnchecked(43);
    mDepthSlider.setBounds(150, 0, 150, 150);
    depthLabel2.setBounds(25,0,150,150);
    depthLabel2.setText("Visit Zarabeth", juce::dontSendNotification);
    depthLabel2.setColour (juce::Label::textColourId, juce::Colours::lightseagreen);
    addAndMakeVisible(depthLabel2);
    mDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDepthSlider.setRange(depthParameter->range.start, depthParameter->range.end);
    mDepthSlider.setValue(*depthParameter);
    addAndMakeVisible(mDepthSlider);
    mDepthSlider.onValueChange = [this, depthParameter] { *depthParameter = mDepthSlider.getValue(); };
    mDepthSlider.onDragStart = [depthParameter] {depthParameter->beginChangeGesture(); };
    mDepthSlider.onDragEnd = [depthParameter] {depthParameter->endChangeGesture(); };
    
    TitleLabel.setBounds(600,550,300,300);
    TitleLabel.setText("WAYLOMOD UD 2.0", juce::dontSendNotification);
    TitleLabel.setColour (juce::Label::textColourId, juce::Colours::yellow);
    TitleLabel.setFont (juce::Font (40.0f, juce::Font::bold));
    addAndMakeVisible(TitleLabel);
    mDryGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDryGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDryGainSlider.setRange(dryGainParameter->range.start, dryGainParameter->range.end);
    mDryGainSlider.setValue(*dryGainParameter);
    addAndMakeVisible(mDryGainSlider);
    //mDryGainSlider.onValueChange = [this, dryGainParameter] { *dryGainParameter = mDryGainSlider.getValue(); };
    mDryGainSlider.onValueChange = [this, dryGainParameter] { *dryGainParameter = mDryGainSlider.getValue(); };
    mDryGainSlider.onDragStart = [dryGainParameter] {dryGainParameter->beginChangeGesture(); };
    mDryGainSlider.onDragEnd = [dryGainParameter] {dryGainParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(2);
    mDelayOneGainSlider.setBounds(150, 160 , 150, 150);
    delayGainLabel.setBounds(10,130,200,200);
    delayGainLabel.setText("Delay Gain", juce::dontSendNotification);
    delayGainLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible(delayGainLabel);
    mDelayOneGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayOneGainSlider.setRange(delayOneGainParameter->range.start, delayOneGainParameter->range.end);
    mDelayOneGainSlider.setValue(*delayOneGainParameter);
    addAndMakeVisible(mDelayOneGainSlider);
    mDelayOneGainSlider.onValueChange = [this, delayOneGainParameter] { *delayOneGainParameter = mDelayOneGainSlider.getValue(); };
    mDelayOneGainSlider.onDragStart = [delayOneGainParameter] {delayOneGainParameter->beginChangeGesture(); };
    mDelayOneGainSlider.onDragEnd = [delayOneGainParameter] {delayOneGainParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneModDepthParameter = (juce::AudioParameterFloat*)params.getUnchecked(3);
    mDelayOneModDepthSlider.setBounds(150, 240 , 150, 150);
    
    depthLabel.setBounds(10,210,200,200);
    depthLabel.setText("Mod Depth", juce::dontSendNotification);
    depthLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible(depthLabel);
    
    
    mDelayOneModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayOneModDepthSlider.setRange(delayOneModDepthParameter->range.start, delayOneModDepthParameter->range.end);
    mDelayOneModDepthSlider.setValue(*delayOneModDepthParameter);
    addAndMakeVisible(mDelayOneModDepthSlider);
    mDelayOneModDepthSlider.onValueChange = [this, delayOneModDepthParameter] { *delayOneModDepthParameter = mDelayOneModDepthSlider.getValue(); };
    mDelayOneModDepthSlider.onDragStart = [delayOneModDepthParameter] {delayOneModDepthParameter->beginChangeGesture(); };
    mDelayOneModDepthSlider.onDragEnd = [delayOneModDepthParameter] {delayOneModDepthParameter->endChangeGesture(); };
    
    
    
    
    
    juce::AudioParameterFloat* delayOneFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(5);
    mDelayOneFeedbackSlider.setBounds(150, 400 , 150, 150);
    
    FeedbackLabel.setBounds(10,370,200,200);
    FeedbackLabel.setText("Feedback", juce::dontSendNotification);
    FeedbackLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible(FeedbackLabel);
    
    PanLabel.setBounds(30,450,200,200);
    PanLabel.setText("Pan", juce::dontSendNotification);
    PanLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible(PanLabel);
    
    
    mDelayOneFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayOneFeedbackSlider.setRange(delayOneFeedbackParameter->range.start, delayOneFeedbackParameter->range.end);
    mDelayOneFeedbackSlider.setValue(*delayOneFeedbackParameter);
    addAndMakeVisible(mDelayOneFeedbackSlider);
    mDelayOneFeedbackSlider.onValueChange = [this, delayOneFeedbackParameter] { *delayOneFeedbackParameter = mDelayOneFeedbackSlider.getValue(); };
    mDelayOneFeedbackSlider.onDragStart = [delayOneFeedbackParameter] {delayOneFeedbackParameter->beginChangeGesture(); };
    mDelayOneFeedbackSlider.onDragEnd = [delayOneFeedbackParameter] {delayOneFeedbackParameter->endChangeGesture(); };
    
    
    
    
    juce::AudioParameterFloat* delayTwoTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(6);
    mDelayTwoTimeSlider.setBounds(300, 80 , 150, 150);
    mDelayTwoTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoTimeSlider.setRange(delayTwoTimeParameter->range.start, delayTwoTimeParameter->range.end);
    mDelayTwoTimeSlider.setValue(*delayTwoTimeParameter);
    addAndMakeVisible(mDelayTwoTimeSlider);
    mDelayTwoTimeSlider.onValueChange = [this, delayTwoTimeParameter] { *delayTwoTimeParameter = mDelayTwoTimeSlider.getValue(); };
    mDelayTwoTimeSlider.onDragStart = [delayTwoTimeParameter] {delayTwoTimeParameter->beginChangeGesture(); };
    mDelayTwoTimeSlider.onDragEnd = [delayTwoTimeParameter] {delayTwoTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayTwoGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(7);
    mDelayTwoGainSlider.setBounds(300, 160 , 150, 150);
    mDelayTwoGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoGainSlider.setRange(delayTwoGainParameter->range.start, delayTwoGainParameter->range.end);
    mDelayTwoGainSlider.setValue(*delayTwoGainParameter);
    addAndMakeVisible(mDelayTwoGainSlider);
    mDelayTwoGainSlider.onValueChange = [this, delayTwoGainParameter] { *delayTwoGainParameter = mDelayTwoGainSlider.getValue(); };
    mDelayTwoGainSlider.onDragStart = [delayTwoGainParameter] {delayTwoGainParameter->beginChangeGesture(); };
    mDelayTwoGainSlider.onDragEnd = [delayTwoGainParameter] {delayTwoGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayTwoModDepthParameter = (juce::AudioParameterFloat*)params.getUnchecked(8);
    mDelayTwoModDepthSlider.setBounds(300, 240 , 150, 150);
    mDelayTwoModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoModDepthSlider.setRange(delayTwoModDepthParameter->range.start, delayTwoModDepthParameter->range.end);
    mDelayTwoModDepthSlider.setValue(*delayTwoModDepthParameter);
    addAndMakeVisible(mDelayTwoModDepthSlider);
    mDelayTwoModDepthSlider.onValueChange = [this, delayTwoModDepthParameter] { *delayTwoModDepthParameter = mDelayTwoModDepthSlider.getValue(); };
    mDelayTwoModDepthSlider.onDragStart = [delayTwoModDepthParameter] {delayTwoModDepthParameter->beginChangeGesture(); };
    mDelayTwoModDepthSlider.onDragEnd = [delayTwoModDepthParameter] {delayTwoModDepthParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayOneModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(4);
    mDelayOneModRateSlider.setBounds(150, 320 , 150, 150);
    RateLabel.setBounds(10,290,200,200);
    RateLabel.setText("Mod Rate", juce::dontSendNotification);
    RateLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    addAndMakeVisible(RateLabel);
    
    mDelayOneModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOneModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayOneModRateSlider.setRange(delayOneModRateParameter->range.start, delayOneModRateParameter->range.end);
    mDelayOneModRateSlider.setValue(*delayOneModRateParameter);
    addAndMakeVisible(mDelayOneModRateSlider);
    mDelayOneModRateSlider.onValueChange = [this, delayOneModRateParameter] { *delayOneModRateParameter = mDelayOneModRateSlider.getValue(); };
    mDelayOneModRateSlider.onDragStart = [delayOneModRateParameter] {delayOneModRateParameter->beginChangeGesture(); };
    mDelayOneModRateSlider.onDragEnd = [delayOneModRateParameter] {delayOneModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayTwoModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(9);
    mDelayTwoModRateSlider.setBounds(300, 320 , 150, 150);
    mDelayTwoModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoModRateSlider.setRange(delayTwoModRateParameter->range.start, delayTwoModRateParameter->range.end);
    mDelayTwoModRateSlider.setValue(*delayTwoModRateParameter);
    addAndMakeVisible(mDelayTwoModRateSlider);
    mDelayTwoModRateSlider.onValueChange = [this, delayTwoModRateParameter] { *delayTwoModRateParameter = mDelayTwoModRateSlider.getValue(); };
    mDelayTwoModRateSlider.onDragStart = [delayTwoModRateParameter] {delayTwoModRateParameter->beginChangeGesture(); };
    mDelayTwoModRateSlider.onDragEnd = [delayTwoModRateParameter] {delayTwoModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayTwoFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(10);
    mDelayTwoFeedbackSlider.setBounds(300, 400 , 150, 150);
    mDelayTwoFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoFeedbackSlider.setRange(delayTwoFeedbackParameter->range.start, delayTwoFeedbackParameter->range.end);
    mDelayTwoFeedbackSlider.setValue(*delayTwoFeedbackParameter);
    addAndMakeVisible(mDelayTwoFeedbackSlider);
    mDelayTwoFeedbackSlider.onValueChange = [this, delayTwoFeedbackParameter] { *delayTwoFeedbackParameter = mDelayTwoFeedbackSlider.getValue(); };
    mDelayTwoFeedbackSlider.onDragStart = [delayTwoFeedbackParameter] {delayTwoFeedbackParameter->beginChangeGesture(); };
    mDelayTwoFeedbackSlider.onDragEnd = [delayTwoFeedbackParameter] {delayTwoFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(11);
    mDelayThreeTimeSlider.setBounds(450, 80 , 150, 150);
    mDelayThreeTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreeTimeSlider.setRange(delayThreeTimeParameter->range.start, delayThreeTimeParameter->range.end);
    mDelayThreeTimeSlider.setValue(*delayThreeTimeParameter);
    addAndMakeVisible(mDelayThreeTimeSlider);
    mDelayThreeTimeSlider.onValueChange = [this, delayThreeTimeParameter] { *delayThreeTimeParameter = mDelayThreeTimeSlider.getValue(); };
    mDelayThreeTimeSlider.onDragStart = [delayThreeTimeParameter] {delayThreeTimeParameter->beginChangeGesture(); };
    mDelayThreeTimeSlider.onDragEnd = [delayThreeTimeParameter] {delayThreeTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayThreeGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(12);
    mDelayThreeGainSlider.setBounds(450, 160 , 150, 150);
    mDelayThreeGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreeGainSlider.setRange(delayThreeGainParameter->range.start, delayThreeGainParameter->range.end);
    mDelayThreeGainSlider.setValue(*delayThreeGainParameter);
    addAndMakeVisible(mDelayThreeGainSlider);
    mDelayThreeGainSlider.onValueChange = [this, delayThreeGainParameter] { *delayThreeGainParameter = mDelayThreeGainSlider.getValue(); };
    mDelayThreeGainSlider.onDragStart = [delayThreeGainParameter] {delayThreeGainParameter->beginChangeGesture(); };
    mDelayThreeGainSlider.onDragEnd = [delayThreeGainParameter] {delayThreeGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayThreeModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(13);
    mDelayThreeModDepthSlider.setBounds(450, 240 , 150, 150);
    mDelayThreeModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreeModDepthSlider.setRange(delayThreeModDpethParameter->range.start, delayThreeModDpethParameter->range.end);
    mDelayThreeModDepthSlider.setValue(*delayThreeModDpethParameter);
    addAndMakeVisible(mDelayThreeModDepthSlider);
    mDelayThreeModDepthSlider.onValueChange = [this, delayThreeModDpethParameter] { *delayThreeModDpethParameter = mDelayThreeModDepthSlider.getValue(); };
    mDelayThreeModDepthSlider.onDragStart = [delayThreeModDpethParameter] {delayThreeModDpethParameter->beginChangeGesture(); };
    mDelayThreeModDepthSlider.onDragEnd = [delayThreeModDpethParameter] {delayThreeModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(14);
    mDelayThreeModRateSlider.setBounds(450, 320 , 150, 150);
    mDelayThreeModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreeModRateSlider.setRange(delayThreeModRateParameter->range.start, delayThreeModRateParameter->range.end);
    mDelayThreeModRateSlider.setValue(*delayThreeModRateParameter);
    addAndMakeVisible(mDelayThreeModRateSlider);
    mDelayThreeModRateSlider.onValueChange = [this, delayThreeModRateParameter] { *delayThreeModRateParameter = mDelayThreeModRateSlider.getValue(); };
    mDelayThreeModRateSlider.onDragStart = [delayThreeModRateParameter] {delayThreeModRateParameter->beginChangeGesture(); };
    mDelayThreeModRateSlider.onDragEnd = [delayThreeModRateParameter] {delayThreeModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreeFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(15);
    mDelayThreeFeedbackSlider.setBounds(450, 400 , 150, 150);
    mDelayThreeFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreeFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreeFeedbackSlider.setRange(delayThreeFeedbackParameter->range.start, delayThreeFeedbackParameter->range.end);
    mDelayThreeFeedbackSlider.setValue(*delayThreeFeedbackParameter);
    addAndMakeVisible(mDelayThreeFeedbackSlider);
    mDelayThreeFeedbackSlider.onValueChange = [this, delayThreeFeedbackParameter] { *delayThreeFeedbackParameter = mDelayThreeFeedbackSlider.getValue(); };
    mDelayThreeFeedbackSlider.onDragStart = [delayThreeFeedbackParameter] {delayThreeFeedbackParameter->beginChangeGesture(); };
    mDelayThreeFeedbackSlider.onDragEnd = [delayThreeFeedbackParameter] {delayThreeFeedbackParameter->endChangeGesture(); };
    
    
    
    
    
    juce::AudioParameterFloat* delayFourTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(16);
    mDelayFourTimeSlider.setBounds(600, 80 , 150, 150);
    mDelayFourTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourTimeSlider.setRange(delayFourTimeParameter->range.start, delayFourTimeParameter->range.end);
    mDelayFourTimeSlider.setValue(*delayFourTimeParameter);
    addAndMakeVisible(mDelayFourTimeSlider);
    mDelayFourTimeSlider.onValueChange = [this, delayFourTimeParameter] { *delayFourTimeParameter = mDelayFourTimeSlider.getValue(); };
    mDelayFourTimeSlider.onDragStart = [delayFourTimeParameter] {delayFourTimeParameter->beginChangeGesture(); };
    mDelayFourTimeSlider.onDragEnd = [delayFourTimeParameter] {delayFourTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFourGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(17);
    mDelayFourGainSlider.setBounds(600, 160 , 150, 150);
    mDelayFourGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourGainSlider.setRange(delayFourGainParameter->range.start, delayFourGainParameter->range.end);
    mDelayFourGainSlider.setValue(*delayFourGainParameter);
    addAndMakeVisible(mDelayFourGainSlider);
    mDelayFourGainSlider.onValueChange = [this, delayFourGainParameter] { *delayFourGainParameter = mDelayFourGainSlider.getValue(); };
    mDelayFourGainSlider.onDragStart = [delayFourGainParameter] {delayFourGainParameter->beginChangeGesture(); };
    mDelayFourGainSlider.onDragEnd = [delayFourGainParameter] {delayFourGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFourModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(18);
    mDelayFourModDepthSlider.setBounds(600, 240 , 150, 150);
    mDelayFourModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourModDepthSlider.setRange(delayFourModDpethParameter->range.start, delayFourModDpethParameter->range.end);
    mDelayFourModDepthSlider.setValue(*delayFourModDpethParameter);
    addAndMakeVisible(mDelayFourModDepthSlider);
    mDelayFourModDepthSlider.onValueChange = [this, delayFourModDpethParameter] { *delayFourModDpethParameter = mDelayFourModDepthSlider.getValue(); };
    mDelayFourModDepthSlider.onDragStart = [delayFourModDpethParameter] {delayFourModDpethParameter->beginChangeGesture(); };
    mDelayFourModDepthSlider.onDragEnd = [delayFourModDpethParameter] {delayFourModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFourModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(19);
    mDelayFourModRateSlider.setBounds(600, 320 , 150, 150);
    mDelayFourModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourModRateSlider.setRange(delayFourModRateParameter->range.start, delayFourModRateParameter->range.end);
    mDelayFourModRateSlider.setValue(*delayFourModRateParameter);
    addAndMakeVisible(mDelayFourModRateSlider);
    mDelayFourModRateSlider.onValueChange = [this, delayFourModRateParameter] { *delayFourModRateParameter = mDelayFourModRateSlider.getValue(); };
    mDelayFourModRateSlider.onDragStart = [delayFourModRateParameter] {delayFourModRateParameter->beginChangeGesture(); };
    mDelayFourModRateSlider.onDragEnd = [delayFourModRateParameter] {delayFourModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFourFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(20);
    mDelayFourFeedbackSlider.setBounds(600, 400 , 150, 150);
    mDelayFourFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourFeedbackSlider.setRange(delayFourFeedbackParameter->range.start, delayFourFeedbackParameter->range.end);
    mDelayFourFeedbackSlider.setValue(*delayFourFeedbackParameter);
    addAndMakeVisible(mDelayFourFeedbackSlider);
    mDelayFourFeedbackSlider.onValueChange = [this, delayFourFeedbackParameter] { *delayFourFeedbackParameter = mDelayFourFeedbackSlider.getValue(); };
    mDelayFourFeedbackSlider.onDragStart = [delayFourFeedbackParameter] {delayFourFeedbackParameter->beginChangeGesture(); };
    mDelayFourFeedbackSlider.onDragEnd = [delayFourFeedbackParameter] {delayFourFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(21);
    mDelayFiveTimeSlider.setBounds(750, 80 , 150, 150);
    mDelayFiveTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFiveTimeSlider.setRange(delayFiveTimeParameter->range.start, delayFiveTimeParameter->range.end);
    mDelayFiveTimeSlider.setValue(*delayFiveTimeParameter);
    addAndMakeVisible(mDelayFiveTimeSlider);
    mDelayFiveTimeSlider.onValueChange = [this, delayFiveTimeParameter] { *delayFiveTimeParameter = mDelayFiveTimeSlider.getValue(); };
    mDelayFiveTimeSlider.onDragStart = [delayFiveTimeParameter] {delayFiveTimeParameter->beginChangeGesture(); };
    mDelayFiveTimeSlider.onDragEnd = [delayFiveTimeParameter] {delayFiveTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFiveGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(22);
    mDelayFiveGainSlider.setBounds(750, 160 , 150, 150);
    mDelayFiveGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFiveGainSlider.setRange(delayFiveGainParameter->range.start, delayFiveGainParameter->range.end);
    mDelayFiveGainSlider.setValue(*delayFiveGainParameter);
    addAndMakeVisible(mDelayFiveGainSlider);
    mDelayFiveGainSlider.onValueChange = [this, delayFiveGainParameter] { *delayFiveGainParameter = mDelayFiveGainSlider.getValue(); };
    mDelayFiveGainSlider.onDragStart = [delayFiveGainParameter] {delayFiveGainParameter->beginChangeGesture(); };
    mDelayFiveGainSlider.onDragEnd = [delayFiveGainParameter] {delayFiveGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayFiveModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(23);
    mDelayFiveModDepthSlider.setBounds(750, 240 , 150, 150);
    mDelayFiveModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFiveModDepthSlider.setRange(delayFiveModDpethParameter->range.start, delayFiveModDpethParameter->range.end);
    mDelayFiveModDepthSlider.setValue(*delayFiveModDpethParameter);
    addAndMakeVisible(mDelayFiveModDepthSlider);
    mDelayFiveModDepthSlider.onValueChange = [this, delayFiveModDpethParameter] { *delayFiveModDpethParameter = mDelayFiveModDepthSlider.getValue(); };
    mDelayFiveModDepthSlider.onDragStart = [delayFiveModDpethParameter] {delayFiveModDpethParameter->beginChangeGesture(); };
    mDelayFiveModDepthSlider.onDragEnd = [delayFiveModDpethParameter] {delayFiveModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(24);
    mDelayFiveModRateSlider.setBounds(750, 320 , 150, 150);
    mDelayFiveModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFiveModRateSlider.setRange(delayFiveModRateParameter->range.start, delayFiveModRateParameter->range.end);
    mDelayFiveModRateSlider.setValue(*delayFiveModRateParameter);
    addAndMakeVisible(mDelayFiveModRateSlider);
    mDelayFiveModRateSlider.onValueChange = [this, delayFiveModRateParameter] { *delayFiveModRateParameter = mDelayFiveModRateSlider.getValue(); };
    mDelayFiveModRateSlider.onDragStart = [delayFiveModRateParameter] {delayFiveModRateParameter->beginChangeGesture(); };
    mDelayFiveModRateSlider.onDragEnd = [delayFiveModRateParameter] {delayFiveModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFiveFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(25);
    mDelayFiveFeedbackSlider.setBounds(750, 400 , 150, 150);
    mDelayFiveFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFiveFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFiveFeedbackSlider.setRange(delayFiveFeedbackParameter->range.start, delayFiveFeedbackParameter->range.end);
    mDelayFiveFeedbackSlider.setValue(*delayFiveFeedbackParameter);
    addAndMakeVisible(mDelayFiveFeedbackSlider);
    mDelayFiveFeedbackSlider.onValueChange = [this, delayFiveFeedbackParameter] { *delayFiveFeedbackParameter = mDelayFiveFeedbackSlider.getValue(); };
    mDelayFiveFeedbackSlider.onDragStart = [delayFiveFeedbackParameter] {delayFiveFeedbackParameter->beginChangeGesture(); };
    mDelayFiveFeedbackSlider.onDragEnd = [delayFiveFeedbackParameter] {delayFiveFeedbackParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(26);
    mDelaySixTimeSlider.setBounds(900, 80 , 150, 150);
    mDelaySixTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixTimeSlider.setRange(delaySixTimeParameter->range.start, delaySixTimeParameter->range.end);
    mDelaySixTimeSlider.setValue(*delaySixTimeParameter);
    addAndMakeVisible(mDelaySixTimeSlider);
    mDelaySixTimeSlider.onValueChange = [this, delaySixTimeParameter] { *delaySixTimeParameter = mDelaySixTimeSlider.getValue(); };
    mDelaySixTimeSlider.onDragStart = [delaySixTimeParameter] {delaySixTimeParameter->beginChangeGesture(); };
    mDelaySixTimeSlider.onDragEnd = [delaySixTimeParameter] {delaySixTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySixGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(27);
    mDelaySixGainSlider.setBounds(900, 160 , 150, 150);
    mDelaySixGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixGainSlider.setRange(delaySixGainParameter->range.start, delaySixGainParameter->range.end);
    mDelaySixGainSlider.setValue(*delaySixGainParameter);
    addAndMakeVisible(mDelaySixGainSlider);
    mDelaySixGainSlider.onValueChange = [this, delaySixGainParameter] { *delaySixGainParameter = mDelaySixGainSlider.getValue(); };
    mDelaySixGainSlider.onDragStart = [delaySixGainParameter] {delaySixGainParameter->beginChangeGesture(); };
    mDelaySixGainSlider.onDragEnd = [delaySixGainParameter] {delaySixGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySixModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(28);
    mDelaySixModDepthSlider.setBounds(900, 240 , 150, 150);
    mDelaySixModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixModDepthSlider.setRange(delaySixModDpethParameter->range.start, delaySixModDpethParameter->range.end);
    mDelaySixModDepthSlider.setValue(*delaySixModDpethParameter);
    addAndMakeVisible(mDelaySixModDepthSlider);
    mDelaySixModDepthSlider.onValueChange = [this, delaySixModDpethParameter] { *delaySixModDpethParameter = mDelaySixModDepthSlider.getValue(); };
    mDelaySixModDepthSlider.onDragStart = [delaySixModDpethParameter] {delaySixModDpethParameter->beginChangeGesture(); };
    mDelaySixModDepthSlider.onDragEnd = [delaySixModDpethParameter] {delaySixModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(29);
    mDelaySixModRateSlider.setBounds(900, 320 , 150, 150);
    mDelaySixModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixModRateSlider.setRange(delaySixModRateParameter->range.start, delaySixModRateParameter->range.end);
    mDelaySixModRateSlider.setValue(*delaySixModRateParameter);
    addAndMakeVisible(mDelaySixModRateSlider);
    mDelaySixModRateSlider.onValueChange = [this, delaySixModRateParameter] { *delaySixModRateParameter = mDelaySixModRateSlider.getValue(); };
    mDelaySixModRateSlider.onDragStart = [delaySixModRateParameter] {delaySixModRateParameter->beginChangeGesture(); };
    mDelaySixModRateSlider.onDragEnd = [delaySixModRateParameter] {delaySixModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(30);
    mDelaySixFeedbackSlider.setBounds(900, 400 , 150, 150);
    mDelaySixFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixFeedbackSlider.setRange(delaySixFeedbackParameter->range.start, delaySixFeedbackParameter->range.end);
    mDelaySixFeedbackSlider.setValue(*delaySixFeedbackParameter);
    addAndMakeVisible(mDelaySixFeedbackSlider);
    mDelaySixFeedbackSlider.onValueChange = [this, delaySixFeedbackParameter] { *delaySixFeedbackParameter = mDelaySixFeedbackSlider.getValue(); };
    mDelaySixFeedbackSlider.onDragStart = [delaySixFeedbackParameter] {delaySixFeedbackParameter->beginChangeGesture(); };
    mDelaySixFeedbackSlider.onDragEnd = [delaySixFeedbackParameter] {delaySixFeedbackParameter->endChangeGesture(); };
    
    
    juce::AudioParameterFloat* delaySevenTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(31);
    mDelaySevenTimeSlider.setBounds(1050, 80 , 150, 150);
    mDelaySevenTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenTimeSlider.setRange(delaySevenTimeParameter->range.start, delaySevenTimeParameter->range.end);
    mDelaySevenTimeSlider.setValue(*delaySevenTimeParameter);
    addAndMakeVisible(mDelaySevenTimeSlider);
    mDelaySevenTimeSlider.onValueChange = [this, delaySevenTimeParameter] { *delaySevenTimeParameter = mDelaySevenTimeSlider.getValue(); };
    mDelaySevenTimeSlider.onDragStart = [delaySevenTimeParameter] {delaySevenTimeParameter->beginChangeGesture(); };
    mDelaySevenTimeSlider.onDragEnd = [delaySevenTimeParameter] {delaySevenTimeParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(32);
    mDelaySevenGainSlider.setBounds(1050, 160 , 150, 150);
    mDelaySevenGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenGainSlider.setRange(delaySevenGainParameter->range.start, delaySevenGainParameter->range.end);
    mDelaySevenGainSlider.setValue(*delaySevenGainParameter);
    addAndMakeVisible(mDelaySevenGainSlider);
    mDelaySevenGainSlider.onValueChange = [this, delaySevenGainParameter] { *delaySevenGainParameter = mDelaySevenGainSlider.getValue(); };
    mDelaySevenGainSlider.onDragStart = [delaySevenGainParameter] {delaySevenGainParameter->beginChangeGesture(); };
    mDelaySevenGainSlider.onDragEnd = [delaySevenGainParameter] {delaySevenGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delaySevenModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(33);
    mDelaySevenModDepthSlider.setBounds(1050, 240 , 150, 150);
    mDelaySevenModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenModDepthSlider.setRange(delaySevenModDpethParameter->range.start, delaySevenModDpethParameter->range.end);
    mDelaySevenModDepthSlider.setValue(*delaySevenModDpethParameter);
    addAndMakeVisible(mDelaySevenModDepthSlider);
    mDelaySevenModDepthSlider.onValueChange = [this, delaySevenModDpethParameter] { *delaySevenModDpethParameter = mDelaySevenModDepthSlider.getValue(); };
    mDelaySevenModDepthSlider.onDragStart = [delaySevenModDpethParameter] {delaySevenModDpethParameter->beginChangeGesture(); };
    mDelaySevenModDepthSlider.onDragEnd = [delaySevenModDpethParameter] {delaySevenModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(34);
    mDelaySevenModRateSlider.setBounds(1050, 320 , 150, 150);
    mDelaySevenModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenModRateSlider.setRange(delaySevenModRateParameter->range.start, delaySevenModRateParameter->range.end);
    mDelaySevenModRateSlider.setValue(*delaySevenModRateParameter);
    addAndMakeVisible(mDelaySevenModRateSlider);
    mDelaySevenModRateSlider.onValueChange = [this, delaySevenModRateParameter] { *delaySevenModRateParameter = mDelaySevenModRateSlider.getValue(); };
    mDelaySevenModRateSlider.onDragStart = [delaySevenModRateParameter] {delaySevenModRateParameter->beginChangeGesture(); };
    mDelaySevenModRateSlider.onDragEnd = [delaySevenModRateParameter] {delaySevenModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(35);
    mDelaySevenFeedbackSlider.setBounds(1050, 400 , 150, 150);
    mDelaySevenFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenFeedbackSlider.setRange(delaySevenFeedbackParameter->range.start, delaySevenFeedbackParameter->range.end);
    //mDelaySevenFeedbackSlider.setRange(0.0, 0.98, 0.01);
    mDelaySevenFeedbackSlider.setValue(*delaySevenFeedbackParameter);
    addAndMakeVisible(mDelaySevenFeedbackSlider);
    mDelaySevenFeedbackSlider.onValueChange = [this, delaySevenFeedbackParameter] { *delaySevenFeedbackParameter = mDelaySevenFeedbackSlider.getValue(); };
    mDelaySevenFeedbackSlider.onDragStart = [delaySevenFeedbackParameter] {delaySevenFeedbackParameter->beginChangeGesture(); };
    mDelaySevenFeedbackSlider.onDragEnd = [delaySevenFeedbackParameter] {delaySevenFeedbackParameter->endChangeGesture(); };
    
    
    juce::AudioParameterFloat* delayEightTimeParameter = (juce::AudioParameterFloat*)params.getUnchecked(36);
    mDelayEightTimeSlider.setBounds(1200, 80 , 150, 150);
    mDelayEightTimeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightTimeSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightTimeSlider.setRange(delayEightTimeParameter->range.start, delayEightTimeParameter->range.end);
    mDelayEightTimeSlider.setValue(*delayEightTimeParameter);
    addAndMakeVisible(mDelayEightTimeSlider);
    mDelayEightTimeSlider.onValueChange = [this, delayEightTimeParameter] { *delayEightTimeParameter = mDelayEightTimeSlider.getValue(); };
    mDelayEightTimeSlider.onDragStart = [delayEightTimeParameter] {delayEightTimeParameter->beginChangeGesture(); };
    mDelayEightTimeSlider.onDragEnd = [delayEightTimeParameter] {delayEightTimeParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayEightGainParameter = (juce::AudioParameterFloat*)params.getUnchecked(37);
    mDelayEightGainSlider.setBounds(1200, 160 , 150, 150);
    mDelayEightGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightGainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightGainSlider.setRange(delayEightGainParameter->range.start, delayEightGainParameter->range.end);
    mDelayEightGainSlider.setValue(*delayEightGainParameter);
    addAndMakeVisible(mDelayEightGainSlider);
    mDelayEightGainSlider.onValueChange = [this, delayEightGainParameter] { *delayEightGainParameter = mDelayEightGainSlider.getValue(); };
    mDelayEightGainSlider.onDragStart = [delayEightGainParameter] {delayEightGainParameter->beginChangeGesture(); };
    mDelayEightGainSlider.onDragEnd = [delayEightGainParameter] {delayEightGainParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayEightModDpethParameter = (juce::AudioParameterFloat*)params.getUnchecked(38);
    mDelayEightModDepthSlider.setBounds(1200, 240 , 150, 150);
    mDelayEightModDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightModDepthSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightModDepthSlider.setRange(delayEightModDpethParameter->range.start, delayEightModDpethParameter->range.end);
    mDelayEightModDepthSlider.setValue(*delayEightModDpethParameter);
    addAndMakeVisible(mDelayEightModDepthSlider);
    mDelayEightModDepthSlider.onValueChange = [this, delayEightModDpethParameter] { *delayEightModDpethParameter = mDelayEightModDepthSlider.getValue(); };
    mDelayEightModDepthSlider.onDragStart = [delayEightModDpethParameter] {delayEightModDpethParameter->beginChangeGesture(); };
    mDelayEightModDepthSlider.onDragEnd = [delayEightModDpethParameter] {delayEightModDpethParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayEightModRateParameter = (juce::AudioParameterFloat*)params.getUnchecked(39);
    mDelayEightModRateSlider.setBounds(1200, 320 , 150, 150);
    mDelayEightModRateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightModRateSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightModRateSlider.setRange(delayEightModRateParameter->range.start, delayEightModRateParameter->range.end);
    mDelayEightModRateSlider.setValue(*delayEightModRateParameter);
    addAndMakeVisible(mDelayEightModRateSlider);
    mDelayEightModRateSlider.onValueChange = [this, delayEightModRateParameter] { *delayEightModRateParameter = mDelayEightModRateSlider.getValue(); };
    mDelayEightModRateSlider.onDragStart = [delayEightModRateParameter] {delayEightModRateParameter->beginChangeGesture(); };
    mDelayEightModRateSlider.onDragEnd = [delayEightModRateParameter] {delayEightModRateParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayEightFeedbackParameter = (juce::AudioParameterFloat*)params.getUnchecked(40);
    mDelayEightFeedbackSlider.setBounds(1200, 400 , 150, 150);
    mDelayEightFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightFeedbackSlider.setRange(delayEightFeedbackParameter->range.start, delayEightFeedbackParameter->range.end);
    mDelayEightFeedbackSlider.setValue(*delayEightFeedbackParameter);
    //mDelayEightFeedbackSlider.setValue(0.0f);
    addAndMakeVisible(mDelayEightFeedbackSlider);
    mDelayEightFeedbackSlider.onValueChange = [this, delayEightFeedbackParameter] { *delayEightFeedbackParameter = mDelayEightFeedbackSlider.getValue(); };
    mDelayEightFeedbackSlider.onDragStart = [delayEightFeedbackParameter] {delayEightFeedbackParameter->beginChangeGesture(); };
    mDelayEightFeedbackSlider.onDragEnd = [delayEightFeedbackParameter] {delayEightFeedbackParameter->endChangeGesture(); };
    
    
    
    juce::AudioParameterFloat* delayOnePanParameter = (juce::AudioParameterFloat*)params.getUnchecked(44);
    mDelayOnePanSlider.setBounds(150, 480 , 150, 150);
    mDelayOnePanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayOnePanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayOnePanSlider.setRange(delayOnePanParameter->range.start, delayOnePanParameter->range.end);
    mDelayOnePanSlider.setValue(*delayOnePanParameter);
    addAndMakeVisible(mDelayOnePanSlider);
    mDelayOnePanSlider.onValueChange = [this, delayOnePanParameter] { *delayOnePanParameter = mDelayOnePanSlider.getValue(); };
    mDelayOnePanSlider.onDragStart = [delayOnePanParameter] {delayOnePanParameter->beginChangeGesture(); };
    mDelayOnePanSlider.onDragEnd = [delayOnePanParameter] {delayOnePanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayTwoPanParameter = (juce::AudioParameterFloat*)params.getUnchecked(45);
    mDelayTwoPanSlider.setBounds(300, 480 , 150, 150);
    mDelayTwoPanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTwoPanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayTwoPanSlider.setRange(delayTwoPanParameter->range.start, delayTwoPanParameter->range.end);
    mDelayEightFeedbackSlider.setValue(*delayTwoPanParameter);
    addAndMakeVisible(mDelayTwoPanSlider);
    mDelayTwoPanSlider.onValueChange = [this, delayTwoPanParameter] { *delayTwoPanParameter = mDelayTwoPanSlider.getValue(); };
    mDelayTwoPanSlider.onDragStart = [delayTwoPanParameter] {delayTwoPanParameter->beginChangeGesture(); };
    mDelayTwoPanSlider.onDragEnd = [delayTwoPanParameter] {delayTwoPanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayThreePanParameter = (juce::AudioParameterFloat*)params.getUnchecked(46);
    mDelayThreePanSlider.setBounds(450, 480 , 150, 150);
    mDelayThreePanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayThreePanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayThreePanSlider.setRange(delayThreePanParameter->range.start, delayThreePanParameter->range.end);
    mDelayThreePanSlider.setValue(*delayThreePanParameter);
    addAndMakeVisible(mDelayThreePanSlider);
    mDelayThreePanSlider.onValueChange = [this, delayThreePanParameter] { *delayThreePanParameter = mDelayThreePanSlider.getValue(); };
    mDelayThreePanSlider.onDragStart = [delayThreePanParameter] {delayThreePanParameter->beginChangeGesture(); };
    mDelayThreePanSlider.onDragEnd = [delayThreePanParameter] {delayThreePanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFourPanParameter = (juce::AudioParameterFloat*)params.getUnchecked(47);
    mDelayFourPanSlider.setBounds(600, 480 , 150, 150);
    mDelayFourPanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFourPanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFourPanSlider.setRange(delayFourPanParameter->range.start, delayFourPanParameter->range.end);
    mDelayFourPanSlider.setValue(*delayFourPanParameter);
    addAndMakeVisible(mDelayFourPanSlider);
    mDelayFourPanSlider.onValueChange = [this, delayFourPanParameter] { *delayFourPanParameter = mDelayFourPanSlider.getValue(); };
    mDelayFourPanSlider.onDragStart = [delayFourPanParameter] {delayFourPanParameter->beginChangeGesture(); };
    mDelayFourPanSlider.onDragEnd = [delayFourPanParameter] {delayFourPanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayFivePanParameter = (juce::AudioParameterFloat*)params.getUnchecked(48);
    mDelayFivePanSlider.setBounds(750, 480 , 150, 150);
    mDelayFivePanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFivePanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayFivePanSlider.setRange(delayFivePanParameter->range.start, delayFivePanParameter->range.end);
    mDelayFivePanSlider.setValue(*delayFivePanParameter);
    addAndMakeVisible(mDelayFivePanSlider);
    mDelayFivePanSlider.onValueChange = [this, delayFivePanParameter] { *delayFivePanParameter = mDelayFivePanSlider.getValue(); };
    mDelayFivePanSlider.onDragStart = [delayFivePanParameter] {delayFivePanParameter->beginChangeGesture(); };
    mDelayFivePanSlider.onDragEnd = [delayFivePanParameter] {delayFivePanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySixPanParameter = (juce::AudioParameterFloat*)params.getUnchecked(49);
    mDelaySixPanSlider.setBounds(900, 480 , 150, 150);
    mDelaySixPanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySixPanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySixPanSlider.setRange(delaySixPanParameter->range.start, delaySixPanParameter->range.end);
    mDelaySixPanSlider.setValue(*delaySixPanParameter);
    addAndMakeVisible(mDelaySixPanSlider);
    mDelaySixPanSlider.onValueChange = [this, delaySixPanParameter] { *delaySixPanParameter = mDelaySixPanSlider.getValue(); };
    mDelaySixPanSlider.onDragStart = [delaySixPanParameter] {delaySixPanParameter->beginChangeGesture(); };
    mDelaySixPanSlider.onDragEnd = [delaySixPanParameter] {delaySixPanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delaySevenPanParameter = (juce::AudioParameterFloat*)params.getUnchecked(50);
    mDelaySevenPanSlider.setBounds(1050, 480 , 150, 150);
    mDelaySevenPanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelaySevenPanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelaySevenFeedbackSlider.setRange(delaySevenPanParameter->range.start, delaySevenPanParameter->range.end);
    mDelaySevenPanSlider.setRange(delaySevenPanParameter->range.start, delaySevenPanParameter->range.end);
    mDelaySevenPanSlider.setValue(*delaySevenPanParameter);
    addAndMakeVisible(mDelaySevenPanSlider);
    mDelaySevenPanSlider.onValueChange = [this, delaySevenPanParameter] { *delaySevenPanParameter = mDelaySevenPanSlider.getValue(); };
    mDelaySevenPanSlider.onDragStart = [delaySevenPanParameter] {delaySevenPanParameter->beginChangeGesture(); };
    mDelaySevenPanSlider.onDragEnd = [delaySevenPanParameter] {delaySevenPanParameter->endChangeGesture(); };
    
    juce::AudioParameterFloat* delayEightPanParameter = (juce::AudioParameterFloat*)params.getUnchecked(51);
    mDelayEightPanSlider.setBounds(1200, 480 , 150, 150);
    mDelayEightPanSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayEightPanSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 75, 50);
    mDelayEightPanSlider.setRange(delayEightPanParameter->range.start, delayEightPanParameter->range.end);
    mDelayEightPanSlider.setValue(*delayEightPanParameter);
    addAndMakeVisible(mDelayEightPanSlider);
    mDelayEightPanSlider.onValueChange = [this, delayEightPanParameter] { *delayEightPanParameter = mDelayEightPanSlider.getValue(); };
    mDelayEightPanSlider.onDragStart = [delayEightPanParameter] {delayEightPanParameter->beginChangeGesture(); };
    mDelayEightPanSlider.onDragEnd = [delayEightPanParameter] {delayEightPanParameter->endChangeGesture(); };
    
    
    mDelayEightFeedbackSlider.setValue(0.0f);
    
}

WaylodelayUdAudioProcessorEditor::~WaylodelayUdAudioProcessorEditor()
{
    Timer::stopTimer();
}

void WaylodelayUdAudioProcessorEditor::timerCallback()
//void timerCallback()
{
    setSliders();
}

//==============================================================================
void WaylodelayUdAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
}

void WaylodelayUdAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void WaylodelayUdAudioProcessorEditor::setSliders(){
    
    auto& params2 = processor.getParameters();
    
    juce::AudioParameterFloat* dryGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(1);
    
    mDryGainSlider.setValue(*dryGainParameter2);
    
    
    
    juce::AudioParameterFloat* delayTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(0);
    mDelayTimeSlider.setValue(*delayTimeParameter2);
    
    juce::AudioParameterFloat* delayOneGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(2);
    mDelayOneGainSlider.setValue(*delayOneGainParameter2);
    
    
    
    juce::AudioParameterFloat* delayOneFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(5);
    mDelayOneFeedbackSlider.setValue(*delayOneFeedbackParameter2);
    juce::AudioParameterFloat* delayTwoTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(6);
    mDelayTwoGainSlider.setValue(*delayTwoTimeParameter2);
    juce::AudioParameterFloat* delayTwoGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(7);
    mDelayTwoGainSlider.setValue(*delayTwoGainParameter2);
    
    juce::AudioParameterFloat* delayOneModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(3);
    mDelayOneModDepthSlider.setValue(*delayOneModDpethParameter2);
    juce::AudioParameterFloat* delayTwoModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(8);
    mDelayTwoModDepthSlider.setValue(*delayTwoModDpethParameter2);
    
    juce::AudioParameterFloat* delayOneModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(4);
    mDelayOneModRateSlider.setValue(*delayOneModRateParameter2);
    juce::AudioParameterFloat* delayTwoModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(9);
    mDelayTwoModRateSlider.setValue(*delayTwoModRateParameter2);
    
    
    juce::AudioParameterFloat* delayTwoFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(10);
    mDelayTwoFeedbackSlider.setValue(*delayTwoFeedbackParameter2);
    juce::AudioParameterFloat* delayThreeTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(11);
    mDelayThreeTimeSlider.setValue(*delayThreeTimeParameter2);
    juce::AudioParameterFloat* delayThreeGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(12);
    mDelayThreeGainSlider.setValue(*delayThreeGainParameter2);
    juce::AudioParameterFloat* delayThreeModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(13);
    mDelayThreeModDepthSlider.setValue(*delayThreeModDpethParameter2);
    juce::AudioParameterFloat* delayThreeModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(14);
    mDelayThreeModRateSlider.setValue(*delayThreeModRateParameter2);
    juce::AudioParameterFloat* delayThreeFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(15);
    mDelayThreeFeedbackSlider.setValue(*delayThreeFeedbackParameter2);
    juce::AudioParameterFloat* delayFourTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(16);
    mDelayFourTimeSlider.setValue(*delayFourTimeParameter2);
    juce::AudioParameterFloat* delayFourGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(17);
    mDelayFourGainSlider.setValue(*delayFourGainParameter2);
    juce::AudioParameterFloat* delayFourModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(18);
    mDelayFourModDepthSlider.setValue(*delayFourModDpethParameter2);
    juce::AudioParameterFloat* delayFourModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(19);
    mDelayFourModRateSlider.setValue(*delayFourModRateParameter2);
    juce::AudioParameterFloat* delayFourFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(20);
    mDelayFourFeedbackSlider.setValue(*delayFourFeedbackParameter2);
    juce::AudioParameterFloat* delayFiveTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(21);
    mDelayFiveTimeSlider.setValue(*delayFiveTimeParameter2);
    juce::AudioParameterFloat* delayFiveGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(22);
    mDelayFiveGainSlider.setValue(*delayFiveGainParameter2);
    juce::AudioParameterFloat* delayFiveModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(23);
    mDelayFiveModDepthSlider.setValue(*delayFiveModDpethParameter2);
    juce::AudioParameterFloat* delayFiveModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(24);
    mDelayFiveModRateSlider.setValue(*delayFiveModRateParameter2);
    juce::AudioParameterFloat* delayFiveFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(25);
    mDelayFiveFeedbackSlider.setValue(*delayFiveFeedbackParameter2);
    juce::AudioParameterFloat* delaySixTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(26);
    mDelaySixTimeSlider.setValue(*delaySixTimeParameter2);
    juce::AudioParameterFloat* delaySixGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(27);
    mDelaySixGainSlider.setValue(*delaySixGainParameter2);
    juce::AudioParameterFloat* delaySixModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(28);
    mDelaySixModDepthSlider.setValue(*delaySixModDpethParameter2);
    juce::AudioParameterFloat* delaySixModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(29);
    mDelaySixModRateSlider.setValue(*delaySixModRateParameter2);
    juce::AudioParameterFloat* delaySixFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(30);
    mDelaySixFeedbackSlider.setValue(*delaySixFeedbackParameter2);
    juce::AudioParameterFloat* delaySevenTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(31);
    mDelaySevenTimeSlider.setValue(*delaySevenTimeParameter2);
    juce::AudioParameterFloat* delaySevenGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(32);
    mDelaySevenGainSlider.setValue(*delaySevenGainParameter2);
    juce::AudioParameterFloat* delaySevenModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(33);
    mDelaySevenModDepthSlider.setValue(*delaySevenModDpethParameter2);
    juce::AudioParameterFloat* delaySevenModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(34);
    mDelaySevenModRateSlider.setValue(*delaySevenModRateParameter2);
    juce::AudioParameterFloat* delaySevenFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(35);
    mDelaySevenFeedbackSlider.setValue(*delaySevenFeedbackParameter2);
    juce::AudioParameterFloat* delayEightTimeParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(36);
    mDelayEightTimeSlider.setValue(*delayEightTimeParameter2);
    juce::AudioParameterFloat* delayEightGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(37);
    mDelayEightGainSlider.setValue(*delayEightGainParameter2);
    juce::AudioParameterFloat* delayEightModDpethParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(38);
    mDelayEightModDepthSlider.setValue(*delayEightModDpethParameter2);
    juce::AudioParameterFloat* delayEightModRateParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(39);
    mDelayEightModRateSlider.setValue(*delayEightModRateParameter2);
    
    juce::AudioParameterFloat* delayEightFeedbackParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(40);
    mDelayEightFeedbackSlider.setValue(*delayEightFeedbackParameter2);
    
    juce::AudioParameterFloat* wetGainParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(41);
    mWetGainSlider.setValue(*wetGainParameter2);
    
    juce::AudioParameterFloat* rate2= (juce::AudioParameterFloat*)params2.getUnchecked(42);
    mRateSlider.setValue(*rate2);
    
    juce::AudioParameterFloat* depth2 = (juce::AudioParameterFloat*)params2.getUnchecked(43);
    mDepthSlider.setValue(*depth2);
    
    juce::AudioParameterFloat* delayOnePanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(44);
    mDelayOnePanSlider.setValue(*delayOnePanParameter2);
    
    juce::AudioParameterFloat* delaytwoPanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(45);
    mDelayTwoPanSlider.setValue(*delaytwoPanParameter2);
    
    juce::AudioParameterFloat* delayThreePanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(46);
    mDelayThreePanSlider.setValue(*delayThreePanParameter2);
    
    juce::AudioParameterFloat* delayFourPanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(47);
    mDelayFourPanSlider.setValue(*delayFourPanParameter2);
    
    juce::AudioParameterFloat* delayFivePanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(48);
    mDelayFivePanSlider.setValue(*delayFivePanParameter2);
    
    juce::AudioParameterFloat* delaySixPanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(49);
    mDelaySixPanSlider.setValue(*delaySixPanParameter2);
    
    juce::AudioParameterFloat* delaySevenPanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(50);
    mDelaySevenPanSlider.setValue(*delaySevenPanParameter2);
    
    juce::AudioParameterFloat* delayEightPanParameter2 = (juce::AudioParameterFloat*)params2.getUnchecked(51);
    mDelayEightPanSlider.setValue(*delayEightPanParameter2);
    
    
    
    
}

/***
 float settingsArray [10][41] = {{0.7, 0.0236, 0.030, 0.0361, 0.0476, 0.3, 0.4, 0.341, 0.45, // dry gain plus delay times
 0.8,0.8, 0.8, 0.8, 0.5, 0.5, 0.5, 0.5, // delay gains
 0.1 , 0.1 , 0.1 , 0.1 , 0.1 , 0.1 ,0.1 ,0.1, // mod depths
 0.35, 0.4, 0.42 , 0.37, 0.35, 0.38, 0.47, 0.33, // mod rates
 0.0, 0.0, 0.0, 0.0, 0.45, 0.35, 0.43 , 0.34 // feedback levels
 },
 ***/

void WaylodelayUdAudioProcessorEditor::getPreset(){
    auto& params = processor.getParameters();
    int preset = delaySettings.getSelectedId();
    // juce::AudioParameterFloat* dryGainParameter3 = (juce::AudioParameterFloat*)params.getUnchecked(1);
    mDryGainSlider.setValue(settingsArray[preset][0]);
    mDelayTimeSlider.setValue(settingsArray[preset][1]);
    mDelayTwoTimeSlider.setValue(settingsArray[preset][2]);
    mDelayThreeTimeSlider.setValue(settingsArray[preset][3]);
    mDelayFourTimeSlider.setValue(settingsArray[preset][4]);
    mDelayFiveTimeSlider.setValue(settingsArray[preset][5]);
    mDelaySixTimeSlider.setValue(settingsArray[preset][6]);
    mDelaySevenTimeSlider.setValue(settingsArray[preset][7]);
    mDelayEightTimeSlider.setValue(settingsArray[preset][8]);
    mDelayOneGainSlider.setValue(settingsArray[preset][9]);
    mDelayTwoGainSlider.setValue(settingsArray[preset][10]);
    mDelayThreeGainSlider.setValue(settingsArray[preset][11]);
    mDelayFourGainSlider.setValue(settingsArray[preset][12]);
    mDelayFiveGainSlider.setValue(settingsArray[preset][13]);
    mDelaySixGainSlider.setValue(settingsArray[preset][14]);
    mDelaySevenGainSlider.setValue(settingsArray[preset][15]);
    mDelayEightGainSlider.setValue(settingsArray[preset][16]);
    mDelayOneModDepthSlider.setValue(settingsArray[preset][17]);
    mDelayTwoModDepthSlider.setValue(settingsArray[preset][18]);
    mDelayThreeModDepthSlider.setValue(settingsArray[preset][19]);
    mDelayFourModDepthSlider.setValue(settingsArray[preset][20]);
    mDelayFiveModDepthSlider.setValue(settingsArray[preset][21]);
    mDelaySixModDepthSlider.setValue(settingsArray[preset][22]);
    mDelaySevenModDepthSlider.setValue(settingsArray[preset][23]);
    mDelayEightModDepthSlider.setValue(settingsArray[preset][24]);
    mDelayOneModRateSlider.setValue(settingsArray[preset][25]);
    mDelayTwoModRateSlider.setValue(settingsArray[preset][26]);
    mDelayThreeModRateSlider.setValue(settingsArray[preset][27]);
    mDelayFourModRateSlider.setValue(settingsArray[preset][28]);
    mDelayFiveModRateSlider.setValue(settingsArray[preset][29]);
    mDelaySixModRateSlider.setValue(settingsArray[preset][30]);
    mDelaySevenModRateSlider.setValue(settingsArray[preset][31]);
    mDelayEightModRateSlider.setValue(settingsArray[preset][31]);
    mDelayOneFeedbackSlider.setValue(settingsArray[preset][33]);
    mDelayTwoFeedbackSlider.setValue(settingsArray[preset][34]);
    mDelayThreeFeedbackSlider.setValue(settingsArray[preset][35]);
    mDelayFourFeedbackSlider.setValue(settingsArray[preset][36]);
    mDelayFiveFeedbackSlider.setValue(settingsArray[preset][37]);
    mDelaySixFeedbackSlider.setValue(settingsArray[preset][38]);
    mDelaySevenFeedbackSlider.setValue(settingsArray[preset][39]);
    mDelayEightFeedbackSlider.setValue(settingsArray[preset][40]);
    mWetGainSlider.setValue(settingsArray[preset][41]);
    mDepthSlider.setValue(settingsArray[preset][42]);
    mRateSlider.setValue(settingsArray[preset][43]);
    mDelayOnePanSlider.setValue(settingsArray[preset][44]);
    mDelayTwoPanSlider.setValue(settingsArray[preset][45]);
    mDelayThreePanSlider.setValue(settingsArray[preset][46]);
    mDelayFourPanSlider.setValue(settingsArray[preset][47]);
    mDelayFivePanSlider.setValue(settingsArray[preset][48]);
    mDelaySixPanSlider.setValue(settingsArray[preset][49]);
    mDelaySevenPanSlider.setValue(settingsArray[preset][50]);
    mDelayEightPanSlider.setValue(settingsArray[preset][51]);
    
    
}
