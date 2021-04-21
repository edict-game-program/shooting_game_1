#include "SpecialEnemy.h"

#include <cmath>
#include <Sprite.h>
#include <Collision.h>

#include "ShootingGame.h"
#include "SpriteAnime.h"
#include "Player.h"
#include "Bullet.h"

#if COLLISION_VISIBLE
#include <PrimitiveEdgeSprite.h>
#endif

static const int cRushAttackFrame = 20;
static const int cPreliminaryRushFrame = 20;	// ラッシュ予備動作のフレーム数

SpecialEnemy::SpecialEnemy(ShootingGame* manager)
	: GameObject(manager)
	, m_sprites()
	, m_spriteAnime(nullptr)
	, m_collision(nullptr)
	, m_behaviorState(BehaviorState::Appear)
	, m_stateWait(0)
	, m_status(Status_None)
	, m_life(0)
	, m_shotWait(0)
	, m_dirX(0.0f)
	, m_dirY(0.0f)
	, m_speed(0.0f)
	, m_basePositionX(0.0f)
	, m_basePositionY(0.0f)
	, m_rushStep(0)
	, m_rushMoveWait(0)
	, m_rushTargetX(0.0f)
	, m_rushTargetY(0.0f)
	, m_returnPositionX(0.0f)
	, m_returnPositionY(0.0f)
	, m_rushSpeed(0.0f)
	, m_barrageStep(0)
	, m_barrageShotWait(0)
#if COLLISION_VISIBLE
	, m_collisionSprite{}
#endif
{
}

SpecialEnemy::~SpecialEnemy(void)
{
	if (m_spriteAnime)
	{
		delete m_spriteAnime;
		m_spriteAnime = nullptr;
	}

	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		core2d::Sprite::destroy(*it);
	}
	m_sprites.clear();

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

// 初期化処理
void SpecialEnemy::onFirstUpdate()
{
	m_life = 30;	// 仮

	auto mgr = GameObject::manager();
	m_positionX = mgr->getAvalableDisplayWidth() + 64.0f;
	m_positionY = mgr->getAvalableDisplayHeight() * 0.5f;

	// 基準点
	m_basePositionX = mgr->getDisplayWidth() * 0.8f;
	m_basePositionY = mgr->getAvalableDisplayHeight() * 0.5f;

	setBehaviorState(BehaviorState::Appear);

	// スプライトアニメーションの作成
	int imageId[] =
	{
		ImageId::ImageSpecialEnemy1,
		ImageId::ImageSpecialEnemy2,
		ImageId::ImageSpecialEnemy1,
		ImageId::ImageSpecialEnemy3,

		ImageId::ImageEnemyBomb1,		// 敵撃墜エフェクト
		ImageId::ImageEnemyBomb2,
		ImageId::ImageEnemyBomb3,
		ImageId::ImageEnemyBomb4,
		ImageId::ImageEnemyBomb5,
	};

	m_spriteAnime = new SpriteAnime();

	int num = sizeof(imageId) / sizeof(int);
	for (int i = 0; i < num; ++i)
	{
		//core2d::Sprite* sprite = new core2d::Sprite(imageId[i]);
		core2d::Sprite* sprite = new core2d::Sprite(imageId[i], 128, 128);
		sprite->setPriority(static_cast<unsigned int>(DrawPriority::Enemy));
		m_sprites.push_back(sprite);

		m_spriteAnime->addSprite(sprite);
	}
	m_spriteAnime->playLoop(0, 3);

	auto sprite = m_sprites[0];
	m_collision = new core2d::Collision::RectF(core2d::Collision::PointF(-100.f, -100.f), sprite->getWidth(), sprite->getHeight());
	m_collision->setActive(false);
	addCollision(m_collision);

#if COLLISION_VISIBLE
	m_collisionSprite = new core2d::BoxEdgeSprite(sprite->getWidth(), sprite->getHeight());
	m_collisionSprite->setPosition(-100.0f, -100.0f);
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
#endif
}

