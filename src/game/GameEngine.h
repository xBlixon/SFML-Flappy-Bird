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
public:
	sf::RenderWindow window;
	sf::View view;
	EntityManager entityManager;
	ScoreManager scoreManager;
    UserEventsHandler userEventsHandler;
	State state;

	GameEngine()
        : state(State::MainMenu), 
        userEventsHandler(this)
    {

		window.create(sf::VideoMode({ 640, 480 }), "ImGui + SFML = <3");
		window.setFramerateLimit(60);
        window.setKeyRepeatEnabled(false);

        view = sf::View(sf::FloatRect({ 0.f, 0.f }, { 640.f, 480.f }));
        window.setView(view);
    }

	void run() {
        ImGui::SFML::Init(window);

        sf::Clock deltaClock;
        while (window.isOpen()) {

            while (const auto event = window.pollEvent()) {
				userEventsHandler.handle(*event);
            }
            window.clear();

			sf::Time dt = deltaClock.restart();

            {
                ImGui::SFML::Update(window, dt);

                ImGui::ShowDemoWindow();

                ImGui::SFML::Render(window);
            }

            entityManager.updateAll(dt.asSeconds());
            entityManager.drawAll(window);
            window.display();
        }

        ImGui::SFML::Shutdown();
	}
};