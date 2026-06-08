#include <iostream>
#include <game/UserEventsHandler.h>
#include "GameEngine.h" 
#include "imgui.h"

UserEventsHandler::UserEventsHandler(GameEngine* gameEngine) : gameEngine(gameEngine) {}

void UserEventsHandler::handle(const sf::Event& event) {

	ImGui::SFML::ProcessEvent(window(), event);

    if (event.is<sf::Event::Closed>()) {
        window().close();
    }

    if (const auto* scrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
        if (ImGui::GetIO().WantCaptureMouse) return;

        bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

        if (ctrlPressed && gameEngine->debugMode) {
            if (scrolled->delta > 0) {
                view().zoom(0.9f);
            }
            else {
                view().zoom(1.1f);
            }
            window().setView(view());
        }

    }

    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Middle && gameEngine->debugMode) {
            isDragging = true;
            lastMousePos = mousePressed->position;
        }
    }

    if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseReleased->button == sf::Mouse::Button::Middle) {
            isDragging = false;
        }
    }

    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        if (isDragging) {
            float deltaX = static_cast<float>(mouseMoved->position.x - lastMousePos.x);
            float deltaY = static_cast<float>(mouseMoved->position.y - lastMousePos.y);

            view().move({ -deltaX, -deltaY });
            window().setView(view());

            lastMousePos = mouseMoved->position;
        }
    }

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::F3) {
			gameEngine->debugMode ? gameEngine->disableDebugMode() : gameEngine->enableDebugMode();
		}
    }

	entityManager().handleEvent(event);
}

sf::View& UserEventsHandler::view() {
    return gameEngine->view;
}

sf::RenderWindow& UserEventsHandler::window() {
    return gameEngine->window;
}

EntityManager& UserEventsHandler::entityManager() {
    return gameEngine->entityManager;
}