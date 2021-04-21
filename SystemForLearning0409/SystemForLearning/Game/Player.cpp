#include "Player.h"

#include <cmath>
#include <Sprite.h>
#include "ShootingGame.h"
#include "ShootingGameDef.h"
#include "Bullet.h"
#include "UpgradeItem.h"
#include <SpriteAnime.h>
#include <Sound.h>

#include <Collision.h>

#if COLLISION_VISIBLE
#include <PrimitiveEdgeSprite.h>
#endif


//Player通常スプライトアニメーション
static const int cImagePlayerDefaultStart = 0;
static const int cImagePlayerDefaultEnd = cImagePlayerDefaultStart;

//Player上移動スプライトアニメーション
static const int cImagePlayerUpStart = cImagePlayerDefaultStart + 1;
static const int cImagePlayerUpEnd = cImagePlayerUpStart + 2;

//Player下移動スプライトアニメーション
static const int cImagePlayerDownStart = cImagePlayerUpEnd + 1;
static const int cImagePlayerDownEnd = cImagePlayerDownStart + 2;

//Player爆発スプライトアニメーション
static const int cImagePlayerBombStart = cImagePlayerDownEnd + 1;
static const int cImagePlayerBombEnd = cImagePlayerBombStart + 5;

//ジェット通常スプライトアニメーション
static const int cImageFireNormalStart = 0;
static const int cImageFireNormalEnd = cImageFireNormalStart + 2;

//ジェット強スプライトアニメーション
static const int cImageFireBigStart = cImageFireNormalEnd + 1;
static const int cImageFireBigEnd = cImageFireBigStart + 2;

//ジェット弱スプライトアニメーション
static const int cImageFireSmallStart = cImageFireBigEnd + 1;
static const int cImageFireSmallEnd = cImageFireSmallStart + 2;

//プレイヤーのスピード
static const int cSpeedDefault = 3;
static const int cSpeedMax = 5;
static const int cSpeedMin = 1;

// 無敵時間
static const int cSlideInFrame = 10;
static const int cNoDamageFrame = cSlideInFrame + 50;

// 武器に関わるパラメータ
static const float cMainShotOffsetX = 16.f;
static const float cForwardShotOffsetX = 6.f;
static const float cDiffusionShotOffsetX = 1.f;
static const float cDiffusionShotOffsetY = 7.f;
static const int cRapidFireCount	= 3;		// 連射数
static const int cRapidFireInterval	= 6;		// 連射フレーム間隔
static const int cAfterFirstShotsInterval	= 30;
static const int cAfterSecondShotsInterval	= 60;
static const int cGradeMax = 2;

// 各ショットのダメージテーブル
static const int cNormalShotTable[cGradeMax + 1] = {
	1,
	2,
	3
};

static const int cForwardShotTable[cGradeMax + 1] = {
	1,
	1,
	2
};

static const int cDiffusionShotTable[cGradeMax + 1] = {
	1,
	1,
	2
};

Player::Player(ShootingGame* manager, float posX, float posY)
	: GameObject(manager)
	, m_playerSprites()
	, m_fireSprites()
	, m_collision(nullptr)
	, m_playerSpriteAnime(nullptr)
	, m_fireSpriteAnime(nullptr)
	, m_subParts(nullptr)
	, m_offsetFireX(0.f)
	, m_offsetFireY(0.f)
	, m_offsetSubPartsX(0.f)
	, m_offsetSubPartsY(0.f)
	, m_oldInputX(0.f)
	, m_oldInputY(0.f)
	, m_speed(cSpeedDefault)
	, m_status(Status_None)
	, m_startAnimationState(StartAnimationState::SlideIn)
	, m_startAnimationFrame(0)
	, m_startAnimationSpritePosX(0.0f)
	, m_startAnimationMoveSpeed(0.0f)
	, m_weaponGrade{}
	, m_shotDamage{ 1, 1, 1 }
	, m_subWeaponFunction(nullptr)
	, m_subWeaponStep(SubWeaponStep::FirstShots)
	, m_subWeaponWait(0)
	, m_subShotCount(0)
