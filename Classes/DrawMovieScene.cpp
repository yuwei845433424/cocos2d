#include "DrawMovieScene.h"
#include"node.h"
#include"line.h"

USING_NS_CC;
//��node��line�ľ�̬�����ĳ�ʼ��
int node::a[6][6];
int node::amount = 0;
bool node::start = true;
int node::beforeTag = 0;
int node::currentTag = 0;
int node::count = 0;

int line::amount = 0;
int line::count = 0;
int line::beforeTag = 0;

//�ö�ά�������������֮��Ĺ�ϵ
void shuzu(int a[6][6])
{
	a[1][2] = 1;
	a[1][3] = 1;
	a[1][4] = 1;
	a[1][5] = 0;
	a[2][1] = 1;

	a[2][3] = 1;
	a[2][4] = 0;
	a[2][5] = 1;
	a[3][1] = 1;
	a[3][2] = 1;

	a[3][4] = 1;
	a[3][5] = 1;
	a[4][1] = 1;
	a[4][2] = 0;
	a[4][3] = 1;

	a[4][5] = 0;
	a[5][1] = 0;
	a[5][2] = 1;
	a[5][3] = 1;
	a[5][4] = 0;

}


//��˸����

void runAnimate(node *targetNode)
{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("jd.png");
		animation->addSpriteFrameWithFileName("jd~.png");

		animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
		animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
		animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
		
		CCFiniteTimeAction * animate = CCAnimate::create(animation);
		targetNode->runAction(animate);
}
void runAnimate(line *targetLine)
{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("jd.png");
		animation->addSpriteFrameWithFileName("jd~.png");

		animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
		animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
		animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
		
		CCFiniteTimeAction * animate = CCAnimate::create(animation);
		targetLine->runAction(animate);
}
bool DrawMovie::touchGetNode(node *sprite,CCTouch* touch,int tag)
{
		
		CCPoint touchPoint = touch->getLocationInView();     
		touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );         
		CCRect rc1 = sprite->boundingBox(); 
		if(rc1.containsPoint(touchPoint)) return true;
		else return false;
}
CCScene* DrawMovie::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	DrawMovie *layer = DrawMovie::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool DrawMovie::init()
{

	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	this->strike=CCMotionStreak::create(1.0f,//β�ͳ�����ʱ��
			16.0f,//β�ʹ�С
			16.0f,//ͼƬ�Ĵ�С
			ccc3(255,255,0),//��ɫ
			"jd.png"//ʹ�õ�ͼƬ
			);
		addChild(strike,1);
		strike->setPosition(ccp(240,160));
	shuzu(node::a);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		// add "DrawMovie" splash screen"
	CCSprite* pSprite = CCSprite::create("up.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	node *node1 = new node(50,100);
	node *node2 = new node(250,100);
	node *node3 = new node(150,150);
	node *node4 = new node(50,200);
	node *node5 = new node(250,200);
	
	this->addChild(node1,0,node1->tag);
	this->addChild(node2,0,node2->tag);
	this->addChild(node3,0,node3->tag);
	this->addChild(node4,0,node4->tag);
	this->addChild(node5,0,node5->tag);
	//����lines
	line **lines = (line**)new line;
	int k = 0;
	for(int i = 1;i<=node::amount;i++)
		for(int j=i+1;j<=node::amount;j++)
			if(node::a[i][j]==1)
			{
				k++;	
				node* nodeI = (node*)this->getChildByTag(i);
				node* nodeJ = (node*)this->getChildByTag(j);
				lines[k]=line::create(nodeI,nodeJ);
				this->addChild(lines[k],0,lines[k]->tag);
			}
	
	return true;
}
void DrawMovie::onEnter(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCLayer::onEnter();
}

void DrawMovie::onExit(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

/*��ȫ�ֱ���start���ж��Ƿ��ǵ�һ�������㡣
������ǵ�һ���㣬��ǰ��Ϊi���������㣨j����ʱ�����������a[i][j]==1��ʱ��
���������¼����Ϊi����a[i][j]=0,a[j][i]=0;�����㿪ʼ����֮ǰ��ֹͣ��˸
���ɹ�����7���߶Σ����е㿪ʼ��

*/
bool DrawMovie::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	strike->setPosition(touch->getLocation());
	CCLOG("ccTouchBegan");
	node *targetNode;
	CCPoint point = touch->getLocation();
	int tag ;
	if(node::start==true)
	{
	for (tag = 1;tag<=node::amount;tag++)     
	{   
		node* sprite= (node*)this->getChildByTag(tag);   
		if (touchGetNode(sprite,touch,tag))
		{   
			targetNode = sprite;
			runAnimate(targetNode);
			node::start = false;
			node::beforeTag = sprite->tag;
			return true;         
		}
	}
	}
	else{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* sprite= (node*)this->getChildByTag(tag);   
		if (touchGetNode(sprite,touch,tag))
		{   
			targetNode = sprite;
			node::currentTag = sprite->tag;
			if(node::a[node::beforeTag][node::currentTag]==1)
			{
				node *beforeNode = (node *)this->getChildByTag(node::beforeTag);
				int beforeNodeTag = beforeNode->tag,targetNodeTag = targetNode->tag;
				//ʹbeforeNodeTagΪ��С��tag
				if(beforeNodeTag>targetNodeTag)
				{
					int c=beforeNodeTag;
					beforeNodeTag =	targetNodeTag;
					targetNodeTag = c;
				}
				int lineTag = beforeNodeTag*100+targetNodeTag;
				line *targetLine = (line *)this->getChildByTag(lineTag);
				runAnimate(targetNode);
				
//ʵ���㷨��"������ǵ�һ���㣬��ǰ��Ϊi���������㣨j����ʱ�����������a[i][j]==1��ʱ��
//���������¼����Ϊi����a[i][j]=0,a[j][i]=0;�����㿪ʼ����֮ǰ��ֹͣ��˸"
				//��Ӽ�¼��line��beforeTag
				node::a[node::beforeTag][node::currentTag]=0;
				node::a[node::currentTag][node::beforeTag]=0;
				node::count++;
				node *bnode =(node*)this->getChildByTag(node::beforeTag);
				bnode->stopAllActions(); 
				runAnimate(targetLine);
				if(line::beforeTag!=0)
				{
					line *bline = (line*)this->getChildByTag(line::beforeTag);
					bline->stopAllActions();
				}
				node::beforeTag = sprite->tag;
				line::beforeTag = lineTag;
				return true;
			}
		}
	}
		
	}
	//�ɹ������е���
	if(node::count == 7)
		for(int i =1;i<=5;i++)
		{
			node *blinkNode = (node*)this->getChildByTag(i);
			runAnimate(blinkNode);
		}
	return false;   
	
}

