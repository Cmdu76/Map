#include <iostream>

#include <SFML/Graphics.hpp>

#include "Map/Map.hpp"
#include "Map/Properties.hpp"
#include "Map/Orthogonal.hpp"
#include "Map/Isometric.hpp"
#include "Map/DefaultGen.hpp"
#include "Map/ChunkGenerator.hpp"

#include <SFML/Network.hpp>

int main()
{
    int choice = 2;
    do
    {
        std::cout << "Quel type de Map voulez-vous voir ?" << std::endl;
        std::cout << " - 1 : Orthogonal" << std::endl;
        std::cout << " - 2 : Isometric" << std::endl;
        std::cin >> choice;
    } while (choice < 1 && choice > 2);
    if (choice == 1)
    {
        Orthogonal::init();
    }
    else if (choice == 2)
    {
        Isometric::init();
    }

    map::Map mMap(new DefaultGen());

    sf::RenderWindow window(sf::VideoMode(800,600),"Map");
    sf::View view = window.getView();
    view.setCenter(sf::Vector2f(0,0));
    mMap.update(view);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta < 1)
                {
                    view.zoom(1.2f);
                }
                else
                {
                    view.zoom(0.8f);
                }
            }
        }

        sf::Vector2f mvt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            mvt.y--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            mvt.x--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            mvt.y++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            mvt.x++;
        }
        mvt *= clock.restart().asSeconds() * 300.f;
        view.move(mvt);

        mMap.update(view);

        sf::Vector2i coords = map::Properties::worldToGlobalCoords(window.mapPixelToCoords(sf::Mouse::getPosition(window),view));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mMap.setTileId(coords,0,2);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            mMap.setTileId(coords,0,1);
        }

        window.clear();
        window.setView(view);
        mMap.render(window,view,0);
        window.setView(window.getDefaultView());
        window.display();
    }

    return 0;
}





/*#include "../Aharos/Application/Application.hpp"

#include "States/MainState.hpp"
#include "States/WorldState.hpp"
#include "States/TilesetState.hpp"
#include "States/AnimationState.hpp"

#include <iostream>

int main()
{
    // Load Resources
    ah::Application::instance().loadFont("Coolveticca","Assets/Fonts/Coolveticca.ttf");

    // Load Application
    ah::Application::instance().showDebugScreen(true);
    ah::Application::instance().setFont(ah::Application::instance().getFont("Coolveticca"));
    ah::Application::instance().useConsole(true);

    // Window Config
    ah::Application::instance().create(sf::VideoMode(1200,700),"Map");
    ah::Application::instance().setIcon("Assets/Textures/icon.png");
    ah::Application::instance().setMouseCursorTexture("Assets/Textures/cursor.png");
    ah::Application::instance().useCustomMouseCursor();

    // Register States
    ah::Application::instance().registerState<MainState>(MainState::getID());
    ah::Application::instance().registerState<WorldState>(WorldState::getID());
    ah::Application::instance().registerState<TilesetState>(TilesetState::getID());
    ah::Application::instance().registerState<AnimationState>(AnimationState::getID());

    // Run
    ah::Application::instance().pushState(MainState::getID());
    ah::Application::instance().run();

    return EXIT_SUCCESS;
}
*/


