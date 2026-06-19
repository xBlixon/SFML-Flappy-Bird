cmake_minimum_required(VERSION 3.28)
project(FlappyBird LANGUAGES CXX)

add_subdirectory(dependencies)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(main 
	src/main.cpp
	src/utils/ISConvert.h
	src/game/GameEngine.h
	src/game/EntityManager.h
	src/game/EntityManager.cpp
	src/game/ScoreManager.h
	src/game/State.h
	src/game/UserEventsHandler.h
	src/game/UserEventsHandler.cpp
	src/game/GameObject.h
	src/game/Bird.h
	src/game/Pipe.h
	src/utils/ImGuiDebug.h
	src/utils/ImGuiDebug.cpp
	src/game/Obstacle.h
	src/game/Menu.h
	src/game/Concepts.h
	src/game/GameResult.h
)
target_include_directories(main PRIVATE ${imgui_SOURCE_DIR} src)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)