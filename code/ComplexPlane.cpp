#include "ComplexPlane.h"
#include <cmath>
#include <iostream>
#include <complex>
#include <sstream>

using namespace std;

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
          m_vArray[j + i * m_pixelWidth].position = { (float)j,(float)i };
             
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
      }
      // Set the state to DISPLAYING
      m_State = State::DISPLAYING;
    }   
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
unsigned int ComplexPlane::countIterations(Vector2f coord)
{
    // the real and imaginary parts of the complex number
    float real = coord.x;
    float imag = coord.y;

    // initial values of the real and imaginary parts,
    float realTemp = real;
    float imagTemp = imag;

    // Iterate until the escape condition is met or until reaching MAX_ITER
    size_t iterations = 0;
    while (iterations < MAX_ITER)
    {
        // multiple squares of the real and imaginary parts
        float realSquared = real * real;
        float imagSquared = imag * imag;

        // check if the complex number is escaping
        if (realSquared + imagSquared > 4.0)
        {
            break; // escape condition is met
        }

        // mandelbrot formula to update complex numbwr
        imag = 2.0 * real * imag + imagTemp;
        real = realSquared - imagSquared + realTemp;

        // increments iteration count
        iterations++;
    }
    // used for coloring in the rendering process
    return iterations;
}

// Helper function: maps iteration count to RGB color
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    // Check if the maximum iterations are reached
    if (count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0; // Black color
        return;
    }

    // Define color regions
    const size_t regionCount = 5;
    const size_t regionSize = MAX_ITER / regionCount;

    // Determine the region for the given iteration count
    size_t region = count / regionSize;

    // Map iteration count to RGB color based on the region
    switch (region)
    {
    case 0:
        // black color outer picture
        r = 0;
        g = 0;
        b = 0;
        break;
    case 1:
        // Red region
        r = 255;
        g = 0;
        b = 55;
        break;
    case 2:
        // Yellow region
        r = 255;
        g = 247;
        b = 0;
    case 3:
        // Green region
        r = 13;
        g = 255;
        b = 0;
        break;
    case 4:
        // Turquoise region
        r = 0;
        g = 255;
        b = 187;
        break;
    default:
        // Purple/blue region
        r = 111;
        g = 0;
        b = 255;
        break;
    }
}
// helper function: maps pixel location to complex plane coordinates
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    // Calculate the normalized coordinates within the pixel range [0, pixelWidth] and [0, pixelHeight]
    float normalizedX = static_cast<float>(mousePixel.x) / m_pixelWidth;
    float normalizedY = static_cast<float>(mousePixel.y) / m_pixelHeight;

    // Calculate the coordinates within the specified complex plane range of real/imag
    // m_plane_size.y=height - 1.0f - normalizedY=increase from top to bottom - 
    // m_plane_center.x - m_plane_size.x / 2.0f=substracting half of plane's height
    float real = ((normalizedX) * m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0f);
    float imag = ((1.0f - normalizedY) * m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0f);

    return Vector2f(real, imag);
}
