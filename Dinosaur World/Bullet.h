class Bullet 
	: public Entity
{
private:
	int direction;

public:	
	Bullet(String F, Level &lvl, float X, float Y, float W, float H, int dir) :Entity(F, X, Y, W, H){//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.4;
		w = W;
		h = H;
		//выше инициализация в конструкторе
	}

	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;    break;
		case 1: dx = speed; dy = 0;     break;
		default: x = 0; y = 0;
		}


		x += dx*time;//само движение пули по х
		y += dy*time;//по у

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;


		for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
			if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
			{
				life = false;// то пуля умирает
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле

		if (health <= 0){ life = false; }
	}
};