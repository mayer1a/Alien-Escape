#include "Game.h"

int main() { //основной блок
	RenderWindow window(VideoMode(1024, 768), "SPACEFF. Artyom Mayer"); //создаём само окно отображения с заданием разрешения окна и его именем
	if (menu(window)) {
		int numLevel = 1;//сначала 1-ый уровень
		gameRunning(window, numLevel);//запускаем процесс игры
	}
	return 0;
}