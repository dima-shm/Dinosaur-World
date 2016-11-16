class Player 
	: public Entity
{
private:
	enum { left, right, up, down, stay, jump } condition;//перечисление состояний игрока
	enum { leftSide, rightSide } side;

public:
	Player(String F, Level &lev, float X, float Y, float W, float H) :Entity(F, X, Y, W, H)//Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	{
		onGround = false;
		obj = lev.GetAllObjects();//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		speed = 0.18;
		sprite.setTextureRect(IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник
	}

	void controlAndAnimation(float time)
	{
		if (life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && (onGround == true))
			{
				condition = jump; onGround = false;
			}
			else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)))
			{
				condition = left;
				side = leftSide;

				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(106 * int(CurrentFrame), 90, 106, 90));
			}
			else if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)))
			{
				condition = right;
				side = rightSide;

				CurrentFrame += 0.005 * time;
				if (CurrentFrame > 8) CurrentFrame -= 8;
				sprite.setTextureRect(IntRect(106 * int(CurrentFrame), 90, 106, 90));
			}
			else
			{
				condition = stay;

				CurrentFrame += 0.005 * time; //служит для прохождения по "кадрам"
				if (CurrentFrame > 10) CurrentFrame -= 10; //проходимся по кадрам
				sprite.setTextureRect(IntRect(106 * int(CurrentFrame), 0, 106, 90));
			}

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				CurrentFrame += 0.003 * time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(106 * int(CurrentFrame), 180, 106, 90));
			}
			if (onGround == false)
			{
				CurrentFrame += 0.003 * time;
				if (CurrentFrame > 10) CurrentFrame -= 10;
				sprite.setTextureRect(IntRect(106 * int(CurrentFrame), 270, 106, 90));
			}
		}
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		controlAndAnimation(time);//вызываем функцию управления. передаем время для бонуса ускорения

		switch (condition)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case left:  dx = -speed; dy = 0;      break;
		case right: dx = speed;  dy = 0;      break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case up:    dx = 0;      dy = -speed; break;
		case down:  dx = 0;      dy = speed;  break;
		case stay:  dx = 0;      dy = 0;      break;
		case jump:	dy -= 15;                 break;
		}

		x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х

		dy = dy + 0.02*time;//делаем притяжение к земле
		y += dy * time;//аналогично по игреку
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y


		if (side == leftSide)
		{
			sprite.setScale(-1, 1);//отоброжаем спрайт зеркально
			sprite.setPosition(x + 106/2, y);//задается позицию
		}
		if (side == rightSide)
		{
			sprite.setScale(1, 1);
			sprite.setPosition(x, y);//задаем позицию спрайта в место его центра
		}



		if (health <= 0)//если жизней меньше либо равно 0, то
		{
			life = false;//умираем
			speed = 0;//исключаем движение игрока после смерти
			//CurrentFrame = 0;//останавливаем анимацию игрока
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф-ция взаимодействия с картой
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solid")//если встретили препятствие
				{
					if (Dy > 0)	{ y = obj[i].rect.top - h; dy = 0; onGround = true; }
					if (Dy < 0)	{ y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0)	{ x = obj[i].rect.left - w; }
					if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "water")//если встретили кислоту
				{
					health -= 1;
				}
				if (obj[i].name == "SlopeLeft")
				{
					FloatRect r = obj[i].rect;
					
					int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
					if (y > y0)
					{
						if (x + w / 2 > r.left)
						{
							y = y0; dy = 0; condition = stay;
						}
					}
				}
				if (obj[i].name == "SlopeRight")
				{
					FloatRect r = obj[i].rect;
					
					int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
					if (y > y0)
					{
						if (x + w / 2 < r.left + r.width)
						{
							y = y0; dy = 0; condition = stay;
						}
					}
				}
			}
	}

	int getHealth()
	{
		return health;
	}

	float getPlayerCoordinateX()//этим методом будем забирать координату Х	
	{
		return x;
	}

	float getPlayerCoordinateY()//этим методом будем забирать координату Y 
	{
		return y;
	}

	int getSide()
	{
		return side;
	}
};