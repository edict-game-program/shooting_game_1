#pragma once
#ifndef __PLAYER_HEADER__
#define __PLAYER_HEADER__

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

// プレイヤーキャラを表すクラス
class Player : public GameObject
{
public:
	Player(ShootingGame* manager, float posX, float posY);
	virtual ~Player(void);

	// 行動を更新
	void update(void) final;

	void onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target) override;

	bool isDead() { return (m_status == Status_Dead); } //自機がやられたか？

	//移動スピードの取得
	int getSpeed() { return m_speed; }

private:
	void onFirstUpdate() final;

	void setSpritesPosition(float x, float y);
	void setSpritesScale(float x, float y);
	void setSpritesRotate(float degree);
	void setSpritesAlpha(float a);
	void setSpritesActive(bool active);

	void setFireSpritesActive(bool active);

	void createSubParts(int imageId);

	void setSubForward(void);
	void setSubDiffuse(void);
	void updateSubForward(void);
	void updateSubDeffusion(void);

private:
	std::vector<core2d::Sprite*> m_playerSprites;
	std::vector<core2d::Sprite*> m_fireSprites;
	core2d::Sprite* m_subParts;

	core2d::Collision::RectF* m_collision;

	SpriteAnime* m_playerSpriteAnime;
	SpriteAnime* m_fireSpriteAnime;

	float m_offsetFireX;
	float m_offsetFireY;
	float m_offsetSubPartsX;
	float m_offsetSubPartsY;

	float m_oldInputX;
	float m_oldInputY;

	int m_speed;

	enum : int
	{
		Status_None = 0,	//特になにもなし
		Status_Dead,	//自機がやられた
	};

	int m_status;

	// 生成時アニメーション
	enum class StartAnimationState
	{
		SlideIn,
		NoDamage,
		None,
	};
	StartAnimationState m_startAnimationState;
	int m_startAnimationFrame;
	float m_startAnimationSpritePosX;	
	float m_startAnimationMoveSpeed;

	enum class ShotType : int
	{
		Normal,			// メイン武器のみ
		Forward,		// 前方型補助武器あり
		Diffusion,		// 拡散型補助武器あり

		Count
	};
	int m_weaponGrade[static_cast<int>(ShotType::Count)];	// 武器の強化度
	int m_shotDamage[static_cast<int>(ShotType::Count)];	// 威力

	// 補助武器の更新段階
	enum class SubWeaponStep
	{
		FirstShots,
		SecondShots,
	};

	// メンバ関数用の関数ポインタ型を定義
	typedef void (Player::* SubWeapon)(void);

	SubWeapon m_subWeaponFunction;
	SubWeaponStep m_subWeaponStep;
	int m_subWeaponWait;			// 補助武器の発射待ち
	int m_subShotCount;				// 発射数

#if COLLISION_VISIBLE
	core2d::PrimitiveEdgeSprite* m_collisionSprite;
#endif
};

#endif