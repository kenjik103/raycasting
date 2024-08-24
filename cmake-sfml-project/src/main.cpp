#include <SFML/Graphics.hpp>

#include <iostream>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int side;

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
            side = 0;
        } else {
            currentMapIndex.y += step.y;
            distance = rayLength.y;
            rayLength.y += tileSizeY * rayUnitStepSize.y;
            side = 1;
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
    sf::RenderWindow flatWindow(sf::VideoMode(screenWidth, screenHeight), "2D View");
    flatWindow.setVerticalSyncEnabled(true);


    sf::RenderWindow mainView(sf::VideoMode(screenWidth, screenHeight), "3D View");
    mainView.setVerticalSyncEnabled(true);

    //player initialization
    sf::CircleShape player(3.f);
    player.setFillColor(sf::Color::Red);
    player.setPosition( screenWidth / 2.f, screenHeight / 2.f);


    //direction vector initialization
    float directionAngle = 0.f;
    float directionVectorLength = screenWidth /  (float)mapWidth;
    sf::Vertex directionVector[] {
            sf::Vertex(sf::Vector2f(player.getPosition())),
            sf::Vertex(sf::Vector2(10.f, 10.f))
    };

    float cameraPlaneLength = 0.66 * (screenWidth / (float) mapWidth);
    sf::Vertex cameraPlane[]{
            sf::Vertex(sf::Vector2f(player.getPosition())),
            sf::Vertex(sf::Vector2(10.f, 10.f))
    };




    //main gameplay loop
    while (flatWindow.isOpen()) {
        //check for window events
        sf::Event event{};
        while (flatWindow.pollEvent(event) || mainView.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    flatWindow.close();
                    mainView.close();
                    break;

                default:
                    break;
            }
        }

        //clear window
        flatWindow.clear(sf::Color::White);
        mainView.clear(sf::Color::Black);

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

                tile.setPosition(x * tileWidth, y * tileHeight);
                flatWindow.draw(tile);
            }
        }

        //ray logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            directionAngle += M_PI / 128;
            if (directionAngle >= 2 * M_PI) {
                directionAngle = 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            directionAngle -= M_PI / 128;
            if (directionAngle <= 0) {
                directionAngle = 2 * M_PI;
            }
        }


        sf::Vector2f directionVectorLocalLength = {
                directionVectorLength * cos(directionAngle),
                directionVectorLength * sin(directionAngle)};
        directionVector[0] = sf::Vertex(sf::Vector2f(
                player.getPosition().x + player.getRadius() + directionVectorLocalLength.x,
                player.getPosition().y + player.getRadius() + directionVectorLocalLength.y));
        directionVector[1] = sf::Vertex(sf::Vector2f(
                player.getPosition().x + player.getRadius(),
                player.getPosition().y + player.getRadius()
        ));

        float fovRadianOffset = atan(cameraPlaneLength / directionVectorLength);
        cameraPlane[0] = sf::Vertex(sf::Vector2f(
                (player.getPosition().x + player.getRadius()) + (directionVectorLength / cos(fovRadianOffset))  * cos(directionAngle + fovRadianOffset),
                (player.getPosition().y + player.getRadius()) + (directionVectorLength / cos( fovRadianOffset)) * sin(directionAngle + fovRadianOffset)));
        cameraPlane[1] = sf::Vertex(sf::Vector2f(
                (player.getPosition().x + player.getRadius()) + (directionVectorLength / cos( fovRadianOffset)) * cos(directionAngle - fovRadianOffset),
                (player.getPosition().y + player.getRadius()) + (directionVectorLength / cos( fovRadianOffset)) * sin(directionAngle - fovRadianOffset)));


        //create and draw raycasts
        float rayAngle = directionAngle - fovRadianOffset;
        float rayCount = 0.f;
        while (rayAngle < directionAngle + fovRadianOffset){
            sf::Vector2f rayLength = getVectorLength(
                    {player.getPosition().x + player.getRadius(),
                     player.getPosition().y + player.getRadius()}, rayAngle);

            sf::Vertex raycast[] = {
                    sf::Vertex({
                        player.getPosition().x + player.getRadius(),
                        player.getPosition().y + player.getRadius()
                    }),
                    sf::Vertex({
                        player.getPosition().x + player.getRadius() + rayLength.x,
                        player.getPosition().y + player.getRadius() + rayLength.y
                    })
            };

            sf::Vector2f endingPos = {
                    player.getPosition().x + player.getRadius() + rayLength.x,
                    player.getPosition().y + player.getRadius() + rayLength.y
            };

            if (rayAngle > M_PI) {
                endingPos.y -= 1;
            } else {
                endingPos.y += 1;
            }
            if (rayAngle > M_PI / 2 && rayAngle < (3 * M_PI) / 2) {
                endingPos.x -= 1;
            } else {
                endingPos.x += 1;
            }

            sf::Vector2i endingIndex = positionToArrayIndex(endingPos);

            raycast[0].color = sf::Color::Green;
            raycast[1].color = sf::Color::Green;

            //player to camera
            float playerToCameraLength = directionVectorLength / cos(fovRadianOffset);

            //ray to wall
            float cameraRayToWall = sqrt(rayLength.x * rayLength.x + rayLength.y * rayLength.y) - playerToCameraLength;

            //camera plane to wall
            float cameraPlaneToWall = abs(sin(270.f - fovRadianOffset) * cameraRayToWall);

            int wallHeight = (int)((screenHeight / cameraPlaneToWall) * (screenWidth / mapWidth));

            int drawStart = -wallHeight / 2 + screenHeight / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = wallHeight;
            if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

            sf::Color color;
            switch(worldMap[endingIndex.y][endingIndex.x])
            {
                case 1:  color = sf::Color::Blue;  break;
                case 2:  color = sf::Color::Green;  break;
                case 3:  color = sf::Color::Red;   break;
                case 4:  color = sf::Color::Cyan;  break;
                case 5: color = sf::Color::White; break;
                default: color = sf::Color::Magenta; break;
            }

            uint32_t colorVal = color.toInteger();
            if (side == 1) colorVal = color.toInteger() * 0.8;

            //draw the pixels of the stripe as a vertical line
            sf::RectangleShape rectangle(sf::Vector2f(7, drawEnd));
            rectangle.setPosition( rayCount * 7, drawStart);
            rectangle.setFillColor(sf::Color{colorVal});

            mainView.draw(rectangle);

            flatWindow.draw(raycast, 2, sf::Lines);

            rayAngle += M_PI / 256.f;
            rayCount += 1.f;

        }



        //move logic
        float dx = 0;
        float dy = 0;
        float moveSpeedScalar = 1.5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dx = moveSpeedScalar * cos(directionAngle);
            dy = moveSpeedScalar * sin(directionAngle);
        }
        sf::Vector2i deltaMoveCoord = positionToArrayIndex(sf::Vector2f(
                player.getPosition().x + player.getRadius() + dx,
                player.getPosition().y + player.getRadius() + dy
                ));
        if (worldMap[deltaMoveCoord.y][deltaMoveCoord.x] == 0){
            player.move(dx, dy);
        }

        //draw
        flatWindow.draw(player);
        flatWindow.draw(directionVector, 2, sf::Lines);
        flatWindow.draw(cameraPlane, 2, sf::Lines);

        //update
        flatWindow.display();
        mainView.display();

    }

    return 0;
}
