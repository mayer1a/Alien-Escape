#include "movPlatform.h"

//////////////��������//////////////

class Health :public Entity { //����� ��������
public:
	Health(Image &, String, Level &, float, float, int, int); //�����������
	void update(float); //������� ���������� � ��������������
};

Health::Health(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	obj = lvl.GetObjects("Player");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
	life = true;
	sprite.setTextureRect(IntRect(240, 240, w, h));
	sprite.setScale(0.6, 0.6);
}

void Health::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//������ �� �������� Player
		if (getRect().intersects(obj[i].rect)) { //���� ��� ������ ��������� � ������
			life = false;// �� ������ "�������"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////�������//////////////

class Ammu :public Entity { //����� ��������
public:
	Ammu(Image &, String, Level &, float, float, int, int); //�����������
	void update(float); //���������� � ��������������
};

Ammu::Ammu(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	obj = lvl.GetObjects("Player");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
	life = true;
	sprite.setTextureRect(IntRect(300, 300, w, h));
	sprite.setScale(0.6, 0.6);
}

void Ammu::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//������ �� �������� Player
		if (getRect().intersects(obj[i].rect)) { //���� ��� ������ ��������� � ������
			life = false;// �� ����� �������� "�������"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////�����//////////////

class Acid : public Entity { //��������� �����
public:
	Acid(Image &, String, Level &, float, float, int, int); //�����������
	void update(float); //���������� � ��������������
};

Acid::Acid(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	obj = lvl.GetObjects("Player");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
	life = true;
	sprite.setTextureRect(IntRect(180, 0, w, h));
}

void Acid::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//������ �� �������� Player
		if (getRect().intersects(obj[i].rect)) { //���� ��� ������ ��������� � ������
			life = false;// �� ����� "�������"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}

//////////////����������//////////////

class Bang : public Entity { //���������� �����
public:
	Bang(Image &, String, Level &, float, float, int, int); //�����������
	void update(float); //�������������� � ����������
};

Bang::Bang(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	obj = lvl.GetObjects("Player");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
	life = true;
	sprite.setTextureRect(IntRect(120, 0, w, h));
}

void Bang::update(float time) {
	for (int i = 0; i < obj.size(); i++) {//������ �� �������� Player
		if (getRect().intersects(obj[i].rect)) { //���� ��� ������ ��������� � ������
			life = false;// �� ����� "�������"
		}
	}
	sprite.setPosition(x + w / 2, y + h / 2);
}
