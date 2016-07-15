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