// ボスキャラの更新処理
void SpecialEnemy::update(void)
{
	setSpritesColor(1.0f, 1.0f, 1.0f);

	if (m_status == Status_Dead)
	{
		return;
	}

	switch (getBehaviorState())
	{
	case BehaviorState::Appear:
		m_positionX -= 1.f;
		if (m_positionX < m_basePositionX)
		{
			m_positionX = m_basePositionX;
			setBehaviorState(BehaviorState::Transition);
			m_dirX = 0.0f;
			m_dirY = -1.0f;
			m_speed = 1.0f;
		}
		break;

	case BehaviorState::Transition:
		if (--m_stateWait < 0)
		{
			setBehaviorState(BehaviorState::Move);
			m_collision->setActive(true);
		}
		break;

	case BehaviorState::Move:
		m_positionY += m_dirY * m_speed;
		if (m_dirY > 0.0f)
		{
			float distance = abs(m_basePositionY - m_positionY);
			if (distance > 140.f)
			{
				m_dirY = -1.0f;
			}
		}
		else if (m_dirY < 0.0f)
		{
			float distance = abs(m_basePositionY - m_positionY);
			if (distance > 140.f)
			{
				m_dirY = 1.0f;
			}
		}

		// 定期的に弾を撃つ
		if (--m_shotWait < 0)
		{
			EnemyBullet* bullet = manager()->createEnemyBullet(ImageEnemyBullet3);
			bullet->setPosition(m_positionX - 64.0f, m_positionY);
			bullet->setDirection(-1.0f, 0.0f);
			bullet->setSpeed(6.0f);
			m_shotWait = 180;
		}

		// ランダムに行動変化
		if (--m_stateWait < 0)
		{
			switch (rand() % 3)
			{
			default:
			case 0:
				setBehaviorState(BehaviorState::Move);
				break;

			case 1:
				setBehaviorState(BehaviorState::Rush);
				m_rushStep = 0;
				m_rushTargetX = m_sprites[0]->getWidth() + 16.0f;
				m_rushTargetY = m_positionY;
				m_returnPositionX = m_positionX;
				m_returnPositionY = m_positionY;

				m_rushMoveWait = cRushAttackFrame;
				break;

			case 2:
				setBehaviorState(BehaviorState::Barrage);
				m_barrageStep = 0;
				m_barrageShotWait = 30;
				break;
			}
		}
		break;

	case BehaviorState::Rush:
		if (updateRush())
		{
			setBehaviorState(BehaviorState::Transition);
		}
		break;

	case BehaviorState::Barrage:
		if (updateBarrage())
		{
			setBehaviorState(BehaviorState::Transition);
		}
		break;
	}

	setSpritesPosition(m_positionX, m_positionY);

	m_spriteAnime->update();

	m_collision->setPosition(m_positionX, m_positionY);

#if COLLISION_VISIBLE
	m_collisionSprite->setPosition(m_positionX, m_positionY);
	m_collisionSprite->setActive(getCollisionVisible());
#endif
}

// 衝突があったときに呼ばれる関数
void SpecialEnemy::onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target)
{
	if (isDestroy()) return;

	if (m_status == Status_Dead) return;

	unsigned int tag = target->getTag();
	if (tag == GameObjectTag::PlayerBulletTag)
	{
		target->setDestroy(); //相手の弾も消す

		setSpritesColor(2.0f, 2.0f, 2.0f);

		PlayerBullet* bullet = dynamic_cast<PlayerBullet*>(target);
		int damage = bullet->getDamage();
		m_life -= damage;
		if (m_life <= 0)
		{
			m_status = Status_Dead;
			m_spriteAnime->stop();
			//m_spriteAnime->playOnce(4, 8, true);
			manager()->notifySpecialEnemyDead(getId());
			manager()->addScore(10000);

			m_collision->setActive(false);
		}
	}
}

void SpecialEnemy::setSpritesPosition(float x, float y)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setPosition(x, y);
	}
}

void SpecialEnemy::setSpritesColor(float r, float g, float b, float a)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setMaterialColor(r, g, b, a);
	}
}

void SpecialEnemy::setBehaviorState(BehaviorState state)
{
	switch (state)
	{
	case BehaviorState::Transition:					m_stateWait = 40; break;
	case BehaviorState::Move:						m_stateWait = 480; break;
	case BehaviorState::Rush:						m_stateWait = cPreliminaryRushFrame; break;
	case BehaviorState::Barrage:					m_stateWait = 30; break;
	default: break;	// 設定なし
	}
	m_behaviorState = state;
}

