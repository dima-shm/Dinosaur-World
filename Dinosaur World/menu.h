#include <SFML/Graphics.hpp>//работа с графикой библиотеки SFML


using namespace sf;//пространство имен библиотеки SFML


void gameRunning(RenderWindow & window);//предопределение функции
void setting(RenderWindow & window);


void menu(RenderWindow & window)
{
	window.create(VideoMode(960, 640), "Dinosaur World | Menu", Style::Close);
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//загружаем иконку
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//устанавливаем иконку
	window.setPosition(Vector2i(10, 10));


	window.setMouseCursorVisible(false); //убираем курсор
	View fixed = window.getView();


	/////////////////////////////////////////////// Текстуры И Спрайты /////////////////////////
	Texture wall_cat, wall_about, wall_setting, button, new_game;
	Texture about_program, setting_text, exit, cursor;
	wall_cat.loadFromFile("Images/Menu/Wall_Dinosaur_World.png");
	button.loadFromFile("Images/Menu/Button.png");
	new_game.loadFromFile("Images/Menu/New_game.png");
	about_program.loadFromFile("Images/Menu/About_program.png");
	exit.loadFromFile("Images/Menu/Exit.png");
	setting_text.loadFromFile("Images/Menu/Setting.png");
	wall_about.loadFromFile("Images/Menu/Wall_About.png");
	cursor.loadFromFile("Images/cursor.png");
	Sprite Wall_Dinosaur_World(wall_cat), Wall_About(wall_about), Wall_Setting(wall_setting);
	Sprite Button_1(button), Button_2(button), Button_3(button), Button_4(button), New_game(new_game);
	Sprite About_program(about_program), Exit(exit), Setting(setting_text), Cursor(cursor);


	SoundBuffer click, cursorSound;//создаём буфер для звука
	click.loadFromFile("Audio/Menu/Click.ogg");//загружаем в него звук
	cursorSound.loadFromFile("Audio/Menu/Cursor.ogg");//загружаем в него звук
	Sound Click(click), CursorSound(cursorSound);//создаем звук и загружаем в него звук из буфера
	////////////////////////////////////////////////////////////////////////////////////////////


	bool Menu = true;
	int MenuNum = 0;

	Wall_Dinosaur_World.setPosition(0, 0);

	while (window.isOpen())//пока открыто окно window
	{
		while (Menu)
		{
			Event event;
			while (window.pollEvent(event))//проверка состояния на закрытие
			{
				if (event.type == Event::Closed)//если состояние Закрыто
					window.close();//закрываем
			}


			Cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));


			New_game.setColor(Color(250, 250, 65));
			About_program.setColor(Color(250, 250, 65));
			Setting.setColor(Color(250, 250, 65));
			Exit.setColor(Color(250, 250, 65));

			MenuNum = 0;

			window.clear();

			/////////////////////////////////////////// Если навели курсор /////////////////////////////
			if (IntRect(30, 320, 208, 54).contains(Mouse::getPosition(window)))
			{
				CursorSound.play();
				New_game.setColor(Color(186, 0, 1));
				New_game.setPosition(65, 333 + 3);
				Button_1.setPosition(30, 320 + 3);
				MenuNum = 1;
			}
			if (IntRect(30, 380, 208, 54).contains(Mouse::getPosition(window)))
			{
				CursorSound.play();
				About_program.setColor(Color(186, 0, 1));
				About_program.setPosition(36, 393 + 3);
				Button_2.setPosition(30, 380 + 3);
				MenuNum = 2;
			}
			if (IntRect(30, 440, 208, 54).contains(Mouse::getPosition(window)))
			{
				CursorSound.play();
				Setting.setColor(Color(186, 0, 1));
				Setting.setPosition(55, 453 + 3);
				Button_3.setPosition(30, 440 + 3);
				MenuNum = 3;
			}
			if (IntRect(30, 500, 208, 54).contains(Mouse::getPosition(window)))
			{
				CursorSound.play();
				Exit.setColor(Color(186, 0, 1));
				Exit.setPosition(100, 513 + 3);
				Button_4.setPosition(30, 500 + 3);
				MenuNum = 4;
			}
			////////////////////////////////////////////////////////////////////////////////////////////


			/////////////////////////////////////////// Клик мыши //////////////////////////////////////
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (MenuNum == 1)
				{
					Click.play();
					Menu = false;
					gameRunning(window);//запускаем процесс игры
				}
				if (MenuNum == 2)
				{
					Click.play();
					window.create(VideoMode(960, 640), "Dinosaur World | About program", Style::Close);
					window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//устанавливаем иконку
					window.setPosition(Vector2i(10, 10));


					window.setMouseCursorVisible(false); //убираем курсор
					View fixed = window.getView();


					while (window.isOpen())//пока открыто окно window
					{

						Event event;
						while (window.pollEvent(event))//проверка состояния на закрытие
						{
							if (event.type == Event::Closed)//если состояние Закрыто
								window.close();//закрываем
						}


						Cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));


						window.clear();
						window.draw(Wall_About);
						window.setView(fixed);
						window.draw(Cursor);
						window.display();

						if (Keyboard::isKeyPressed(Keyboard::Escape))
						{
							menu(window);
						}
					}
				}
				if (MenuNum == 3)
				{
					Click.play();
					setting(window);
				}
				if (MenuNum == 4)
				{
					window.close();
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////


			/////////////////////////////////////////// Если курсор вне ////////////////////////////////
			if (!(IntRect(30, 320, 208, 54).contains(Mouse::getPosition(window))))
			{
				New_game.setPosition(65, 333); Button_1.setPosition(30, 320);
			}
			if (!(IntRect(30, 380, 208, 54).contains(Mouse::getPosition(window))))
			{
				About_program.setPosition(36, 393); Button_2.setPosition(30, 380);
			}
			if (!(IntRect(30, 440, 208, 54).contains(Mouse::getPosition(window))))
			{
				Setting.setPosition(55, 453); Button_3.setPosition(30, 440);
			}
			if (!(IntRect(30, 500, 208, 54).contains(Mouse::getPosition(window))))
			{
				Exit.setPosition(100, 513); Button_4.setPosition(30, 500);
			}
			////////////////////////////////////////////////////////////////////////////////////////////


			window.draw(Wall_Dinosaur_World);
			window.draw(Button_1);
			window.draw(Button_2);
			window.draw(Button_3);
			window.draw(Button_4);
			window.draw(New_game);
			window.draw(About_program);
			window.draw(Setting);
			window.draw(Exit);
			window.setView(fixed);
			window.draw(Cursor);
			window.display();
		}
	}
}


