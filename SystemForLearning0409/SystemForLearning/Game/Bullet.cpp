#include "Bullet.h"

#include <cmath>
#include <Sprite.h>
#include <Collision.h>
#include "ShootingGame.h"

#if COLLISION_VISIBLE
#include <PrimitiveEdgeSprite.h>
#endif

using namespace core2d;

// -----------------------------------------------------------------------
// 弾を表すクラス
// -----------------------------------------------------------------------
Bullet::Bullet(ShootingGame* manager)
	: GameObject(manager)
	, m_dirX(0.0f)
	, m_dirY(0.0f)
	, m_speed(0.0f)
#if COLLISION_VISIBLE
	, m_collisionSprite(nullptr)
#endif
{
}

Bullet::~Bullet(void)
{
#if COLLISION_VISIBLE
	if (m_collisionSprite)
	{
		core2d::PrimitiveEdgeSprite::destroy(m_collisionSprite);
	}
#endif
}

void Bullet::setDirection(float x, float y)
{
	float length = sqrtf(x * x + y * y);
	if (length < FLT_EPSILON)
	{
		m_dirX = 0.0f;
		m_dirY = 0.0f;
	}
	else
	{
		m_dirX = x / length;
		m_dirY = y / length;
	}
}

void Bullet::setSpeed(float speed)
{
	m_speed = speed;
}

// -----------------------------------------------------------------------
// プレイヤーの弾クラス
// -----------------------------------------------------------------------
PlayerBullet::PlayerBullet(ShootingGame* manager)
	: Bullet(manager)
	, m_sprite(nullptr)
	, m_collision(nullptr)
	, m_damage(1)
{
}

PlayerBullet::~PlayerBullet(void)
{
	if (m_sprite)
	{
		Sprite::destroy(m_sprite);
		m_sprite = nullptr;
	}

	removeCollision();

	if (m_collision)
	{
		delete m_collision;
		m_collision = nullptr;
	}
}

void PlayerBullet::update(void)
{
	if (m_positionX < -10.0f || 650.f < m_positionX || m_positionY < -10.0f || 490.0f < m_positionY)
	{
		manager()->destroyGameObject(this);
		m_sprite->setActive(false);
		return;
	}

	m_positionX += m_dirX * m_speed;
	m_positionY += m_dirY * m_speed;
	m_sprite->setPosition(m_positionX, m_positionY);

	m_collision->x = m_positionX;
	m_collision->y = m_positionY;

	float rad = atan2f(m_dirY, m_dirX);
	m_sprite->setRotate(RAD_TO_DEG(rad));

#if COLLISION_VISIBLE
	m_collisionSprite->setPosition(m_positionX, m_positionY);
	m_collisionSprite->setActive(getCollisionVisible());
#endif
}

void PlayerBullet::onFirstUpdate()
{
	m_sprite = new Sprite(ImagePlayerBullet2);
	m_sprite->setPriority(static_cast<unsigned int>(DrawPriority::Bullet));
	m_sprite->setPosition(-100.0f, -100.0f);

	setDamage(m_damage);

	m_collision = new core2d::Collision::PointF(0, 0);

	addCollision(m_collision);

#if COLLISION_VISIBLE
	m_collisionSprite = new core2d::BoxEdgeSprite(0.0f, 0.0f);
	m_collisionSprite->setPosition(-100, -100);
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
#endif
}

void PlayerBullet::setDamage(int damage)
{
	m_damage = damage;

	if(m_sprite)
	{//威力が上がった場合に少しだけ弾を大きくする
		float scale = static_cast<float>(m_damage);
		if (scale != 1.0f)
		{
			scale = 1.f + (scale * 0.2f);
		}
		m_sprite->setScale(scale, scale);
	}
}

int PlayerBullet::getDamage(void)
{
	return m_damage;
}

// -----------------------------------------------------------------------
// 敵の弾クラス
// -----------------------------------------------------------------------
EnemyBullet::EnemyBullet(ShootingGame* manager, int imageId)
	: Bullet(manager)
	, m_sprite(nullptr)
	, m_collision(nullptr)
	, m_imageId(imageId)
	, m_spriteScaleX(1.0f)
	, m_spriteScaleY(1.0f)
{
}

EnemyBullet::~EnemyBullet(void)
{
	if (m_sprite)
	{
		Sprite::destroy(m_sprite);
		m_sprite = nullptr;
	}

	removeCollision();

	if (m_collision)
	{
		delete m_collision;
		m_collision = nullptr;
	}
}

void EnemyBullet::setSpriteScale(float x, float y)
{
	m_spriteScaleX = x;
	m_spriteScaleY = y;

	if(m_sprite)
	{
		m_sprite->setScale(m_spriteScaleX, m_spriteScaleY);
	}
}

void EnemyBullet::update(void)
{
	if (m_positionX < -10.0f || 650.f < m_positionX || m_positionY < -10.0f || 490.0f < m_positionY)
	{
		manager()->destroyGameObject(this);
		m_sprite->setActive(false);
		return;
	}

	m_positionX += m_dirX * m_speed;
	m_positionY += m_dirY * m_speed;
	m_sprite->setPosition(m_positionX, m_positionY);

	m_collision->x = m_positionX;
	m_collision->y = m_positionY;

	float rad = atan2f(m_dirY, m_dirX);
	m_sprite->setRotate(RAD_TO_DEG(rad));

#if COLLISION_VISIBLE
	m_collisionSprite->setPosition(m_positionX, m_positionY);
	m_collisionSprite->setActive(getCollisionVisible());
#endif
}

void EnemyBullet::onFirstUpdate()
{
	m_sprite = new Sprite(m_imageId);
	m_sprite->setPriority(static_cast<unsigned int>(DrawPriority::Bullet));
	m_sprite->setPosition(-100.0f, -100.0f);

	setSpriteScale(m_spriteScaleX, m_spriteScaleY);

	m_collision = new core2d::Collision::PointF(0, 0);

	addCollision(m_collision);

#if COLLISION_VISIBLE
	m_collisionSprite = new core2d::BoxEdgeSprite(0.0f, 0.0f);
	m_collisionSprite->setPosition(-100, -100);
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
#endif
}


