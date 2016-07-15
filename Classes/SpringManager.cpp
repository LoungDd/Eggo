#include "SpringManager.h"
#include "Player.h"
#include "Spring.h"

bool SpringManager::init()
{
	// 创建弹簧缓存
	createSprings();

	/* 开启update函数调用 */
	this->scheduleUpdate();
	return true;
}

void SpringManager::createSprings()
{
	Spring* Spring = NULL;
	Sprite* sprite = NULL;

}

void SpringManager::update(float dt)
{
	/*
	for (auto Spring : m_SpringArr)
	{
		if (Spring->isAlive())
		{
			// 如果弹簧处于活动状态
			Spring->setPositionX(Spring->getPositionX() - 4);

			// 如果弹簧X坐标小于0，则表示已经超出屏幕范围，隐藏弹簧
			if (Spring->getPositionX() < 0)
			{
				Spring->hide();
			}
			else if (Spring->isCollideWithPlayer(m_player))
			{
				m_player->hit();
				Spring->hide();
			}
		}
		else
		{
			// 弹簧处于非活动状态，让弹簧出场吧
			Spring->show();
		}
	}
	*/
}

void SpringManager::bindPlayer(Player* player)
{
	m_player = player;
}
