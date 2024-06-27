#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

struct Game {
	bool gameInProgress;

	float levelHeight = 200;
	float levelWidth = 200;

	float playerVerticalPosition = 175;
	float playerHorizontalPosition = 60;
	float playerWidth = 80;
	float playerHeight = 25;

	float fruitVerticalPosition = 100;
	float fruitHorizontalPosition = 10;
	float fruitSize = 25;

	float rotVerticalPosition = 0;
	float rotHorizontalPosition = 0;

	float GetRandomNumber() {
		return rand() % 200 + 1;
	}

	void start() {
		std::cout << "Game start\n";

		srand(time(0));

		sf::RenderWindow window(sf::VideoMode(200, 200), "Game title");

		sf::RectangleShape background(sf::Vector2f(levelWidth, levelHeight));
		background.setFillColor(sf::Color::Blue);

		sf::RectangleShape player(sf::Vector2f(playerWidth, playerHeight));
		player.setFillColor(sf::Color::White);
		player.setPosition(playerHorizontalPosition, playerVerticalPosition);

		sf::CircleShape fruit(fruitSize);
		fruit.setFillColor(sf::Color::Green);
	//	fruit.setPosition(fruitHorizontalPosition, fruitVerticalPosition);
		fruit.setPosition(GetRandomNumber(), GetRandomNumber());

		sf::ConvexShape rot;
		rot.setPointCount(3);
		rot.setPoint(0, sf::Vector2f(0.f, 0.f));
		rot.setPoint(1, sf::Vector2f(40.f, 0.f));
		rot.setPoint(2, sf::Vector2f(20.f, 40.f));
		rot.setFillColor(sf::Color::Red);
		rot.setPosition(GetRandomNumber(), GetRandomNumber());
		rotHorizontalPosition = rot.getPosition().x;
		rotVerticalPosition = rot.getPosition().y;

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::A) player.setPosition(0, 175);
					if (event.key.code == sf::Keyboard::S) player.setPosition(60, 175);
					if (event.key.code == sf::Keyboard::D) player.setPosition(120, 175);
				}
			}

			playerHorizontalPosition = player.getPosition().x;
			playerVerticalPosition = player.getPosition().y;

			fall();

			fruit.setPosition(fruitHorizontalPosition, fruitVerticalPosition);
			rot.setPosition(rotHorizontalPosition, rotVerticalPosition);

			if (collision()) {
				std::cout << "Collision detected\n";
			}

			window.clear();
			window.draw(background);
			window.draw(player);
			window.draw(fruit);
			window.draw(rot);
			window.display();
		}
	}

	bool collision() const {
		bool collisionX = playerHorizontalPosition < fruitHorizontalPosition + fruitSize &&
			playerHorizontalPosition + playerWidth > fruitHorizontalPosition;
		bool collisionY = playerVerticalPosition < fruitVerticalPosition + fruitSize &&
			playerVerticalPosition + playerHeight > fruitVerticalPosition;
		return collisionX && collisionY;
	}

	void fall() {
		if (fruitVerticalPosition <= 190 && gameInProgress) {
			fruitVerticalPosition += 0.02f;
		}
		else {
			fruitVerticalPosition = 0;
			fruitHorizontalPosition = GetRandomNumber();
		}

		if (rotVerticalPosition <= 190 && gameInProgress) {
			rotVerticalPosition += 0.02f;
		}
		else {
			rotVerticalPosition = 0;
			rotHorizontalPosition = GetRandomNumber();
		}
	}
};
