#pragma once

#ifndef __ENEMY01_H__
#define __ENEMY01_H__

#include "Enemy.h"

class ShootingGame;

/*===================================================
* “G1ƒNƒ‰ƒX
====================================================*/
class Enemy01 : public Enemy
{
public:
	explicit Enemy01(ShootingGame* manager);
	virtual ~Enemy01();

	void update(void) final;


protected:
	void initSprites() override;

	void createBullet() override;

	void setDead() override;
};

#endif