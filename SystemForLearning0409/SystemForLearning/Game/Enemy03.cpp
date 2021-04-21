#include"Enemy03.h"
#include"ShootingGame.h"
#include"ShootingGameDef.h"
#include"SpriteAnime.h"
#include "Bullet.h"

//#define PI 3.14f

Enemy03::Enemy03(ShootingGame* manager) :Enemy(manager)
, m_rad(0.f)
{
	m_speed = 2.f;

	m_score = 5;
}

Enemy03::~Enemy03()
{

}

void Enemy03::update(void)
{
	Enemy::update();
}

void Enemy03::initSprites()
{
	int imageId[] =
	{
		ImageEnemy3_1,
		ImageEnemy3_2,

		ImageEnemyBomb1,		// “GŒ‚’ÄƒGƒtƒFƒNƒg
		ImageEnemyBomb2,
		ImageEnemyBomb3,
		ImageEnemyBomb4,
		ImageEnemyBomb5,
	};

	createSprites(imageId, sizeof(imageId) / sizeof(int));

	m_enemySpriteAnime->playLoop(0, 1);
}

void Enemy03::movePosition()
{
	if ((m_rad <= cPi)
		|| (m_rad > 3.f * cPi && m_rad <= 4.f * cPi))
	{//’¼i
		m_speed = 2.f;
		m_positionX += m_dirX * m_speed;

		if (m_rad == 0.0f)
		{
			if (m_positionY > 240)
			{
				m_dirY = -1.0f;
			}
			else
			{
				m_dirY = 1.0f;
			}
		}

		setRotation(0);
	}
	else if (m_rad <= 3.f * cPi)
	{//‰~‰^“®
		m_speed = 3.f;
		float x = cosf(m_rad);

		m_positionX += x * m_speed;
		m_positionY += m_dirY * 1.0f;

		float rotate = sinf(m_rad) * 0.5623f;
		
		setRotation(RAD_TO_DEG(rotate));

	}
	else
	{
		m_rad = 0.f;
		return;
	}

	m_rad += 0.1f;

}

void Enemy03::createBullet()
{
	EnemyBullet* bullet = manager()->createEnemyBullet(ImageEnemyBullet3);

	bullet->setPosition(m_positionX - 4.0f, m_positionY);
	bullet->setDirection(-1.0f, 0.0f);
	bullet->setSpeed(6.0f);
}

void Enemy03::setDead()
{
	m_status = Status_Dead;
	m_enemySpriteAnime->setWait(1);
	m_enemySpriteAnime->playOnce(2, 6, true);
}