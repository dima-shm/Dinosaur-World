

#include "level.h"

using namespace sf;

class Entity
{
protected:
	std::vector<Object> obj;//вектор объектов карты
	float x, y;//объявили переменные, в конструкторе Player ниже дадим им значения
	float w, h, dx, dy; // dx dy будут = 0 в конструкторе класса ниже
	float health;//новая переменная, хранящая жизни игрока
	bool life;//переменная жизнь, логическая
	float speed;//скорость игрока
	float CurrentFrame = 0;//хранит текущий кадр
	float moveTimer;
	bool onGround;

	String File; //файл с расширением
	Image image;//sfml изображение
	Texture texture;//sfml текстура
	Sprite sprite;//sfml спрайт

	Entity(String F, float X, float Y, float W, float H)
	{
		dx = 0; dy = 0; speed = 0; health = 100; life = true;//инициализация переменных
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		x = X; y = Y;//координата появления спрайта
		moveTimer = 0;

		image.loadFromFile("Images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/Dragon/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
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

	FloatRect getRect()//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	{
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	virtual void update(float) = 0;//все потомки переопределяют эту ф-цию
};