#pragma once

#include <concepts>

#include <SFML/Graphics/RenderWindow.hpp>

template <typename T>
concept Renderable = requires(T object, sf::RenderWindow & window) {
    { object.draw(window) } -> std::same_as<void>;
};