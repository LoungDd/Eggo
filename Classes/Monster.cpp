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
        /* ���ÿɼ� */
        setVisible(true);
        
        /* ��ǹ���Ϊ�״̬ */
        m_isAlive = true;
    }
}

void Monster::hide() 
{
    if(getSprite() != NULL) 
    {
        /* ���ò��ɼ� */
        setVisible(false);

        /* ���ù������� */
        reset();
        
        /* ��ǹ���Ϊ�ǻ״̬ */
        m_isAlive = false;
    }
}

void Monster::reset() 
{
    if(getSprite() != NULL) 
    {
        /* ��ʼ���������� */
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
