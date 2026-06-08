#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
private:
    float speed = 100.f;
	float isCloser = false;
    static constexpr float initialX = 400.f;
    static constexpr float width = 20.f;
    static constexpr float height = 500.f;

    Pipe() {
        sprite.setSize({ width, height });
        sprite.setFillColor(sf::Color::Green);
    }
public:
    void update(float dt) override {
        sprite.move({ -speed * dt, 0.f });
    }

    static Pipe TopPipe(bool closer) {
        Pipe pipe;
		pipe.isCloser = closer;
        float x;
        if (pipe.isCloser) {
			x = initialX * 0.5;
        }
        else {
			x = initialX;
        }
        return pipe;
    }

    static Pipe BottomPipe(bool closer) {
        Pipe pipe;
        pipe.isCloser = closer;
        float x;
        if (pipe.isCloser) {
            x = initialX * 0.5;
        }
        else {
            x = initialX;
        }
        return pipe;
    }

    void reset() {
        if (isCloser) {
            sprite.setPosition({ initialX * 0.5f, getPosition().y });
        }
        else {
            sprite.setPosition({ initialX, getPosition().y });
        }
	}
};