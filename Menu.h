#include "LifeBar.h"
#include <ctime>



bool menu(RenderWindow &window) {
	Texture startText, aboutText, exitText, interAboutText, bckgrndText, miniText;
	Event event;
	startText.loadFromFile("Resourses/Images/start.png");
	aboutText.loadFromFile("Resourses/Images/about.png");
	exitText.loadFromFile("Resourses/Images/exit.png");
	interAboutText.loadFromFile("Resourses/Images/interAbout.png");
	bckgrndText.loadFromFile("Resourses/Images/spacebg.png");
	miniText.loadFromFile("Resourses/Images/mini_bckg.png");
	Sprite startSp(startText), aboutSp(aboutText), exitSp(exitText), interAboutSp(interAboutText), bckgrndSp(bckgrndText), miniSp(miniText);
	int menuNum = 0;
	startSp.setPosition(300, 170);
	aboutSp.setPosition(300, 345);
	exitSp.setPosition(300, 455);
	bckgrndSp.setPosition(0, 0);
	miniSp.setPosition(275, 100);
	//////////////////////////////МЕНЮ///////////////////
	while (true) {
		menuNum = 0;
		startSp.setColor(Color::White);
		aboutSp.setColor(Color::White);
		exitSp.setColor(Color::White);
		window.clear();

		if (IntRect(310, 195, 385, 150).contains(Mouse::getPosition(window))) {
			startSp.setColor(Color::Yellow);
			menuNum = 1;
		}
		if (IntRect(310, 355, 385, 100).contains(Mouse::getPosition(window))) {
			aboutSp.setColor(Color::Yellow);
			menuNum = 2;
		}
		if (IntRect(310, 469, 385, 100).contains(Mouse::getPosition(window))) {
			exitSp.setColor(Color::Yellow);
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left)) { //если выбрали пункт меню, смотрим какой
			if (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					return false;
				}
			}
			if (menuNum == 1) {
				return true;
			}
			if (menuNum == 2) {
				window.draw(interAboutSp); window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape)) {};
			}
			if (menuNum == 3) {
				window.close();
				return false;
			}
		}

		window.draw(bckgrndSp);
		window.draw(miniSp);
		window.draw(startSp);
		window.draw(aboutSp);
		window.draw(exitSp);
		window.display();

	}
}
