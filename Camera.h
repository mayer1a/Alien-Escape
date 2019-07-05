#include <Graphics.hpp>

using namespace sf;

View view; //������ ������ view

void setPlayerCam(float x, float y) { //������ ���������� ��� ������
	float tempX = x, tempY = y;
	if (x < 600) {
		tempX = 600;
	}
	if (x > 2400) {
		tempX = 2400;
	}
	if (y < 750) {
		tempY = 750;
	}
	if (y > 1770) {
		tempY = 1770;
	}
	view.setCenter(tempX, tempY); //������������� ����� ������ � ���� �����������
}