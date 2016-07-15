/*
    �ļ�����    Entity.h
    �衡����    ʵ�����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
*/
#ifndef __Entity_H__
#define __Entity_H__
#include "cocos2d.h"
USING_NS_CC;

class Entity : public Node {
public:
    Entity();
    ~Entity();
    Sprite* getSprite();	/* ��ȡ������� */
    void bindSprite(Sprite* sprite);	/* �󶨾������ */
private:
    Sprite* m_sprite;
};
#endif