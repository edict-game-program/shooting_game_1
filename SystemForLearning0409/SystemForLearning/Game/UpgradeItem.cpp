#include "UpgradeItem.h"

#include <Sprite.h>
#include <Collision.h>

#include "ShootingGame.h"

#if COLLISION_VISIBLE
#include <PrimitiveEdgeSprite.h>
#endif


UpgradeItem::UpgradeItem(ShootingGame* manager)
	: GameObject(manager)
	, m_sprite(nullptr)
	, m_collision(nullptr)
	, m_speed(1.0f)
	, m_upgradeType(0)
#if COLLISION_VISIBLE
	, m_collisionSprite(nullptr)
#endif
{
}

UpgradeItem::~UpgradeItem(void)
{
	if (m_sprite)
	{
		core2d::Sprite::destroy(m_sprite);
		m_sprite = nullptr;
	}

	removeCollision();

	if (m_collision)
	{
		delete m_collision;
		m_collision = nullptr;
	}

#if COLLISION_VISIBLE
	if (m_collisionSprite)
	{
		core2d::PrimitiveEdgeSprite::destroy(m_collisionSprite);
		m_collisionSprite = nullptr;
	}
#endif
}

void UpgradeItem::onFirstUpdate()
{
	int imageId[3] =
	{
		ImageId::ImageItem1,
		ImageId::ImageItem2,
		ImageId::ImageItem3,
	};
	m_sprite = new core2d::Sprite(imageId[m_upgradeType]);
	m_sprite->setPriority(static_cast<unsigned int>(DrawPriority::Item));
	m_collision = new core2d::Collision::RectF(core2d::Collision::PointF(-100.f, -100.f), m_sprite->getWidth(), m_sprite->getHeight());
	addCollision(m_collision);

#if COLLISION_VISIBLE
	m_collisionSprite = new core2d::BoxEdgeSprite(m_sprite->getWidth(), m_sprite->getHeight());
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
#endif
}

void UpgradeItem::update(void)
{
	if (m_positionX < -40.0f)
	{
		setDestroy();
		m_sprite->setActive(false);
		return;
	}

	m_positionX -= m_speed;
	m_collision->setPosition(m_positionX, m_positionY);
	m_sprite->setPosition(m_positionX, m_positionY);

#if COLLISION_VISIBLE
	m_collisionSprite->setPosition(m_positionX, m_positionY);
	m_collisionSprite->setActive(getCollisionVisible());
#endif
}

void UpgradeItem::initialize(float x, float y, int type)
{
	m_positionX = x;
	m_positionY = y;
	m_speed = 1.0f;
	m_upgradeType = type;
}

int UpgradeItem::getUpgradeType(void)
{
	return m_upgradeType;
}
