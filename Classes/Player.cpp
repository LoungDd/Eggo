#include "Player.h"

Player::Player() 
{
    /* 初始化主角跳跃标记为false，一定不能忘记这一步 */
    m_isJumping = false;

	m_iHP = 1000;
}

Player::~Player() 
{
}

bool Player::init() 
{
    return true;
}

void Player::jump() {
    if (getSprite() == NULL) {
        return;
    }

    /* 如果主角还在跳跃中，则不重复执行 */
    if (m_isJumping) {
        return;
    }

    /* 标记主角为跳跃状态 */
    m_isJumping = true;

    /* 创建跳跃动作：原地跳跃，高度250像素，跳跃一次 */
    auto jump = JumpBy::create(2.0f, Point(0, 0), 250, 1);

    /* 创建回调动作，跳跃结束后修改m_isJumping标记为false */
    auto callFunc = CallFunc::create([&](){
        m_isJumping = false;
    });

    /* 创建连续动作 */
    auto jumpActions = Sequence::create(jump, callFunc, NULL);

    /* 执行动作 */
    this->runAction(jumpActions);
}

void Player::hit() {
	if (getSprite() == NULL) {
		return;
	}
	/*
	FlowWord* flowWord = FlowWord::create();
	this->addChild(flowWord);
	flowWord->showWord("-15", getSprite()->getPosition());

	m_iHP -= 15;
	if (m_iHP < 0) {
		m_iHP = 0;
	}

	auto backMove = MoveBy::create(0.1f, Point(-20, 0));
	auto forwardMove = MoveBy::create(0.1f, Point(20, 0));
	auto backRotate = RotateBy::create(0.1f, -5, 0);
	auto forwardRotate = RotateBy::create(0.1f, 5, 0);

	auto backActions = Spawn::create(backMove, backRotate, NULL);
	auto forwardActions = Spawn::create(forwardMove, forwardRotate, NULL);

	auto actions = Sequence::create(backActions, forwardActions, NULL);

	stopAllActions();
	*/
	// resetData();
	// runAction(actions);
}

int Player::getiHP() {
	return this->m_iHP;
}

void Player::resetData() {
	if (m_isJumping) {
		m_isJumping = false;
	}
	setPosition(Point(200, 140));
	setScale(1.0f);
	setRotation(0);
}
