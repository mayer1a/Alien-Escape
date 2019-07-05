#include "Objects.h"

class LifeBar { //����� ���-����
public:
	Image lifeIm; //����������� ������� �����
	Texture lifeT; //��������
	Sprite healthSp, ammuSp, timeSp; //�������
	int maxH,maxA; //������������ �������� �������� � ��������
	RectangleShape healthBar, ammuBar;

	LifeBar(); //�����������
	void update(int, int); //������� ���������� ����� ������� ���������������
	void draw(RenderWindow &window); //������� ����������
};

LifeBar::LifeBar() {
	lifeIm.loadFromFile("Resourses/Images/lifebar.png"); //��������� �������� ������ ����
	lifeT.loadFromImage(lifeIm); //������ ��������
	healthSp.setTexture(lifeT); //������ ��� ������ �������
	ammuSp.setTexture(lifeT);
	timeSp.setTexture(lifeT);
	healthSp.setTextureRect(IntRect(340, 0, 680, 80)); //������������� ������������� ��� ������� ��������������
	ammuSp.setTextureRect(IntRect(0, 0, 330, 90));
	timeSp.setTextureRect(IntRect(0, 90, 330, 167));
	healthSp.setScale(0.5, 0.5); ammuSp.setScale(0.5, 0.5); timeSp.setScale(0.63, 0.5); //������������ ������� ������ ����
	healthBar.setFillColor(Color(0, 0, 0)); //������ ������������� ������������� ������ � ���������� ������ ���������� ��������
	ammuBar.setFillColor(Color(0, 0, 0)); //������������� �� ��� "������", �� ���� ����������� ��������, ������ ������������� �����������
	maxH = 100; maxA = 500; //������������ ��������, ���������� ��������
}

void LifeBar::update(int k, int j) {
	//k - ������� ��������, j - ���������� ��������
	if (k > 0 && k < maxH) { 
		//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� ������ ��� ������� ��������������
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
	Vector2f center = window.getView().getCenter(); //������ ����� ������ �������������� � ��� ������
	Vector2f size = window.getView().getSize();

	healthSp.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10); //������� �� ������
	healthBar.setPosition(center.x - size.x / 2 + 59, center.y - size.y / 2 + 23); //��� ��������

	ammuSp.setPosition(center.x - size.x / 2 + 210, center.y - size.y / 2 + 7);//������� �� ������
	ammuBar.setPosition(center.x - size.x / 2 + 255, center.y - size.y / 2 + 21); //��� ��������

	timeSp.setPosition(center.x - size.x / 2 + 410, center.y - size.y / 2 + 10);//������� �� ������ ��� �������

	window.draw(healthSp);//������� ������ ������� ��������
	window.draw(ammuSp);//������ ������� ��������
	window.draw(timeSp);//������ ������� ��� �������
	window.draw(healthBar);//������ ��� ������ ������������� ��� ������� ��������
	window.draw(ammuBar);//������ �� ��� ������ ������������� ��� ������� ��������
}