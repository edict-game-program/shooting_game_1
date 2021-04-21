#include"Enemy01.h"
#include"ShootingGame.h"
#include"ShootingGameDef.h"
#include"SpriteAnime.h"
#include "Bullet.h"

Enemy01::Enemy01(ShootingGame* manager) :Enemy(manager)
{
	m_speed = 0.5f;

	m_score = 1;
}

Enemy01::~Enemy01()
{

}

void Enemy01::update(void)
{
	Enemy::update();
}

void Enemy01::initSprites()
{
	int imageId[] =
	{
		ImageEnemy1_1,
		ImageEnemy1_2,

		ImageEnemyBomb1,		// 敵撃墜エフェクト
		ImageEnemyBomb2,
		ImageEnemyBomb3,
		ImageEnemyBomb4,
		ImageEnemyBomb5,
	};

	createSprites(imageId, sizeof(imageId)/sizeof(int));

	m_enemySpriteAnime->playLoop(0,1);

}

void Enemy01::createBullet()
{
	EnemyBullet* bullet = manager()->createEnemyBullet(ImageEnemyBullet3);

	bullet->setPosition(m_positionX - 4.0f, m_positionY);
	bullet->setDirection(-1.0f, 0.0f);
	bullet->setSpeed(6.0f);
}

void Enemy01::setDead()
{
	m_status = Status_Dead;
	m_enemySpriteAnime->setWait(1);
	m_enemySpriteAnime->playOnce(2, 6, true);
}