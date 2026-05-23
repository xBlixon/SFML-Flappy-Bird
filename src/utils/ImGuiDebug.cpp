#include "ImGuiDebug.h"
#include "game/GameEngine.h"

ImGuiDebug::ImGuiDebug(GameEngine* gameEngine) : gameEngine(gameEngine) {
	ImGui::SFML::Init(gameEngine->window);
}

void ImGuiDebug::show(sf::Time dt) {
	ImGui::SFML::Update(gameEngine->window, dt);
	ImGui::ShowDemoWindow();

	ImGui::Begin("Game editor");


	pauseButton();
	pipeGap();
	birdGravity();


	ImGui::End();

	ImGui::SFML::Render(gameEngine->window);
}

void ImGuiDebug::pauseButton() {
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

void ImGuiDebug::pipeGap() {
	ImGui::SeparatorText("Pipes");
	if ( ImGui::DragFloat("Bottom Y", &gameEngine->entityManager.BottomPipeY, 0.5f) )
	{
		gameEngine->entityManager.updateHeightOfBottomPipes();
	}
}

void ImGuiDebug::birdGravity() {
	ImGui::SeparatorText("Bird");
	ImGui::DragFloat("Gravity", &gameEngine->entityManager.gravityForce, 0.5f);
}