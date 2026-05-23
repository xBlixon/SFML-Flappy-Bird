#include "ImGuiDebug.h"
#include "game/GameEngine.h"

ImGuiDebug::ImGuiDebug(GameEngine* gameEngine) : gameEngine(gameEngine) {
	ImGui::SFML::Init(gameEngine->window);
}

void ImGuiDebug::show(sf::Time dt) {
	ImGui::SFML::Update(gameEngine->window, dt);
	ImGui::ShowDemoWindow();
	pauseButton();
	ImGui::SFML::Render(gameEngine->window);
}

void ImGuiDebug::pauseButton() {
	ImGui::Begin("Game Status");
	if (gameEngine->state == State::Paused) {
		if (ImGui::Button("Paused")) {
			gameEngine->state = State::Playing;
		}
	}
	else
	{
		if (ImGui::Button("Playing")) {
			gameEngine->state = State::Paused;
		}
	}
	ImGui::End();
}