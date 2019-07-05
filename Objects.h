#include "movPlatform.h"

//////////////ЗДОРОВЬЕ//////////////

class Health :public Entity { //класс здоровья
public:
	Health(Image &, String, Level &, float, float, int, int); //конструктор
	void update(float); //функция обновления и взаимодействия
};

Health::Health(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
	obj = lvl.GetObjects("Player");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	life = true;
	sprite.setTextureRect(IntRect(240, 240, w, h));
	sprite.setScale(0.6, 0.6);
}

void Health::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//проход по объектам Player
		if (getRect().intersects(obj[i].rect)) { //если наш объёкт пересекся с героем
			life = false;// то сердце "умирает"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////ПАТРОНЫ//////////////

class Ammu :public Entity { //Класс патронов
public:
	Ammu(Image &, String, Level &, float, float, int, int); //конструктор
	void update(float); //обновление и взаимодействие
};

Ammu::Ammu(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
	obj = lvl.GetObjects("Player");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	life = true;
	sprite.setTextureRect(IntRect(300, 300, w, h));
	sprite.setScale(0.6, 0.6);
}

void Ammu::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//проход по объектам Player
		if (getRect().intersects(obj[i].rect)) { //если наш объёкт пересекся с героем
			life = false;// то набор патронов "умирает"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////ХИМИЯ//////////////

class Acid : public Entity { //Кислотные бочки
public:
	Acid(Image &, String, Level &, float, float, int, int); //конструктор
	void update(float); //обновление и взаимодействие
};

Acid::Acid(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
	obj = lvl.GetObjects("Player");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	life = true;
	sprite.setTextureRect(IntRect(180, 0, w, h));
}

void Acid::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//проход по объектам Player
		if (getRect().intersects(obj[i].rect)) { //если наш объёкт пересекся с героем
			life = false;// то бочка "умирает"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////ВЗРЫВЧАТКА//////////////

class Bang : public Entity { //взрывчатые бочки
public:
	Bang(Image &, String, Level &, float, float, int, int); //конструктор
	void update(float); //взаимодействие и обновление
};

Bang::Bang(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
	obj = lvl.GetObjects("Player");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
	life = true;
	sprite.setTextureRect(IntRect(120, 0, w, h));
}

void Bang::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//проход по объектам Player
		if (getRect().intersects(obj[i].rect)) { //если наш объёкт пересекся с героем
			life = false;// то бочка "умирает"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}
