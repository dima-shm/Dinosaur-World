class Bullet 
	: public Entity
{
private:
	int direction;

public:	
	Bullet(String F, Level &lvl, float X, float Y, float W, float H, int dir) :Entity(F, X, Y, W, H){//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.4;
		w = W;
		h = H;
		//���� ������������� � ������������
	}

	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;    break;
		case 1: dx = speed; dy = 0;     break;
		default: x = 0; y = 0;
		}


		x += dx*time;//���� �������� ���� �� �
		y += dy*time;//�� �

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;


		for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
			if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			{
				life = false;// �� ���� �������
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����

		if (health <= 0){ life = false; }
	}
};