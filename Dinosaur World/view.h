#include <SFML/Graphics.hpp>

using namespace sf;

View view;//объ€вили sfml объект "вид", который и €вл€етс€ камерой

void getPlayerCoordinateForView(float x, float y) //функци€ дл€ считывани€ координат игрока
{
	float tempX = x; float tempY = y;//считываем коорд игрока и провер€ем их, чтобы убрать кра€

	//if (x < 383) tempX = 383;//убираем из вида левую сторону
	//if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 8) tempY = 8;//нижнюю сторону

	view.setCenter(tempX, 320); //следим за игроком, передава€ его координаты. 
}

void changeView()
{
	if (Keyboard::isKeyPressed(Keyboard::U))
	{
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}
	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		view.setSize(840 + 200, 480 + 200);//например другой размер
	}
	if (Keyboard::isKeyPressed(Keyboard::O))
	{
		view.setSize(960, 640);//например другой размер
	}
}