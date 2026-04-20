#include <cstdint>
#include <concepts>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <utils/ISConvert.hpp>

int main() {
    ImVec4 color(0.f, 0.8f, 0.f, 1.f);

    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
    window.setFramerateLimit(60);

	sf::View view(sf::FloatRect({ 0.f, 0.f }, { 640.f, 480.f }));
	window.setView(view);

    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* scrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (ImGui::GetIO().WantCaptureMouse) continue;

                bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

                if (ctrlPressed) {
					// Zoom is counter-intuitive.
                    // Zoom means how much is the view scaled.
                    // If zoom is 0.9 it means the view gets smaller,
                    // so the world looks bigger.
                    if (scrolled->delta > 0) {
                        view.zoom(0.9f);
                    }
                    else {
                        view.zoom(1.1f);
                    }

                    window.setView(view);
                }
            }
        }
        window.clear();

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::ColorEdit3("MyColor##1", (float*)&color);
        ImGui::End();

        shape.setFillColor(ISConvert::imVec4ToSfColor(color));
        window.draw(shape);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}