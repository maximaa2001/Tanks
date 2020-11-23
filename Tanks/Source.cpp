#pragma warning(disable : 4996) .
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System\String.hpp>
#include "Tank.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include <list>
#include <iostream>
#include <ctime>
#include <sstream>


using namespace sf;
using namespace std;

int randDirX();
int randDirY();
bool isBarrierY(float x, float enemyY, float heroY, int& level);
bool isBarrierX(float y, float enemyX, float heroX, int& level);
void interactionWithMap(list<Bullet*>& list, int& level);
void interactionWithMap(Bullet* bullet, Tank& hero, list<Enemy*>& list, int& level);
void interectionWithHero(list<Bullet*>& list, Tank& hero);
void loadMenu(RenderWindow& window, int& menu, RectangleShape& rectangle, float& time, bool& isMenu, Tank& hero);
void destructionHero(RenderWindow& window, Tank& hero, bool& isMenu, Music& gameOver, bool& isPlayGameOver);



int wWinMain(int args, wchar_t* argc[])
{
	RenderWindow window(VideoMode(1200, 800), "Tanks");
	Tank hero("tank.png", 150, 70, 75, 52);

	Texture map_texture;
	map_texture.loadFromFile("images/map.png");

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	RectangleShape rectangle(Vector2f(285, 50));
	rectangle.setFillColor(Color::Red);

	SoundBuffer bufferShotHero;
	bufferShotHero.loadFromFile("music/ShotHero.ogg");
	Sound shotHero(bufferShotHero);

	SoundBuffer bufferShotEnemy;
	bufferShotEnemy.loadFromFile("music/ShotEnemy.ogg");
	Sound shotEnemy(bufferShotEnemy);

	Music gameOverMus;
	gameOverMus.openFromFile("music/GameOver.ogg");
	bool isPlayGameOver = false;

	Music youWinMus;
	youWinMus.openFromFile("music/YouWin.ogg");
	bool isPlayYouWin = false;

	Clock clock;
	float time;
	float timeShotEnemy = 3000;
	float timePressed = 0;
	float readyGamer = 0;
	float timeLevelCompleted = 0;
	bool LevelCompleted = false;
	int level = 1;
	const int MAX_LEVEL = 4;
	Vector2f vector_hero;
	Vector2f vector_enemy;

	list<Enemy*> enemyes;
	list<Bullet*> bullets;
	list<Bullet*>::iterator iterator_bul;
	list<Enemy*>::iterator iterator;
	list<Enemy*>::iterator iterator_2;
	bool isClash;
	bool startGame = false;
	bool loadEnemy = false;
	bool isMenu = true;
	int menu = 1;

	Font font;
	font.loadFromFile("DS Stamper.ttf");

	while (window.isOpen())
	{
		while (isMenu && window.isOpen()) {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
			}
			enemyes.clear();
			bullets.clear();
			isPlayGameOver = false;
			isPlayYouWin = false;
			loadEnemy = false;
			level = 1;
			float t = clock.getElapsedTime().asMicroseconds();
			t = t / 800;
			clock.restart();
			timePressed += t;
			loadMenu(window, menu, rectangle, timePressed, isMenu, hero);
			readyGamer = 0;
		}
		time = clock.getElapsedTime().asMicroseconds();
		time = time / 800;
		clock.restart();

		timeShotEnemy += time;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/*
		* Загрузка первого уровня
		*/
		if (level == 1) {
			for (int i = 0; i < HEIGH_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (level_1[i][j] == '0') {
						map_sprite.setTextureRect(IntRect(0, 0, 50, 50));
					}
					if (level_1[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(50, 0, 50, 50));
					}
					map_sprite.setPosition(j * 50, i * 50);

					window.draw(map_sprite);
				}
			}
			/*
			* Загрузка врагов(добавление их в список)
			*/
			if (!loadEnemy) {
				enemyes.push_back(new Enemy("tank.png", 350, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 600, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 500, 700, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 850, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1050, 700, 75, 52, 0, 0.15));
				loadEnemy = true;
			}
		}
		/*
		* Загрузка второго уровня
		*/

		else if (level == 2) {
			for (int i = 0; i < HEIGH_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (level_2[i][j] == '0') {
						map_sprite.setTextureRect(IntRect(0, 0, 50, 50));
					}
					if (level_2[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(50, 0, 50, 50));
					}
					map_sprite.setPosition(j * 50, i * 50);

					window.draw(map_sprite);
				}
			}
			/*
			* Загрузка врагов(добавление их в список)
			*/
			if (!loadEnemy) {
				enemyes.push_back(new Enemy("tank.png", 600, 100, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 600, 700, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 650, 450, 75, 52, 0, 0.15));
				enemyes.push_back(new Enemy("tank.png", 800, 70, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 800, 700, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 450, 75, 52, 3, 0.15));
				loadEnemy = true;
			}
		}
		/*
		* Загрузка третьего уровня
		*/
		else if (level == 3) {
			for (int i = 0; i < HEIGH_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (level_3[i][j] == '0') {
						map_sprite.setTextureRect(IntRect(0, 0, 50, 50));
					}
					if (level_3[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(50, 0, 50, 50));
					}
					map_sprite.setPosition(j * 50, i * 50);

					window.draw(map_sprite);
				}
			}
			/*
			* Загрузка врагов(добавление их в список)
			*/
			if (!loadEnemy) {
				enemyes.push_back(new Enemy("tank.png", 100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 300, 730, 75, 52, 0, 0.15));
				enemyes.push_back(new Enemy("tank.png", 900, 730, 75, 52, 0, 0.15));
				loadEnemy = true;
			}
		}
		/*
		* Загрузка четвертого уровня
		*/
		else if (level == 4) {
			for (int i = 0; i < HEIGH_MAP; i++) {
				for (int j = 0; j < WIDTH_MAP; j++) {
					if (level_4[i][j] == '0') {
						map_sprite.setTextureRect(IntRect(0, 0, 50, 50));
					}
					if (level_4[i][j] == ' ') {
						map_sprite.setTextureRect(IntRect(50, 0, 50, 50));
					}
					map_sprite.setPosition(j * 50, i * 50);

					window.draw(map_sprite);
				}
			}
			/*
			* Загрузка врагов(добавление их в список)
			*/
			if (!loadEnemy) {
				enemyes.push_back(new Enemy("tank.png", 100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 450, 70, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 650, 70, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 950, 280, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 100, 730, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 730, 75, 52, 3, 0.15));
				loadEnemy = true;
			}
		}
		Text timeToStartGame("", font, 100);
		timeToStartGame.setColor(Color::Red);
		timeToStartGame.setStyle(Text::Bold);
		readyGamer += time;
		if (readyGamer > 0 && readyGamer < 1000) {
			timeToStartGame.setString("3");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 1000 && readyGamer < 2000) {
			timeToStartGame.setString("2");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 2000 && readyGamer < 3000) {
			timeToStartGame.setString("1");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 3000 && readyGamer < 4000) {
			timeToStartGame.setString("Go");
			timeToStartGame.setPosition(520, 350);
			window.draw(timeToStartGame);
			startGame = true;
			hero.setIsLife(true);
		}
		if (startGame && hero.getIsLife()) {
			hero.controls(time, level, shotHero);// управление героем, его движение и взаимодействие с картой
			/*
			* Проверка выстелил ли герой
			*/
			if (hero.getIsShot()) {
				hero.getBullet()->update(time);// если выстрелил, движение пули
				interactionWithMap(hero.getBullet(), hero, enemyes, level); // взаимодействие пули с картой и врагами
				window.draw(hero.getBullet()->getSprite());// отображение пули
			}

			for (iterator = enemyes.begin();iterator != enemyes.end();iterator++) {
				(*iterator)->updateEnemy(time);//движение врагов
				(*iterator)->incRepeatShot(time);// инкремент времени выстрела
				bool isNotWall = (*iterator)->interactionWithMap(level);// проверка врезался ли враг в стену
				if (!isNotWall) {// если не врезался

					/*
					* движение врага влево или вправо при одинаковой координате X
					*/
					if ((*iterator)->getX() > hero.getX() - hero.getW() / 2 && (*iterator)->getX() < hero.getX() + hero.getW() / 2 && !isBarrierY((*iterator)->getX(), (*iterator)->getY(), hero.getY(), level)) {//остановка при наличии героя на одной линии
						if (hero.getY() > (*iterator)->getY()) {
							(*iterator)->setDir(2);
							(*iterator)->setSpeed(0);// остановка и выстрел при находжении героя
							if ((*iterator)->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", (*iterator)->getX(), (*iterator)->getY(), 0.5, (*iterator)->getDir()));
								shotEnemy.play();
								(*iterator)->setRepeatShot(0);
							}
						}
						if (hero.getY() < (*iterator)->getY()) {
							(*iterator)->setDir(0);
							(*iterator)->setSpeed(0);// остановка и выстрел при находжении героя
							if ((*iterator)->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", (*iterator)->getX(), (*iterator)->getY(), 0.5, (*iterator)->getDir()));
								shotEnemy.play();
								(*iterator)->setRepeatShot(0);
							}
						}
						(*iterator)->setIsTurnX(true);
					}
					else {
						/*
						* вернуться к движению вдоль оси ОХ
						*/
						if ((*iterator)->getIsTurnX()) {
							(*iterator)->setDir(randDirX());
							(*iterator)->setSpeed(0.15);
							(*iterator)->setIsTurnX(false);
						}
					}
					/*
					*движение врага вверх и вниз при одинаковой координате Y
					*/
					if ((*iterator)->getY() > hero.getY() - hero.getH() / 2 && (*iterator)->getY() < hero.getY() + hero.getH() / 2 && !isBarrierX((*iterator)->getY(), (*iterator)->getX(), hero.getX(), level)) {//остановка при наличии героя на одной линии
						if (hero.getX() > (*iterator)->getX()) {
							(*iterator)->setDir(1);
							(*iterator)->setSpeed(0);// остановка и выстрел при находжении героя
							if ((*iterator)->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", (*iterator)->getX(), (*iterator)->getY(), 0.5, (*iterator)->getDir()));
								shotEnemy.play();
								(*iterator)->setRepeatShot(0);
							}
						}
						if (hero.getX() < (*iterator)->getX()) {
							(*iterator)->setDir(3);
							(*iterator)->setSpeed(0);// остановка и выстрел при находжении героя
							if ((*iterator)->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", (*iterator)->getX(), (*iterator)->getY(), 0.5, (*iterator)->getDir()));
								shotEnemy.play();
								(*iterator)->setRepeatShot(0);
							}
						}
						(*iterator)->setIsTurnY(true);
					}
					else {
						/*
						* вернуться к движению вдоль оси OY
						*/
						if ((*iterator)->getIsTurnY()) {
							(*iterator)->setDir(randDirY());
							(*iterator)->setSpeed(0.15);
							(*iterator)->setIsTurnY(false);
						}
					}
				}
			}
			for (iterator_bul = bullets.begin();iterator_bul != bullets.end();iterator_bul++) {//перебор всех вражеских пуль
				(*iterator_bul)->update(time);//движение пуль
				window.draw((*iterator_bul)->getSprite());//отображение пули
			}
			interactionWithMap(bullets, level);// их взаимодействие с картой
			interectionWithHero(bullets, hero);// их взаимодействие с героем
			for (iterator = enemyes.begin(); iterator != enemyes.end();iterator++) { //столкновения врагов
				switch ((*iterator)->getDir())
				{
				case 0: vector_enemy.x = (*iterator)->getX();
					vector_enemy.y = (*iterator)->getY() - (*iterator)->getH() / 2;
					break;
				case 1: vector_enemy.x = (*iterator)->getX() + (*iterator)->getW() / 2;
					vector_enemy.y = (*iterator)->getY();
					break;
				case 2: vector_enemy.x = (*iterator)->getX();
					vector_enemy.y = (*iterator)->getY() + (*iterator)->getH() / 2;
					break;
				case 3: vector_enemy.x = (*iterator)->getX() - (*iterator)->getW() / 2;
					vector_enemy.y = (*iterator)->getY();
					break;
				}
				isClash = false;
				for (int i = vector_enemy.x - (*iterator)->getW() / 2;i <= vector_enemy.x + (*iterator)->getW() / 2;i++) {
					for (int j = vector_enemy.y - (*iterator)->getH() / 2;j <= vector_enemy.y + (*iterator)->getH() / 2;j++) {
						iterator_2 = iterator;
						iterator_2++;
						while (iterator_2 != enemyes.end()) {
							if (i >= (*iterator_2)->getX() - (*iterator_2)->getW() / 2 && i <= (*iterator_2)->getX() + (*iterator_2)->getW() / 2 &&
								j >= (*iterator_2)->getY() - (*iterator_2)->getH() / 2 && j <= (*iterator_2)->getY() + (*iterator_2)->getH() / 2) {

								if ((*iterator)->getDir() == 0 || (*iterator)->getDir() == 2) {
									(*iterator)->setDir(randDirX());

								}
								else if ((*iterator)->getDir() == 1 || (*iterator)->getDir() == 3) {
									(*iterator)->setDir(randDirY());
								}

								if ((*iterator_2)->getDir() == 0 || (*iterator_2)->getDir() == 2) {
									(*iterator_2)->setDir(randDirX());
								}
								else if ((*iterator_2)->getDir() == 1 || (*iterator_2)->getDir() == 3) {
									(*iterator_2)->setDir(randDirY());

								}

							}
							iterator_2++;
						}
					}
					if (isClash) {
						break;
					}
				}
			}

			for (iterator = enemyes.begin(); iterator != enemyes.end();iterator++) { // столкновения героя и врагов
				switch (hero.getDir())
				{
				case 0: vector_hero.x = hero.getX();
					vector_hero.y = hero.getY() - hero.getH() / 2;
					break;
				case 1: vector_hero.x = hero.getX() + hero.getW() / 2;
					vector_hero.y = hero.getY();
					break;
				case 2: vector_hero.x = hero.getX();
					vector_hero.y = hero.getY() + hero.getH() / 2;
					break;
				case 3: vector_hero.x = hero.getX() - hero.getW() / 2;
					vector_hero.y = hero.getY();
					break;
				}
				isClash = false;
				for (int i = vector_hero.x - hero.getW() / 2;i <= vector_hero.x + hero.getW() / 2;i++) {
					for (int j = vector_hero.y - hero.getH() / 2;j <= vector_hero.y + hero.getH() / 2;j++) {
						if (i >= (*iterator)->getX() - (*iterator)->getW() / 2 && i <= (*iterator)->getX() + (*iterator)->getW() / 2 &&
							j >= (*iterator)->getY() - (*iterator)->getH() / 2 && j <= (*iterator)->getY() + (*iterator)->getH() / 2) {
							if (hero.getDir() == 0) {
								hero.setY(hero.getY() + 0.5);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 1) {
								hero.setX(hero.getX() - 0.5);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 2) {
								hero.setY(hero.getY() - 0.5);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 3) {
								hero.setX(hero.getX() + 0.5);
								isClash = true;
								break;
							}
						}
					}
					if (isClash) {
						break;
					}
				}
			}
			if (enemyes.size() == 0) {
				startGame = false;
				bullets.clear();
				LevelCompleted = true;
				timeLevelCompleted = 0;
			}
		}
		if (LevelCompleted) {
			if (level < MAX_LEVEL) {
				Text levelCompleted("Level completed", font, 70);
				levelCompleted.setColor(Color::Red);
				levelCompleted.setStyle(Text::Bold);
				levelCompleted.setPosition(300, 380);
				timeLevelCompleted += time;
				hero.setRepeatShot(3000);
				if (timeLevelCompleted < 3000) {
					window.draw(levelCompleted);
				}
				else {
					readyGamer = 0;
					LevelCompleted = false;
					level++;
					loadEnemy = false;
					if (level == 2) {
						hero.setX(100);
						hero.setY(100);
					}
					else if (level == 3) {
						hero.setX(600);
						hero.setY(500);
					}
					else if (level == 4) {
						hero.setX(550);
						hero.setY(650);
					}
				}
			}
			else if (level == MAX_LEVEL) {
				if (!isPlayYouWin) {
					youWinMus.play();
					youWinMus.setLoop(true);
					isPlayYouWin = true;
				}
				Text YouWin("You Win", font, 100);
				Text Continue("Press ESCAPE to exit in main menu", font, 30);
				YouWin.setColor(Color::Red);
				Continue.setColor(Color::White);
				YouWin.setStyle(Text::Bold);
				Continue.setStyle(Text::Bold);
				YouWin.setPosition(400, 350);
				Continue.setPosition(350, 450);
				window.draw(YouWin);
				window.draw(Continue);
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					isMenu = true;
					LevelCompleted = false;
					youWinMus.stop();
				}
			}
		}
		if (hero.getIsLife() && startGame) {
			window.draw(hero.getSprite());
			for (iterator = enemyes.begin(); iterator != enemyes.end();iterator++) {
				window.draw((*iterator)->getSprite());
			}
		}
		if (!hero.getIsLife()) {
			startGame = false;
			destructionHero(window, hero, isMenu, gameOverMus, isPlayGameOver);
			if (!isPlayGameOver) {
				gameOverMus.play();
				gameOverMus.setLoop(true);
				isPlayGameOver = true;
			}

		}
		window.display();
	}
	return 0;
}

