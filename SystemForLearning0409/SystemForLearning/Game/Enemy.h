#pragma once
#ifndef __ENEMY_HEADER__
#define __ENEMY_HEADER__

#include "GameObject.h"

namespace core2d
{
	class Sprite;
	namespace Collision
	{
		class RectF;
	}
#if COLLISION_VISIBLE
	class PrimitiveEdgeSprite;
#endif
}

class SpriteAnime;

// ザコ敵クラス
class Enemy : public GameObject
{
public:
	Enemy(ShootingGame* manager);
	virtual ~Enemy(void);

	void update(void) override;

	void onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target) override;

	void setUpgradeItem(int itemType);

	int getScore() { return m_score; }

protected:
	void onFirstUpdate() final;

	void createSprites(int* imageId, int num);
	virtual void initSprites() = 0;
	virtual void movePosition(); //移動

	virtual void createBullet() {};

	void setSpritesPosition(float x, float y);
	void setSpritesScale(float x, float y);
	void setSpritesRotate(float degree);
	void setSpritesActive(bool active);

	virtual void setDead() {};

protected:
	//core2d::Sprite* m_sprite;
	std::vector<core2d::Sprite*> m_enemySprites;
	SpriteAnime* m_enemySpriteAnime;

	int m_shotWait;
	int m_shotInterval;

	float m_dirX;
	float m_dirY;

	float m_speed;

	core2d::Collision::RectF* m_collision;

	enum : int
	{
		Status_None,
		Status_Dead,
	};

	int m_status;

	int m_upgradeItem;

	int m_score;	//撃破した時の得点

#if COLLISION_VISIBLE
	core2d::PrimitiveEdgeSprite* m_collisionSprite;
#endif
};

#endif