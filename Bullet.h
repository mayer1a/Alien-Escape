#include "Enemy.h"

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����

	Bullet(Image &, String, Level &, float, float, int, int, int); //�����������
	void update(float); //������� ���������� �������� ����, ��������������
};

Bullet::Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	//�������������� .�������� ������ ������� ��� �������������� ���� � ������
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
	switch (direction) { //����������� ����� ����
	case 0: dx = -speed; dy = 0;   break;//������� �������� state = left
	case 1: dx = speed; dy = 0;   break;//������� �������� state = right
	}

	x += dx * time * 2;//���� �������� ���� �� �

	//if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
	//if (y <= 0) y = 1;

	for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid � enemy
		if (getRect().intersects(obj[i].rect)) { //���� ���� ������ ���������� � ����� ��� ������
			if (obj[i].name == "solid" || obj[i].name == "EasyEnemy" || obj[i].name == "Enemy")
				life = false;// �� ���� �������
		}
	}

	sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
}