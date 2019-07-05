#include "Enemy.h"

class Bullet :public Entity {//класс пули
public:
	int direction;//направление пули

	Bullet(Image &, String, Level &, float, float, int, int, int); //конструктор
	void update(float); //функция обновления движения пули, взаимодействия
};

Bullet::Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
	//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	obj = lvl.GetAllObjects();
	x = X;
	y = Y;
	direction = dir;
	speed = 0.8;
	w = W;
	h = H;
	life = true;
	sprite.setTextureRect(IntRect(20, 5, w, h));
	sprite.setScale(0.4, 0.4);
}

void Bullet::update(float time) {
	switch (direction) { //направление полёта пули
	case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
	case 1: dx = speed; dy = 0;   break;//интовое значение state = right
	}

	x += dx * time * 2;//само движение пули по х

	//if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
	//if (y <= 0) y = 1;

	for (int i = 0; i < obj.size(); i++) {//проход по объектам solid и enemy
		if (getRect().intersects(obj[i].rect)) { //если этот объект столкнулся с пулей или врагом
			if (obj[i].name == "solid" || obj[i].name == "EasyEnemy" || obj[i].name == "Enemy")
				life = false;// то пуля умирает
		}
	}

	sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
}