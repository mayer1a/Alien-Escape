#include <sstream>
#include "Level.h"
using namespace sf;
using namespace std;


class Entity { //������������(�������) �����
public:
	vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed, moveTimer; //����������, ��������� �������� �������� �� ����, ��������, ������ ��������
	int w, h, health; //������ � ������ ��������, ��������
	bool life, onGround; //�����, ��������� �� ����� ��� ���
	Texture texture; //��������
	Sprite sprite; //������
	String name; //������ ����� �������
	Image image; //�����������

	Entity(Image &, String, float, float, int, int); //�����������
	FloatRect getRect(); //�-��� ��������� �����.: ������ � ������ ���������������(����� ��� checkCollision)
	FloatRect getEnemyRect(); //�-��� ��������� �����.: ������ � ������ ��������������� ��� ������� ������ �����
	virtual void update(float time) = 0; //����������� ������� update, ��� ����������� ������ �������������� ��� �-���
};

Entity::Entity(Image &image, String name, float x, float y, int w, int h) {
	this->x = x; this->y = y; this->w = w; this->h = h; //�������������� ����������
	this->name = name; moveTimer = 0; speed = 0;
	health = 100; dx = 0; dy = 0;
	life = true; onGround = false;
	texture.loadFromImage(image); //������ ��������
	sprite.setTexture(texture); //������� ������ �� ��������
	sprite.setOrigin(w / 2, h / 2); //������ ����� ������ ���������� �������
}

FloatRect Entity::getRect() {
	return FloatRect(x, y, w, h);
}

FloatRect Entity::getEnemyRect() {
	return FloatRect(x - 200, y - 100, w + 400, h + 100);
}