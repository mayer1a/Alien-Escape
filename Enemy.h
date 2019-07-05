#include "Hero.h"

class Enemy : public Entity { //класс противника
public:
	float currentFrame; //переменная текущего кадра для анимации
	Enemy(Image &, String, Level, float, float, int, int); //конструктор
	void checkCollision(float, float); //функция проверки столкновений
	void update(float); //обновление движения, отображение, взаимодействие
	FloatRect getEnemyRect(); //ф-ция получения коорд.: ширины и высоты прямоугольнинка для области обзора врага
};

Enemy::Enemy(Image &image, String name, Level lvl, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
	//инициализируем врага, получаем все объекты для взаимодействия врага с картой
	obj = lvl.GetAllObjects();
	currentFrame = 0;
	sprite.setTextureRect(IntRect(10, 120, w, h)); //создаем спрайт врага

	if (name == "EasyEnemy") { //если имя EasyEnemy = 1 уровень
		dx = 0.1; //задаём скорость движения врага
	}
	if (name == "Enemy") { //если имя Enemy = 2 уровень
		sprite.setColor(Color::Color(255, 0, 255)); //меняем цвет спрайта
		dx = 0.2; //задаём бОльшую скорость движения врага
	}
}

void Enemy::checkCollision(float Dx, float Dy) {//проверка столкновений
	for (int i = 0; i < obj.size(); i++) {//проходимся по объектам
		if (getRect().intersects(obj[i].rect)) {//проверяем пересечение с объектом
			if (obj[i].name == "solid" || obj[i].name == "solid1") {//если встретили препятствие
				if (name == "EasyEnemy") { //если враг первого уровня
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; } //не проваливаемся сквозь пол, из-за гравитации
					/*if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }*/
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); } //если столкнулись, объект справа, разворачиваемся
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); } //если столкнулись, объект слева, разворачиваемся
				}
				if (name == "Enemy") { //если враг второго уровня
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					/*if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }*/
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.2; sprite.scale(-1, 1); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.2; sprite.scale(-1, 1); }
				}
			}
		}
	}
}

void Enemy::update(float time) { //обновление движения, отображение
	currentFrame += 0.007*time; //прирост текущего кадра
	if (currentFrame > 8) { //если кадров больше восьми, возвращаемся на начало проигрывания анимации
		currentFrame -= 8;
	}
	//отображаем тот кусок спрайта, который следующий для анимации
	sprite.setTextureRect(IntRect(60 * int(currentFrame), 120, 60, 72)); //создаем спрайт врага

	x += dx * time; //приросты координат
	checkCollision(dx, 0); //проверяем столкновения
	y += dy * time;
	checkCollision(0, dy);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем координаты спрайта

	if (health <= 0) { //если жизней нет, умирает
		life = false;
	}

	dy = dy + 0.0015*time; //гравитация
}

FloatRect Enemy::getEnemyRect() {
	return FloatRect(x - 100, y, w + 200, h); //возвращаем прямоугольник увеличенного размера - область видимости врага
}