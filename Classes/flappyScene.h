/*
    文件名：    flappyScene.h
    描　述：    关卡场景
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/
#ifndef __FlappyScene_H__
#define __FlappyScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MonsterManager.h"
#include "ui\UIButton.h"
#include "Pipe.h"
#include "ui\UIText.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

USING_NS_CC_EXT;
#define database UserDefault::getInstance()
class Player;
class flappyScene : public Layer {
public:
    static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(flappyScene);

    virtual void update(float delta);

private:
    void initBG();          // 初始化关卡背景
    void loadUI();          // 加载UI
	void menuCloseCallback(Ref* pSender);
	void restart_game(Ref*, TouchEventType type);
	void pause_game(Ref*, TouchEventType type);
	void return_game(Ref*, TouchEventType type);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void changeBG();
	void changeBGback();
	void end();
	void changeGravity();
private:
	Sprite* m_bgSprite1;	// night 1
	Sprite* m_bgSprite2;	// night 2
	Sprite* m_bgSprite3;	// day 1
	Sprite* m_bgSprite4;	// day 2
	Sprite* gravity;
	Sprite* Oppogravity;

	MonsterManager* monsterMgr;

	Sprite* UP;				//操作位置
	Sprite* LEFT;
	Sprite* DOWN;
	Sprite* RIGHT;
	Sprite* up;				//操作图标
	Sprite* left;			//操作图标
	Sprite* down;			//操作图标
	Sprite* right;			//操作图标

	Sprite* moon;
	Sprite* sun;
	Sprite* black;
	Player* m_player;		// 主角
	
	Sprite* posV[4];		// 绝对位置
	Sprite* keyV[4];		// 图示

	Sprite* deadScene;

	int keyM[4];			// 0123对应着变化的功能序列，如: wsda
	bool isPress[4];		// 记录 wasd 这一功能序列的状态值
	bool stopPlay;
	bool isFalling = true;
	bool needChangeG = false;

private:
	int isDay;
	bool over;
	int curScore;
	int maxScore;
	int flash; //闪现标识
	int back;
	Text* flashLab;
	Text* backLab;

	Text* maxScoreLab;
	Text* curScoreLab;
	Label *label_end;

	Pipe pipe;
	void SpawnPipe(float dt);

	int hour;
	Text* hourLab;
	int minute;
	Text* minuteLab;
	int second;

	int iSpeed;
	int mapSpeed;
	int pScore;

	bool isPause;

	int counterForPause;
};

#endif