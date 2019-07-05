#include <sstream>
#include "Level.h"
using namespace sf;
using namespace std;


class Entity { //родительский(базовый) класс
public:
	vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer; //координаты, изменение скорости движени€ по ос€м, скорость, таймер движени€
	int w, h, health; //ширина и высота спрайтов, здоровье
	bool life, onGround; //жизнь, состо€ние на земле или нет
	Texture texture; //текстура
	Sprite sprite; //спрайт
	String name; //строка имени объекта
	Image image; //изображение

	Entity(Image &, String, float, float, int, int); //конструктор
	FloatRect getRect(); //ф-ци€ получени€ коорд.: ширины и высоты пр€моугольнинка(нужно дл€ checkCollision)
	FloatRect getEnemyRect(); //ф-ци€ получени€ коорд.: ширины и высоты пр€моугольнинка дл€ области обзора врага
	virtual void update(float time) = 0; //виртуальна€ функци€ update, все наследуемые классы переопредел€ют эту ф-цию
};

Entity::Entity(Image &image, String name, float x, float y, int w, int h) {
	this->x = x; this->y = y; this->w = w; this->h = h; //инициализируем переменные
	this->name = name; moveTimer = 0; speed = 0;
	health = 100; dx = 0; dy = 0;
	life = true; onGround = false;
	texture.loadFromImage(image); //создаЄм текстуру
	sprite.setTexture(texture); //создаем спрайт из текстуры
	sprite.setOrigin(w / 2, h / 2); //задаем точку центра посередине спрайта
}

FloatRect Entity::getRect() {
	return FloatRect(x, y, w, h);
}

FloatRect Entity::getEnemyRect() {
	return FloatRect(x - 200, y - 100, w + 400, h + 100);
}