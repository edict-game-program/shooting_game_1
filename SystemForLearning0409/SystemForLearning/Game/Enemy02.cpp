#include"Enemy02.h"
#include"ShootingGame.h"
#include"ShootingGameDef.h"
#include"SpriteAnime.h"
#include "Bullet.h"
#include "Player.h"

Enemy02::Enemy02(ShootingGame* manager) :Enemy(manager)
, m_rad(0.f)
{
	m_speed = 1.f;

	m_score = 2;
}

Enemy02::~Enemy02()
{

}

void Enemy02::update(void)
{
	Enemy::update();
}

void Enemy02::initSprites()
{
	int imageId[] =
	{
		ImageEnemy2_1,
		ImageEnemy2_2,

		ImageEnemyBomb1,		// 敵撃墜エフェクト
		ImageEnemyBomb2,
		ImageEnemyBomb3,
		ImageEnemyBomb4,
		ImageEnemyBomb5,
	};

	createSprites(imageId, sizeof(imageId) / sizeof(int));

	m_enemySpriteAnime->playLoop(0, 1);
}

void Enemy02::movePosition()
{
	float y = sinf(m_rad);

	m_positionX += m_dirX * m_speed;
	m_positionY += y * m_speed;

	m_rad += 0.05f;

}

void Enemy02::createBullet()
{
	EnemyBullet* bullet = manager()->createEnemyBullet(ImageEnemyBullet1);
	Player* player = manager()->getPlayerObject();

	bullet->setPosition(m_positionX - 4.0f, m_positionY);

	if (player)
	{
		float vectorX = player->getPositionX() - m_positionX;
		float vectorY = player->getPositionY() - m_positionY;

		bullet->setDirection(vectorX, vectorY);
	}
	else
	{//プレイヤーが死んでいる時は正面に発射
		bullet->setDirection(-1.0f, 0.0f);
	}
	bullet->setSpeed(6.0f);
}

void Enemy02::setDead()
{
	m_status = Status_Dead;
	m_enemySpriteAnime->setWait(1);
	m_enemySpriteAnime->playOnce(2, 6, true);
}