#include "data.h"

int data::clock = 0;//ʱ���ʼ��Ϊ0

class passenger data::empty = passenger(-1, -1);//���尴�˵��ݼ�ȴû���ϵ��ݻ��������ݽ��ߵĳ˿�

class floor data::floors[21] =
{
	//�������¥���Ӧ�Ľṹ��
	floor(0),
	floor(1),
	floor(2),
	floor(3),
	floor(4),
	floor(5),
	floor(6),
	floor(7),
	floor(8),
	floor(9),
	floor(10),
	floor(11),
	floor(12),
	floor(13),
	floor(14),
	floor(15),
	floor(16),
	floor(17),
	floor(18),
	floor(19),
	floor(20)
};

class elevator data::elevators[4] =
{
	//��ʼ���������ݵĵ������ͣ�����ؿ��������������
	elevator(1,10,800),
	elevator(2,10,800),
	elevator(3,10,800),
	elevator(4,20,2000)
};