#if COLLISION_VISIBLE
	, m_collisionSprite(nullptr)
#endif
{
	m_positionX = posX;
	m_positionY = posY;
}


Player::~Player(void)
{

	if (m_playerSpriteAnime)
	{
		delete m_playerSpriteAnime;
		m_playerSpriteAnime = nullptr;
	}

	if (m_fireSpriteAnime)
	{
		delete m_fireSpriteAnime;
		m_fireSpriteAnime = nullptr;
	}

	if (m_subParts)
	{
		core2d::Sprite::destroy(m_subParts);
		m_subParts = nullptr;
	}

	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		core2d::Sprite::destroy(*it);
	}
	m_playerSprites.clear();

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		core2d::Sprite::destroy(*it);
	}
	m_fireSprites.clear();

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


void Player::onFirstUpdate()
{
	m_shotDamage[static_cast<int>(ShotType::Normal)] = cNormalShotTable[m_weaponGrade[static_cast<int>(ShotType::Normal)]];

	//コリジョンの登録
	m_collision = new core2d::Collision::RectF(core2d::Collision::PointF(-100.f, -100.f), 26, 8);
	m_collision->setActive(false);
	addCollision(m_collision);

#if COLLISION_VISIBLE
	m_collisionSprite = new  core2d::BoxEdgeSprite(26, 8);
	m_collisionSprite->setColor(0.0f, 1.0f, 0.5f);
	m_collisionSprite->setPosition(-100, -100);
#endif

	//
	m_playerSpriteAnime = new SpriteAnime();
	m_fireSpriteAnime = new SpriteAnime();
	//自機のスプライト生成
	{
		int playerSpriteId[] =
		{
			ImagePlayer,

			ImagePlayerUp1,
			ImagePlayerUp2,
			ImagePlayerUp3,

			ImagePlayerDown1,
			ImagePlayerDown2,
			ImagePlayerDown3,

			ImagePlayerBomb1,		// 自機撃墜エフェクト
			ImagePlayerBomb2,
			ImagePlayerBomb3,
			ImagePlayerBomb4,
			ImagePlayerBomb5,
			ImagePlayerBomb6,
		};

		for (int i = 0; i < sizeof(playerSpriteId) / sizeof(int); ++i)
		{
			core2d::Sprite* sprite = new core2d::Sprite(playerSpriteId[i]);
			sprite->setPriority(static_cast<unsigned int>(DrawPriority::Player));
			m_playerSprites.push_back(sprite);

			m_playerSpriteAnime->addSprite(sprite);
		}

		m_offsetFireX = -1.f * m_playerSprites.at(0)->getWidth() + 10.f;
		m_offsetFireY = 1.f;
		m_offsetSubPartsX = m_playerSprites.at(0)->getWidth()/2 + 4.f;
		m_offsetSubPartsY = 0.f;
	}

	//ジェット噴射のスプライト生成
	{
		int fireSpriteId[] =
		{
			ImagePlayerFire1,
			ImagePlayerFire2,
			ImagePlayerFire3,

			ImagePlayerFireBig1,
			ImagePlayerFireBig2,
			ImagePlayerFireBig3,

			ImagePlayerFireSmall1,
			ImagePlayerFireSmall2,
			ImagePlayerFireSmall3,
		};

		for (int i = 0; i < sizeof(fireSpriteId) / sizeof(int); ++i)
		{
			core2d::Sprite* sprite = new core2d::Sprite(fireSpriteId[i]);
			sprite->setPriority(static_cast<unsigned int>(DrawPriority::Player));
			m_fireSprites.push_back(sprite);

			m_fireSpriteAnime->addSprite(sprite);
		}
	}

	setSpritesScale(-1, 1);

	m_playerSpriteAnime->playOnce(cImagePlayerDefaultStart, cImagePlayerDefaultEnd);
	m_fireSpriteAnime->playLoop(cImageFireNormalStart, cImageFireNormalEnd);

	m_startAnimationState = StartAnimationState::SlideIn;
	m_startAnimationSpritePosX = -64.0f;
	m_startAnimationMoveSpeed = (m_positionX - m_startAnimationSpritePosX) / static_cast<float>(cSlideInFrame);

	setSpritesPosition(m_startAnimationSpritePosX, m_positionY);

}

