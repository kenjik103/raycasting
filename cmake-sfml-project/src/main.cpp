#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Raycast Demo");
    window.setVerticalSyncEnabled(true);


    //player initialization
    sf::CircleShape player(15.f);
    player.setFillColor(sf::Color::Red);
    player.setPosition(600.f, 300.f);

    //raycast initialization
    sf::Vertex raycast[] = {
            sf::Vertex(sf::Vector2f(player.getPosition())),
            sf::Vertex(sf::Vector2(10.f, 10.f))
    };
    float rayAngle = 0.f;
    float rayPosX;
    float rayPosY;
    float rayLen = 50.f;

    while (window.isOpen()) {

        //check for events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        //clear window
        window.clear(sf::Color::Black);

        //ray logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rayAngle += 0.1f;
            if (rayAngle > 2 * M_PI) {
                rayAngle = 0.f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rayAngle -= 0.1f;
            if (rayAngle < -2 * M_PI) {
                rayAngle = 0.f;
            }
        }

        rayPosX = rayLen * (cos(rayAngle));
        rayPosY = rayLen * (sin(rayAngle));

        raycast[0] = sf::Vertex(sf::Vector2f(
                player.getPosition().x + player.getRadius() + rayPosX,
                player.getPosition().y + player.getRadius() + rayPosY));
        raycast[1] = sf::Vertex(sf::Vector2f(
                player.getPosition().x + player.getRadius(),
                player.getPosition().y + player.getRadius()
                ));

        //move logic
        float moveSpeedScalar = 4.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move( moveSpeedScalar * rayPosX / rayLen, moveSpeedScalar * rayPosY / rayLen);
        }


        //draw
        window.draw(player);
        window.draw(raycast, 2, sf::Lines);

        //update
        window.display();

    }

    return 0;
}
