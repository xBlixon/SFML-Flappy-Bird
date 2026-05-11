#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <game/EntityManager.h>
#include <game/ScoreManager.h>
#include <game/State.h>
#include <game/UserEventsHandler.h>

#include <utils/ISConvert.h>

class GameEngine
{
protected:
	sf::RenderWindow window;
	sf::View view;
	EntityManager entityManager;
	ScoreManager scoreManager;
    UserEventsHandler userEventsHandler;
	State state;
public:

	GameEngine()
        : state(State::MainMenu), 
        userEventsHandler(&window, &view)
    {

		window.create(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
		window.setFramerateLimit(60);

        view = sf::View(sf::FloatRect({ 0.f, 0.f }, { 640.f, 480.f }));
        window.setView(view);
    }

	void run() {
        ImGui::SFML::Init(window);

        ImVec4 color(0.f, 0.8f, 0.f, 1.f);

        sf::CircleShape shape(100.f);

        sf::Clock deltaClock;
        while (window.isOpen()) {

            while (const auto event = window.pollEvent()) {
                ImGui::SFML::ProcessEvent(window, *event);
				userEventsHandler.handle(*event);
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
};