#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameEngine;
class EntityManager;

class UserEventsHandler
{
private:
    GameEngine* gameEngine;

public:
    UserEventsHandler(GameEngine* gameEngine);

    UserEventsHandler(const UserEventsHandler&) = delete;
    UserEventsHandler& operator=(const UserEventsHandler&) = delete;

    void handle(const sf::Event& event);

    sf::View& view();
    sf::RenderWindow& window();
    EntityManager& entityManager();
};