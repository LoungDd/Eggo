#include "Monster.h"
#include "Player.h"
// #include "ccMacros.h"

Monster::Monster() 
{
    m_isAlive = false;
}

Monster::~Monster() 
{
}

bool Monster::init() 
{
    bool bRet = false;

    do {
        bRet = true;
    } while (0);

    return bRet;
}

void Monster::show() 
{
    if(getSprite() != NULL) 
    {
        /* 设置可见 */
        setVisible(true);
        
        /* 标记怪物为活动状态 */
        m_isAlive = true;
    }
}

void Monster::hide() 
{
    if(getSprite() != NULL) 
    {
        /* 设置不可见 */
        setVisible(false);

        /* 重置怪物数据 */
        reset();
        
        /* 标记怪物为非活动状态 */
        m_isAlive = false;
    }
}

void Monster::reset() 
{
    if(getSprite() != NULL) 
    {
        /* 初始化怪物坐标 */
        setPosition(Point(800 + CCRANDOM_0_1() * 3000, CCRANDOM_0_1() * 400));
    }
}

bool Monster::isAlive() 
{
    return m_isAlive;
}

bool Monster::isCollideWithPlayer( Player* player ) 
{
	Rect entityRect = player->getBoundingBox();
	Rect mosterRect = getBoundingBox();
	return entityRect.intersectsRect(mosterRect);
}
