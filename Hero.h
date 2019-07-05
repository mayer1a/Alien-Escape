#include "Entity.h"

class Hero : public Entity { //класс игрока
public:
	enum { left, right, stay } state; //создаём переменную, хранящая состояние героя
	int shop, dir; //переменная, хранящая очки игрока
	bool isShot; //состояние стрельбы
	float currentFrame; //переменная текущего кадра для анимации

	Hero(Image &, String, Level, float, float, int, int); //конструктор
	void control(); //функция контроля движения
	void checkCollision(float, float); //функция проверки столкновений
	void update(float); //обновление движения, отображение, взаимодействие
};

Hero::Hero(Image &image, String name, Level lvl, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
	shop = 0; currentFrame = 0;
	state = stay; obj = lvl.GetObjects("solid");//инициализируем, получаем все объекты для взаимодействия персонажа с картой
	isShot = false; //стреляем или нет
	sprite.setTextureRect(IntRect(0, 80, w, h)); //задаём спрайт героя
}

void Hero::control() {
	if (Keyboard::isKeyPressed(Keyboard::Left)) { //если клавиша движения влево
		state = left; //состояние - влево
		dir = 0; //для направления полёта пулями
		speed = 0.15; //скорость
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) { //если клавиша движения вправо
		state = right; //состояние - вправо
		dir = 1; //для направления полёта пулями
		speed = 0.15; //скорость
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) { //если клавиша прыжка и состояние=на земле
		dy = -0.6; //скорость "приземления"
		onGround = false; //теперь не на земле, чтобы не прыгать в воздухе
	}
	if (Keyboard::isKeyPressed(Keyboard::Return)) { //если нажали Enter, выстрелили
		isShot = true; //состояние выстрела - да
	}
}

void Hero::checkCollision(float Dx, float Dy) {
	for (int i = 0; i < obj.size(); i++) {//проходимся по объектам
		if (getRect().intersects(obj[i].rect)) {//проверяем пересечение игрока с объектом
												//если встретили препятствие
			if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; } //если на земле
			if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; } //если в воздухе
			if (Dx > 0) { x = obj[i].rect.left - w; } //если идём вправо
			if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; } //если идём влево
		}
	}
}

void Hero::update(float time) {
	if (life) { //если игрок жив
		control(); //функция контроля движения
		switch (state) { //смотрим, в каком состоянии игрок
		case right: dx = speed; //если состояние - вправо, изменение скорости = положительное
			currentFrame += 0.007*time; //прирост текущего кадра
			if (currentFrame > 3) { //если кадров больше трёх, возвращаемся на начало проигрывания анимации
				currentFrame -= 3;
			}
			//отображаем тот кусок спрайта, который следующий для анимации
			sprite.setTextureRect(IntRect(45 * int(currentFrame), 80, 44, 70));
			state = stay; //состояние бездействия
			break;

		case left: dx = -speed; //если состояние - влево, изменение скорости = отрицательное
			currentFrame += 0.007*time; //прирост текущего кадра
			if (currentFrame > 3) { //если кадров больше трёх, возвращаемся на начало проигрывания анимации
				currentFrame -= 3;
			}
			//отображаем тот кусок спрайта, который следующий для анимации
			sprite.setTextureRect(IntRect(45 * int(currentFrame) + 44, 80, -44, 70));
			state = stay; //состояние бездействия
			break;

		case stay: dx = 0; break; //если стоим, прирост по скорости = 0
		}

		x += dx * time; //делаем приращение в координатах*время, чтобы была плавность и движение анимации
		checkCollision(dx, 0); //проверка на столкновения
		y += dy * time;
		checkCollision(0, dy);

		sprite.setPosition(x + w / 2, y + h / 2); //устанавливаем позицию спрайта
		if (health <= 0) { //если у игрока 0 жизней
			life = false;  //он мертв
		}
		speed = 0; //скорость, чтобы не происходило "залипание" клавиши движениия
		dy = dy + 0.00104*time; //гравитация для теста
		setPlayerCam(x, y); //задаем позицию камере
	}
}