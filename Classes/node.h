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
	static int count;
	static int a[6][6];
	static bool start ;
	static int beforeTag ;
	static int currentTag ;

	//�������Ĺ��캯������������ȷ����ͼƬ��ѡȡ��amount�Լӡ�id��tag����
	node(int positionX, int positionY);
	node(void);
	~node(void);
	void blink();
private:
	int positionX;
	int positionY;

	

	
};


