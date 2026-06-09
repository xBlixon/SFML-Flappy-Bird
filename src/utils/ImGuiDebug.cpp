#include "ImGuiDebug.h"
#include "game/GameEngine.h"

ImGuiDebug::ImGuiDebug(GameEngine* gameEngine) : gameEngine(gameEngine) {
	ImGui::SFML::Init(gameEngine->window);
}

void ImGuiDebug::show(sf::Time dt) {
	ImGui::SFML::Update(gameEngine->window, dt);
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Game editor");


	score();
	gameState();
	pipes();
	bird();


	ImGui::End();

	ImGui::SFML::Render(gameEngine->window);
}

void ImGuiDebug::gameState() {
	ImGui::SeparatorText("Game status");

	switch (gameEngine->state)
	{
	case State::MainMenu:
		if (ImGui::Button("Main Menu")) {
			gameEngine->state = State::Playing;
		}
		break;
	case State::Playing:
		if (ImGui::Button("Playing")) {
			gameEngine->state = State::Paused;
		}
		break;
	case State::Paused:
		if (ImGui::Button("Paused")) {
			gameEngine->state = State::Playing;
		}
		break;
	case State::GameOver:
		if (ImGui::Button("Game Over")) {
			gameEngine->restart();
		}
		break;
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

void ImGuiDebug::score() {
	ImGui::SeparatorText("Score");
	ImGui::Text("Score: %d", gameEngine->scoreManager.getScore());
}