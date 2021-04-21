#pragma once

#ifndef __ENEMY02_H__
#define __ENEMY02_H__


#include "Enemy.h"

class ShootingGame;

/*===================================================
* “G2ƒNƒ‰ƒX
====================================================*/
class Enemy02 : public Enemy
{
public:
	explicit Enemy02(ShootingGame* manager);
	virtual ~Enemy02();

	void update(void) final;

protected:
	void initSprites() override;

	void movePosition() override;

	void createBullet() override;

	void setDead() override;

protected:
	float m_rad;
};

#endif