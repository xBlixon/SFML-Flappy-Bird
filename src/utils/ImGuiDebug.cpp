#include "ImGuiDebug.h"
#include "game/GameEngine.h"

ImGuiDebug::ImGuiDebug(GameEngine* gameEngine) : gameEngine(gameEngine) {
	ImGui::SFML::Init(gameEngine->window);
}

void ImGuiDebug::show(sf::Time dt) {
	ImGui::SFML::Update(gameEngine->window, dt);
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Game editor");


	gameState();
	pipes();
	bird();


	ImGui::End();

	ImGui::SFML::Render(gameEngine->window);
}

void ImGuiDebug::gameState() {
	ImGui::SeparatorText("Game status");
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
}

void ImGuiDebug::pipes() {
	ImGui::SeparatorText("Pipes");
	if ( ImGui::DragFloat("Gap", &gameEngine->entityManager.pipeGap, 0.5f) )
	{
		gameEngine->entityManager.updatePipeGap();
	}
}

void ImGuiDebug::bird() {
	ImGui::SeparatorText("Bird");
	ImGui::DragFloat("Jump force   ", &gameEngine->entityManager.jumpForce,    0.5f);
	ImGui::DragFloat("Gravity force", &gameEngine->entityManager.gravityForce, 0.5f);
}