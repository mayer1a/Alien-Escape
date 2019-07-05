#include "Entity.h"

class Hero : public Entity { //����� ������
public:
	enum { left, right, stay } state; //������ ����������, �������� ��������� �����
	int shop, dir; //����������, �������� ���� ������
	bool isShot; //��������� ��������
	float currentFrame; //���������� �������� ����� ��� ��������

	Hero(Image &, String, Level, float, float, int, int); //�����������
	void control(); //������� �������� ��������
	void checkCollision(float, float); //������� �������� ������������
	void update(float); //���������� ��������, �����������, ��������������
};

Hero::Hero(Image &image, String name, Level lvl, float x, float y, int w, int h) :Entity(image, name, x, y, w, h) {
	shop = 0; currentFrame = 0;
	state = stay; obj = lvl.GetObjects("solid");//��������������, �������� ��� ������� ��� �������������� ��������� � ������
	isShot = false; //�������� ��� ���
	sprite.setTextureRect(IntRect(0, 80, w, h)); //����� ������ �����
}

void Hero::control() {
	if (Keyboard::isKeyPressed(Keyboard::Left)) { //���� ������� �������� �����
		state = left; //��������� - �����
		dir = 0; //��� ����������� ����� ������
		speed = 0.15; //��������
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) { //���� ������� �������� ������
		state = right; //��������� - ������
		dir = 1; //��� ����������� ����� ������
		speed = 0.15; //��������
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) { //���� ������� ������ � ���������=�� �����
		dy = -0.6; //�������� "�����������"
		onGround = false; //������ �� �� �����, ����� �� ������� � �������
	}
	if (Keyboard::isKeyPressed(Keyboard::Return)) { //���� ������ Enter, ����������
		isShot = true; //��������� �������� - ��
	}
}

void Hero::checkCollision(float Dx, float Dy) {
	for (int i = 0; i < obj.size(); i++) {//���������� �� ��������
		if (getRect().intersects(obj[i].rect)) {//��������� ����������� ������ � ��������
												//���� ��������� �����������
			if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; } //���� �� �����
			if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; } //���� � �������
			if (Dx > 0) { x = obj[i].rect.left - w; } //���� ��� ������
			if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; } //���� ��� �����
		}
	}
}

void Hero::update(float time) {
	if (life) { //���� ����� ���
		control(); //������� �������� ��������
		switch (state) { //�������, � ����� ��������� �����
		case right: dx = speed; //���� ��������� - ������, ��������� �������� = �������������
			currentFrame += 0.007*time; //������� �������� �����
			if (currentFrame > 3) { //���� ������ ������ ���, ������������ �� ������ ������������ ��������
				currentFrame -= 3;
			}
			//���������� ��� ����� �������, ������� ��������� ��� ��������
			sprite.setTextureRect(IntRect(45 * int(currentFrame), 80, 44, 70));
			state = stay; //��������� �����������
			break;

		case left: dx = -speed; //���� ��������� - �����, ��������� �������� = �������������
			currentFrame += 0.007*time; //������� �������� �����
			if (currentFrame > 3) { //���� ������ ������ ���, ������������ �� ������ ������������ ��������
				currentFrame -= 3;
			}
			//���������� ��� ����� �������, ������� ��������� ��� ��������
			sprite.setTextureRect(IntRect(45 * int(currentFrame) + 44, 80, -44, 70));
			state = stay; //��������� �����������
			break;

		case stay: dx = 0; break; //���� �����, ������� �� �������� = 0
		}

		x += dx * time; //������ ���������� � �����������*�����, ����� ���� ��������� � �������� ��������
		checkCollision(dx, 0); //�������� �� ������������
		y += dy * time;
		checkCollision(0, dy);

		sprite.setPosition(x + w / 2, y + h / 2); //������������� ������� �������
		if (health <= 0) { //���� � ������ 0 ������
			life = false;  //�� �����
		}
		speed = 0; //��������, ����� �� ����������� "���������" ������� ���������
		dy = dy + 0.00104*time; //���������� ��� �����
		setPlayerCam(x, y); //������ ������� ������
	}
}