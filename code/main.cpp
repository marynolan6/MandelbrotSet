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
ComplexPlane complexPlane(pixelWidth, pixelHeight);

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
				cout << "the left button was pressed" << endl;
				cout << "mouse x: " << event.mouseButton.x << endl;
				cout << "mouse y: " << event.mouseButton.y << endl;

				/*zoomIn and call setCenter on 
				the ComplexPlane object with the 
				(x,y) pixel location of the mouse click*/
				complexPlane.zoomIn();
				complexPlane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));

			}
			// same for left except zoomOut
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				cout << "the right button was pressed" << endl;
				cout << "mouse x: " << event.mouseButton.x << endl;
				cout << "mouse y: " << event.mouseButton.y << endl;
					
				/*zoomOut and call setCenter on 
				the ComplexPlane object with the 
				(x,y) pixel location of the mouse click*/
				complexPlane.zoomOut();
				complexPlane.setCenter(Vector2i(event.mouseButton.x, event.mouseButton.y));
			}

			//Set state to CALCULATING here
			//ComplexPlane::State::CALCULATING;
	    }

        if (event.type == sf::Event::MouseMoved)
        {
        /*Call setMouseLocation on the ComplexPlane object 
        to store the (x,y) pixel location of the mouse click*/
		complexPlane.setMouseLocation(Vector2i(event.mouseMove.x, event.mouseMove.y));
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

	//Call updateRender on the ComplexPlane object
	complexPlane.updateRender();
	//Call loadText on the ComplexPlane object
	complexPlane.loadText(text);
/*
	****************************************
	Draw the scene
	****************************************
*/

	//Clear the RenderWindow object
	window.clear();
	// draw the ComplexPlane object
	window.draw(complexPlane);
	//draw the Text object
	window.draw(text);
	//Display the RenderWindow object
	window.display();

//End of window.isOpen() loop
}

return 0;
}