SpecialEnemy::BehaviorState SpecialEnemy::getBehaviorState(void)
{
	return m_behaviorState;
}

// 突進行動の更新処理
bool SpecialEnemy::updateRush(void)
{
	bool end = false;
	if (m_rushStep == 0)
	{
		if (--m_rushMoveWait < 0)
		{
			setBehaviorState(BehaviorState::Rush);
			++m_rushStep;
			m_rushMoveWait = 20;
			m_rushTargetX = m_sprites[0]->getWidth() * 0.5f + 16.0f;
			m_rushTargetY = m_positionY;
			m_returnPositionX = m_positionX;
			m_returnPositionY = m_positionY;

			m_rushSpeed = abs(m_rushTargetX - m_returnPositionX) / static_cast<float>(cRushAttackFrame);
		}
		else
		{
			float halfFrame = static_cast<float>(cPreliminaryRushFrame / 2);
			float sub = abs(halfFrame - m_rushMoveWait);
			float distance = (1.0f - sub / halfFrame) * 8.f;

			float omega = DEG_TO_RAD(112.0f);
			m_positionX = m_returnPositionX + cosf(omega * m_rushMoveWait) * distance;
			m_positionY = m_returnPositionY + sinf(omega * m_rushMoveWait) * distance;
		}
	}
	else if (m_rushStep == 1)
	{
		if (--m_rushMoveWait < 0)
		{
			++m_rushStep;
		}
	}
	else if (m_rushStep == 2)
	{
		m_positionX -= m_rushSpeed;
		if (m_positionX < m_rushTargetX)
		{
			m_positionX = m_rushTargetX;
			m_positionY = m_rushTargetY;

			m_rushMoveWait = 10;
			++m_rushStep;
		}
	}
	else if(m_rushStep == 3)
	{
		if (--m_rushMoveWait < 0)
		{
			++m_rushStep;
		}
	}
	else if (m_rushStep == 4)
	{
		m_positionX += m_rushSpeed * 0.9f;
		if (m_positionX > m_returnPositionX)
		{
			m_positionX = m_returnPositionX;
			m_positionY = m_returnPositionY;

			++m_rushStep;
			m_rushMoveWait = 20;
		}
	}
	else
	{
		if (--m_rushMoveWait < 0)
		{
			end = true;
		}
	}
	return end;
	
}


// 弾幕行動の更新処理
bool SpecialEnemy::updateBarrage(void)
{
	bool end = false;
	if (m_barrageStep == 0)
	{
		if (--m_barrageShotWait < 0)
		{
			++m_barrageStep;
			m_barrageShotWait = 20;
		}
	}
	else if (m_barrageStep == 1)
	{
		if (--m_barrageShotWait < 0)
		{
			shotBarrage(12, 0.0f, 4.0f);
			m_barrageShotWait = 90;
			++m_barrageStep;
		}
	}
	else if (m_barrageStep == 2)
	{
		if (--m_barrageShotWait < 0)
		{
			shotBarrage(12, 0.5f, 4.0f);
			m_barrageShotWait = 40;
			++m_barrageStep;
		}
	}
	else if (m_barrageStep == 3)
	{
		if (--m_barrageShotWait < 0)
		{
			shotBarrage(12, 0.0f, 4.0f);
			m_barrageShotWait = 50;
			++m_barrageStep;
		}
	}
	else
	{
		if (--m_barrageShotWait < 0)
		{
			end = true;
		}
	}
	return end;
}


// 弾幕を作成する関数
void SpecialEnemy::shotBarrage(int shotCount, float shiftRatio, float speed)
{
	if (shotCount < 1) return;

	auto mgr = manager();
	float omega = DEG_TO_RAD(360.0f / static_cast<float>(shotCount));
	float shift = omega * shiftRatio;
	for (int i = 0; i < shotCount; ++i)
	{
		float radian = omega * i + shift;
		auto bullet = mgr->createEnemyBullet(ImageId::ImageEnemyBullet1);
		bullet->setPosition(m_positionX - 64.0f, m_positionY);
		bullet->setDirection(cosf(radian), sinf(radian));
		bullet->setSpeed(speed);
		bullet->setSpriteScale(4.f , 4.f);
	}
}