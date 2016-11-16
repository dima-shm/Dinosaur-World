#include <SFML/Graphics.hpp>//������ � �������� ���������� SFML

using namespace sf;

class LifeBar
{
private:
	Image image;
	Texture life_texture;
	Sprite life;
	int max;
	RectangleShape bar;

public:
	LifeBar()
	{
		image.loadFromFile("Images/life.png");
		life_texture.loadFromImage(image);
		life.setTexture(life_texture);
		life.setTextureRect(IntRect(0, 0, 14, 84));

		bar.setFillColor(Color(0, 0, 0));//������ ������������� ������������� ������ � ���������� ������ ���������� ��������
		max = 100;
	}

	void update(int k)// k-������� ��������
	{
		if (k > 0)
		{
			if (k < max)
			{
				bar.setSize(Vector2f(6, (max - k) * 63 / max));//���� �� ������������ � ��� ���� ������ ���������, �� ������������� ����� �������� (����� ������) ��� ������� ��������������
			}
		}
	}

	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		life.setPosition(center.x - size.x / 2 + 12, center.y - size.y / 2 + 10);//������� �� ������
		bar.setPosition(center.x - size.x / 2 + 16, center.y - size.y / 2 + 14);

		window.draw(life);//������� ������ ������� ��������
		window.draw(bar);//������ �� ��� ������ �������������, �� ��� �� ��������� �
	}
};