#ifndef __SpringManager_H__
#define __SpringManager_H__

#include "cocos2d.h"
//#include "Spring.h"
USING_NS_CC;

// #define MAX_Spring_NUM 10  // �����������
class SpringManager : public Node {
public:
	CREATE_FUNC(SpringManager);
	virtual bool init();

	virtual void update(float dt);	/* ��дupdate���� */

	/* ����Ҷ��� */
	void bindPlayer(Player* player);
private:
	void createSprings();	/* �������ɶ��� */


	// Vector<Spring*> m_SpringArr;	/*��ŵ��ɶ����б� */

	Player* m_player;       /* ��Ҷ��� */
};

#endif