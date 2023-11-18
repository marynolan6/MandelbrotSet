/*
- I switched around the i and j in the for loop of updateRender(), just in the 
  header where theyre initialized. I'm not 100% sure if thats right but he said j was x and 
  i was y so that's why I did it. We can change it back if its wrong
- fixed some of the parts that were underlined in red.
- Added in the last three functions
- Added Juice File
- The terminal was giving a warning on line 196 bc it was comparing an int i
  with the unsigned int MAX_ITER so i changed it from returning int to returning unsigned int
*/

// last 3 functions, I have no idea...I hate math
// The rest I did, but obviosuly if I did something wrong, just change it

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
      for (int j = 0; j < m_pixelHeight; ++j)
      {
        for (int i = 0; i < m_pixelWidth; ++i)
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
  //Given coord, count the number of iterations using the equation. 
  //zi+1 = zi^2 + c, where c is a + bi
  //coord = (a, b)
  //absolute value of z cannot exceed 2.0 and i cannot exceed 64 iterations

  // holds number of iterations
  unsigned int i = 0;

  //bool value to tell if z > 2.0;
  bool over2 = false;

  //getting the real and imaginary components
  double re = coord.x;
  double im = coord.y;

  //defining them as complex numbers
  complex<double> c (re,im);

  //defining the z value
  complex<double> z (0,0);

  //loop to go over iterations
  while (!over2 && i <= MAX_ITER)
  {
    z = z*z + c;

    if (abs(z) > 2.0)
    {
        over2 = true;
    }
    else
    {
        i++;
    }
  }

  return i;

}

// helper function: maps iteration count to RGB color
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
  //Setting up the colors based on the number of iterations (count)
  //using the color examples the prof gave to us but we can change it later if we want
  if (count == MAX_ITER) //At 64 iterations color pixel black
  {
    r = 0;
    g = 0;
    b = 0;
  }
  else if (count > 59) // red for high iteration counts
  {
    r = 255;
    g = 0;
    b = 55;
  }
  else if (count > 41) //Yellow
  {
    r = 255;
    g = 247;
    b = 0;
  }
  else if (count > 23) //Green
  {
    r = 13;
    g = 255;
    b = 0;
  }
  else if (count > 5) //Turqouise
  {
    r = 0;
    g = 255;
    b = 187;
  }
  else if (count >= 0) //purple for low iteration counts
  {
    r = 111;
    g = 0;
    b = 255;
  }
}

// helper function: maps pixel location to complex plane coordinates
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
  //((n-a)/(b-a))*(d-c)+c
  Vector2f resultCoord;

  //n is the mouse pixel in x or y direction
  //[a,b] is the range of display pixels in x or y direction
  //Ex. [a,b] = [0,1920] in x direction
  //[c,d] is the range of the imaginary plane
  //Ex. [c,d] = [-2,2]


  //Calculating in x direction
  resultCoord.x = ((mousePixel.x - 0) / (1920 - 0)) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x /2.0);

  //Calculating in y direction
  resultCoord.x = ((mousePixel.y - 1080) / (0 - 1080)) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y /2.0);


  return resultCoord;
}
