#include "ComplexPlane.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
//Get desktop resolution:
int pixelWidth = VideoMode::getDesktopMode().width / 2;
int pixelHeight = VideoMode::getDesktopMode().height / 2;

//Construct VideoMode object vm
VideoMode vm(pixelWidth, pixelHeight);

//Construct RenderWindow window
RenderWindow window(vm, "Mandelbrot", Style::Default);

//Construct ComplexPlane object here



//Load font //Can change later if you want
Font font;
if (!font.loadFromFile("JUICE___.TTF")) 
{
    cerr << "Font not found boo" << endl;
    return 1;
}

// Create text object
Text text;
text.setFont(font); 
text.setString("Instructions: ");
text.setCharacterSize(24);
text.setFillColor(Color::Green);
text.setStyle(Text::Bold);

//Display the text
window.draw(text);

//Begin main loop
while (window.isOpen())
{
/*
	****************************************
	Handle the players input
	****************************************
*/
    Event event;
		while (window.pollEvent(event))
		{
            //Close window if event is closed
	    if (event.type == sf::Event::Closed) window.close();

            //Zoom in and zoom out
	    if (event.type == sf::Event::MouseButtonPressed)
	    {
		if (event.mouseButton.button == sf::Mouse::Left)
		{
		    std::cout << "the left button was pressed" << std::endl;
		    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
		    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    /*zoomIn and call setCenter on 
                    the ComplexPlane object with the 
                    (x,y) pixel location of the mouse click*/

		}
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
		    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
		    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    /*zoomOut and call setCenter on 
                    the ComplexPlane object with the 
                    (x,y) pixel location of the mouse click*/
                }

                //Set state to CALCULATING here



	    }

            if (event.type == sf::Event::MouseMoved)
            {
                /*Call setMouseLocation on the ComplexPlane object 
                to store the (x,y) pixel location of the mouse click*/
	    }
		
		
		}

        //Check if Keyboard::isKeyPressed(Keyboard::Escape) to close the window
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}


/*
	****************************************
	Update the scene
	****************************************
*/

/*Call updateRender on the ComplexPlane object
Call loadText on the ComplexPlane object*/

/*
	****************************************
	Draw the scene
	****************************************
*/

/*Clear the RenderWindow object
draw the ComplexPlane object
draw the Text object
Display the RenderWindow object*/



//End of window.isOpen() loop
}

return 0;
}