// プレイヤークラスの更新処理
void Player::update(void)
{
	if (m_startAnimationState != StartAnimationState::None)
	{
		++m_startAnimationFrame;
		setSpritesAlpha(static_cast<float>(m_startAnimationFrame % 2));

		if (m_startAnimationState == StartAnimationState::SlideIn)
		{
			m_startAnimationSpritePosX += m_startAnimationMoveSpeed;
			if (m_startAnimationSpritePosX > m_positionX)
			{
				m_startAnimationState = StartAnimationState::NoDamage;
				m_startAnimationSpritePosX = m_positionX;
			}
			setSpritesPosition(m_startAnimationSpritePosX, m_positionY);
			return;
		}
		else if (m_startAnimationState == StartAnimationState::NoDamage)
		{
			if (m_startAnimationFrame > cNoDamageFrame)
			{
				m_startAnimationState = StartAnimationState::None;
				setSpritesAlpha(1.0f);
				m_collision->setActive(true);
			}
		}
	}

	if (isDead())
	{
		m_playerSpriteAnime->update();

		if (m_playerSpriteAnime->isEnd())
		{
			//setDestroy();
			setSpritesActive(false);
			m_collision->setActive(false);
			manager()->notifyPlayerDead();
			//m_status = Status_None;
			//m_playerSpriteAnime->playOnce(ImagePlayerDefaultStart, ImagePlayerDefaultEnd);
			//m_fireSpriteAnime->playLoop(ImageFireNormalStart, ImageFireNormalEnd);
		}
		return;
	}

	// キー入力でプレイヤーの移動
	float x = manager()->getThumbX();
	float y = manager()->getThumbY();

	if (x > 0)
	{
		if (m_oldInputX <= 0)
		{
			m_fireSpriteAnime->playLoop(cImageFireBigStart, cImageFireBigEnd);
		}
	}
	else if (x < 0)
	{
		if (m_oldInputX >= 0)
		{
			m_fireSpriteAnime->playLoop(cImageFireSmallStart, cImageFireSmallEnd);
		}
	}
	else if(x == 0)
	{
		if (m_oldInputX != 0)
		{
			m_fireSpriteAnime->playLoop(cImageFireNormalStart, cImageFireNormalEnd);
		}
	}

	//自機の上下移動に合わせてスプライトを切り替える
	if (y > 0)
	{
		if (m_oldInputY <= 0)
		{
			m_playerSpriteAnime->playOnce(cImagePlayerUpStart, cImagePlayerUpEnd);
		}
	}
	else if (y < 0)
	{
		if (m_oldInputY >= 0)
		{
			m_playerSpriteAnime->playOnce(cImagePlayerDownStart, cImagePlayerDownEnd);
		}
	}
	else if(y == 0)
	{
		if (m_oldInputY != 0)
		{
			m_playerSpriteAnime->playOnce(cImagePlayerDefaultStart, cImagePlayerDefaultEnd);
		}
	}

	// 移動量を加算
	m_positionX += x * m_speed;
	m_positionY += y * m_speed;

	// 範囲制限
	float halfWidth = m_playerSprites[0]->getWidth() * 0.5f;
	if (m_positionX < halfWidth + 1.0f)
	{
		m_positionX = halfWidth + 1.0f;
	}
	else if (m_positionX > manager()->getAvalableDisplayWidth() - halfWidth)
	{
		m_positionX = manager()->getAvalableDisplayWidth() - halfWidth;
	}

	float halfHeight = m_playerSprites[0]->getHeight() * 0.5f;
	if (m_positionY < halfHeight)
	{
		m_positionY = halfHeight;
	}
	else if (m_positionY > manager()->getAvalableDisplayHeight() - halfHeight)
	{
		m_positionY = manager()->getAvalableDisplayHeight() - halfHeight;
	}

	//コリジョンの位置
	m_collision->setPosition(m_positionX, m_positionY);

	//スプライトの表示位置を同期
	setSpritesPosition(m_positionX, m_positionY);

	// 発射の処理
	if (manager()->getPushed(ButtonItem::A))
	{
		PlayerBullet* bullet = manager()->createPlayerBullet();

		//弾の速度、角度変更
		bullet->setPosition(m_positionX + cMainShotOffsetX, m_positionY);
		bullet->setDirection(1.0f, 0.0f);
		bullet->setSpeed(5.0f);		//マイナスにすると逆方向に動く
		bullet->setDamage(m_shotDamage[static_cast<int>(ShotType::Normal)]);

		core2d::SoundManager::instance()->startSe(GameSeId::Shot);
	}

	if (m_subWeaponFunction)
	{
		(this->*m_subWeaponFunction)();
	}

	//スピード変更
	if (manager()->getPushed(ButtonItem::X)
		&& m_speed > cSpeedMin)
	{
		--m_speed;
		manager()->notifyUpdateSpeed();
	}
	else if(manager()->getPushed(ButtonItem::Y)
		&& m_speed < cSpeedMax)
	{
		++m_speed;
		manager()->notifyUpdateSpeed();
	}
	
	m_playerSpriteAnime->update();
	m_fireSpriteAnime->update();

	m_oldInputX = x;
	m_oldInputY = y;

#if COLLISION_VISIBLE
	m_collisionSprite->setPosition(m_positionX, m_positionY);
	m_collisionSprite->setActive(getCollisionVisible());
#endif
}


