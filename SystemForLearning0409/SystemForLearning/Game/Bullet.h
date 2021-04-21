#pragma once
#ifndef __BULLET_HEADER__
#define __BULLET_HEADER__

#include "GameObject.h"

namespace core2d
{
	class Sprite;
	namespace Collision
	{
		struct PointF;
	}
#if COLLISION_VISIBLE
	class PrimitiveEdgeSprite;
#endif
}

// -----------------------------------------------------------------------
// 弾を表すクラス
// -----------------------------------------------------------------------
class Bullet : public GameObject
{
public:
	Bullet(ShootingGame* manager);
	virtual ~Bullet(void);

	void setDirection(float x, float y);
	void setSpeed(float speed);

protected:
	float m_dirX;
	float m_dirY;
	float m_speed;

#if COLLISION_VISIBLE
	core2d::PrimitiveEdgeSprite* m_collisionSprite;
#endif
};

// -----------------------------------------------------------------------
// プレイヤーの弾クラス
// -----------------------------------------------------------------------
class PlayerBullet : public Bullet
{
public:
	PlayerBullet(ShootingGame* manager);
	virtual ~PlayerBullet(void);

	void update(void) final;

	void setDamage(int damage);
	int getDamage(void);

protected:
	void onFirstUpdate() final;

private:
	core2d::Sprite* m_sprite;

	core2d::Collision::PointF* m_collision;

	int m_damage;
};

// -----------------------------------------------------------------------
// 敵の弾クラス
// -----------------------------------------------------------------------
class EnemyBullet : public Bullet
{
public:
	EnemyBullet(ShootingGame* manager, int imageId);
	virtual ~EnemyBullet(void);

	void setSpriteScale(float x, float y);

	void update(void) final;

protected:
	void onFirstUpdate() final;

private:
	core2d::Sprite* m_sprite;

	core2d::Collision::PointF* m_collision;

	float m_spriteScaleX;
	float m_spriteScaleY;

	int m_imageId;

};

#endif