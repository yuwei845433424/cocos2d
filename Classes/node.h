#pragma once
#include"cocos2d.h"
class node: public cocos2d::CCSprite
{
public:
	//����
	int tag;
	int color;
	int id;
	static int amount;

	//�������Ĺ��캯������������ȷ����ͼƬ��ѡȡ��amount�Լӡ�id��tag����
	node(int positionX, int positionY);
	node(void);
	~node(void);
	void blink();
private:
	int positionX;
	int positionY;

	

	
};

