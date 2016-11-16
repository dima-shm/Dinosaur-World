#include <SFML/Graphics.hpp>

using namespace sf;

View view;//�������� sfml ������ "���", ������� � �������� �������

void getPlayerCoordinateForView(float x, float y) //������� ��� ���������� ��������� ������
{
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	//if (x < 383) tempX = 383;//������� �� ���� ����� �������
	//if (y < 240) tempY = 240;//������� �������
	if (y > 8) tempY = 8;//������ �������

	view.setCenter(tempX, 320); //������ �� �������, ��������� ��� ����������. 
}

void changeView()
{
	if (Keyboard::isKeyPressed(Keyboard::U))
	{
		view.zoom(1.0100f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}
	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		view.setSize(840 + 200, 480 + 200);//�������� ������ ������
	}
	if (Keyboard::isKeyPressed(Keyboard::O))
	{
		view.setSize(960, 640);//�������� ������ ������
	}
}