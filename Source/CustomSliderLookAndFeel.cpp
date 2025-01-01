/*
  ==============================================================================

    CustomSliderLookAndFeel.cpp
    Created: 31 Dec 2024 12:24:49pm
    Author:  Morris Blaustein

  ==============================================================================
*/


#include "CustomSliderLookAndFeel.h"


CustomSliderLookAndFeel::CustomSliderLookAndFeel()
{
    DBG("test");
}

void CustomSliderLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider)
{
    rotaryStartAngle = 0.0f;
    rotaryEndAngle = 359.f;
//    g.setColour(juce::Colour(255, 0, 0));
    int size = std::min(width,height)-5;
    int newY =(height-size)/2;
    x = (width-size)/2;
//    juce::ColourGradient gradient1(
//        juce::Colour(128,255,0),                       // Start color
//        x + size / 2, newY + size / 2,             // Start position (center of arc)
//        juce::Colour(255,0,128),                        // End color
//        x + size, newY + size,                     // End position (bottom-right of arc)
//        true                                      // Is radial?
//    );
//
//    // Set the gradient to the graphics context
//    g.setGradientFill(gradient1);

    // Fill the path with the gradient
//    g.fillPath(sliderFill);
    g.setColour(juce::Colours::black);
    g.fillEllipse(x,newY,size,size);
    
    

    
    
    
    
    juce::Path sliderFill;
    sliderFill.addCentredArc(x+size/2, newY+size/2, size/2, size/2
                             , juce::MathConstants<float>::pi/2, 0, (sliderPos)*(juce::MathConstants<float>::twoPi), true);
    sliderFill.lineTo(x+size/2,newY+size/2);
    juce::ColourGradient gradient2(
        juce::Colours::blue,                       // Start color
        x + size / 2, newY + size / 2,             // Start position (center of arc)
        juce::Colours::red,                        // End color
        x + size+sliderPos*100, newY + size+sliderPos*100,                     // End position (bottom-right of arc)
        true                                      // Is radial?
    );

    // Set the gradient to the graphics context
    g.setGradientFill(gradient2);

    // Fill the path with the gradient
    g.fillPath(sliderFill);
    
    g.setColour(juce::Colour(255, 255, 255));
    g.drawLine(x + size / 2, newY + size / 2,
                x + size / 2 + std::cos(rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle) * juce::MathConstants<float>::pi / 180.0f   ) * size / 2,
                newY + size / 2 + std::sin(rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle) * juce::MathConstants<float>::pi / 180.0f ) * size / 2 ,
                2.0f);
    g.drawLine(x+size/2, newY+size/2, x+size, newY+size/2, 2.0f);
    juce::Path ellipsePath;

    // Create a path for the hollow ellipse
    ellipsePath.addEllipse(x, newY, size, size);
    ellipsePath.addEllipse(x-1, newY-1, size+2, size+2);

    // Set the fill rule to create the hollow effect
    ellipsePath.setUsingNonZeroWinding(false);
    
    
    g.fillPath(ellipsePath);

    
}


void CustomSliderLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle style, juce::Slider& slider)
    {
    float trackHeight = 20.0f;  // Taller track height
           juce::Rectangle<float> track(x, y + (height - trackHeight) / 2, width, trackHeight);
           
           // Draw the track background
           g.setColour(juce::Colours::darkgrey.darker(0.3f));
           g.fillRoundedRectangle(track, trackHeight / 4);

           // Add subtle highlight to the top of the track
           g.setGradientFill(juce::ColourGradient::vertical(juce::Colours::darkgrey.brighter(0.5f),
                                                            track.getY(),
                                                            juce::Colours::darkgrey,
                                                            track.getBottom()));
           g.fillRoundedRectangle(track, trackHeight / 4);

           // Gradient fill for the slider up to the thumb position
           juce::ColourGradient gradient(juce::Colours::yellow, track.getX(), track.getY(),
                                         juce::Colours::purple, sliderPos, track.getY(),
                                         false);
           g.setGradientFill(gradient);
           g.fillRoundedRectangle(track, trackHeight / 4);

           // Fill the rest with black
           juce::Rectangle<float> filledTrack(track.getX() + sliderPos - x, track.getY(),
                                               track.getWidth() - (sliderPos - x), trackHeight);
           g.setColour(juce::Colours::black);
           g.fillRoundedRectangle(filledTrack, trackHeight / 4);

           // Draw the outline of the slider
           g.setColour(juce::Colours::white);  // Outline color
           g.drawRoundedRectangle(track, trackHeight / 4, 2.0f);  // 2.0f for the outline thickness

           // Custom thumb as a vertical line with rounded ends
           float lineThickness = 6.0f; // Thicker line for thumb
           g.setColour(juce::Colours::white);
           g.drawLine(juce::Line<float>(sliderPos, track.getY(), sliderPos, track.getBottom()), lineThickness);
       
}

void CustomSliderLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        // Get the button's bounds
        auto bounds = toggleButton.getLocalBounds().toFloat();
        auto isOn = toggleButton.getToggleState();

        // Background
        g.setColour(juce::Colours::lightgrey);
//        g.fillRoundedRectangle(bounds, 5.0f);

        // Triangle color
        g.setColour(juce::Colours::lightgrey);

        // Draw the triangle
        juce::Path triangle;
        if (isOn) // If toggled on, draw a left-facing triangle
        {
            triangle.addTriangle(
                bounds.getCentreX() - 10, bounds.getCentreY(),    // Left point
                bounds.getCentreX() + 10, bounds.getCentreY() - 10, // Top right point
                bounds.getCentreX() + 10, bounds.getCentreY() + 10  // Bottom right point
            );
        }
        else // If toggled off, draw a right-facing triangle
        {
            triangle.addTriangle(
                bounds.getCentreX() + 10, bounds.getCentreY(),    // Right point
                bounds.getCentreX() - 10, bounds.getCentreY() - 10, // Top left point
                bounds.getCentreX() - 10, bounds.getCentreY() + 10  // Bottom left point
            );
        }

        g.fillPath(triangle);
    }
