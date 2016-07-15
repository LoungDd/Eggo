/*
    文件名：    Monster.h
    描　述：    怪物
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/
#ifndef __Monster_H__
#define __Monster_H__

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Player;
class Monster : public Entity {
public:
    Monster();
    ~Monster();
    CREATE_FUNC(Monster);
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