#include "Hero.h"

class Enemy : public Entity { //����� ����������
public:
	float currentFrame; //���������� �������� ����� ��� ��������
	Enemy(Image &, String, Level, float, float, int, int); //�����������
	void checkCollision(float, float); //������� �������� ������������
	void update(float); //���������� ��������, �����������, ��������������
	FloatRect getEnemyRect(); //�-��� ��������� �����.: ������ � ������ ��������������� ��� ������� ������ �����
};

Enemy::Enemy(Image &image, String name, Level lvl, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
	//�������������� �����, �������� ��� ������� ��� �������������� ����� � ������
	obj = lvl.GetAllObjects();
	currentFrame = 0;
	sprite.setTextureRect(IntRect(10, 120, w, h)); //������� ������ �����

	if (name == "EasyEnemy") { //���� ��� EasyEnemy = 1 �������
		dx = 0.1; //����� �������� �������� �����
	}
	if (name == "Enemy") { //���� ��� Enemy = 2 �������
		sprite.setColor(Color::Color(255, 0, 255)); //������ ���� �������
		dx = 0.2; //����� ������� �������� �������� �����
	}
}

void Enemy::checkCollision(float Dx, float Dy) {//�������� ������������
	for (int i = 0; i < obj.size(); i++) {//���������� �� ��������
		if (getRect().intersects(obj[i].rect)) {//��������� ����������� � ��������
			if (obj[i].name == "solid" || obj[i].name == "solid1") {//���� ��������� �����������
				if (name == "EasyEnemy") { //���� ���� ������� ������
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; } //�� ������������� ������ ���, ��-�� ����������
					/*if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }*/
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); } //���� �����������, ������ ������, ���������������
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); } //���� �����������, ������ �����, ���������������
				}
				if (name == "Enemy") { //���� ���� ������� ������
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					/*if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }*/
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.2; sprite.scale(-1, 1); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.2; sprite.scale(-1, 1); }
				}
			}
		}
	}
}

void Enemy::update(float time) { //���������� ��������, �����������
	currentFrame += 0.007*time; //������� �������� �����
	if (currentFrame > 8) { //���� ������ ������ ������, ������������ �� ������ ������������ ��������
		currentFrame -= 8;
	}
	//���������� ��� ����� �������, ������� ��������� ��� ��������
	sprite.setTextureRect(IntRect(60 * int(currentFrame), 120, 60, 72)); //������� ������ �����

	x += dx * time; //�������� ���������
	checkCollision(dx, 0); //��������� ������������
	y += dy * time;
	checkCollision(0, dy);

	sprite.setPosition(x + w / 2, y + h / 2); //������ ���������� �������

	if (health <= 0) { //���� ������ ���, �������
		life = false;
	}

	dy = dy + 0.0015*time; //����������
}

FloatRect Enemy::getEnemyRect() {
	return FloatRect(x - 100, y, w + 200, h); //���������� ������������� ������������ ������� - ������� ��������� �����
}