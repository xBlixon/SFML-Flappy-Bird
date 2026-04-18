cmake_minimum_required(VERSION 3.28)
project(FlappyBird LANGUAGES CXX)

add_subdirectory(dependencies)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE ${imgui_SOURCE_DIR})
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)