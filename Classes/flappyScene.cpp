#include "flappyScene.h"
#include "Player.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "MonsterManager.h"
#include "ui\UIHelper.h"
#include "AppDelegate.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "Pipe.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;

Scene* flappyScene::createScene() 
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	// add layer as a child to scene
	// 'layer' is an autorelease object
	auto layer = flappyScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool flappyScene::init() 
{
    if (!Layer::init())
    {
        return false;
    }
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("music/back.mp3", true);
	//添加键盘事件
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(flappyScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(flappyScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	auto listener = EventListenerKeyboard::create();

	// 创建主角
	m_player = Player::create();
	m_player->bindSprite(Sprite::create("cry.png"));
	m_player->setPosition(Point(100, 460));

	this->addChild(m_player, 3);

	/* 初始化背景图片 */
	initBG();
	//this->schedule(schedule_selector(flappyScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

	// 设置最高分
	maxScore = 0;
	if (!database->getBoolForKey("isExist"))
	{
		database->setBoolForKey("isExist", true);
	}


    /* 加载UI */
	loadUI();

	gravity = Sprite::create("down.png");
	Oppogravity = Sprite::create("up.png");
	gravity->setPosition(Point(190, 420));
	Oppogravity->setPosition(Point(190, 420));
	this->addChild(Oppogravity, 3);
	Oppogravity->setVisible(false);
	this->addChild(gravity, 3);

	curScore = 0;
	second = 0;
	hour = 0;
	flash = 3;
	back = 3;
	minute = 0;
	isDay = 1;
	stopPlay = false;
	isPause = false;
	counterForPause = 0;

    this->scheduleUpdate();

	monsterMgr = MonsterManager::create();
	this->addChild(monsterMgr, 4);
	monsterMgr->bindPlayer(m_player);


	black = Sprite::create("black.png");
	black->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	black->setVisible(false);
	this->addChild(black, 3);
    return true;
}

void flappyScene::initBG()
{
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	// night
	m_bgSprite1 = Sprite::create("star.png");
	m_bgSprite1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_bgSprite1, 1);

	//moon = Sprite::create("moon.png");
	//moon->setPosition(Point(visibleSize.width * 7 / 8, visibleSize.height * 3 / 4));
	//this->addChild(moon, 1);

	m_bgSprite2 = Sprite::create("star.png");
	m_bgSprite2->setPosition(Point(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	m_bgSprite2->setFlippedX(true);	// 水平翻转精灵
	this->addChild(m_bgSprite2, 1);

	//day
	m_bgSprite3 = Sprite::create("day.png");
	m_bgSprite3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_bgSprite3, 0);

	m_bgSprite4 = Sprite::create("day.png");
	m_bgSprite4->setPosition(Point(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	m_bgSprite4->setFlippedX(true);	// 水平翻转精灵
	this->addChild(m_bgSprite4, 0);
	return;
}

void flappyScene::changeBG()
{
	FadeOut* fadeOut1 = FadeOut::create(2.0f);
    m_bgSprite1->runAction(fadeOut1);
	FadeOut* fadeOut2 = FadeOut::create(2.0f);
	m_bgSprite2->runAction(fadeOut2);
	FadeOut* fadeOut3 = FadeOut::create(2.0f);
	//moon->runAction(fadeOut3);
	return;
}

void flappyScene::changeBGback()
{
	FadeIn* fadeIn1 = FadeIn::create(2.0f);
	m_bgSprite1->runAction(fadeIn1);
	FadeIn* fadeIn2 = FadeIn::create(2.0f);
	m_bgSprite2->runAction(fadeIn2);
	FadeIn* fadeIn3 = FadeIn::create(2.0f);
	//moon->runAction(fadeIn3);
	return;
}

void flappyScene::update(float delta)
{
	// 暂停游戏按钮的防抖动处理
	counterForPause++;


    int posX1 = m_bgSprite1->getPositionX();	//背景地图1的X坐标
    int posX2 = m_bgSprite2->getPositionX();	//背景地图2的X坐标

    //跟新怪物滚动速度
	if (curScore < 500)
		iSpeed = 2;
	iSpeed = 2 + curScore / 500;
	monsterMgr->setMS(iSpeed);
	//如果分数破记录，最高分跟随滚动
	if (curScore > database->getIntegerForKey("maxScore"))
		database->setIntegerForKey("maxScore", curScore);

	//地图速度
	mapSpeed = 2;

	// 秒计时
	second += 30;

	// 计分因子
	pScore = 1;

	// 如果游戏结束：按键无效（玩家静止）、地图静止、怪物静止
	if (isPause)
	{
		//for (int i = 0; i < 4; i++) isPress[i] = false;
		mapSpeed = 0;
		monsterMgr->setMS(0);
		second = 0;
		pScore = 0;

	}
	if (monsterMgr->isDied())
	{
		//for (int i = 0; i < 4; i++) isPress[i] = false;
		mapSpeed = 0;
		monsterMgr->setMS(0);
		second = 0;
		pScore = 0;
		end();
	}


    /* 两张地图向左滚动（两张地图是相邻的，所以要一起滚动，否则会出现空隙） */
    posX1 -= mapSpeed;
    posX2 -= mapSpeed;

    // 地图大小
    Size mapSize = m_bgSprite1->getContentSize();

    /* 当第1个地图完全离开屏幕时，第2个地图刚好完全出现在屏幕上，这时候就让第1个地图紧贴在
     第2个地图后面 */
    if (posX1 <= -mapSize.width / 2) {
        posX1 = mapSize.width + mapSize.width / 2;
    }
    /* 同理，当第2个地图完全离开屏幕时，第1个地图刚好完全出现在屏幕上，这时候就让第2
     个地图紧贴在第1个地图后面 */
    if (posX2 <= -mapSize.width / 2) {
        posX2 = mapSize.width + mapSize.width / 2;
    }

	m_bgSprite1->setPositionX(posX1);
	m_bgSprite2->setPositionX(posX2);
	m_bgSprite3->setPositionX(posX1);
	m_bgSprite4->setPositionX(posX2);

	float flySpeed = 2;
	//cocos2d::log("minute %d", minute);
	

	if (second == 60)
	{
		second = 0;
		minute += 1;
		curScore += pScore;
	}
	if (minute == 60)
	{
		minute = 0;
		hour += 1;
	}
	if (hour == 24)
	{
		hour = 0;
	}
	if (hour >= 7 && hour <= 19)
	{
		if (!isDay)
		{
			isDay = 1;
			changeBG();
		}
	}
	else
	{
		if (isDay)
		{
			isDay = 0;
			changeBGback();
		}
	}
	int randomHour1 = 2;
	int randomHour2 = 2;
	if (hour == 1 && minute == 0)
	{
		srand((unsigned)time(NULL));
		randomHour1 = (int)(rand() % 12);
		randomHour2 = 12 + (int)(rand() % 24);
	}
	if ((hour == 8 || hour == 14 || hour == 17 || hour == 22 ) && minute == 0)
	{
		// 只能在这个小时执行一次，不然hour == 10 是很久的，动作会非常混乱
		//randomKey();
		//changeGravity();
		flash = 3;
		back = 3;
	}

	if ((hour == 8 || hour == 14 || hour == 17 || hour == 22) && second == 0 && minute == 0)
	{
		// 只能在这个小时执行一次，不然hour == 10 是很久的，动作会非常混乱
		//randomKey();
		needChangeG = bool(1 - int(needChangeG));
		//cocos2d::log("change %d", needChangeG);
		//CCLOG("nimabi");
	}

	if (needChangeG) {
		gravity->setVisible(false);
		Oppogravity->setVisible(true);
	}
	else {
		gravity->setVisible(true);
		Oppogravity->setVisible(false);
	}

	if (isFalling) {
		if (needChangeG) {
			if (m_player->getPositionY() < 420) {
				m_player->setPositionY(m_player->getPositionY() + flySpeed * 2);
			}
		}
		else {
			if (m_player->getPositionY() > 20) {
				m_player->setPositionY(m_player->getPositionY() - flySpeed * 1.5);
			}
		}
	}
	else {
		if (needChangeG) {
			if (m_player->getPositionY() > 20) {
				m_player->setPositionY(m_player->getPositionY() - flySpeed * 1.5);
			}
		}
		else {
			if (m_player->getPositionY() < 420) {
				m_player->setPositionY(m_player->getPositionY() + flySpeed * 2);
			}
		}
		//isFalling = true;
	}


	// 显示时间
	hourLab->setText(Value(hour).asString());
	minuteLab->setText(Value(minute).asString());
	// 显示分数
	maxScoreLab->setText(Value(database->getIntegerForKey("maxScore")).asString());
	curScoreLab->setText(Value(curScore).asString());

	flashLab->setText(Value(flash).asString());
	backLab->setText(Value(back).asString());

	return;
}

void flappyScene::loadUI()
{
    /* 加载UI */
    
	auto UI = CSLoader::createNode("res/MainScene2.csb");
	this->addChild(UI, 3);
	
    // 获取按钮 和 监听
	auto returnBtn = (Button*)UI->getChildByName("return");
	auto pauseBtn = (Button*)UI->getChildByName("pause");
	auto restartBtn = (Button*)UI->getChildByName("restart");
	// 用更高层的按钮覆盖原按钮
	auto restartBtn2 = Button::create("restart.png");
	restartBtn2->setPosition(restartBtn->getPosition());
	restartBtn2->setScale(0.12f);
	this->addChild(restartBtn2, 6);

	returnBtn->addTouchEventListener(this, toucheventselector(flappyScene::return_game));
	pauseBtn->addTouchEventListener(this, toucheventselector(flappyScene::pause_game));
	restartBtn2->addTouchEventListener(this, toucheventselector(flappyScene::restart_game));
	// 获取时间label
	hourLab = (Text*)UI->getChildByName("hour");
	minuteLab = (Text*)UI->getChildByName("minute");
	// 获取分数label
	maxScoreLab = (Text*)UI->getChildByName("maxScore");
	curScoreLab = (Text*)UI->getChildByName("curScore");

	flashLab = (Text*)UI->getChildByName("flashtimes");
	backLab = (Text*)UI->getChildByName("backtimes");
	return;
}

void flappyScene::restart_game(Ref*, TouchEventType type)
{
	curScore = 0;
	auto scene = Scene::create();
	auto *layer = flappyScene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/back.mp3", true);
}

void flappyScene::pause_game(Ref*, TouchEventType type)
{
	if (!isPause && counterForPause > 10)
	{
		counterForPause = 0;
		isPause = true;
	}
	else if (isPause && counterForPause > 10) {
		counterForPause = 0;
		isPause = false;
	}
	else
	{

	}
	return;
}

void flappyScene::return_game(Ref*, TouchEventType type)
{
		Director::getInstance()->replaceScene(
			TransitionFadeBL::create(3.0f, HelloWorld::createScene()));
		return;
}

void flappyScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		isFalling = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_F){
		if (flash > 0) {
			if (m_player->getPositionX() < 580) {
				m_player->setPositionX(m_player->getPositionX() + 200);
				flash--;
				//flashLab->setText(Value(flash).asString());
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (back > 0) {
			if (m_player->getPositionX() > 220) {
				m_player->setPositionX(m_player->getPositionX() - 200);
				back--;
				//backLab->setText(Value(back).asString());
			}
		}
	}
	return;
}

void flappyScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		isFalling = true;
	}
	return;
}


void flappyScene::end() {
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	label_end = Label::createWithTTF("Game Over!", "fonts/Marker Felt.ttf", 60);
	label_end->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	label_end->setVisible(true);
	addChild(label_end, 5);
	black->setVisible(true);

	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/back.mp3");

	//SimpleAudioEngine::getInstance()->playEffect("music/fail.wav");
}
void flappyScene::SpawnPipe(float dt) {
	pipe.SpawnPipe(this);
}

void flappyScene::changeGravity() {
	isFalling = bool(1 - int(isFalling));
}