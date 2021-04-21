#include "Enemy.h"

#include <Sprite.h>
#include <PrimitiveEdgeSprite.h>
#include "ShootingGame.h"
#include "Bullet.h"
#include "SpriteAnime.h"
#include "UpgradeItem.h"

#include <Collision.h>
#include <Sound.h>

#if COLLISION_VISIBLE
#include <PrimitiveEdgeSprite.h>
#endif

using namespace core2d;

Enemy::Enemy(ShootingGame* manager)
	: GameObject(manager)
	//, m_sprite(nullptr)
	, m_enemySprites()
	, m_enemySpriteAnime(nullptr)
	, m_shotWait(0)
	, m_shotInterval(150)
	, m_dirX(0.0f)
	, m_dirY(0.0f)
	, m_speed(0.0f)
	, m_collision(nullptr)
	, m_status(Status_None)
	, m_upgradeItem(UpgradeType::ItemNone)
	, m_score(0)
#if COLLISION_VISIBLE
	, m_collisionSprite(nullptr)
#endif
{
	//m_sprite = new Sprite(32, 32);
	//m_sprite->setMaterialColor(0.0f, 1.0f, 0.2f, 1.0f);
	//m_sprite->setActive(false);

	// ¡‚¾‚¯
	m_dirX = -1.0f;
	m_dirY = 0.0f;

#if COLLISION_VISIBLE
	m_collisionSprite = new core2d::BoxEdgeSprite(32.f, 32.f);
	m_collisionSprite->setPosition(-100.f, -100.f);
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
#endif
}

Enemy::~Enemy(void)
{
	/*
	if (m_sprite)
	{
		Sprite::destroy(m_sprite);
		m_sprite = nullptr;
	}
	*/

	if (m_enemySpriteAnime)
	{
		delete m_enemySpriteAnime;
		m_enemySpriteAnime = nullptr;
	}

	for (auto it = m_enemySprites.begin(); it != m_enemySprites.end(); ++it)
	{
		core2d::Sprite::destroy(*it);
	}
	m_enemySprites.clear();

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

void Enemy::onFirstUpdate()
{
	initSprites();

	m_collision = new core2d::Collision::RectF(core2d::Collision::PointF(-100.f, -100.f), 32, 32);
	addCollision(m_collision);
}

void Enemy::update(void)
{
	if (m_status == Status_Dead)
	{
		if (m_enemySpriteAnime)
		{
			m_enemySpriteAnime->update();

			if (m_enemySpriteAnime->isEnd())
			{
				setDestroy();

				if (m_upgradeItem != UpgradeType::ItemNone)
				{
					auto item = manager()->createUpgradeItem();
					item->initialize(m_positionX, m_positionY, m_upgradeItem);
				}
			}
		}
		return;
	}

	//m_sprite->setActive();
	// ˆæŠOˆ—
	if (m_positionX < -10.0f /*|| 650.f < m_positionX*/ || m_positionY < -10.0f || 490.0f < m_positionY)
	{
		manager()->destroyGameObject(this);
		//m_sprite->setActive(false);
		setSpritesActive(false);
		return;
	}

	// “K“–‚ÉˆÚ“®‚µ‚Ü‚Ó
	movePosition();

	//m_sprite->setPosition(m_positionX, m_positionY);

	//m_collision->setPosition(m_positionX, m_positionY);

	setSpritesPosition(m_positionX, m_positionY);
	setSpritesScale(m_scaleX, m_scaleY);
	setSpritesRotate(m_rotation);

	// shotŠÖ”‚ğŒÄ‚Ñ‚Ü‚·
	if (--m_shotWait < 0)
	{
		createBullet();

		m_shotWait = m_shotInterval;
	}

	if (m_enemySpriteAnime) m_enemySpriteAnime->update();
}

void Enemy::setUpgradeItem(int itemType)
{
	m_upgradeItem = itemType;
}

void Enemy::createSprites(int* imageId, int num)
{
	m_enemySpriteAnime = new SpriteAnime();

	for (int i = 0; i < num; ++i)
	{
		core2d::Sprite* sprite = new Sprite(imageId[i]);
		sprite->setPriority(static_cast<unsigned int>(DrawPriority::Enemy));
		m_enemySprites.push_back(sprite);

		m_enemySpriteAnime->addSprite(sprite);
	}
}

void Enemy::movePosition()
{
	m_positionX += m_dirX * m_speed;
	m_positionY += m_dirY * m_speed;
}

void Enemy::setSpritesPosition(float x, float y)
{
	for (auto it = m_enemySprites.begin(); it != m_enemySprites.end(); ++it)
	{
		(*it)->setPosition(x, y);
	}

	if(m_collision)m_collision->setPosition(x, y);

#if COLLISION_VISIBLE
	if (m_collisionSprite)
	{
		m_collisionSprite->setPosition(x, y);
		m_collisionSprite->setActive(getCollisionVisible());
	}
#endif
}

void Enemy::setSpritesScale(float x, float y)
{
	for (auto it = m_enemySprites.begin(); it != m_enemySprites.end(); ++it)
	{
		(*it)->setScale(x, y);
	}
}

void Enemy::setSpritesRotate(float degree)
{
	for (auto it = m_enemySprites.begin(); it != m_enemySprites.end(); ++it)
	{
		(*it)->setRotate(degree);
	}
}

void Enemy::setSpritesActive(bool active)
{
	for (auto it = m_enemySprites.begin(); it != m_enemySprites.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

void Enemy::onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target)
{
	if (isDestroy()) return; //íœ–½—ß‚ª‚Å‚Ä‚¢‚é‚Æ‚«‚Íˆ—‚µ‚È‚¢

	if (m_status == Status_Dead) return;

	unsigned int tag = target->getTag();
	if (tag == GameObjectTag::PlayerBulletTag)
	{
		//setDestroy();
		setDead();

		core2d::SoundManager::instance()->startSe(GameSeId::Bomber);

		target->setDestroy(); //‘Šè‚Ì’e‚àÁ‚·

		manager()->addScore(getScore()); //“¾“_‰ÁZ
	}
}
