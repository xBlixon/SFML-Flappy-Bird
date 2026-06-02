#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
private:
    float speed = 100.f;
	float isCloser = false;
    static constexpr float initialX = 400.f;
    static constexpr float width = 20.f;
    static constexpr float height = 50.f;

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
        pipe.sprite.setPosition({x, 0});
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
        pipe.sprite.setPosition({x, height});
        return pipe;
    }

    void reset() {
        if (isCloser) {
            sprite.setPosition({ initialX * 0.5f, sprite.getPosition().y });
        }
        else {
            sprite.setPosition({ initialX, sprite.getPosition().y });
        }
	}
};