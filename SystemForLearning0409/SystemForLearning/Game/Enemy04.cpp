#include"Enemy04.h"
#include"ShootingGame.h"
#include"ShootingGameDef.h"
#include"SpriteAnime.h"
#include "Bullet.h"
#include "Player.h"

Enemy04::Enemy04(ShootingGame* manager) :Enemy(manager)
{
	m_rad = 0.f;
	m_speed = 1.0f;

	m_score = 10;
}

Enemy04::~Enemy04()
{

}

void Enemy04::update(void)
{
	Enemy::update();
}

void Enemy04::initSprites()
{
	int imageId[] =
	{
		ImageEnemy4_1,
		ImageEnemy4_2,

		ImageEnemyBomb1,		// 敵撃墜エフェクト
		ImageEnemyBomb2,
		ImageEnemyBomb3,
		ImageEnemyBomb4,
		ImageEnemyBomb5,
	};

	createSprites(imageId, sizeof(imageId) / sizeof(int));

	m_enemySpriteAnime->playLoop(0, 1);
}

void Enemy04::movePosition()
{
	float x = cosf(m_rad);

	if (x > 0)
	{
		m_dirX = -1.0f;
		m_speed = 1.5f;
	}
	else if (x < 0)
	{
		m_dirX = 1.0f;
		m_speed = 0.5f;
	}

	m_positionX += m_dirX * m_speed;

	m_rad += 0.01f;

}

void Enemy04::createBullet()
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
	bullet->setSpeed(3.0f);
}

void Enemy04::setDead()
{
	m_status = Status_Dead;
	m_enemySpriteAnime->setWait(1);
	m_enemySpriteAnime->playOnce(2, 6, true);
}