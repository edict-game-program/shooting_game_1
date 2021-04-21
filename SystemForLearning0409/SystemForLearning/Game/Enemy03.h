#pragma once

#ifndef __ENEMY03_H__
#define __ENEMY03_H__


#include "Enemy.h"

class ShootingGame;

/*===================================================
* “G3ƒNƒ‰ƒX
====================================================*/
class Enemy03 : public Enemy
{
public:
	explicit Enemy03(ShootingGame* manager);
	virtual ~Enemy03();

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