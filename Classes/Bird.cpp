#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer )
{
    visibleSize = Director::getInstance( )->getVisibleSize( );
    origin = Director::getInstance( )->getVisibleOrigin( );
    
    flappyBird = Sprite::create( "egg.png" );
    flappyBird->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    layer->addChild( flappyBird, 100 );  
    isFalling = true;
}

void Bird::Fall( )
{
    if ( true == isFalling )
    {
		flappyBird->setPositionX( visibleSize.width / 2 + origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() - ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
    else
    {
        flappyBird->setPositionX( visibleSize.width / 2 + origin.x );
        flappyBird->setPositionY( flappyBird->getPositionY() + ( BIRD_FALLING_SPEED * visibleSize.height ) );
    }
}




