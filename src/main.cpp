#include <cstdint>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    ImVec4 color(0.f, 0.8f, 0.f, 1.f);
    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::ColorEdit3("MyColor##1", (float*)&color);
        ImGui::End();

        window.clear();

        shape.setFillColor(sf::Color(
            static_cast<std::uint8_t>(color.x * 255),
            static_cast<std::uint8_t>(color.y * 255),
            static_cast<std::uint8_t>(color.z * 255),
            static_cast<std::uint8_t>(color.w * 255)
        ));

        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}