#pragma once

#include "GameObject.h"
#include <thread>
#include <atomic>
#include <chrono>

class Pipe : public GameObject
{
public:
    enum Type { Top, Bottom };
    enum class AnimState { None, FadingIn, FadingOut };

private:
    float speed = 100.f;
    float isCloser = false;
    static constexpr float initialX = 400.f;
    static constexpr float width = 30.f;
    static constexpr float height = 600.f;

    std::atomic<int> targetAlpha{ 255 };
    std::atomic<AnimState> currentAnim{ AnimState::None };

public:
    Pipe(Type type, bool closer) {
        sprite.setSize({ width, height });
        sprite.setFillColor(sf::Color::Green);
        isCloser = closer;

        if (type == Top) {
            sprite.setOrigin({ width, height });
        }
        else if (type == Bottom) {
            sprite.setOrigin({ width, 0.f });
        }
    }

    void update(float dt) override {
        sprite.move({ -speed * dt, 0.f });

        sf::Color color = sprite.getFillColor();
        color.a = static_cast<std::uint8_t>(targetAlpha.load());
        sprite.setFillColor(color);
    }

    void fadeOut(float seconds) {
        if (currentAnim == AnimState::FadingOut) return;

        currentAnim = AnimState::FadingOut;

        int steps = 51;
        float stepTimeMs = (seconds * 1000.f) / steps;

        std::thread([this, stepTimeMs]() {
            targetAlpha = 255;
            while (currentAnim == AnimState::FadingOut && targetAlpha > 0) {
                targetAlpha -= 5;
                if (targetAlpha < 0) targetAlpha = 0;
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(stepTimeMs)));
            }
            if (currentAnim == AnimState::FadingOut) currentAnim = AnimState::None;
            }).detach();
    }

    void fadeIn(float seconds) {
        if (currentAnim == AnimState::FadingIn) return;

        currentAnim = AnimState::FadingIn;
        targetAlpha = 0;

        int steps = 51;
        float stepTimeMs = (seconds * 1000.f) / steps;

        std::thread([this, stepTimeMs]() {
            while (currentAnim == AnimState::FadingIn && targetAlpha < 255) {
                targetAlpha += 5;
                if (targetAlpha > 255) targetAlpha = 255;
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(stepTimeMs)));
            }
            if (currentAnim == AnimState::FadingIn) currentAnim = AnimState::None;
            }).detach();
    }

    void reset() {
        currentAnim = AnimState::None;
        targetAlpha = 255;
        sprite.setFillColor(sf::Color::Green);

        if (isCloser) {
            sprite.setPosition({ initialX * 0.5f, getPosition().y });
        }
        else {
            sprite.setPosition({ initialX, getPosition().y });
        }
    }
};