#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System\String.hpp>
#include "Map.h"
#include "Enemy.h"
#include <list>
using namespace sf;
using namespace std;

class Bullet {
private:
	Texture bullet_texture;
	Sprite bullet_sprite;
	float x, y, speed, speed_x, speed_y;
	int dir;
	String image;

public:
	Bullet(String image, float x, float y, float speed, float dir) {
		if (dir == 0) {
			this->x = x;
			this->y = y - 38;
		}
		else if (dir == 1) {
			this->x = x + 38;
			this->y = y;
		}
		else if (dir == 2) {
			this->x = x;
			this->y = y + 38;
		}
		else if (dir == 3) {
			this->x = x - 38;
			this->y = y;
		}
		this->speed = speed;
		this->dir = dir;
		bullet_texture.loadFromFile("images/" + image);
		bullet_sprite.setTexture(bullet_texture);
		bullet_sprite.setOrigin(5, 9.5);

	}

	void update(float time) {
		switch (dir)
		{
		case 0:speed_x = 0; speed_y = -speed;break;
		case 1:speed_x = speed; speed_y = 0; bullet_sprite.setRotation(90); break;
		case 2:speed_x = 0; speed_y = speed;bullet_sprite.setRotation(180);break;
		case 3:speed_x = -speed; speed_y = 0;bullet_sprite.setRotation(-90);break;
		}
		x += speed_x * time;
		y += speed_y * time;
		bullet_sprite.setPosition(x, y);
	}


	Sprite getSprite() {
		return bullet_sprite;
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}
};