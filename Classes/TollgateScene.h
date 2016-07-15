/*
    �ļ�����    TollgateScene.h
    �衡����    �ؿ�����
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
*/
#ifndef __TollgateScene_H__
#define __TollgateScene_H__

#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "LifeManager.h"
#include "MonsterManager.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;
USING_NS_CC_EXT;
#define database UserDefault::getInstance()
class Player;
class TollgateScene : public Layer {
public:
    static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);

    virtual void update(float delta);

private:
    void initBG();          // ��ʼ���ؿ�����
    void loadUI();          // ����UI
	void menuCloseCallback(Ref* pSender);
	void restart_game(Ref*, TouchEventType type);
	void pause_game(Ref*, TouchEventType type);
	void return_game(Ref*, TouchEventType type);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void changeBG();
	void changeBGback();
	void randomKey();
	void end();
private:
	Sprite* m_bgSprite1;	// night 1
	Sprite* m_bgSprite2;	// night 2
	Sprite* m_bgSprite3;	// day 1
	Sprite* m_bgSprite4;	// day 2

	MonsterManager* monsterMgr;
	LifeManager* lifeMgr;

	Sprite* UP;				//����λ��
	Sprite* LEFT;
	Sprite* DOWN;
	Sprite* RIGHT;
	Sprite* up;				//����ͼ��
	Sprite* left;			//����ͼ��
	Sprite* down;			//����ͼ��
	Sprite* right;			//����ͼ��

	Sprite* moon;
	Sprite* sun;
	Sprite* black;
	Player* m_player;		// ����
	
	Sprite* posV[4];		// ����λ��
	Sprite* keyV[4];		// ͼʾ

	Sprite* deadScene;

	int keyM[4];			// 0123��Ӧ�ű仯�Ĺ������У���: wsda
	bool isPress[4];		// ��¼ wasd ��һ�������е�״ֵ̬
	bool stopPlay;

private:
	int life = 0;
	Text* lifeLab;
	int isDay;
	bool over;
	int curScore;
	int maxScore;
	Text* maxScoreLab;
	Text* curScoreLab;
	Label *label_end;

	//Label *lifeLab;        //��ʾ����ֵ��label
	//Text* life;            //����ֵ

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