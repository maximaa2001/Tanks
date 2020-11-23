#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System\String.hpp>
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
using namespace sf;
using namespace std;

class Tank {
private:
	Texture tank_texture;
	Sprite tank_sprite;
	float x, y, firstX, firstY, speed, speed_x, speed_y, repeate_shot;
	int w, h, temp;
	int dir;
	bool isLife, isShot, isU, isR, isD, isLe;
	String image;
	Bullet* bullet;
public:
	Tank(String image, float x, float y, int w, int h) {
		this->image = image;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		firstX = x;
		firstY = y;
		tank_texture.loadFromFile("images/" + image);
		tank_sprite.setTexture(tank_texture);
		tank_sprite.setTextureRect(IntRect(23, 31, this->w, this->h));
		tank_sprite.setOrigin(this->w / 2, this->h / 2);
		tank_sprite.setPosition(this->x, this->y);
		repeate_shot = 3000;
		this->dir = 1;
		isShot = false;
		isLife = true;
		isU = true;
		isR = true;
		isD = true;
		isLe = true;
	}

	Sprite getSprite() {
		return tank_sprite;
	}

	Bullet* getBullet() {
		return bullet;
	}

	float getX() {
		return x;
	}

	float getFirstX() {
		return firstX;
	}

	float getY() {
		return y;
	}

	float getFirstY() {
		return firstY;
	}

	bool getIsShot() {
		return isShot;
	}

	void setIsShot(bool isShot) {
		this->isShot = isShot;
	}

	void setRepeatShot(float repeate_shot) {
		this->repeate_shot = repeate_shot;
	}

	int getDir() {
		return dir;
	}

	void setX(float x) {
		this->x = x;
	}

	void setIsLife(bool isLife) {
		this->isLife = isLife;
	}

	void setY(float y) {
		this->y = y;
	}

	int getW() {
		return w;
	}

	int getH() {
		return h;
	}

	bool getIsLife() {
		return isLife;
	}

	void setSpeed(float speed) {
		this->speed = speed;
	}

	void controls(float time, int level, Sound& shot) {
		repeate_shot += time;
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Up) && isU) {
				if (dir == 1 || dir == 3) {
					temp = w;
					w = h;
					h = w;
				}
				dir = 0;
				speed = 0.28;
				tank_sprite.setRotation(-90);
				isR = true;
				isD = true;
				isLe = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) && isR) {
				if (dir == 0 || dir == 2) {
					temp = w;
					w = h;
					h = w;
				}
				dir = 1;
				speed = 0.28;
				tank_sprite.setRotation(0);
				isU = true;
				isD = true;
				isLe = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && isD) {
				if (dir == 1 || dir == 3) {
					temp = w;
					w = h;
					h = w;
				}
				dir = 2;
				speed = 0.28;
				tank_sprite.setRotation(90);
				isR = true;
				isU = true;
				isLe = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left) && isLe) {
				if (dir == 0 || dir == 2) {
					temp = w;
					w = h;
					h = w;
				}
				dir = 3;
				speed = 0.28;
				tank_sprite.setRotation(180);
				isR = true;
				isD = true;
				isU = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (repeate_shot >= 3000) {
					if (!isShot) {
						bullet = new Bullet("bullet.png", this->getX(), this->getY(), 0.5, this->getDir());
						shot.play();
						isShot = true;
						repeate_shot = 0;
					}
				}
			}
		}
		update(time, level);
	}

	void update(float time, int level) {
		switch (dir)
		{
		case 0:
			speed_x = 0;
			speed_y = -speed;
			break;

		case 1:
			speed_x = speed;
			speed_y = 0;
			break;

		case 2:
			speed_x = 0;
			speed_y = speed;
			break;

		case 3:
			speed_x = -speed;
			speed_y = 0;
			break;
		}
		x += time * speed_x;
		y += time * speed_y;
		speed = 0;
		tank_sprite.setPosition(x, y);
		interactionWithMap(level);
	}

	void interactionWithMap(int level) {
		for (int i = y / 50;i < HEIGH_MAP && i < (y + h) / 50 - 1; i++) {
			for (int j = x / 50;j < WIDTH_MAP && j < (x + w) / 50 - 1; j++) {
				if (level == 1) {
					if (level_1[i][j] == '0') {
						if (speed_y > 0) {
							y = i * 50 - h / 2;
							isD = false;
						}
						if (speed_y < 0) {
							y = i * 50 + 75;
							isU = false;
						}
						if (speed_x < 0) {
							x = j * 50 + 75;
							isLe = false;
						}
						if (speed_x > 0) {
							x = j * 50 - w / 2;
							isR = false;
						}
					}
				}
				else if (level == 2) {
					if (level_2[i][j] == '0') {
						if (speed_y > 0) {
							y = i * 50 - h / 2;
							isD = false;
						}
						if (speed_y < 0) {
							y = i * 50 + 75;
							isU = false;
						}
						if (speed_x < 0) {
							x = j * 50 + 75;
							isLe = false;
						}
						if (speed_x > 0) {
							x = j * 50 - w / 2;
							isR = false;
						}
					}
				}
				else if (level == 3) {
					if (level_3[i][j] == '0') {
						if (speed_y > 0) {
							y = i * 50 - h / 2;
							isD = false;
						}
						if (speed_y < 0) {
							y = i * 50 + 75;
							isU = false;
						}
						if (speed_x < 0) {
							x = j * 50 + 75;
							isLe = false;
						}
						if (speed_x > 0) {
							x = j * 50 - w / 2;
							isR = false;
						}
					}
				}
				else if (level == 4) {
					if (level_4[i][j] == '0') {
						if (speed_y > 0) {
							y = i * 50 - h / 2;
							isD = false;
						}
						if (speed_y < 0) {
							y = i * 50 + 75;
							isU = false;
						}
						if (speed_x < 0) {
							x = j * 50 + 75;
							isLe = false;
						}
						if (speed_x > 0) {
							x = j * 50 - w / 2;
							isR = false;
						}
					}
				}
			}
		}
	}
};