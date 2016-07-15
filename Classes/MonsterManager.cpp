#include "MonsterManager.h"
#include "Player.h"
#include "Monster.h"
#include "flappyScene.h"

bool MonsterManager::init() 
{
    /* 创建怪物缓存 */
    createMonsters();

	moveSpeed = 2;
	died = false;

    /* 开启update函数调用 */
    this->scheduleUpdate();
    return true;
}

void MonsterManager::createMonsters() 
{
    Monster* monster = NULL;
    Sprite* sprite = NULL;

    for(int i = 0; i < MAX_MONSTER_NUM; i++) 
    {
        monster = Monster::create();
		float tmp = CCRANDOM_0_1();
		if (tmp < 0.5)
			monster->bindSprite(Sprite::create("cloud1.png"));
		else
			monster->bindSprite(Sprite::create("cloud1.png"));
		monster->reset();

        this->addChild(monster, 0);

		m_monsterArr.pushBack(monster);
    }
}

void MonsterManager::update( float dt ) 
{
    for (auto monster : m_monsterArr) 
    {
        if (monster->isAlive()) 
        {
            /* 如果怪物处于活动状态 */
            monster->setPositionX(monster->getPositionX() - moveSpeed);

            /* 如果怪物X坐标小于0，则表示已经超出屏幕范围，隐藏怪物 */
            if (monster->getPositionX() < 0) 
            {
                monster->hide();
            }
			else if (monster->isCollideWithPlayer(m_player))
			{
				m_player->hit();
				monster->hide();
				died = true;
			}
        }
        else 
        {
            /* 怪物处于非活动状态，让怪物出场吧 */
            monster->show();
        }
    }
}

void MonsterManager::bindPlayer(Player* player)
{
    m_player = player;
}
