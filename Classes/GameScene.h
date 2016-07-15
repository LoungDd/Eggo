#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    void SpawnPipe( float dt );
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    
    void StopFlying( float dt );
    void update( float dt );
    
    cocos2d::PhysicsWorld *sceneWorld;
    
    Pipe pipe;
    
    Bird *bird;
    
    unsigned int score;
    
    cocos2d::Label *scoreLabel;

	void onKeyPressed( EventKeyboard::KeyCode key, Event* event );

	void onKeyReleased( EventKeyboard::KeyCode key, Event* event );
};

#endif // __GAME_SCENE_H__
