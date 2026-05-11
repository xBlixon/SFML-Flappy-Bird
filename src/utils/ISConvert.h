#pragma once

#include <cstdint>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

/*
* ISConvert - [I]mgui [S]fml [Convert]
*/
namespace ISConvert
{
	// Convert a sf::Color to an ImGui color (ImVec4)
	ImVec4 sfColorToImVec4(const sf::Color& color)
	{
		return ImVec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	// Convert an ImGui color (ImVec4) to a sf::Color
	sf::Color imVec4ToSfColor(const ImVec4& color)
	{
		return sf::Color(
			static_cast<std::uint8_t>(color.x * 255), 
			static_cast<std::uint8_t>(color.y * 255), 
			static_cast<std::uint8_t>(color.z * 255), 
			static_cast<std::uint8_t>(color.w * 255)
		);
	}
}