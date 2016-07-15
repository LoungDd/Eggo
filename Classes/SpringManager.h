#ifndef __SpringManager_H__
#define __SpringManager_H__

#include "cocos2d.h"
//#include "Spring.h"
USING_NS_CC;

// #define MAX_Spring_NUM 10  // 弹簧最大数量
class SpringManager : public Node {
public:
	CREATE_FUNC(SpringManager);
	virtual bool init();

	virtual void update(float dt);	/* 重写update函数 */

	/* 绑定玩家对象 */
	void bindPlayer(Player* player);
private:
	void createSprings();	/* 创建弹簧对象 */


	// Vector<Spring*> m_SpringArr;	/*存放弹簧对象列表 */

	Player* m_player;       /* 玩家对象 */
};

#endif