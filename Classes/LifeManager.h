#ifndef __LifeManager_H__
#define __LifeManager_H__

#include "cocos2d.h"
#include "Life.h"
USING_NS_CC;

#define MAX_LIFE_NUM 5  // 怪物最大数量
class LifeManager : public Node {
public:
	CREATE_FUNC(LifeManager);
	virtual bool init();

	virtual void update(float dt);	/* 重写update函数 */

	/* 绑定玩家对象 */
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
	void createLifes();	        /* 创建怪物对象 */
	int moveSpeed;
	Vector<Life*> m_lifeArr;	/* 存放怪物对象列表 */

	Player* m_player;           /* 玩家对象 */
	bool died;
};

#endif