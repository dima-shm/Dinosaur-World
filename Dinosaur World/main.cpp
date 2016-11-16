#include <SFML/Graphics.hpp>//������ � �������� ���������� SFML
#include <SFML/Audio.hpp>//������ � ����� ���������� SFML

#include "Entity.h"//����� ����� ��������
#include "Player.h"//����� ������
#include "Enemy.h"//����� �����
#include "Bullet.h"//����� ����
#include "LifeBar.h"//����� � ������� ��������

#include "view.h"//���������� ��� � ����� ������
#include "menu.h"//���������� ��� ����

#include <sstream>//������ �� ��������
#include <iostream>//��� ������ �� �������

#include "level.h"
#include <vector>
#include <list>


using namespace sf;//������������ ���� ���������� SFML


Level lvl;//������� ��������� ������ �������


/////////////////////////////////////////////////// ������� ���� ///////////////////////////////////////////////////////////////////////////////////////////
bool startGame(RenderWindow & window)
{
	/////////////////////////////////////////////// �������� � ������� /////////////////////////////////////////////////////////////////////////////////////
	Music Dinosaur_World_Theme;//������� ������� Music 
	Dinosaur_World_Theme.openFromFile("Audio/Dinosaur_World_Theme.ogg");//��������� �����

	SoundBuffer game_over, go, click, cursor;//������ ����� ��� �����
	game_over.loadFromFile("Audio/Game_over.ogg");//��������� � ���� ����
	go.loadFromFile("Audio/Go.ogg");
	click.loadFromFile("Audio/Menu/Click.ogg");
	cursor.loadFromFile("Audio/Menu/Cursor.ogg");
	Sound Game_over(game_over), Go(go), Click(click), Cursor(cursor);//������� ������� Sound � ������� ������ SoundBuffer


	Texture result, cursor_img, background;
	Texture restart_button, restart_text;//������� ������� Texture (��������)	
	result.loadFromFile("Images/Result.png");//��������� ��������
	restart_button.loadFromFile("Images/Restart_Button.png");
	restart_text.loadFromFile("Images/Restart_Text.png");
	cursor_img.loadFromFile("Images/cursor.png");
	background.loadFromFile("Images/background.png");
	Sprite Result(result), Restart_Button(restart_button);//������� ������� Sprite � ������� ������ Texture
	Sprite Restart_Text(restart_text), Cursor_img(cursor_img), Background(background);


	Font font;//������� ������� Font (�����)
	font.loadFromFile("CenturyGothic.ttf");//��������� �����
	Text Time("", font, 24);//������� ������ Text (�����). (������, �����, ������ ������(� ��������))
	Time.setColor(Color(250, 250, 65));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	window.create(VideoMode(960, 640), "Dinosaur World", Style::Close);
	window.setPosition(Vector2i(10, 10));
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//��������� ������
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//������������� ������
	window.setMouseCursorVisible(false); //������� ������
	View fixed = window.getView();


	view.reset(FloatRect(0, 0, 960, 640));//������ "����" ������ ��� �������� ������� ���� ������


	Clock clocke; //������� ���������� �������, �.�. �������� �� �������(� �� �������������/�������� ����������).
	float CurrentFrame_Coin = 0;//������ ������� ����
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ����
	int gameTime = 0;//�������� ������� �����, ���������������
	int playWallMusic = 0;//�������� �� ������������� ������� ������


	Object player = lvl.GetObject("Player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	Player Girl("Player.png", lvl, player.rect.left, player.rect.top, 106/2, 90);//������� ������ p ������ player,������ "Player.png" ��� ��� �����


	std::list<Enemy*> rat;//������ ������, ���� ���� ������ ������� ������
	std::list<Enemy*>::iterator it_rat;//�������� ����� ��������� �� ��-��� ������

	std::list<Bullet*> bullet;//������ ����
	std::list<Bullet*>::iterator it_bullet;


	std::vector<Object> r = lvl.GetObjects("EasyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������
	for (int i = 0; i < r.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		rat.push_back(new Enemy("Enemy.png", lvl, r[i].rect.left, r[i].rect.top, 87, 72));//� ���������� � ������ ���� ����� ������ � �����


	LifeBar lifeBarPlayer;//��������� ������ ������� ��������


	/////////////////////////////////////////////// ���� � ����� ///////////////////////////////////////////////////////////////////////////////////////////
	while (window.isOpen())//���� ������� ���� window
	{
		float time = clocke.getElapsedTime().asMicroseconds();//���� ��������� ����� � �������������
		clocke.restart(); //������������� �����


		time /= 500; //�������� ����


		Event event;
		while (window.pollEvent(event))//�������� ��������� �� ��������
		{
			if (event.type == Event::Closed)//���� ��������� �������
				window.close();//���������
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Space))
				{
					bullet.push_back(new Bullet("bullet.png", lvl, Girl.getX() + 20, Girl.getY() + 41, 5, 5, Girl.getSide()));//���� ����������, �� ���������� ����. enum �������� ��� int 
				}
			}
		}


		Cursor_img.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));


		if (Keyboard::isKeyPressed(Keyboard::Escape)){ window.close(); }//���� ������ ������� Esc, �� ������� �� ����


		/////////////////////////////////////////// ������ ����� ///////////////////////////////////////////////////////////////////////////////////////////		
		window.clear();
		window.draw(Background);
		changeView();//������ ����
		window.setView(view);//"��������" ������ � ���� sfml	
		
		lvl.Draw(window);//������ ����� �����
		for (it_rat = rat.begin(); it_rat != rat.end(); it_rat++)
		{
			window.draw((*it_rat)->getSprite()); //������ entities ������� (������ ��� ������ �����)
		}
		for (it_bullet = bullet.begin(); it_bullet != bullet.end(); it_bullet++)
		{
			window.draw((*it_bullet)->getSprite()); //������ entities ������� (������ ��� ������ �����)
		}
		lifeBarPlayer.draw(window);//������ ������� ��������
		window.draw(Girl.getSprite());//������ ������ ������� Cat ������ Player
		window.setView(fixed);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////// ���������� ���������� � �������� ///////////////////////////////////////////////////////////////////////
		if (Girl.getLife())
		{
			Girl.update(time);//���������� ����������
			lifeBarPlayer.update(Girl.getHealth());//���� �������� �������� ��������


			/////////////////////////////////////////////// �������� ����� � ���� ������ ///////////////
			for (it_rat = rat.begin(); it_rat != rat.end();)//������� ��� ���������� �� ������ �� �����
			{
				Entity *r = *it_rat;//��� ��������, ����� �� ������ (*it_rat)->
				r->update(time);//�������� �-��� update ��� ���� ������

				if (r->getLife() == false)//���� ���� ������ �����	
				{
					it_rat = rat.erase(it_rat); delete r;//�� ������� ���
				}
				else it_rat++;//� ���� ���������� � ���� �������. ��� ������ �� ����� ��������� ������
			}
			for (it_bullet = bullet.begin(); it_bullet != bullet.end();)//������� ��� ���������� �� ������ �� �����
			{
				Entity *b = *it_bullet;//��� ��������, ����� �� ������ (*it_bullet)->
				b->update(time);

				if (b->getLife() == false)//���� ���� ������ �����	
				{
					it_bullet = bullet.erase(it_bullet); delete b;//�� ������� ���
				}
				else it_bullet++;//� ���� ���������� � ���� �������. ��� ������ �� ����� ��������� ������
			}

			for (it_rat = rat.begin(); it_rat != rat.end(); it_rat++)//���������� �� ��-��� ������ �����
			{
				for (it_bullet = bullet.begin(); it_bullet != bullet.end(); it_bullet++)//���������� �� ��-��� ������ ����
				{
					if ((*it_rat)->getRect().intersects((*it_bullet)->getRect()))//���� ������������� ������� ����� ������������ � �����
					{
						(*it_rat)->setHealth((*it_rat)->getHealth() - 50);//�� �������� �������� �����
						(*it_bullet)->setHealth(0);
					}
				}

				if ((*it_rat)->getRect().intersects(Girl.getRect()))//���� ������������� ������� ����� ������������ � �������
				{
					Girl.setHealth(Girl.getHealth() - 1);//���� ������� ����	
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////


			gameTime = gameTimeClock.getElapsedTime().asSeconds();//������� ����� � �������� ��� ������, ���� ��� �����


			if (Dinosaur_World_Theme.getStatus() == false)//������ ������� ������
			{
				//Go.play();
				Dinosaur_World_Theme.play();
			}


			getPlayerCoordinateForView(Girl.getPlayerCoordinateX(), Girl.getPlayerCoordinateY());//�������� ���������� ������ � ������� ���������� �������
		}
		else
		{
			Dinosaur_World_Theme.stop();//������������� ������� ������
			if (Game_over.getStatus() == false && playWallMusic == 0)//������ ������� ������
			{
				Game_over.play();
				playWallMusic = 1;
			}

			/////////////////////////////////////////// ����������� ���������� /////////////////////////////////////////////////////////////////////////////
			Vector2f center = window.getView().getCenter();

			Result.setTextureRect(IntRect(0, 0, 190, 200));
			Result.setPosition(center.x + 100, center.y - 100);


			std::ostringstream gameTimeString;//�������� ���������� �������
			gameTimeString << gameTime;//��������� ������
			Time.setString(L"�����: " + gameTimeString.str() + L" ���.");//������ ������ ������ � �������� �������������� ���� ������ ������� .str()
			Time.setPosition(center.x + 120, center.y - 20);//������ ������� ������, �������� �� ������ ������
			window.draw(Result);
			window.draw(Time);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			/////////////////////////////////////////// ������ �������� ////////////////////////////////////////////////////////////////////////////////////
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
		window.display();//���������� ���
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////// ������� ������������ ���� //////////////////////////////////////////////////////////////////////////////
void gameRunning(RenderWindow & window)//�-��� ������������� ���� , ���� ��� ����������
{
	if (startGame(window) == true)
	{
		gameRunning(window);//�� �������� ������ �-��� gameRunning, ������� � ���� ������� ����� �������� startGame() 
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void main()
{
	Image icon;
	icon.loadFromFile("Images/Dinosaur_World_Icon.png");//��������� ������
	RenderWindow window(VideoMode(960, 640), "Dinosaur World", Style::None); //�������� ������� ���� window
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//������������� ������
	window.setPosition(Vector2i(10, 10));

	lvl.LoadFromFile("map.tmx");//��������� �����

	menu(window);//����� ����
}