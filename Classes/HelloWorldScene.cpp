#include "HelloWorldScene.h"
//#include "physics\CCPhysicsBody.h"
#include "ui\UIButton.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "ui\UIWidget.h"
#include "MainMenuScene.h"
#include "ui\CocosGUI.h"
#include "ui\UIHelper.h"
#include "StartScene.h"
#include "flappyScene.h"
#include "TollgateScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();

    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto UI = CSLoader::createNode("res/modeScene.csb");
	this->addChild(UI, 3);

	// Ìí¼Ó°´Å¥ ºÍ ¼àÌý
	auto mode1_btn = (Button*)UI->getChildByName("freemode");
	auto mode2_btn = (Button*)UI->getChildByName("flappymode");
	auto btn3 = (Button*)UI->getChildByName("Button_3");
	mode1_btn->addTouchEventListener(this, toucheventselector(HelloWorld::start1));
	mode2_btn->addTouchEventListener(this, toucheventselector(HelloWorld::start2));
	btn3->addTouchEventListener(this, toucheventselector(HelloWorld::back));
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/back.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/back.mp3", true);

    return true;
}

void HelloWorld::start1(Ref*, TouchEventType type) {
	auto scene = TollgateScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(3.0f, scene));
}

void HelloWorld::start2(Ref*, TouchEventType type) {
	auto scene = flappyScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeTR::create(3.0f, scene));
}

void HelloWorld::back(Ref*, TouchEventType type) {
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(3.0f, scene));
}