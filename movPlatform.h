#include "Bullet.h"

class movingPlatform : public Entity {//класс движущейся платформы
public:
	movingPlatform(Image &, String, Level &, float, float, int, int); //конструктор
	void update(float); //функция обновления для движения платформы
};

movingPlatform::movingPlatform(Image &image, String Name, Level &lvl, float x, float y, int w, int h) :Entity(image, Name, x, y, w, h) { 
	//инициализируем
	sprite.setTextureRect(IntRect(360, 60, w, h));//создаём спрайт платформы
	dy = 0.08;//скорость движения по y
}

void movingPlatform::update(float time) {
	y += dy * time;//движения по вертикали
	moveTimer += time;//увеличиваем таймер
	
	if (moveTimer>2000) { //если прошло 2 сек, меням направление движения платформы
		dy *= -1; //меняем направление движения платформы 
		moveTimer = 0; //сбрасываем таймер
	}

	sprite.setPosition(x + w / 2, y + h / 2);//задаем позицию спрайту
}