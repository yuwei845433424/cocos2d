#pragma once
#include"cocos2d.h"
#include"node.h"
class line: public cocos2d::CCSprite
{
public:
	//����
	int tag;
	int color;
	int currentNodeTag;
	int beforeNodeTag;
	int id;
	static int amount;
	static int count;
	static int beforeTag;

	//�������Ĺ��캯������������ȷ����ͼƬ��ѡȡ��amount�Լӡ�id��tag����
	line(int positionX, int positionY,int currentNodeTag,int beforeNodeTag);
	line(void);
	~line(void);
	void blink();
	static line *create(node *p1,node *p2);
private:
	int positionX;
	int positionY;

	

	
};


