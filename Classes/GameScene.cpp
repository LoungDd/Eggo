#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "ui\UIHelper.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics( );

    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "day.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    this->addChild( backgroundSprite );
    
    this->schedule( schedule_selector( GameScene::SpawnPipe ), PIPE_SPAWN_FREQUENCY * visibleSize.width );
    
    bird = new Bird( this );

    score = 0;
    
    __String *tempScore = __String::createWithFormat( "%i", score );
    
    scoreLabel = Label::createWithTTF( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    
    this->addChild( scoreLabel, 10000 );
    
	//add keyboard event
	auto listenerKeyboard = EventListenerKeyboard::create( );
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2( GameScene::onKeyPressed, this );
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2( GameScene::onKeyReleased, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( listenerKeyboard, this );
	auto listener = EventListenerKeyboard::create();

    this->scheduleUpdate( );
    
    return true;
}

void GameScene::onKeyPressed( EventKeyboard::KeyCode key, Event* event ) {
	if ( key == EventKeyboard::KeyCode::KEY_SPACE ) {
		bird->Fly( );
		this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);
	}
	return;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event) {
	if (key == EventKeyboard::KeyCode::KEY_SPACE) {
		bird->StopFlying( );
	}
	return;
}

void GameScene::SpawnPipe( float dt )
{
    pipe.SpawnPipe( this );
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    
    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( "Sounds/Hit.mp3" );
        
        auto scene = GameOverScene::createScene( score );
        
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    else if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask( ) && POINT_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        CocosDenshion::SimpleAudioEngine::getInstance( )->playEffect( "Sounds/Point.mp3" );
        
        score++;
        
        __String *tempScore = __String::createWithFormat( "%i", score );
        
        scoreLabel->setString( tempScore->getCString( ) );
    }
    
    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event )
{
    bird->Fly( );
    
    this->scheduleOnce( schedule_selector( GameScene::StopFlying ), BIRD_FLY_DURATION );
    
    return true;
}

void GameScene::StopFlying( float dt )
{
    bird->StopFlying( );
}

void GameScene::update( float dt )
{
    bird->Fall( );
}










