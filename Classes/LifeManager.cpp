#include "LifeManager.h"
#include "Player.h"
#include "Life.h"
#include "TollgateScene.h"

bool LifeManager::init()
{
	/* �������ﻺ�� */
	createLifes();

	moveSpeed = 2;
	died = false;

	/* ����update�������� */
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
			/* ������ﴦ�ڻ״̬ */
			monster->setPositionX(monster->getPositionX() - moveSpeed);

			/* �������X����С��0�����ʾ�Ѿ�������Ļ��Χ�����ع��� */
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
			/* ���ﴦ�ڷǻ״̬���ù�������� */
			monster->show();
		}
	}
}

void LifeManager::bindPlayer(Player* player)
{
	m_player = player;
}
