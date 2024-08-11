#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Raycast Demo");
    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {

        //check for events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    break;

                default:
                    break;
            }
        }

        //clear window
        window.clear(sf::Color::Black);


        //draw
        window.draw(shape);

        //update
        window.display();

    }

    return 0;
}
