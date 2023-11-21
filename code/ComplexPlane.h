#pragma once
#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>

// make code easier to type with "using namespace"
using namespace sf;

class ComplexPlane : public sf::Drawable 
{
   public:
     // declare global constants
     const unsigned int MAX_ITER = 64;
     const float BASE_WIDTH = 4.0;
     const float BASE_HEIGHT = 4.5;
     const float BASE_ZOOM = 0.5;

     // declare enum class type
     enum class State 
     {
        CALCULATING,
        DISPLAYING
     };

     // constructor
     ComplexPlane(int pixelWidth, int pixelHeight);

     // member functions
     void zoomIn();
     void zoomOut();
     void setCenter(Vector2i mousePixel);
     void setMouseLocation(Vector2i mousePixel);
     void loadText(Text& text);
     void updateRender();

     //
     void processRow(int i);

   private:
     // overridden draw function
     virtual void draw(RenderTarget& target, RenderStates states) const;

     // helper functions
     unsigned int countIterations(Vector2f coord);
     //sf::Thread m_thread;
     void iterationsToRGB(size_t count, Uint8& r, Uint8& g, sf::Uint8& b);
     Vector2f mapPixelToCoords(Vector2i mousePixel);

     // member variables
     float m_aspectRatio;
     Vector2f m_plane_center;
     Vector2f m_plane_size;
     int m_zoomCount;
     State m_State;

     VertexArray m_vArray;
     Vector2f m_mouseLocation;
     Vector2i m_pixel_size;
     int m_pixelHeight;
     int m_pixelWidth;
};

#endif // COMPLEXPLANE_H
