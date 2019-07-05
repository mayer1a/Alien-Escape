#include "Camera.h"
#include <list>
#include "Menu.h"
#include <fstream>

void changeLevel(Level &lvl, int &numLevel) {
	if (numLevel == 1) { //загружаем в него карту первого уровня
		lvl.LoadFromFile("Resourses/Maps/map.tmx");
	}
	if (numLevel == 2) { //второго
		lvl.LoadFromFile("Resourses/Maps/map2.tmx");
	}
}

bool startGame(RenderWindow &window, int &numLevel) {
	ofstream fin, fout;

	view.reset(FloatRect(0, 0, 1200, 900)); //создаём "камеру" и указываем ёё размеры

	Level lvl;//создаём экземпляр класса уровень
	changeLevel(lvl, numLevel);

	Font font1; //создаём экземпляр класса шрифт
	font1.loadFromFile("Resourses/Fonts/a_LCDNova3DCmObl.TTF"); //загружаем шрифт из файла
	Text text("", font1, 16); //пока будет пустая строка, обрабатываем шрифт, размер шрифта
	text.setColor(Color::Green); //задаём цвет шрифта

	Image objectsIm;
	objectsIm.loadFromFile("Resourses/Images/images.png"); //изображения объектов
	objectsIm.createMaskFromColor(Color::Color(51, 58, 76)); //создаём маску цвета для удаления фона

	Image heroIm; //создаём экземпляр класса картинка
	heroIm.loadFromFile("Resourses/Images/char1.png"); //загружаем в него изображение героя из файла

	Image easyEnemyIm;
	easyEnemyIm.loadFromFile("Resourses/Images/enn1.png"); //загружаем в него изображение врага из файла
	easyEnemyIm.createMaskFromColor(Color::Black); //создаём маску цвета, чтобы убрать фон

	Image bulletIm;
	bulletIm.loadFromFile("Resourses/Images/bullet.png"); //изображение пули

	list<Entity*>  entities;//создаём список, зедсь будут объекты врагов
	list<Entity*>::iterator it, it2;//первый итератор чтобы проходить по эл-там списка, второй итератор для взаимодействия между объектами списка
	vector<Object> e = lvl.GetAllObjects(); // все объекты на tmx карте будут храниться здесь

	for (int i = 0; i < e.size(); i++) {//проходимся по элементам вектора
		if (e[i].name == "easyEnemy") { //враги
			entities.push_back(new Enemy(easyEnemyIm, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 40, 72));
		}
		if (e[i].name == "Enemy") { //враги
			entities.push_back(new Enemy(easyEnemyIm, "Enemy", lvl, e[i].rect.left, e[i].rect.top, 40, 72));
		}
		if (e[i].name == "mov") { //платформы
			entities.push_back(new movingPlatform(objectsIm, "mov", lvl, e[i].rect.left, e[i].rect.top, 120, 60));
		}
		if (e[i].name == "health") { //сердечки
			entities.push_back(new Health(objectsIm, "health", lvl, e[i].rect.left, e[i].rect.top, 60, 60));
		}
		if (e[i].name == "ammu") {
			entities.push_back(new Ammu(objectsIm, "ammu", lvl, e[i].rect.left, e[i].rect.top, 60, 60));
		}
		if (e[i].name == "acid") {
			entities.push_back(new Acid(objectsIm, "acid", lvl, e[i].rect.left, e[i].rect.top, 60, 60));
		}
		if (e[i].name == "bang") {
			entities.push_back(new Bang(objectsIm, "bang", lvl, e[i].rect.left, e[i].rect.top, 60, 60));
		}
	}//и закидываем соотв. объекты в список

	Object player = lvl.GetObject("player");//создаём объект игрока на нашей карте, задаем координаты игроку в начале при помощи него
	Hero hero(heroIm, "Player", lvl, player.rect.left, player.rect.top, 40, 70);//передаем координаты прямоугольника player из карты в координаты нашего игрока

	Clock clock; //экземпляр класса времени
	Clock gameTimeClock; //экземпляр класса времени 
	int gameTime = gameTimeClock.getElapsedTime().asSeconds(), dir, plscr = 0; //

	while (window.isOpen()) { //пока открыто окно, "играем"

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { //если таб, то перезагружаем игру
			if (numLevel != 2) { //НУЖНО УБРАТЬ - для теста
				numLevel++;
			}
			return true;
		}

		float time = clock.getElapsedTime().asMicroseconds(), moveTimer; //создаём переменную времени - отвечает за движение и плавность

		gameTime = gameTimeClock.getElapsedTime().asSeconds();

		clock.restart(); //перезагружаем время
		time /= 800;

		Event event; //экземпляр класса событие

		LifeBar lifeBarPlayer;
		lifeBarPlayer.update(hero.health, hero.shop);

		while (window.pollEvent(event)) { //если событие

			if (event.type == Event::Closed) { //"окно закрыть"
				fout << "Время игры: " << gameTime / 60 << " минут " << gameTime % 60 << " секунд" << endl;
				fout << "Количество набранных очков: " << plscr << "" << endl;
				fout << "Вы были на " << numLevel << " уровне";
				fout.close(); // закрываем файл
				window.close(); //закрываем окна
				return false;
			}

			if (hero.isShot == true && hero.shop > 0) {
				hero.isShot = false;
				hero.shop -= 1;
				entities.push_back(new Bullet(bulletIm, "Bullet", lvl, hero.x, hero.y, 59, 13, hero.dir));
			}
		}

		for (it = entities.begin(); it != entities.end();) {//проходимся от начала до конца списка
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов, которые "живы"
			if (b->life == false) { // если мертвы, то удаляем
				it = entities.erase(it);
				delete b;
			}
			else { //иначе идем курсором (итератором) к след объекту
				it++;
			}
		}

		for (it = entities.begin(); it != entities.end(); it++) {//проходимся по эл-там списка(от начала до конца)

			if (hero.getRect().intersects((*it)->getEnemyRect())) {
				if ((*it)->name == "EasyEnemy") {
					if ((*it)->x > hero.x && hero.onGround == true) {
						if ((*it)->dx > 0) {
							(*it)->sprite.scale(-1, 1);
						}
						(*it)->dx = -0.2;
					}

					if ((*it)->x < hero.x && hero.onGround == true) {
						if ((*it)->dx < 0) {
							(*it)->sprite.scale(-1, 1);
						}
						(*it)->dx = 0.2;
					}
				}
				if ((*it)->name == "Enemy") {
					if ((*it)->x > hero.x && hero.onGround == true) {
						if ((*it)->dx > 0) {
							(*it)->sprite.scale(-1, 1);
						}
						(*it)->dx = -0.3;
					}

					if ((*it)->x < hero.x && hero.onGround == true) {
						if ((*it)->dx < 0) {
							(*it)->sprite.scale(-1, 1);
						}
						(*it)->dx = 0.3;
					}
				}
			}

			if (numLevel == 1) {
				if (hero.getRect().intersects(FloatRect(120, 600, 60, 120))) {
					numLevel++;
					return true;
				}
			}

			if (numLevel == 2) {
				if (hero.getRect().intersects(FloatRect(2340, 240, 60, 120))) {
					Texture winT;
					winT.loadFromFile("Resourses/Images/win.png");
					Sprite winSp(winT);
					winSp.setPosition(view.getCenter().x - 600, view.getCenter().y - 450);
					window.clear();
					window.draw(winSp);
					window.display();

					while (1) {
						if (Mouse::isButtonPressed(Mouse::Left)) {
							if (window.pollEvent(event)) {
								if (event.type == Event::Closed) { window.close(); return false; }
							}
							else { window.close(); return false; }
						}
					}
				}
			}

			if ((*it)->getRect().intersects(hero.getRect())) {//если объект пересекается с игроком
				if ((*it)->name == "EasyEnemy" || (*it)->name == "Enemy") {//и при этом имя объекта EasyEnemy,то..

					if ((hero.dy > 0) && (hero.onGround == false)) {//если прыгнули на врага
						(*it)->dx = 0; hero.dy = -0.2; (*it)->life = false; //останавливаем врага, отпрыгиваем, жизнь врага = 0
						plscr += 1;
					}

					if ((*it)->dx > 0) {//если враг идет вправо
						(*it)->x = hero.x - (*it)->w; //отталкиваем его от игрока влево
						(*it)->dx *= -1;//меняем направление
						(*it)->sprite.scale(-1, 1); //отражаем спрайт врага зеркально
						hero.health -= 5; //отнимаем у игрока 5 жизней(так как столкнулись)
					}

					else if ((*it)->dx < 0) {//иначе если враг идет влево
						(*it)->x = hero.x + hero.w; //отталкиваем вправо
						(*it)->dx *= -1;//меняем направление
						(*it)->sprite.scale(-1, 1); //отражаем спрайт врага зеркально
						hero.health -= 5; //отнимаем у игрока 5 жизней
					}

					if (hero.dx < 0) { //не даем герою "выталкивать" врага
						hero.x = (*it)->x + (*it)->w; //если столкнулись с врагом и идём влево то выталкиваем игрока
					}
					if (hero.dx > 0) {
						hero.x = (*it)->x - hero.w; //если столкнулись с врагом и идём вправо то выталкиваем игрока
					}
				}

				if ((*it)->name == "health") {
					hero.health += 30;
					if (hero.health > 100) {
						hero.health = 100;
					}
					(*it)->life = false;
				}

				if ((*it)->name == "ammu") {
					hero.shop += 50;
					(*it)->life = false;
				}

				if ((*it)->name == "mov") {
					if ((hero.dy > 0) || (hero.onGround == false)) {//если игрок находится в состоянии "после прыжка"
						if ((hero.y + hero.h) < ((*it)->y + (*it)->h)) {//если игрок находится выше платформы
							hero.y = (*it)->y - hero.h + 3; // то выталкиваем игрока так, чтобы он стоял на платформе
							hero.x += (*it)->dx*time;
							hero.dy = 0;
							hero.onGround = true;
						}
					}
				}

				if ((*it)->name == "acid") {
					hero.health -= 20;
					(*it)->life = false;
				}

				if ((*it)->name == "bang") {
					hero.health -= 50;
					(*it)->life = false;
				}

			}

			for (it2 = entities.begin(); it2 != entities.end(); it2++) { //идём вторым итератором для взаимодействия двух объектов - врагов
				if ((*it)->getRect() != (*it2)->getRect()) {
					if ((*it)->getRect().intersects((*it2)->getRect())) {
						if (((*it)->name == "Bullet") && ((*it2)->name == "EasyEnemy" || (*it2)->name == "Enemy")) {
							(*it2)->health -= 5;
							(*it)->life = false;
						}
					}
				}
			}
		}

		hero.update(time); //делаем "обновление" игрока
		window.clear(); //делаем "очистку" экрана
		window.setView(view); //отображаем камеру
		lvl.Draw(window);//рисуем новую карту 

		if (hero.life) {
			ostringstream playerScore, playerShop, gameTimeS, gameTimeM;//строка здоровья игрока, строка очков игрока
			playerShop << hero.shop;
			gameTimeM << (gameTime / 60);
			gameTimeS << (gameTime % 60);
			text.setString("Мин " + gameTimeM.str() + " Сек " + gameTimeS.str()); //создаём текстовую строку(цельную)
			text.setPosition(view.getCenter().x - 139, view.getCenter().y - 432);//позиция текстового блока в игре
		}
		else {
			fout.open("Resourses/Statistic/Stat.txt"); // связываем объект с файлом
			fout << "Время игры: \t" << gameTime / 60 << " минут \t" << gameTime % 60 << " секунд" << endl;
			fout << "Количество набранных очков: \t" << plscr << endl;
			fout << "Вы были на \t" << numLevel << "\t уровне";
			fout.close(); // закрываем файл

			Texture statT;
			statT.loadFromFile("Resourses/Images/stat.png");
			Sprite statS(statT);
			statS.setPosition(view.getCenter().x - 600, view.getCenter().y - 450);

			string s1, s2, s3;
			ifstream fin("Resourses/Statistic/Stat.txt");
			getline(fin, s1); getline(fin, s2); getline(fin, s3);

			text.setColor(Color::Cyan); //задаём цвет шрифта
			text.setCharacterSize(48);
			text.setString(s1 + "\n\n" + s2 + "\n\n\t\t\t" + s3);
			text.setPosition(view.getCenter().x - 500, view.getCenter().y - 180);

			window.clear();
			window.draw(statS);
			window.draw(text);
			window.display();

			while (1) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (window.pollEvent(event)) {
						if (event.type == Event::Closed) { window.close(); return false; }
					}
					else { window.close(); return false; }
				}
			}
		}
		window.draw(hero.sprite); //рисуем игрока

		for (it = entities.begin(); it != entities.end(); it++) {//рисуем entities объекты
			window.draw((*it)->sprite);
		}

		window.draw(text); //рисуем
		lifeBarPlayer.draw(window);
		window.display(); //отображаем всё
	}
}

void gameRunning(RenderWindow &window, int &numLevel) {//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numLevel)) { //принимает с какого уровня начать игру
		gameRunning(window, numLevel);
	}
}