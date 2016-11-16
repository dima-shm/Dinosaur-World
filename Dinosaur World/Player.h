class Player 
	: public Entity
{
private:
	enum { left, right, up, down, stay, jump } condition;//������������ ��������� ������
	enum { leftSide, rightSide } side;

public:
	Player(String F, Level &lev, float X, float Y, float W, float H) :Entity(F, X, Y, W, H)//����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	{
		onGround = false;
		obj = lev.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������
		speed = 0.18;
		sprite.setTextureRect(IntRect(0, 0, w, h));  //������ ������� ���� �������������
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

				CurrentFrame += 0.005 * time; //������ ��� ����������� �� "������"
				if (CurrentFrame > 10) CurrentFrame -= 10; //���������� �� ������
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

	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		controlAndAnimation(time);//�������� ������� ����������. �������� ����� ��� ������ ���������

		switch (condition)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case left:  dx = -speed; dy = 0;      break;
		case right: dx = speed;  dy = 0;      break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case up:    dx = 0;      dy = -speed; break;
		case down:  dx = 0;      dy = speed;  break;
		case stay:  dx = 0;      dy = 0;      break;
		case jump:	dy -= 15;                 break;
		}

		x += dx * time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �

		dy = dy + 0.02*time;//������ ���������� � �����
		y += dy * time;//���������� �� ������
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y


		if (side == leftSide)
		{
			sprite.setScale(-1, 1);//���������� ������ ���������
			sprite.setPosition(x + 106/2, y);//�������� �������
		}
		if (side == rightSide)
		{
			sprite.setScale(1, 1);
			sprite.setPosition(x, y);//������ ������� ������� � ����� ��� ������
		}



		if (health <= 0)//���� ������ ������ ���� ����� 0, ��
		{
			life = false;//�������
			speed = 0;//��������� �������� ������ ����� ������
			//CurrentFrame = 0;//������������� �������� ������
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//�-��� �������������� � ������
	{
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (Dy > 0)	{ y = obj[i].rect.top - h; dy = 0; onGround = true; }
					if (Dy < 0)	{ y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0)	{ x = obj[i].rect.left - w; }
					if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "water")//���� ��������� �������
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

	float getPlayerCoordinateX()//���� ������� ����� �������� ���������� �	
	{
		return x;
	}

	float getPlayerCoordinateY()//���� ������� ����� �������� ���������� Y 
	{
		return y;
	}

	int getSide()
	{
		return side;
	}
};