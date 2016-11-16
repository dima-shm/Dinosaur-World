#include <SFML/Graphics.hpp>//работа с графикой библиотеки SFML

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

		bar.setFillColor(Color(0, 0, 0));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
		max = 100;
	}

	void update(int k)// k-текущее здоровье
	{
		if (k > 0)
		{
			if (k < max)
			{
				bar.setSize(Vector2f(6, (max - k) * 63 / max));//если не отрицательно и при этом меньше максимума, то устанавливаем новое значение (новый размер) для черного прямоугольника
			}
		}
	}

	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		life.setPosition(center.x - size.x / 2 + 12, center.y - size.y / 2 + 10);//позиция на экране
		bar.setPosition(center.x - size.x / 2 + 16, center.y - size.y / 2 + 14);

		window.draw(life);//сначала рисуем полоску здоровья
		window.draw(bar);//поверх неё уже черный прямоугольник, он как бы покрывает её
	}
};