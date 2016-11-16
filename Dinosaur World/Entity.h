

#include "level.h"

using namespace sf;

class Entity
{
protected:
	std::vector<Object> obj;//������ �������� �����
	float x, y;//�������� ����������, � ������������ Player ���� ����� �� ��������
	float w, h, dx, dy; // dx dy ����� = 0 � ������������ ������ ����
	float health;//����� ����������, �������� ����� ������
	bool life;//���������� �����, ����������
	float speed;//�������� ������
	float CurrentFrame = 0;//������ ������� ����
	float moveTimer;
	bool onGround;

	String File; //���� � �����������
	Image image;//sfml �����������
	Texture texture;//sfml ��������
	Sprite sprite;//sfml ������

	Entity(String F, float X, float Y, float W, float H)
	{
		dx = 0; dy = 0; speed = 0; health = 100; life = true;//������������� ����������
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		x = X; y = Y;//���������� ��������� �������
		moveTimer = 0;

		image.loadFromFile("Images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/Dragon/png");
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
	}

public:
	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
	}

	Sprite getSprite()
	{
		return sprite;
	}

	bool getLife()
	{
		return life;
	}

	void setLife(bool Life)
	{
		life = Life;
	}

	float getHealth()
	{
		return health;
	}

	void setHealth(float Health)
	{
		health = Health;
	}

	FloatRect getRect()//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	{
		return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
	}

	virtual void update(float) = 0;//��� ������� �������������� ��� �-���
};