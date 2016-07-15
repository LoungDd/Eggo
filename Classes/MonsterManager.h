#ifndef __MonsterManager_H__
#define __MonsterManager_H__

#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;

#define MAX_MONSTER_NUM 14  // 怪物最大数量
class MonsterManager : public Node {
public:
    CREATE_FUNC(MonsterManager);
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
		for (auto monster : m_monsterArr)
		{
			if (monster->isAlive())
			{
				monster->hide();
			}
		}
	}
private:
    void createMonsters();	/* 创建怪物对象 */
	int moveSpeed;
    Vector<Monster*> m_monsterArr;	/* 存放怪物对象列表 */

    Player* m_player;       /* 玩家对象 */
	bool died;
};

#endif