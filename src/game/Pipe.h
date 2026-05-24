#pragma once

#include "GameObject.h"

class Pipe : public GameObject
{
private:
    float speed = 100.f;
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
        float x;
        if (closer) {
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
        float x;
        if (closer) {
            x = initialX * 0.5;
        }
        else {
            x = initialX;
        }
        pipe.sprite.setPosition({x, height});
        return pipe;
    }
};