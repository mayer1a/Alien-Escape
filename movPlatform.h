#include "Bullet.h"

class movingPlatform : public Entity {//����� ���������� ���������
public:
	movingPlatform(Image &, String, Level &, float, float, int, int); //�����������
	void update(float); //������� ���������� ��� �������� ���������
};

movingPlatform::movingPlatform(Image &image, String Name, Level &lvl, float x, float y, int w, int h) :Entity(image, Name, x, y, w, h) { 
	//��������������
	sprite.setTextureRect(IntRect(360, 60, w, h));//������ ������ ���������
	dy = 0.08;//�������� �������� �� y
}

void movingPlatform::update(float time) {
	y += dy * time;//�������� �� ���������
	moveTimer += time;//����������� ������
	
	if (moveTimer>2000) { //���� ������ 2 ���, ����� ����������� �������� ���������
		dy *= -1; //������ ����������� �������� ��������� 
		moveTimer = 0; //���������� ������
	}

	sprite.setPosition(x + w / 2, y + h / 2);//������ ������� �������
}