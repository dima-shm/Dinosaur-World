#include <SFML/Graphics.hpp>//работа с графикой библиотеки SFML
#include <SFML/Audio.hpp>//работа с аудио библиотеки SFML

#include "Entity.h"//общий класс родитель
#include "Player.h"//класс игрока
#include "Enemy.h"//класс врага
#include "Bullet.h"//класс пули
#include "LifeBar.h"//класс с полосой здоровья

#include "view.h"//подключили код с видом камеры
#include "menu.h"//подключили код меню

#include <sstream>//работа со строками
#include <iostream>//для вывода на консоль

#include "level.h"
#include <vector>
#include <list>


using namespace sf;//пространство имен библиотеки SFML


Level lvl;//создали экземпляр класса уровень


/////////////////////////////////////////////////// Функция Игры ///////////////////////////////////////////////////////////////////////////////////////////
bool startGame(RenderWindow & window)
{
	/////////////////////////////////////////////// Текстуры И Спрайты /////////////////////////////////////////////////////////////////////////////////////
	Music Dinosaur_World_Theme;//создаем объекты Music 
	Dinosaur_World_Theme.openFromFile("Audio/Dinosaur_World_Theme.ogg");//загружаем аудио

	SoundBuffer game_over, go, click, cursor;//создаём буфер для звука
	game_over.loadFromFile("Audio/Game_over.ogg");//загружаем в него звук
	go.loadFromFile("Audio/Go.ogg");
	click.loadFromFile("Audio/Menu/Click.ogg");
	cursor.loadFromFile("Audio/Menu/Cursor.ogg");
	Sound Game_over(game_over), Go(go), Click(click), Cursor(cursor);//создаем объекты Sound и передаём объект SoundBuffer


	Texture result, cursor_img, background;
	Texture restart_button, restart_text;//создаем объекты Texture (текстура)	
	result.loadFromFile("Images/Result.png");//загружаем картинку
	restart_button.loadFromFile("Images/Restart_Button.png");
	restart_text.loadFromFile("Images/Restart_Text.png");
	cursor_img.loadFromFile("Images/cursor.png");
	background.loadFromFile("Images/background.png");
	Sprite Result(result), Restart_Button(restart_button);//создаем объекты Sprite и передаём объект Texture
	Sprite Restart_Text(restart_text), Cursor_img(cursor_img), Background(background);


	Font font;//создаем объекты Font (шрифт)
	font.loadFromFile("CenturyGothic.ttf");//загружаем шрифт
	Text Time("", font, 24);//создаем объект Text (текст). (строка, шрифт, размер шрифта(в пикселях))
	Time.setColor(Color(250, 250, 65));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	window.create(VideoMode(960, 640), "Dinosaur World", Style::Close);
	window.setPosition(Vector2i(10, 10));
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//загружаем иконку
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//устанавливаем иконку
	window.setMouseCursorVisible(false); //убираем курсор
	View fixed = window.getView();


	view.reset(FloatRect(0, 0, 960, 640));//размер "вида" камеры при создании объекта вида камеры


	Clock clocke; //создаем переменную времени, т.о. привязка ко времени(а не загруженности/мощности процессора).
	float CurrentFrame_Coin = 0;//хранит текущий кадр
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры
	int gameTime = 0;//объявили игровое время, инициализировал
	int playWallMusic = 0;//отвечает за проигрованние фоновой музыки


	Object player = lvl.GetObject("Player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	Player Girl("Player.png", lvl, player.rect.left, player.rect.top, 106/2, 90);//создаем объект p класса player,задаем "Player.png" как имя файла


	std::list<Enemy*> rat;//создаю список, сюда буду кидать объекты врагов
	std::list<Enemy*>::iterator it_rat;//итератор чтобы проходить по эл-там списка

	std::list<Bullet*> bullet;//список пуль
	std::list<Bullet*>::iterator it_bullet;


	std::vector<Object> r = lvl.GetObjects("EasyEnemy");//все объекты врага на tmx карте хранятся в этом векторе
	for (int i = 0; i < r.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		rat.push_back(new Enemy("Enemy.png", lvl, r[i].rect.left, r[i].rect.top, 87, 72));//и закидываем в список всех наших врагов с карты


	LifeBar lifeBarPlayer;//экземпляр класса полоски здоровья


	/////////////////////////////////////////////// Цикл С Игрой ///////////////////////////////////////////////////////////////////////////////////////////
	while (window.isOpen())//пока открыто окно window
	{
		float time = clocke.getElapsedTime().asMicroseconds();//дать прошедшее время в микросекундах
		clocke.restart(); //перезагружает время


		time /= 500; //скорость игры


		Event event;
		while (window.pollEvent(event))//проверка состояния на закрытие
		{
			if (event.type == Event::Closed)//если состояние Закрыто
				window.close();//закрываем
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					bullet.push_back(new Bullet("bullet.png", lvl, Girl.getX() + 20, Girl.getY() + 41, 5, 5, Girl.getSide()));//если выстрелили, то появляется пуля. enum передаем как int 
				}
			}
		}


		Cursor_img.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));


		if (Keyboard::isKeyPressed(Keyboard::Escape)){ window.close(); }//если нажата клавиша Esc, то выходим из игры


		/////////////////////////////////////////// Рисуем Карту ///////////////////////////////////////////////////////////////////////////////////////////		
		window.clear();
		window.draw(Background);
		changeView();//камера вида
		window.setView(view);//"оживляем" камеру в окне sfml	
		
		lvl.Draw(window);//рисуем новую карту
		for (it_rat = rat.begin(); it_rat != rat.end(); it_rat++)
		{
			window.draw((*it_rat)->getSprite()); //рисуем entities объекты (сейчас это только враги)
		}
		for (it_bullet = bullet.begin(); it_bullet != bullet.end(); it_bullet++)
		{
			window.draw((*it_bullet)->getSprite()); //рисуем entities объекты (сейчас это только враги)
		}
		lifeBarPlayer.draw(window);//рисуем полоску здоровья
		window.draw(Girl.getSprite());//рисуем спрайт объекта Cat класса Player
		window.setView(fixed);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////// Управление Персонажем И Анимация ///////////////////////////////////////////////////////////////////////
		if (Girl.getLife())
		{
			Girl.update(time);//управление персонажем
			lifeBarPlayer.update(Girl.getHealth());//сюда передаем значение здоровья


			/////////////////////////////////////////////// Убийство Врага И Урон Игроку ///////////////
			for (it_rat = rat.begin(); it_rat != rat.end();)//говорим что проходимся от начала до конца
			{
				Entity *r = *it_rat;//для удобства, чтобы не писать (*it_rat)->
				r->update(time);//вызываем ф-цию update для всех врагов

				if (r->getLife() == false)//если этот объект мертв	
				{
					it_rat = rat.erase(it_rat); delete r;//то удаляем его
				}
				else it_rat++;//и идем итератором к след объекту. так делаем со всеми объектами списка
			}
			for (it_bullet = bullet.begin(); it_bullet != bullet.end();)//говорим что проходимся от начала до конца
			{
				Entity *b = *it_bullet;//для удобства, чтобы не писать (*it_bullet)->
				b->update(time);

				if (b->getLife() == false)//если этот объект мертв	
				{
					it_bullet = bullet.erase(it_bullet); delete b;//то удаляем его
				}
				else it_bullet++;//и идем итератором к след объекту. так делаем со всеми объектами списка
			}

			for (it_rat = rat.begin(); it_rat != rat.end(); it_rat++)//проходимся по эл-там списка врага
			{
				for (it_bullet = bullet.begin(); it_bullet != bullet.end(); it_bullet++)//проходимся по эл-там списка пули
				{
					if ((*it_rat)->getRect().intersects((*it_bullet)->getRect()))//если прямоугольник спрайта врага пересекается с пулей
					{
						(*it_rat)->setHealth((*it_rat)->getHealth() - 50);//то отнимаем здоровье врага
						(*it_bullet)->setHealth(0);
					}
				}

				if ((*it_rat)->getRect().intersects(Girl.getRect()))//если прямоугольник спрайта врага пересекается с игроком
				{
					Girl.setHealth(Girl.getHealth() - 1);//враг наносит урон	
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////


			gameTime = gameTimeClock.getElapsedTime().asSeconds();//игровое время в секундах идёт вперед, пока жив игрок


			if (Dinosaur_World_Theme.getStatus() == false)//играем фоновую музыку
			{
				//Go.play();
				Dinosaur_World_Theme.play();
			}


			getPlayerCoordinateForView(Girl.getPlayerCoordinateX(), Girl.getPlayerCoordinateY());//передаем координаты игрока в функцию управления камерой
		}
		else
		{
			Dinosaur_World_Theme.stop();//останавливаем фоновую музыку
			if (Game_over.getStatus() == false && playWallMusic == 0)//играем фоновую музыку
			{
				Game_over.play();
				playWallMusic = 1;
			}

			/////////////////////////////////////////// Отображение Результата /////////////////////////////////////////////////////////////////////////////
			Vector2f center = window.getView().getCenter();

			Result.setTextureRect(IntRect(0, 0, 190, 200));
			Result.setPosition(center.x + 100, center.y - 100);


			std::ostringstream gameTimeString;//объявили переменную времени
			gameTimeString << gameTime;//формируем строку
			Time.setString(L"Время: " + gameTimeString.str() + L" сек.");//задаем строку тексту и вызываем сформированную выше строку методом .str()
			Time.setPosition(center.x + 120, center.y - 20);//задаем позицию текста, отступая от центра камеры
			window.draw(Result);
			window.draw(Time);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			/////////////////////////////////////////// Кнопка Рестарта ////////////////////////////////////////////////////////////////////////////////////
			Restart_Button.setTextureRect(IntRect(0, 0, 190, 49));
			Restart_Text.setTextureRect(IntRect(0, 0, 190, 45));

			bool restart = false;

			Restart_Text.setColor(Color(250, 250, 65));

			if (IntRect(center.x + 100, center.y + 110, 190, 49).contains(Mouse::getPosition(window)))
			{
				Cursor.play();
				Restart_Text.setColor(Color(186, 0, 1));
				Restart_Text.setPosition(center.x + 100, center.y + 110 + 3);
				Restart_Button.setPosition(center.x + 100, center.y + 110 + 3);
				restart = true;
			}
			else
			{
				Restart_Button.setPosition(center.x + 100, center.y + 110);
				Restart_Text.setPosition(center.x + 100, center.y + 110);
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (restart == true)
				{
					Click.play();
					Girl.setLife(true);
					Girl.setHealth(100);
					return true;
				}
			}


			window.draw(Restart_Button);
			window.draw(Restart_Text);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		window.draw(Cursor_img);
		window.display();//отоброжаем все
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////// Функция Перезагрузки Игры //////////////////////////////////////////////////////////////////////////////
void gameRunning(RenderWindow & window)//ф-ция перезагружает игру , если это необходимо
{
	if (startGame(window) == true)
	{
		gameRunning(window);//то вызываем заново ф-цию gameRunning, которая в свою очередь опять вызывает startGame() 
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void main()
{
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//загружаем иконку
	RenderWindow window(VideoMode(960, 640), "Dinosaur World", Style::None); //создание объекта окна window
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//устанавливаем иконку
	window.setPosition(Vector2i(10, 10));

	lvl.LoadFromFile("map.tmx");//загрузили карту

	menu(window);//вызов меню
}