void Player::setSpritesPosition(float x, float y)
{
	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		(*it)->setPosition(x, y);
	}

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setPosition(x + m_offsetFireX, y + m_offsetFireY);
	}

	if (m_subParts)
	{
		m_subParts->setPosition(x + m_offsetSubPartsX, y + m_offsetSubPartsY);
	}


}

void Player::setSpritesScale(float x, float y)
{
	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		(*it)->setScale(x, y);
	}

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setScale(x, y);
	}

	if (m_subParts)
	{
		m_subParts->setScale(x, y);
	}
}

void Player::setSpritesRotate(float degree)
{
	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		(*it)->setRotate(degree);
	}

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setRotate(degree);
	}

	if (m_subParts)
	{
		m_subParts->setRotate(degree);
	}
}

void Player::setSpritesAlpha(float a)
{
	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		(*it)->setMaterialColor(1.0f, 1.0f, 1.0f, a);
	}

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setMaterialColor(1.0f, 1.0f, 1.0f, a);
	}

	if (m_subParts)
	{
		m_subParts->setMaterialColor(1.0f, 1.0f, 1.0f, a);
	}
}

void Player::setSpritesActive(bool active)
{
	for (auto it = m_playerSprites.begin(); it != m_playerSprites.end(); ++it)
	{
		(*it)->setActive(active);
	}

	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setActive(active);
	}

	if (m_subParts)
	{
		m_subParts->setActive(active);
	}
}

