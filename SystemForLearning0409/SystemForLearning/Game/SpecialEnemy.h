#pragma once
#ifndef __SPECIALENEMY_HEADER__
#define __SPECIALENEMY_HEADER__

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

// ボスキャラを表すクラス
class SpecialEnemy : public GameObject
{
public:
	SpecialEnemy(ShootingGame* manager);
	virtual ~SpecialEnemy(void);

	void update(void) final;

	void onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target) override;

protected:
	void onFirstUpdate() final;

private:
	void setSpritesPosition(float x, float y);
	void setSpritesColor(float r, float g, float b, float a = 1.0f);

	enum class BehaviorState
	{
		Appear,						// 登場
		Transition,					// 通常への移行
		Move,						// 通常行動
		Rush,						// 突進攻撃
		Barrage,					// 弾幕攻撃
	};
	void setBehaviorState(BehaviorState state);
	BehaviorState getBehaviorState(void);

private:
	std::vector<core2d::Sprite*> m_sprites;
	SpriteAnime* m_spriteAnime;

	core2d::Collision::RectF* m_collision;

	enum : int
	{
		Status_None,
		Status_Dead,
	};

	int m_status;

	int m_life;

	BehaviorState m_behaviorState;
	int m_stateWait;		// 状態の切り替わりウエイト

	int m_shotWait;			// 通常時の発射間隔

	float m_dirX;
	float m_dirY;
	float m_speed;

	float m_basePositionX;
	float m_basePositionY;

	// 突進攻撃の更新
	bool updateRush(void);
	int m_rushStep;
	int m_rushMoveWait;
	float m_rushTargetX;
	float m_rushTargetY;
	float m_returnPositionX;
	float m_returnPositionY;
	float m_rushSpeed;

	// 弾幕攻撃の更新
	bool updateBarrage(void);
	// 指定数で円形に弾幕を作成
	void shotBarrage(int shotCount, float shiftRatio, float speed);
	int m_barrageStep;
	int m_barrageShotWait;
	

#if COLLISION_VISIBLE
	core2d::PrimitiveEdgeSprite* m_collisionSprite;
#endif
};

#endif