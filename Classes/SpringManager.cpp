#include "SpringManager.h"
#include "Player.h"
#include "Spring.h"

bool SpringManager::init()
{
	// �������ɻ���
	createSprings();

	/* ����update�������� */
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
			// ������ɴ��ڻ״̬
			Spring->setPositionX(Spring->getPositionX() - 4);

			// �������X����С��0�����ʾ�Ѿ�������Ļ��Χ�����ص���
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
			// ���ɴ��ڷǻ״̬���õ��ɳ�����
			Spring->show();
		}
	}
	*/
}

void SpringManager::bindPlayer(Player* player)
{
	m_player = player;
}
