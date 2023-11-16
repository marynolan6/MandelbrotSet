// last 3 functions, I have no idea...I hate math
// The rest I did, but obviosuly if I did something wrong, just change it

#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <sstream>

// constructor
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    // assign m_pixelWidth with the parameter values
    m_pixelWidth = pixelWidth;
    m_pixelHeight = pixelHeight;
    
    // Calculate and assign the aspect ratio of the monitor, m_aspectRatio - makes sure it outputs a float
    m_aspectRatio = static_cast<float>(m_pixelHeight) / static_cast<float>(m_pixelWidth);
  
    // Assign m_plane_center with {0,0} - float of 0.0
    m_plane_center = { 0.0f, 0.0f };
  
    // Assign m_plane_size with {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio}
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
  
    // Assign m_zoomCount with 0
    m_zoomCount = 0;

    // Assign m_State with State::CALCULATING to be ready for the initial screen
    m_State = State::CALCULATING;

    // Initialize VertexArray - draws color for each pixel - set primitive type to Points
    m_vArray.setPrimitiveType(Points);
  
    // Resize it to pixelWidth * pixelHeight
    m_vArray.resize(m_pixelWidth * m_pixelHeight);
}

// overridden draw function
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

// updating the rendering of the Mandelbrot set
void ComplexPlane::updateRender()
{
    if (m_State == State::CALCULATING)
    {
      // Create a double for loop to loop through all pixels in the screen height and width
      for (int i = 0; i < m_pixelHeight; ++i)
      {
        for (int j = 0; j < m_pixelWidth; ++j)
        {
          /* Set the position variable in the element of VertexArray that corresponds to the screen coordinate j,i 
            mapping the two-dimensional position at j,i to its 1D array */
          vArray[j + i * pixelWidth].position = { (float)j,(float)i }
             
          // Use ComplexPlane::mapPixelToCoords to find the Vector2f coordinate in the complex plane
          Vector2f coord = mapPixelToCoords(Vector2i(j, i));
            
          // Call ComplexPlane::countIterations with the Vector2f coordinate as its argument
          size_t iterations = countIterations(coord);
        
          // store the RGB values for the current pixel
          Uint8 r, g, b;
        
          // pass iterations & RGB values by reference
          iterationsToRGB(iterations, r, g, b);

          // Set the color variable in the element of VertexArray that corresponds to the screen coordinate j,i
          m_vArray[j + i * m_pixelWidth].color = { r, g, b };
    }
  
    // Set the state to DISPLAYING
    m_State = State::DISPLAYING;
}

// zoomIn
void ComplexPlane::zoomIn()
{
    // Increment m_zoomCount
    ++m_zoomCount;
  
    // Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
    float newXSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);

    // Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
    float newYSize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    // Assign m_plane_size with this new size
    m_plane_size = { newXSize, newYSize };

    // Set m_State to CALCULATING
    m_State = State::CALCULATING;
}

// zoomOut
void ComplexPlane::zoomOut()
{
    // Decrement m_zoomCount
    --m_zoomCount;

    // Set a local variable for the x size to BASE_WIDTH * (BASE_ZOOM to the m_ZoomCount power)
    float newXSize = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);

    // Set a local variable for the y size to BASE_HEIGHT * m_aspectRatio * (BASE_ZOOM to the m_ZoomCount power)
    float newYSize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    // Assign m_plane_size with this new size
    m_plane_size = { newXSize, newYSize };

    // Set m_State to CALCULATING
    m_State = State::CALCULATING;
}

// set center of complex plane based on pixel location of click
void ComplexPlane::setCenter(Vector2i mousePixel)
{
    // Use ComplexPlane::mapPixelToCoords to find the Vector2f coordinate in the complex plane
    Vector2f coords = mapPixelToCoords(mousePixel);

    // Assign m_plane_center with this coordinate
    m_plane_center = coords;

    // Set m_State to CALCULATING
    m_State = State::CALCULATING;
}

// set mouse location based on pixel location
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    // Use ComplexPlane::mapPixelToCoords to find the Vector2f coordinate in the complex plane
    m_mouseLocation = mapPixelToCoords(mousePixel);
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

