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

sf::Vector2i positionToArrayIndex(sf::Vector2f pos) {
    int x = mapWidth * (pos.x / screenWidth);
    int y = mapHeight * (pos.y / screenHeight);

    return {x, y};
}

sf::Vector2f getVectorLength(sf::Vector2f playerOrigin, float rayAngle){
    //DDA Algorithm
    //credit: https://www.youtube.com/watch?v=NbSee-XM7WA&t=1270s
    sf::Vector2f rayStartingPos = {playerOrigin};
    sf::Vector2f rayDirection = sf::Vector2f(cos(rayAngle), sin(rayAngle));

    sf::Vector2f rayUnitStepSize = {abs(1 / cos(rayAngle)), abs(1 / sin(rayAngle))};
    sf::Vector2i currentMapIndex = positionToArrayIndex(rayStartingPos);
    sf::Vector2f rayLength;

    float tileSizeX = screenWidth / (float)mapWidth;
    float tileSizeY = screenHeight / (float)mapHeight;

    sf::Vector2i step;
    if (rayDirection.x < 0) {
        step.x = -1;
        rayLength.x = (rayStartingPos.x - (tileSizeX * (float)currentMapIndex.x)) * rayUnitStepSize.x;
    } else {
        step.x = 1;
        rayLength.x = (tileSizeX * ((float)currentMapIndex.x + 1) - rayStartingPos.x) * rayUnitStepSize.x;
    }
    if (rayDirection.y < 0) {
        step.y = -1;
        rayLength.y = (rayStartingPos.y -  (tileSizeY * (float)currentMapIndex.y)) * rayUnitStepSize.y;
    } else {
        step.y = 1;
        rayLength.y = (tileSizeY * ((float)currentMapIndex.y + 1) - rayStartingPos.y) * rayUnitStepSize.y;
    }

    bool tileFound = false;
    float maxDistance = 1000.0f;
    float distance = 0.f;
    while (!tileFound && distance < maxDistance){
        if (rayLength.x < rayLength.y) {
            currentMapIndex.x += step.x;
            distance = rayLength.x;
            rayLength.x += tileSizeX * rayUnitStepSize.x;
        } else {
            currentMapIndex.y += step.y;
            distance = rayLength.y;
            rayLength.y += tileSizeY * rayUnitStepSize.y;
        }

        if (currentMapIndex.x >= 0 && currentMapIndex.x <= mapWidth && currentMapIndex.y >= 0 && currentMapIndex.y <= mapHeight) {
            if (worldMap[currentMapIndex.y][currentMapIndex.x] > 0) {
                tileFound = true;
            }
        }
    }

    return {rayDirection.x * distance, rayDirection.y * distance};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Raycast Demo");
    window.setVerticalSyncEnabled(true);


    //player initialization
    sf::CircleShape player(3.f);
    player.setFillColor(sf::Color::Red);
    player.setPosition( screenWidth / 2.f, screenHeight / 2.f);

    //raycast initialization
    sf::Vertex raycast[] = {
            sf::Vertex(sf::Vector2f(player.getPosition())),
            sf::Vertex(sf::Vector2(10.f, 10.f))
    };
    float rayAngle = 0.f;

    //direction vector initialization
    sf::Vertex directionVector[] {
            sf::Vertex(sf::Vector2f(player.getPosition())),
            sf::Vertex(sf::Vector2(10.f, 10.f))
    };


    //main gameplay loop
    while (window.isOpen()) {
        //check for window events
        sf::Event event{};
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
            rayAngle += M_PI / 128;
            if (rayAngle >= 2 * M_PI) {
                rayAngle = 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rayAngle -= M_PI / 128;
            if (rayAngle <= 0) {
                rayAngle = 2 * M_PI;
            }
        }


        sf::Vector2f rayLength = getVectorLength(
                {player.getPosition().x + player.getRadius(),
                 player.getPosition().y + player.getRadius()}, rayAngle);
        raycast[0] = sf::Vertex(sf::Vector2f(
                player.getPosition().x + player.getRadius() + rayLength.x,
                player.getPosition().y + player.getRadius() + rayLength.y));
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

                sf::Vector2i playerIndex = positionToArrayIndex(sf::Vector2f(
                        player.getPosition().x + player.getRadius(),
                        player.getPosition().y + player.getRadius()));

                if (y == playerIndex.y && x == playerIndex.x) {
                    tile.setFillColor(sf::Color::Green);
                }

                tile.setPosition(x * tileWidth, y * tileHeight);
                window.draw(tile);
            }
        }


        //move logic
        float dx = 0;
        float dy = 0;
        float moveSpeedScalar = 1.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dx = moveSpeedScalar * cos(rayAngle);
            dy = moveSpeedScalar * sin(rayAngle);
        }
        sf::Vector2i deltaMoveCoord = positionToArrayIndex(sf::Vector2f(
                player.getPosition().x + player.getRadius() + dx,
                player.getPosition().y + player.getRadius() + dy
                ));
        if (worldMap[deltaMoveCoord.y][deltaMoveCoord.x] == 0){
            player.move(dx, dy);
        }


        //draw
        window.draw(player);
        window.draw(raycast, 2, sf::Lines);

        //update
        window.display();

    }

    return 0;
}
