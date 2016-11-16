class Enemy 
	: public Entity
{
public:
	Enemy(String F, Level &lvl, float X, float Y, float W, float H) :Entity(F, X, Y, W, H)//����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	{
		obj = lvl.GetObjects("solidForEnemy");//��������������.�������� ������ ������� ��� �������������� ����� � ������
		dx = -0.06;//���� ��������.���� ������ ������ ���������
	}

	void update(float time)
	{
		CurrentFrame += 0.003 * time; //������ ��� ����������� �� "������"
		if (CurrentFrame > 7) CurrentFrame -= 7; //���������� �� ������
		sprite.setTextureRect(IntRect(81 * int(CurrentFrame), 0, 81, 76));


		interactionWithMap(dx, dy);//������������ ������������ �� �

		x += dx * time;

		sprite.setPosition(x, y); //������ ������� ������� � ����� ��� ������

		if (health <= 0)
		{
			dx = 0;
			CurrentFrame += 0.00000005 * time; //������ ��� ����������� �� "������"
			sprite.setTextureRect(IntRect(103 * int(CurrentFrame), 82, 103, 76));


			moveTimer += time;
			if (moveTimer > 700) { life = false; }
		}
	}

	void interactionWithMap(float Dx, float Dy)//�-��� �������������� � ������
	{
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solidForEnemy")//���� ��������� �����������
				{
					if (Dy > 0)	{ y = obj[i].rect.top - h;	                dy = 0; }
					if (Dy < 0)	{ y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0)	{ x = obj[i].rect.left - w;					dx = -0.06; sprite.scale(-1, 1); }
					if (Dx < 0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.06;  sprite.scale(-1, 1); }
				}
			}
	}
};