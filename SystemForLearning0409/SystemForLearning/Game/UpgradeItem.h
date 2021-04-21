#pragma once
#ifndef __UPGRADEITEM_HEADER__
#define __UPGRADEITEM_HEADER__

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

// �����A�C�e����\���N���X
class UpgradeItem : public GameObject
{
public:
	UpgradeItem(ShootingGame* manager);
	virtual ~UpgradeItem(void);

	void update(void) final;

	// �����ʒu�Ǝ�ނ�ݒ�
	void initialize(float x, float y, int type);

	int getUpgradeType(void);

protected:
	void onFirstUpdate() final;

private:
	core2d::Sprite* m_sprite;
	core2d::Collision::RectF* m_collision;
	float m_speed;
	int m_upgradeType;

#if COLLISION_VISIBLE
	core2d::PrimitiveEdgeSprite* m_collisionSprite;
#endif
};

#endif