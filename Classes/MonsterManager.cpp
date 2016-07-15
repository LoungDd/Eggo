#include "MonsterManager.h"
#include "Player.h"
#include "Monster.h"
#include "flappyScene.h"

bool MonsterManager::init() 
{
    /* �������ﻺ�� */
    createMonsters();

	moveSpeed = 2;
	died = false;

    /* ����update�������� */
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

void MonsterManager::bindPlayer(Player* player)
{
    m_player = player;
}
