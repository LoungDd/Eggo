#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "physics\CCPhysicsBody.h"
#include "ui\UIButton.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "ui\UIWidget.h"
#include "MainMenuScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace CocosDenshion;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);
	void start1(Ref*, TouchEventType type);
	void start2(Ref*, TouchEventType type);
	void back(Ref*, TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__
