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
#include <utils/ImGuiDebug.h>

class GameEngine
{
public:
	sf::RenderWindow window;
	sf::View view;
	ScoreManager scoreManager;
	EntityManager entityManager;
    UserEventsHandler userEventsHandler;
	State state;
	bool debugMode = false;

	GameEngine()
        : state(State::MainMenu), 
        userEventsHandler(this),
		entityManager(this)
    {

		window.create(sf::VideoMode({ 1280, 720 }), "Flappy Bird Clone");
		window.setFramerateLimit(60);
        window.setKeyRepeatEnabled(false);

        view = sf::View(sf::FloatRect({ -640.f, -360.f }, { 1280, 720 }));
        window.setView(view);
    }

	void run() {
        sf::Clock deltaClock;

        ImGuiDebug debug = ImGuiDebug(this);

        while (window.isOpen()) {

            while (const auto event = window.pollEvent()) {
				userEventsHandler.handle(*event);
            }
            window.clear();

			sf::Time dt = deltaClock.restart();

            if (state == State::Playing) {
                entityManager.updateAll(dt.asSeconds());
            }
            entityManager.drawAll(window);

            if (debugMode) {
                debug.show(dt);
            }

            window.display();
        }


        ImGui::SFML::Shutdown();
	}

    void restart() {
		entityManager.reset();
		state = State::MainMenu;
    }
   
    void pause() {
		entityManager.pause();
		state = State::Paused;
    }

    void gameOver() {
		entityManager.gameOver();
		state = State::GameOver;
        scoreManager.addCurrentGameToHistory();
    }

    void enableDebugMode() {
		debugMode = true;
    }

	void disableDebugMode() {
        debugMode = false;
		resetView();
	}

    void resetView() {
        view.setCenter({ 0.f, 0.f });
        view.setSize({ 1280.f, 720.f });
        window.setView(view);
	}
};