void setting(RenderWindow & window)
{
	window.create(VideoMode(960, 640), "Dinosaur World | Setting", Style::Close);
	window.setPosition(Vector2i(10, 10));
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//загружаем иконку
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//устанавливаем иконку


	window.setMouseCursorVisible(false); //убираем курсор
	View fixed = window.getView();


	/////////////////////////////////////////////// Текстуры И Спрайты /////////////////////////
	Texture wall_setting, button_setting, cursor;
	wall_setting.loadFromFile("Images/Menu/Wall_Setting.png");
	button_setting.loadFromFile("Images/Menu/Button_setting.png");
	cursor.loadFromFile("Images/cursor.png");
	Sprite Wall_Setting(wall_setting), Button_setting_1(button_setting), Button_setting_2(button_setting);
	Sprite Button_setting_3(button_setting), Cursor(cursor);


	SoundBuffer click, cursorSound;//создаём буфер для звука
	click.loadFromFile("Audio/Menu/Click.ogg");//загружаем в него звук
	cursorSound.loadFromFile("Audio/Menu/Cursor.ogg");
	Sound Click(click), CursorSound(cursorSound);//создаем звук и загружаем в него звук из буфера
	////////////////////////////////////////////////////////////////////////////////////////////


	Button_setting_1.setPosition(100, 100);
	Button_setting_2.setPosition(200, 100);
	Button_setting_3.setPosition(300, 100);


	while (window.isOpen())//пока открыто окно window
	{
		Event event;
		while (window.pollEvent(event))//проверка состояния на закрытие
		{
			if (event.type == Event::Closed)//если состояние Закрыто
				window.close();//закрываем
		}


		Cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));


		window.clear();


		int SettingNum = 0;


		/////////////////////////////////////////// Если навели курсор /////////////////////////////
		if (IntRect(100, 100, 49, 49).contains(Mouse::getPosition(window)))
		{
			CursorSound.play();
			Button_setting_1.setPosition(100, 100 + 3);
			SettingNum = 1;
		}
		if (IntRect(200, 100, 49, 49).contains(Mouse::getPosition(window)))
		{
			CursorSound.play();
			Button_setting_2.setPosition(200, 100 + 3);
			SettingNum = 2;
		}
		if (IntRect(300, 100, 49, 49).contains(Mouse::getPosition(window)))
		{
			CursorSound.play();
			Button_setting_3.setPosition(300, 100 + 3);
			SettingNum = 3;
		}
		////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////// Клик мыши //////////////////////////////////////
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (SettingNum == 1)
			{
				Click.play();
			}
			if (SettingNum == 2)
			{
				Click.play();
			}
			if (SettingNum == 3)
			{
				Click.play();
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////// Если курсор вне ////////////////////////////////
		if (!(IntRect(100, 100, 49, 49).contains(Mouse::getPosition(window))))
		{
			Button_setting_1.setPosition(100, 100);
		}
		if (!(IntRect(200, 100, 49, 49).contains(Mouse::getPosition(window))))
		{
			Button_setting_2.setPosition(200, 100);
		}
		if (!(IntRect(300, 100, 49, 49).contains(Mouse::getPosition(window))))
		{
			Button_setting_3.setPosition(300, 100);
		}
		////////////////////////////////////////////////////////////////////////////////////////////


		if (!Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.draw(Wall_Setting);
		}
		else
		{
			menu(window);
		}


		window.draw(Button_setting_1);
		window.draw(Button_setting_2);
		window.draw(Button_setting_3);
		window.setView(fixed);
		window.draw(Cursor);
		window.display();
	}
}