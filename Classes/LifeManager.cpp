#include "LifeManager.h"
#include "Player.h"
#include "Life.h"
#include "TollgateScene.h"

bool LifeManager::init()
{
	/* 创建怪物缓存 */
	createLifes();

	moveSpeed = 2;
	died = false;

	/* 开启update函数调用 */
	this->scheduleUpdate();
	return true;
}

void LifeManager::createLifes()
{
	Life* life = NULL;
	Sprite* sprite = NULL;

	for (int i = 0; i < MAX_LIFE_NUM; i++)
	{
		life = Life::create();
		float tmp = CCRANDOM_0_1();
		if (tmp < 0.5)
			life->bindSprite(Sprite::create("egg-life.png"));
		//monster->bindSprite(Sprite::create("egg-life.png"));
		else
			life->bindSprite(Sprite::create("egg-life.png"));
		life->reset();

		this->addChild(life);

		m_lifeArr.pushBack(life);
	}
}

void LifeManager::update(float dt)
{
	for (auto monster : m_lifeArr)
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

void LifeManager::bindPlayer(Player* player)
{
	m_player = player;
}