void Player::setFireSpritesActive(bool active)
{
	for (auto it = m_fireSprites.begin(); it != m_fireSprites.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

void Player::onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target)
{
	if (isDestroy()) return; //削除命令がでているときは処理しない

	if (isDead()) return; //自機がやられている状態なら処理しない

	unsigned int tag = target->getTag();
	if (tag == GameObjectTag::EnemyBulletTag
		|| tag == GameObjectTag::EnemyTag
		|| tag == GameObjectTag::SpecialEnemyTag)
	{
		m_status = Status_Dead;
		m_playerSpriteAnime->playOnce(cImagePlayerBombStart, cImagePlayerBombEnd, true);
		m_fireSpriteAnime->stop();
		setFireSpritesActive(false);
		core2d::SoundManager::instance()->startSe(GameSeId::Bomber);

		if (m_subParts)
		{
			core2d::Sprite::destroy(m_subParts);
			m_subParts = nullptr;
		}

		if (tag == GameObjectTag::EnemyBulletTag)
		{
			target->setDestroy();
		}

		return;
		//setDestroy();
	}
	else if (tag == GameObjectTag::UpgradeItemTag)
	{
		core2d::SoundManager::instance()->startSe(GameSeId::ItemGet);

		auto item = dynamic_cast<UpgradeItem*>(target);
		if (item->getUpgradeType() == UpgradeType::MainPower)
		{
			int& grade = m_weaponGrade[static_cast<int>(ShotType::Normal)];
			if (grade < cGradeMax)
			{
				++grade;
			}
			m_shotDamage[static_cast<int>(ShotType::Normal)] = cNormalShotTable[grade];
		}
		else if (item->getUpgradeType() == UpgradeType::Forward)
		{
			setSubForward();
		}
		if (item->getUpgradeType() == UpgradeType::Diffusion)
		{
			setSubDiffuse();
		}
		target->setDestroy();
	}
}

void Player::createSubParts(int imageId)
{
	if (m_subParts)
	{
		core2d::Sprite::destroy(m_subParts);
	}

	m_subParts = new core2d::Sprite(imageId);
	m_subParts->setScale(-1.f, 1.f);
	m_subParts->setPosition(m_positionX + m_offsetSubPartsX, m_positionY + m_offsetSubPartsY);
}


void Player::setSubForward(void)
{
	if (m_subWeaponFunction != &Player::updateSubForward)
	{
		m_subWeaponFunction = &Player::updateSubForward;
		m_subWeaponStep = SubWeaponStep::FirstShots;

		m_subWeaponWait = 0;
		m_subShotCount = 0;

		m_offsetSubPartsX = m_playerSprites.at(0)->getWidth() / 2 - 8.f;
		m_offsetSubPartsY = -6.f;

		createSubParts(ImagePlayerSub2);

	}
	else
	{
		int& grade = m_weaponGrade[static_cast<int>(ShotType::Forward)];
		if (grade < cGradeMax)
		{
			++grade;
		}
	}
}

void Player::setSubDiffuse(void)
{
	if (m_subWeaponFunction != &Player::updateSubDeffusion)
	{
		m_subWeaponFunction = &Player::updateSubDeffusion;
		m_subWeaponStep = SubWeaponStep::FirstShots;

		m_subWeaponWait = 0;
		m_subShotCount = 0;

		m_offsetSubPartsX = m_playerSprites.at(0)->getWidth() / 2 + 4.f;
		m_offsetSubPartsY = 0.f;

		createSubParts(ImagePlayerSub1);
	}
	else
	{
		int& grade = m_weaponGrade[static_cast<int>(ShotType::Diffusion)];
		if (grade < cGradeMax)
		{
			++grade;
		}
	}
}

// 補助武器１前方型の更新処理
void Player::updateSubForward(void)
{
	switch (m_subWeaponStep)
	{
	case SubWeaponStep::FirstShots:
		if (--m_subWeaponWait <= 0)
		{
			core2d::SoundManager::instance()->startSe(GameSeId::SubShot);

			PlayerBullet* bullet = manager()->createPlayerBullet();
			bullet->setPosition(m_positionX + m_offsetSubPartsX + cForwardShotOffsetX, m_positionY + m_offsetSubPartsY);
			bullet->setDirection(1.0f, 0.0f);
			bullet->setSpeed(4.0f);
			bullet->setDamage(m_shotDamage[static_cast<int>(ShotType::Forward)]);

			m_subWeaponWait = cRapidFireInterval;

			if (++m_subShotCount == cRapidFireCount)
			{
				m_subWeaponWait = cAfterFirstShotsInterval;
				m_subWeaponStep = SubWeaponStep::SecondShots;
				m_subShotCount = 0;
			}
		}
		break;

	case SubWeaponStep::SecondShots:
		if (--m_subWeaponWait <= 0)
		{
			if (m_weaponGrade[static_cast<int>(ShotType::Forward)] > 0)
			{
				core2d::SoundManager::instance()->startSe(GameSeId::SubShot);

				PlayerBullet* bullet = manager()->createPlayerBullet();
				bullet->setPosition(m_positionX + m_offsetSubPartsX + cForwardShotOffsetX, m_positionY + m_offsetSubPartsY);
				bullet->setDirection(1.0f, 0.0f);
				bullet->setSpeed(4.0f);
				bullet->setDamage(m_shotDamage[static_cast<int>(ShotType::Forward)]);
			}

			m_subWeaponWait = cRapidFireInterval;

			if (++m_subShotCount == cRapidFireCount)
			{
				m_subWeaponWait = cAfterSecondShotsInterval;
				m_subWeaponStep = SubWeaponStep::FirstShots;
				m_subShotCount = 0;
			}
		}
		break;
	}
}

// 補助武器２拡散型の更新処理
void Player::updateSubDeffusion(void)
{
	switch (m_subWeaponStep)
	{
	case SubWeaponStep::FirstShots:
		if (--m_subWeaponWait <= 0)
		{
			core2d::SoundManager::instance()->startSe(GameSeId::SubShot);

			float rad = DEG_TO_RAD(7.5f + 10.0f * m_subShotCount);
			float dirX = cosf(rad);
			float dirY = sinf(rad);

			int damage = m_shotDamage[static_cast<int>(ShotType::Diffusion)];

			PlayerBullet* bullet = manager()->createPlayerBullet();
			bullet->setPosition(m_positionX + m_offsetSubPartsX + cDiffusionShotOffsetX, m_positionY + m_offsetSubPartsY + cDiffusionShotOffsetY);
			bullet->setDirection(dirX, dirY);
			bullet->setSpeed(4.0f);
			bullet->setDamage(damage);

			bullet = manager()->createPlayerBullet();
			bullet->setPosition(m_positionX + m_offsetSubPartsX + cDiffusionShotOffsetX, m_positionY + m_offsetSubPartsY - cDiffusionShotOffsetY);
			bullet->setDirection(dirX, -dirY);
			bullet->setSpeed(4.0f);
			bullet->setDamage(damage);

			m_subWeaponWait = cRapidFireInterval;

			if (++m_subShotCount == cRapidFireCount)
			{
				m_subWeaponWait = cAfterFirstShotsInterval;
				m_subWeaponStep = SubWeaponStep::SecondShots;
				m_subShotCount = 0;
			}
		}
		break;

	case SubWeaponStep::SecondShots:
		if (--m_subWeaponWait <= 0)
		{
			if (m_weaponGrade[static_cast<int>(ShotType::Diffusion)] > 0)
			{
				core2d::SoundManager::instance()->startSe(GameSeId::SubShot);

				float dirX = cosf(DEG_TO_RAD(12.5f + 10.0f * m_subShotCount));
				float dirY = sinf(DEG_TO_RAD(12.5f + 10.0f * m_subShotCount));

				int damage = m_shotDamage[static_cast<int>(ShotType::Diffusion)];

				PlayerBullet* bullet = manager()->createPlayerBullet();
				bullet->setPosition(m_positionX + m_offsetSubPartsX + cDiffusionShotOffsetX, m_positionY + m_offsetSubPartsY + cDiffusionShotOffsetY);
				bullet->setDirection(dirX, dirY);
				bullet->setSpeed(4.0f);
				bullet->setDamage(damage);

				bullet = manager()->createPlayerBullet();
				bullet->setPosition(m_positionX + m_offsetSubPartsX + cDiffusionShotOffsetX, m_positionY + m_offsetSubPartsY - cDiffusionShotOffsetY);
				bullet->setDirection(dirX, -dirY);
				bullet->setSpeed(4.0f);
				bullet->setDamage(damage);
			}

			m_subWeaponWait = cRapidFireInterval;

			if (++m_subShotCount == cRapidFireCount)
			{
				m_subWeaponWait = cAfterSecondShotsInterval;
				m_subWeaponStep = SubWeaponStep::FirstShots;
				m_subShotCount = 0;
			}
		}
		break;
	}
}