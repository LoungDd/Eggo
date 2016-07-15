/*
    �ļ�����    Monster.h
    �衡����    ����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
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
    void show();    // ��ʾ����
    void hide();    // ���ع���
    void reset();   // ���ù�������

    bool isAlive(); // �Ƿ�״̬
    /* �����ײ */
    bool isCollideWithPlayer(Player* player);
private:
    bool m_isAlive;
};

#endif