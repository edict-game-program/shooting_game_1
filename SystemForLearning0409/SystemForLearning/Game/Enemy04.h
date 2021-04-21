#pragma once

#ifndef __ENEMY04_H__
#define __ENEMY04_H__


#include "Enemy.h"

class ShootingGame;

/*===================================================
* 敵4クラス
====================================================*/
class Enemy04 : public Enemy
{
public:
	explicit Enemy04(ShootingGame* manager);
	virtual ~Enemy04();

	void update(void) final;

protected:
	void initSprites() override;

	void movePosition() override;

	void createBullet() override;

	void setDead() override;

protected:
	float m_rad; //ラジアン
};

#endif