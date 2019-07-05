#include "Objects.h"

class LifeBar { //класс бар-меню
public:
	Image lifeIm; //изображение полоски жизни
	Texture lifeT; //текстура
	Sprite healthSp, ammuSp, timeSp; //спрайты
	int maxH,maxA; //максимальное значение здоровья и патронов
	RectangleShape healthBar, ammuBar;

	LifeBar(); //конструктор
	void update(int, int); //функция обновления наших полосок идентификаторов
	void draw(RenderWindow &window); //функция прорисовки
};

LifeBar::LifeBar() {
	lifeIm.loadFromFile("Resourses/Images/lifebar.png"); //загружаем картинку нашего бара
	lifeT.loadFromImage(lifeIm); //создаём текстуру
	healthSp.setTexture(lifeT); //спрайт для каждой полоски
	ammuSp.setTexture(lifeT);
	timeSp.setTexture(lifeT);
	healthSp.setTextureRect(IntRect(340, 0, 680, 80)); //устанавливаем прямоугольник для каждого идентификатора
	ammuSp.setTextureRect(IntRect(0, 0, 330, 90));
	timeSp.setTextureRect(IntRect(0, 90, 330, 167));
	healthSp.setScale(0.5, 0.5); ammuSp.setScale(0.5, 0.5); timeSp.setScale(0.63, 0.5); //корректируем размеры нашего бара
	healthBar.setFillColor(Color(0, 0, 0)); //черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
	ammuBar.setFillColor(Color(0, 0, 0)); //накладывается на всю "обойму", по мере прибавления патронов, чёрный прямоугольник уменьшается
	maxH = 100; maxA = 500; //максимальное здоровье, количество патронов
}

void LifeBar::update(int k, int j) {
	//k - текущее здоровье, j - количество патронов
	if (k > 0 && k < maxH) { 
		//если не отрицательно и при этом меньше максимума, то устанавливаем новый размер для черного прямоугольника
		healthBar.setSize(Vector2f(((maxH - k) * 110 / maxH), 15));
	}
	if (k < 0) {
		healthBar.setSize(Vector2f(115, 15)); 
	}
	if (j <= maxA && j > 0) {
		ammuBar.setSize(Vector2f((maxA * 110) / (maxA + j * 2), 15));
	}
	if (j == 0) {
		ammuBar.setSize(Vector2f(115, 15));
	}
}

void LifeBar::draw(RenderWindow &window) {
	Vector2f center = window.getView().getCenter(); //создаём центр нашего прямоугольника и его размер
	Vector2f size = window.getView().getSize();

	healthSp.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10); //позиция на экране
	healthBar.setPosition(center.x - size.x / 2 + 59, center.y - size.y / 2 + 23); //для здоровья

	ammuSp.setPosition(center.x - size.x / 2 + 210, center.y - size.y / 2 + 7);//позиция на экране
	ammuBar.setPosition(center.x - size.x / 2 + 255, center.y - size.y / 2 + 21); //для патронов

	timeSp.setPosition(center.x - size.x / 2 + 410, center.y - size.y / 2 + 10);//позиция на экране для времени

	window.draw(healthSp);//сначала рисуем полоску здоровья
	window.draw(ammuSp);//рисуем полоску патронов
	window.draw(timeSp);//рисуем полоску для времени
	window.draw(healthBar);//поверх уже черный прямоугольник для полоски здоровья
	window.draw(ammuBar);//поверх неё уже черный прямоугольник для полоски патронов
}