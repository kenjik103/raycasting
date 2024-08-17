#include <SFML/Graphics.hpp>

#include <iostream>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
        {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

sf::Vector2f positionToArrayIndex(sf::Vector2f pos) {
    float x = mapWidth * (pos.x / screenWidth);
    float y = mapHeight * (pos.y / screenHeight);

    return {x, y};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Raycast Demo");
    window.setVerticalSyncEnabled(true);


    //player initialization
    sf::CircleShape player(5.f);
    player.setFillColor(sf::Color::Red);
    player.setPosition(screenWidth / 2.f, screenHeight / 2.f);

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
        //check for window events
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
        window.clear(sf::Color::White);

        //ray logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rayAngle += 0.05f;
            if (rayAngle > 2 * M_PI) {
                rayAngle = 0.f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rayAngle -= 0.05f;
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


        //draw array
        float tileWidth = screenWidth / (float)mapWidth;
        float tileHeight = screenHeight / (float)mapHeight;
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {

                sf::RectangleShape tile(sf::Vector2f( tileWidth - 1.f, tileHeight - 1.f));

                if (worldMap[y][x] > 0) {
                    tile.setFillColor(sf::Color::Blue);
                } else if (worldMap[y][x] == 0) {
                    tile.setFillColor(sf::Color::Black);
                }

                sf::Vector2f playerIndex = positionToArrayIndex(player.getPosition());
                if (y == (int)playerIndex.y && x == (int)playerIndex.x) {
                    tile.setFillColor(sf::Color::Green);
                }

                tile.setPosition(x * tileWidth, y * tileHeight);
                window.draw(tile);
            }
        }


        //move logic
        float moveSpeedScalar = 1.5;
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
