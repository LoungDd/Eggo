#include "Life.h"
#include "Player.h"
// #include "ccMacros.h"

Life::Life()
{
	m_isAlive = false;
}

Life::~Life()
{
}

bool Life::init()
{
	bool bRet = false;

	do {
		bRet = true;
	} while (0);

	return bRet;
}

void Life::show()
{
	if (getSprite() != NULL)
	{
		/* ���ÿɼ� */
		setVisible(true);

		/* ��ǹ���Ϊ�״̬ */
		m_isAlive = true;
	}
}

void Life::hide()
{
	if (getSprite() != NULL)
	{
		/* ���ò��ɼ� */
		setVisible(false);

		/* ���ù������� */
		reset();

		/* ��ǹ���Ϊ�ǻ״̬ */
		m_isAlive = false;
	}
}

void Life::reset()
{
	if (getSprite() != NULL)
	{
		/* ��ʼ���������� */
		setPosition(Point(800 + CCRANDOM_0_1() * 3000, CCRANDOM_0_1() * 400));
	}
}

bool Life::isAlive()
{
	return m_isAlive;
}

bool Life::isCollideWithPlayer(Player* player)
{
	Rect entityRect = player->getBoundingBox();
	Rect mosterRect = getBoundingBox();
	return entityRect.intersectsRect(mosterRect);
}
