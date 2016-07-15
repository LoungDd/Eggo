#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

#define MAX_MONSTER_NUM 14  // �����������
class MonsterManager : public Node {
public:
    CREATE_FUNC(MonsterManager);
    virtual bool init();

    virtual void update(float dt);	/* ��дupdate���� */

    /* ����Ҷ��� */
    void bindPlayer(Player* player);
	int getMS() {
		return moveSpeed;
	}
	void setMS(int moveS) {
		this->moveSpeed = moveS;
	}
	void setDied(bool d) {
		died = d;
	}
	bool isDied() {
		return died;
	}
	void hideAll() {
		for (auto monster : m_monsterArr)
		{
			if (monster->isAlive())
			{
				monster->hide();
			}
		}
	}
private:
    void createMonsters();	/* ����������� */
	int moveSpeed;
    Vector<Monster*> m_monsterArr;	/* ��Ź�������б� */

    Player* m_player;       /* ��Ҷ��� */
	bool died;
};

#endif