#pragma once

#include <random>
#include "Pipe.h"


class Obstacle
{
private:
	float verticalOffset;
	float resetBoundary = -60.f;
	float gap = 100.f;
	std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> distribution{ -150.f, 150.f };

	Pipe topPipe;
	Pipe bottomPipe;

public:
	Obstacle(bool closer) 
		: topPipe (Pipe::TopPipe   (closer)), 
		bottomPipe(Pipe::BottomPipe(closer))
	{
		rerollVerticalOffset();
		//topPipe.sprite.move(
		//	{
		//		0.f,
		//		verticalOffset - gap / 2
		//	}
		//);
		//bottomPipe.sprite.move(
		//	{
		//		0.f,
		//		verticalOffset + gap / 2
		//	}
		//);
	};

	void draw(sf::RenderWindow& window) {
		topPipe.draw(window);
		bottomPipe.draw(window);
	}

	void rerollVerticalOffset() {
		verticalOffset = distribution(rng);
	}

	void setGap(float gap) {
		this->gap = gap;

		topPipe.setPosition(
			{
				topPipe.getPosition().x,
				-topPipe.sprite.getSize().y + verticalOffset - this->gap / 2
			}
		);

		bottomPipe.setPosition(
			{
				bottomPipe.getPosition().x,
				this->gap/2 + verticalOffset
			}
			);
	}

	void update(float dt) {
		float resetPositionX = 400.f;
		topPipe.update(dt);
		bottomPipe.update(dt);
		if (topPipe.getPosition().x < resetBoundary) {
			rerollVerticalOffset();

			topPipe.setPosition(
				{
					resetPositionX,
					-topPipe.sprite.getSize().y + verticalOffset - gap / 2
				}
			);

			bottomPipe.setPosition(
				{ 
					resetPositionX,
					verticalOffset + gap / 2
				}
			);
		}
	}

	Pipe& getTopPipe() {
		return topPipe;
	}

	Pipe& getBottomPipe() {
		return bottomPipe;
	}

	void reset() {
		rerollVerticalOffset();
		topPipe.reset();
		bottomPipe.reset();
		setGap(gap); // Update vertical offset after resetting position
	}
};