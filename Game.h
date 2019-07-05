#include "Camera.h"
#include <list>
#include "Menu.h"
#include <fstream>

void changeLevel(Level &lvl, int &numLevel) {
	if (numLevel == 1) { //��������� � ���� ����� ������� ������
		lvl.LoadFromFile("Resourses/Maps/map.tmx");
	}
	if (numLevel == 2) { //�������
		lvl.LoadFromFile("Resourses/Maps/map2.tmx");
	}
}

bool startGame(RenderWindow &window, int &numLevel) {
	ofstream fin, fout;

	view.reset(FloatRect(0, 0, 1200, 900)); //������ "������" � ��������� �� �������

	Level lvl;//������ ��������� ������ �������
	changeLevel(lvl, numLevel);

	Font font1; //������ ��������� ������ �����
	font1.loadFromFile("Resourses/Fonts/a_LCDNova3DCmObl.TTF"); //��������� ����� �� �����
	Text text("", font1, 16); //���� ����� ������ ������, ������������ �����, ������ ������
	text.setColor(Color::Green); //����� ���� ������

	Image objectsIm;
	objectsIm.loadFromFile("Resourses/Images/images.png"); //����������� ��������
	objectsIm.createMaskFromColor(Color::Color(51, 58, 76)); //������ ����� ����� ��� �������� ����

	Image heroIm; //������ ��������� ������ ��������
	heroIm.loadFromFile("Resourses/Images/char1.png"); //��������� � ���� ����������� ����� �� �����

	Image easyEnemyIm;
	easyEnemyIm.loadFromFile("Resourses/Images/enn1.png"); //��������� � ���� ����������� ����� �� �����
	easyEnemyIm.createMaskFromColor(Color::Black); //������ ����� �����, ����� ������ ���

	Image bulletIm;
	bulletIm.loadFromFile("Resourses/Images/bullet.png"); //����������� ����

	list<Entity*>  entities;//������ ������, ����� ����� ������� ������
	list<Entity*>::iterator it, it2;//������ �������� ����� ��������� �� ��-��� ������, ������ �������� ��� �������������� ����� ��������� ������
	vector<Object> e = lvl.GetAllObjects(); // ��� ������� �� tmx ����� ����� ��������� �����

	for (int i = 0; i < e.size(); i++) {//���������� �� ��������� �������
		if (e[i].name == "easyEnemy") { //�����
			entities.push_back(new Enemy(easyEnemyIm, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 40, 72));
		}
		if (e[i].name == "Enemy") { //�����
			entities.push_back(new Enemy(easyEnemyIm, "Enemy", lvl, e[i].rect.left, e[i].rect.top, 40, 72));
		}
		if (e[i].name == "mov") { //���������
			entities.push_back(new movingPlatform(objectsIm, "mov", lvl, e[i].rect.left, e[i].rect.top, 120, 60));
		}
		if (e[i].name == "health") { //��������
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
	}//� ���������� �����. ������� � ������

	Object player = lvl.GetObject("player");//������ ������ ������ �� ����� �����, ������ ���������� ������ � ������ ��� ������ ����
	Hero hero(heroIm, "Player", lvl, player.rect.left, player.rect.top, 40, 70);//�������� ���������� �������������� player �� ����� � ���������� ������ ������

	Clock clock; //��������� ������ �������
	Clock gameTimeClock; //��������� ������ ������� 
	int gameTime = gameTimeClock.getElapsedTime().asSeconds(), dir, plscr = 0; //

	while (window.isOpen()) { //���� ������� ����, "������"

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { //���� ���, �� ������������� ����
			if (numLevel != 2) { //����� ������ - ��� �����
				numLevel++;
			}
			return true;
		}

		float time = clock.getElapsedTime().asMicroseconds(), moveTimer; //������ ���������� ������� - �������� �� �������� � ���������

		gameTime = gameTimeClock.getElapsedTime().asSeconds();

		clock.restart(); //������������� �����
		time /= 800;

		Event event; //��������� ������ �������

		LifeBar lifeBarPlayer;
		lifeBarPlayer.update(hero.health, hero.shop);

		while (window.pollEvent(event)) { //���� �������

			if (event.type == Event::Closed) { //"���� �������"
				fout << "����� ����: " << gameTime / 60 << " ����� " << gameTime % 60 << " ������" << endl;
				fout << "���������� ��������� �����: " << plscr << "" << endl;
				fout << "�� ���� �� " << numLevel << " ������";
				fout.close(); // ��������� ����
				window.close(); //��������� ����
				return false;
			}

			if (hero.isShot == true && hero.shop > 0) {
				hero.isShot = false;
				hero.shop -= 1;
				entities.push_back(new Bullet(bulletIm, "Bullet", lvl, hero.x, hero.y, 59, 13, hero.dir));
			}
		}

		for (it = entities.begin(); it != entities.end();) {//���������� �� ������ �� ����� ������
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� ��������, ������� "����"
			if (b->life == false) { // ���� ������, �� �������
				it = entities.erase(it);
				delete b;
			}
			else { //����� ���� �������� (����������) � ���� �������
				it++;
			}
		}

		for (it = entities.begin(); it != entities.end(); it++) {//���������� �� ��-��� ������(�� ������ �� �����)

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

			if ((*it)->getRect().intersects(hero.getRect())) {//���� ������ ������������ � �������
				if ((*it)->name == "EasyEnemy" || (*it)->name == "Enemy") {//� ��� ���� ��� ������� EasyEnemy,��..

					if ((hero.dy > 0) && (hero.onGround == false)) {//���� �������� �� �����
						(*it)->dx = 0; hero.dy = -0.2; (*it)->life = false; //������������� �����, �����������, ����� ����� = 0
						plscr += 1;
					}

					if ((*it)->dx > 0) {//���� ���� ���� ������
						(*it)->x = hero.x - (*it)->w; //����������� ��� �� ������ �����
						(*it)->dx *= -1;//������ �����������
						(*it)->sprite.scale(-1, 1); //�������� ������ ����� ���������
						hero.health -= 5; //�������� � ������ 5 ������(��� ��� �����������)
					}

					else if ((*it)->dx < 0) {//����� ���� ���� ���� �����
						(*it)->x = hero.x + hero.w; //����������� ������
						(*it)->dx *= -1;//������ �����������
						(*it)->sprite.scale(-1, 1); //�������� ������ ����� ���������
						hero.health -= 5; //�������� � ������ 5 ������
					}

					if (hero.dx < 0) { //�� ���� ����� "�����������" �����
						hero.x = (*it)->x + (*it)->w; //���� ����������� � ������ � ��� ����� �� ����������� ������
					}
					if (hero.dx > 0) {
						hero.x = (*it)->x - hero.w; //���� ����������� � ������ � ��� ������ �� ����������� ������
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
					if ((hero.dy > 0) || (hero.onGround == false)) {//���� ����� ��������� � ��������� "����� ������"
						if ((hero.y + hero.h) < ((*it)->y + (*it)->h)) {//���� ����� ��������� ���� ���������
							hero.y = (*it)->y - hero.h + 3; // �� ����������� ������ ���, ����� �� ����� �� ���������
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

			for (it2 = entities.begin(); it2 != entities.end(); it2++) { //��� ������ ���������� ��� �������������� ���� �������� - ������
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

		hero.update(time); //������ "����������" ������
		window.clear(); //������ "�������" ������
		window.setView(view); //���������� ������
		lvl.Draw(window);//������ ����� ����� 

		if (hero.life) {
			ostringstream playerScore, playerShop, gameTimeS, gameTimeM;//������ �������� ������, ������ ����� ������
			playerShop << hero.shop;
			gameTimeM << (gameTime / 60);
			gameTimeS << (gameTime % 60);
			text.setString("��� " + gameTimeM.str() + " ��� " + gameTimeS.str()); //������ ��������� ������(�������)
			text.setPosition(view.getCenter().x - 139, view.getCenter().y - 432);//������� ���������� ����� � ����
		}
		else {
			fout.open("Resourses/Statistic/Stat.txt"); // ��������� ������ � ������
			fout << "����� ����: \t" << gameTime / 60 << " ����� \t" << gameTime % 60 << " ������" << endl;
			fout << "���������� ��������� �����: \t" << plscr << endl;
			fout << "�� ���� �� \t" << numLevel << "\t ������";
			fout.close(); // ��������� ����

			Texture statT;
			statT.loadFromFile("Resourses/Images/stat.png");
			Sprite statS(statT);
			statS.setPosition(view.getCenter().x - 600, view.getCenter().y - 450);

			string s1, s2, s3;
			ifstream fin("Resourses/Statistic/Stat.txt");
			getline(fin, s1); getline(fin, s2); getline(fin, s3);

			text.setColor(Color::Cyan); //����� ���� ������
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
		window.draw(hero.sprite); //������ ������

		for (it = entities.begin(); it != entities.end(); it++) {//������ entities �������
			window.draw((*it)->sprite);
		}

		window.draw(text); //������
		lifeBarPlayer.draw(window);
		window.display(); //���������� ��
	}
}

void gameRunning(RenderWindow &window, int &numLevel) {//�-��� ������������� ���� , ���� ��� ����������
	if (startGame(window, numLevel)) { //��������� � ������ ������ ������ ����
		gameRunning(window, numLevel);
	}
}