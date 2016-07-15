#ifndef __Life_H__
#define __Life_H__

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Player;
class Life : public Entity {
public:
	Life();
	~Life();
	CREATE_FUNC(Life);
	virtual bool init();

public:
	void show();    // 显示怪物
	void hide();    // 隐藏怪物
	void reset();   // 重置怪物数据

	bool isAlive(); // 是否活动状态
	/* 检查碰撞 */
	bool isCollideWithPlayer(Player* player);
private:
	bool m_isAlive;
};

#endif