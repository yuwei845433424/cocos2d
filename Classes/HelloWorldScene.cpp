#include "HelloWorldScene.h"
#include"node.h"
USING_NS_CC;
int a[6][6];
bool start = true;
int beforeTag = 0;
int currentTag = 0;
int count = 0;
int node::amount = 0;
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
CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	shuzu(a);
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		// add "HelloWorld" splash screen"
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

	return true;
}
void HelloWorld::onEnter(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	CCLayer::onEnter();
}

void HelloWorld::onExit(){
	
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

/*��ȫ�ֱ���start���ж��Ƿ��ǵ�һ�������㡣
������ǵ�һ���㣬��ǰ��Ϊi���������㣨j����ʱ�����������a[i][j]==1��ʱ��
���������¼����Ϊi����a[i][j]=0,a[j][i]=0;�����㿪ʼ����֮ǰ��ֹͣ��˸
���ɹ�����7���߶Σ����е㿪ʼ��

*/
bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	node *targetNode;
	CCLOG("ccTouchBegan");
	CCPoint point = touch->getLocation();
	int tag ;
	if(start==true)
	{
	for (tag = 1;tag<=node::amount;tag++)     
	{   
		node* sprite= (node*)this->getChildByTag(tag);   
		CCPoint touchPoint = touch->getLocationInView();     
		touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );         
		CCRect rc1 = sprite->boundingBox();        
		if (rc1.containsPoint(touchPoint))
		{   
			targetNode = sprite;

			CCAnimation* animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("jd.png");
			animation->addSpriteFrameWithFileName("jd~.png");

			animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
			animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
			animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
		
			CCFiniteTimeAction * animate = CCAnimate::create(animation);
			targetNode->runAction(animate);
			start = false;
			beforeTag = sprite->tag;
			return true;         
		}
	}
	}
	else{
		for (tag = 1;tag<=node::amount;tag++)     
		{   
		node* sprite= (node*)this->getChildByTag(tag);   
		CCPoint touchPoint = touch->getLocationInView();     
		touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );         
		CCRect rc1 = sprite->boundingBox();        
		if (rc1.containsPoint(touchPoint))
		{   
			targetNode = sprite;
			currentTag = sprite->tag;
			if(a[beforeTag][currentTag]==1)
			{
			CCAnimation* animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("jd.png");
			animation->addSpriteFrameWithFileName("jd~.png");

			animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
			animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
			animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
		
			CCFiniteTimeAction * animate = CCAnimate::create(animation);
			targetNode->runAction(animate);
			a[beforeTag][currentTag]=0;
			a[currentTag][beforeTag]=0;
			count++;
			node *bnode =(node*)this->getChildByTag(beforeTag);
			bnode->stopAllActions();  
			beforeTag = sprite->tag;
			return true;
			}
			

		}
	}
		
	}
	//�ɹ������е���
	if(count == 6)
		for(int i =1;i<=5;i++)
		{
			node *blinkNode = (node*)this->getChildByTag(i);

			CCAnimation* animation = CCAnimation::create();
			animation->addSpriteFrameWithFileName("jd.png");
			animation->addSpriteFrameWithFileName("jd~.png");

			animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
			animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
			animation->setLoops(-1);//�ظ����� ��-1:����ѭ��
			CCFiniteTimeAction * animate = CCAnimate::create(animation);
			
			blinkNode ->runAction(animate);
		
		}
	return false;   
	
}

void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent* event){
	CCLOG("ccTouchMoved");
}

void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCLOG("ccTouchEnded");

	//targetNode = getChildByTag();
	//��ȡ�뿪��Ļʱ��Ӧ������
  /*  CCPoint point = touch->getLocation();
	
	//��ȡ��tag=922�ľ���
	for(int i=0;i<10;i++)
	{
		touchNumber[i]=1;
	
	//����ǵ�һ�ε���������������
	if(touchNumber[i] == 1&&point.x>(x[i]-3)&&point.x<(x[i]+3)&&point.y>(y[i]-3)&&point.x<(y[i]+3)){
		//ͨ����ǩ��þ�������ָ��
		CCSprite* sp = (CCSprite*)this->getChildByTag(i);
	//��ͣ���ж���
		sp->stopAllActions();  
	
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("jd.png");
		animation->addSpriteFrameWithFileName("jd~.png");

		animation->setDelayPerUnit(2.8f / 14.0f);//�������÷��򲻻ᶯ̬����
		animation->setRestoreOriginalFrame(true);//�Ƿ�ص���һ֡
		animation->setLoops(-1);//�ظ����� ��-1:����ѭ����
		
		CCFiniteTimeAction * animate = CCAnimate::create(animation);
		sp->runAction(animate);
	}
	touchNumber[i]++;
	}
	*/
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
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
