// UserEventsHandler.cpp
#include <game/UserEventsHandler.h>
#include "GameEngine.h"  // Tutaj ju¿ mo¿emy bezpiecznie do³¹czyæ
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

        if (ctrlPressed) {
            if (scrolled->delta > 0) {
                view().zoom(0.9f);
            }
            else {
                view().zoom(1.1f);
            }
            window().setView(view());
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