#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <sstream>

// constructor
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
  
}

// overridden draw function
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

// updating the rendering of the Mandelbrot set
void ComplexPlane::updateRender()
{
  
}

// zoomIn
void ComplexPlane::zoomIn()
{

}

// zoomOut
void ComplexPlane::zoomOut()
{
  
}

// set center of complex plane based on pixel location of click
void ComplexPlane::setCenter(Vector2i mousePixel)
{
  
}

// set mouse location based on pixel location
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
  
}

// load text with information about the current state
void ComplexPlane::loadText(Text& text)
{
    // stringstream for formatting the output
    std::stringstream ss;

    // text
    ss << "Mandelbrot Set\n";

    // information required
    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n";
    ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    ss << "Left-click to Zoom in\n";
    ss << "Right-click to Zoom out\n";

    // assign ss - setString=from text - str()=extracts string
    text.setString(ss.str());
}

// helper function: counts iterations for given coordinate
int ComplexPlane::countIterations(Vector2f coord)
{
  
}

// helper function: maps iteration count to RGB color
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
  
}

// helper function: maps pixel location to complex plane coordinates
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
  
}