void DrawMovie::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCLOG("ccTouchMoved");
	int tag ;
	node *targetNode;
	if(node::start==false)
	{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
			node* sprite= (node*)this->getChildByTag(tag);   
		if (touchGetNode(sprite,touch,tag))
		{   
			targetNode = sprite;
			node::currentTag = sprite->tag;
			if(node::a[node::beforeTag][node::currentTag]==1)
			{
			runAnimate(targetNode);
//ʵ���㷨��"������ǵ�һ���㣬��ǰ��Ϊi���������㣨j����ʱ�����������a[i][j]==1��ʱ��
//���������¼����Ϊi����a[i][j]=0,a[j][i]=0;�����㿪ʼ����֮ǰ��ֹͣ��˸"
			node::a[node::beforeTag][node::currentTag]=0;
			node::a[node::currentTag][node::beforeTag]=0;
			node::count++;
			node *bnode =(node*)this->getChildByTag(node::beforeTag);
			bnode->stopAllActions();
			
			node *beforeNode = (node *)this->getChildByTag(node::beforeTag);
			int beforeNodeTag = beforeNode->tag,targetNodeTag = targetNode->tag;
			
			//ʹbeforeNodeTagΪ��С��tag
			if(beforeNodeTag>targetNodeTag)
			{
				int c=beforeNodeTag;
				beforeNodeTag =	targetNodeTag;
				targetNodeTag = c;
			}
			int lineTag = beforeNodeTag*100+targetNodeTag;
			line *targetLine = (line *)this->getChildByTag(lineTag);
			runAnimate(targetLine);
			if(line::beforeTag!=0)
			{
				line *bline = (line*)this->getChildByTag(line::beforeTag);
				bline->stopAllActions();
			}
			node::beforeTag = sprite->tag;
			line::beforeTag = lineTag;
			
			
		}
	}
		
	}
	}
	if(node::count == 7)
		for(int i =1;i<=5;i++)
		{
			node *blinkNode = (node*)this->getChildByTag(i);
			runAnimate(blinkNode);
		}
	strike->setPosition(touch->getLocation());
}

void DrawMovie::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");


}


void DrawMovie::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}