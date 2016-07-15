#ifndef __LifeManager_H__
#define __LifeManager_H__

#include "cocos2d.h"
#include "Life.h"
USING_NS_CC;

#define MAX_LIFE_NUM 5  // �����������
class LifeManager : public Node {
public:
	CREATE_FUNC(LifeManager);
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
		for (auto life : m_lifeArr)
		{
			if (life->isAlive())
			{
				life->hide();
			}
		}
	}
private:
	void createLifes();	        /* ����������� */
	int moveSpeed;
	Vector<Life*> m_lifeArr;	/* ��Ź�������б� */

	Player* m_player;           /* ��Ҷ��� */
	bool died;
};

#endif