int randDirX() {// рандомное движение вдоль оси OX
	int number = rand() % 2;
	if (number == 0) {
		number = 3;
	}
	return number;
}

int randDirY() {// рандомное движение вдоль оси OY
	int number = rand() % 2;
	if (number == 1) {
		number = 2;
	}
	return number;
}

bool isBarrierY(float x, float enemyY, float heroY, int& level) {// проверка на наличие препятствия вдоль оси OY
	bool isBarrierY = false;
	int enemyX = x / 50;
	if (level == 1) {
		if (enemyY / 50 < heroY / 50) {
			for (int i = enemyY / 50; i < heroY / 50;i++) {
				if (level_1[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
		else if (heroY / 50 < enemyY / 50) {
			for (int i = heroY / 50; i < enemyY / 50;i++) {
				if (level_1[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
	}
	else if (level == 2) {
		if (enemyY / 50 < heroY / 50) {
			for (int i = enemyY / 50; i < heroY / 50;i++) {
				if (level_2[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
		else if (heroY / 50 < enemyY / 50) {
			for (int i = heroY / 50; i < enemyY / 50;i++) {
				if (level_2[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
	}
	else if (level == 3) {
		if (enemyY / 50 < heroY / 50) {
			for (int i = enemyY / 50; i < heroY / 50;i++) {
				if (level_3[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
		else if (heroY / 50 < enemyY / 50) {
			for (int i = heroY / 50; i < enemyY / 50;i++) {
				if (level_3[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
	}
	else if (level == 4) {
		if (enemyY / 50 < heroY / 50) {
			for (int i = enemyY / 50; i < heroY / 50;i++) {
				if (level_4[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
		else if (heroY / 50 < enemyY / 50) {
			for (int i = heroY / 50; i < enemyY / 50;i++) {
				if (level_4[i][enemyX] == '0') {
					isBarrierY = true;
					break;
				}
			}
		}
	}
	return isBarrierY;
}

bool isBarrierX(float y, float enemyX, float heroX, int& level) {// проверка на наличие препятствия вдоль оси OX
	bool isBarrierX = false;
	int enemyY = y / 50;
	if (level == 1) {
		if (enemyX / 50 < heroX / 50) {
			for (int i = enemyX / 50; i < heroX / 50;i++) {
				if (level_1[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
		else if (heroX / 50 < enemyX / 50) {
			for (int i = heroX / 50; i < enemyX / 50;i++) {
				if (level_1[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
	}
	else if (level == 2) {
		if (enemyX / 50 < heroX / 50) {
			for (int i = enemyX / 50; i < heroX / 50;i++) {
				if (level_2[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
		else if (heroX / 50 < enemyX / 50) {
			for (int i = heroX / 50; i < enemyX / 50;i++) {
				if (level_2[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
	}
	else if (level == 3) {
		if (enemyX / 50 < heroX / 50) {
			for (int i = enemyX / 50; i < heroX / 50;i++) {
				if (level_3[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
		else if (heroX / 50 < enemyX / 50) {
			for (int i = heroX / 50; i < enemyX / 50;i++) {
				if (level_3[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}

	}
	else if (level == 4) {
		if (enemyX / 50 < heroX / 50) {
			for (int i = enemyX / 50; i < heroX / 50;i++) {
				if (level_4[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
		else if (heroX / 50 < enemyX / 50) {
			for (int i = heroX / 50; i < enemyX / 50;i++) {
				if (level_4[enemyY][i] == '0') {
					isBarrierX = true;
					break;
				}
			}
		}
	}
	return isBarrierX;
}

void interactionWithMap(list<Bullet*>& list, int& level) {// взаимодействие с картой вражеских пуль
	auto iterator = list.begin();
	while (iterator != list.end()) {
		int i = (*iterator)->getY() / 50;
		int j = (*iterator)->getX() / 50;
		if (level == 1) {
			if (level_1[i][j] == '0') {
				delete* iterator;
				list.erase(iterator);
			}
		}
		else if (level == 2) {
			if (level_2[i][j] == '0') {
				delete* iterator;
				list.erase(iterator);
			}
		}
		else if (level == 3) {
			if (level_3[i][j] == '0') {
				delete* iterator;
				list.erase(iterator);
			}
		}
		else if (level == 4) {
			if (level_4[i][j] == '0') {
				delete* iterator;
				list.erase(iterator);
			}
		}
		iterator++;
	}
}
void interectionWithHero(list<Bullet*>& list, Tank& hero) {
	auto iterator = list.begin();
	while (iterator != list.end()) {
		if ((*iterator)->getX() >= hero.getX() - hero.getW() / 2 && (*iterator)->getX() <= hero.getX() + hero.getW() / 2 &&
			(*iterator)->getY() >= hero.getY() - hero.getH() / 2 && (*iterator)->getY() <= hero.getY() + hero.getW() / 2) {
			if (hero.getIsShot()) {
				delete hero.getBullet();
				hero.setIsShot(false);
			}
			hero.setIsLife(false);
		}
		iterator++;
	}
}

void interactionWithMap(Bullet* bullet, Tank& hero, list<Enemy*>& list, int& level) {// взаимодействие с картой пуль героя
	int i = (bullet)->getY() / 50;
	int j = (bullet)->getX() / 50;
	if (level == 1) {
		if (level_1[i][j] == '0') {
			delete bullet;
			hero.setIsShot(false);
		}
		else {
			auto iterator = list.begin();
			while (iterator != list.end()) {
				if (bullet->getX() >= (*iterator)->getX() - (*iterator)->getW() / 2 && bullet->getX() <= (*iterator)->getX() + (*iterator)->getW() / 2 &&
					bullet->getY() >= (*iterator)->getY() - (*iterator)->getH() / 2 && bullet->getY() <= (*iterator)->getY() + (*iterator)->getH() / 2) {
					delete* iterator;
					list.erase(iterator);
					delete bullet;
					hero.setIsShot(false);
					break;
				}
				iterator++;
			}
		}
	}
	else if (level == 2) {
		if (level_2[i][j] == '0') {
			delete bullet;
			hero.setIsShot(false);
		}
		else {
			auto iterator = list.begin();
			while (iterator != list.end()) {
				if (bullet->getX() >= (*iterator)->getX() - (*iterator)->getW() / 2 && bullet->getX() <= (*iterator)->getX() + (*iterator)->getW() / 2 &&
					bullet->getY() >= (*iterator)->getY() - (*iterator)->getH() / 2 && bullet->getY() <= (*iterator)->getY() + (*iterator)->getH() / 2) {
					delete* iterator;
					list.erase(iterator);
					delete bullet;
					hero.setIsShot(false);
					break;
				}
				iterator++;
			}
		}
	}
	else if (level == 3) {
		if (level_3[i][j] == '0') {
			delete bullet;
			hero.setIsShot(false);
		}
		else {
			auto iterator = list.begin();
			while (iterator != list.end()) {
				if (bullet->getX() >= (*iterator)->getX() - (*iterator)->getW() / 2 && bullet->getX() <= (*iterator)->getX() + (*iterator)->getW() / 2 &&
					bullet->getY() >= (*iterator)->getY() - (*iterator)->getH() / 2 && bullet->getY() <= (*iterator)->getY() + (*iterator)->getH() / 2) {
					delete* iterator;
					list.erase(iterator);
					delete bullet;
					hero.setIsShot(false);
					break;
				}
				iterator++;
			}
		}
	}
	else if (level == 4) {
		if (level_4[i][j] == '0') {
			delete bullet;
			hero.setIsShot(false);
		}
		else {
			auto iterator = list.begin();
			while (iterator != list.end()) {
				if (bullet->getX() >= (*iterator)->getX() - (*iterator)->getW() / 2 && bullet->getX() <= (*iterator)->getX() + (*iterator)->getW() / 2 &&
					bullet->getY() >= (*iterator)->getY() - (*iterator)->getH() / 2 && bullet->getY() <= (*iterator)->getY() + (*iterator)->getH() / 2) {
					delete* iterator;
					list.erase(iterator);
					delete bullet;
					hero.setIsShot(false);
					break;
				}
				iterator++;
			}
		}
	}
}

void loadMenu(RenderWindow& window, int& menu, RectangleShape& rectangle, float& time, bool& isMenu, Tank& hero) {
	if (menu == 1) {
		rectangle.setPosition(790, 300);
	}
	Texture menu_tank, fon;
	menu_tank.loadFromFile("images/menu_tank.png");
	fon.loadFromFile("images/fon.jpg");
	Sprite menu_1(menu_tank);
	Sprite fon_sprite(fon);
	menu_1.setPosition(100, 100);
	fon_sprite.setPosition(0, 0);
	Font font;
	font.loadFromFile("DS Stamper.ttf");
	Text StartGame("Начать игру", font, 40);
	Text AboutGame("Об игре", font, 40);
	Text Exit("Выход", font, 40);
	StartGame.setColor(Color::White);
	AboutGame.setColor(Color::White);
	Exit.setColor(Color::White);
	StartGame.setStyle(Text::Bold);
	AboutGame.setStyle(Text::Bold);
	Exit.setStyle(Text::Bold);
	StartGame.setPosition(800, 300);
	AboutGame.setPosition(840, 380);
	Exit.setPosition(860, 460);
	if (Keyboard::isKeyPressed) {
		if (time > 200) {
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				if (menu == 1) {
					rectangle.setPosition(790, 380);
					menu = 2;
					time = 0;
				}
				else if (menu == 2) {
					rectangle.setPosition(790, 460);
					menu = 3;
					time = 0;
				}
				else if (menu == 3) {
					rectangle.setPosition(790, 300);
					menu = 1;
					time = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (menu == 1) {
					rectangle.setPosition(790, 460);
					menu = 3;
					time = 0;
				}
				else if (menu == 2) {
					rectangle.setPosition(790, 300);
					menu = 1;
					time = 0;
				}
				else if (menu == 3) {
					rectangle.setPosition(790, 380);
					menu = 2;
					time = 0;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				if (menu == 1) {
					isMenu = false;
					hero.setX(hero.getFirstX());
					hero.setY(hero.getFirstY());
				}
				else if (menu == 2) {
					window.clear();
					while (!Keyboard::isKeyPressed(Keyboard::Escape) && window.isOpen()) {
						Text title_1("Об игре", font, 40);
						Text About(" Данное игровое программное средство написано студентом \n Белорусского Государственного Университета Информатики и \n Радиоэлектроники Авсюкевичем Максимом. Цель игры : уничтожение \n всех вражеских танков.", font, 30);
						Text title_2("Обратная связь", font, 40);
						Texture qr_code;
						qr_code.loadFromFile("images/qr.png");
						Sprite qr_sprite(qr_code);
						title_1.setColor(Color::Red);
						About.setColor(Color::White);
						title_2.setColor(Color::Red);
						title_1.setStyle(Text::Bold);
						About.setStyle(Text::Bold);
						title_2.setStyle(Text::Bold);
						title_1.setPosition(500, 0);
						About.setPosition(0, 60);
						title_2.setPosition(430, 250);
						qr_sprite.setPosition(400, 350);
						window.draw(fon_sprite);
						window.draw(title_1);
						window.draw(About);
						window.draw(title_2);
						window.draw(qr_sprite);
						window.display();

						Event event;
						while (window.pollEvent(event))
						{
							if (event.type == Event::Closed)
								window.close();
						}
					}
				}
				else if (menu == 3) {
					window.close();
				}
			}
		}
	}
	window.draw(fon_sprite);
	window.draw(menu_1);
	window.draw(rectangle);
	window.draw(StartGame);
	window.draw(AboutGame);
	window.draw(Exit);
	window.display();
}

void destructionHero(RenderWindow& window, Tank& hero, bool& isMenu, Music& gameOverMus, bool& isPlayGameOver) {
	Font font;
	font.loadFromFile("DS Stamper.ttf");
	Text GameOver("Game Over", font, 100);
	Text ClickToContinue("Press LEFT SHIFT to continue", font, 30);
	GameOver.setColor(Color::Red);
	ClickToContinue.setColor(Color::White);
	GameOver.setStyle(Text::Bold);
	ClickToContinue.setStyle(Text::Bold);
	GameOver.setPosition(300, 300);
	ClickToContinue.setPosition(350, 420);
	window.draw(GameOver);
	window.draw(ClickToContinue);
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		isMenu = true;
		hero.setIsLife(true);
		gameOverMus.stop();
	}

}