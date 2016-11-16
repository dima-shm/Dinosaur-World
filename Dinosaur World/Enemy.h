class Enemy 
	: public Entity
{
public:
	Enemy(String F, Level &lvl, float X, float Y, float W, float H) :Entity(F, X, Y, W, H)//Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	{
		obj = lvl.GetObjects("solidForEnemy");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		dx = -0.06;//даем скорость.этот объект всегда двигается
	}

	void update(float time)
	{
		CurrentFrame += 0.003 * time; //служит для прохождения по "кадрам"
		if (CurrentFrame > 7) CurrentFrame -= 7; //проходимся по кадрам
		sprite.setTextureRect(IntRect(81 * int(CurrentFrame), 0, 81, 76));


		interactionWithMap(dx, dy);//обрабатываем столкновение по Х

		x += dx * time;

		sprite.setPosition(x, y); //задаем позицию спрайта в место его центра

		if (health <= 0)
		{
			dx = 0;
			CurrentFrame += 0.00000005 * time; //служит для прохождения по "кадрам"
			sprite.setTextureRect(IntRect(103 * int(CurrentFrame), 82, 103, 76));


			moveTimer += time;
			if (moveTimer > 700) { life = false; }
		}
	}

	void interactionWithMap(float Dx, float Dy)//ф-ция взаимодействия с картой
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "solidForEnemy")//если встретили препятствие
				{
					if (Dy > 0)	{ y = obj[i].rect.top - h;	                dy = 0; }
					if (Dy < 0)	{ y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0)	{ x = obj[i].rect.left - w;					dx = -0.06; sprite.scale(-1, 1); }
					if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.06;  sprite.scale(-1, 1); }
				}
			}
	}
};