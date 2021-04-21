
#include <Sprite.h>
#include <SpriteAnime.h>

#include "ExplosionEffect.h"
#include "ShootingGame.h"
#include "ShootingGameDef.h"

static const int cEXPLOSION_SPRITE_START_INDEX = 0;
static const int cEXPLOSION_SPRITE_END_INDEX = 5;

ExplosionEffect::ExplosionEffect(ShootingGame* manager) : GameObject(manager)
, m_playFlag(PlayFlag::None), m_status(Status::None)
, m_onceDestroy(false)
,m_sprites(),m_spriteAnime()
{

}

ExplosionEffect::~ExplosionEffect()
{
	if (m_spriteAnime)
	{
		delete m_spriteAnime;
		m_spriteAnime = nullptr;
	}

	for(auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		core2d::Sprite::destroy(*it);
	}
}

void ExplosionEffect::onFirstUpdate()
{
	int imageId[] =
	{
		ImagePlayerBomb1,
		ImagePlayerBomb2,
		ImagePlayerBomb3,
		ImagePlayerBomb4,
		ImagePlayerBomb5,
		ImagePlayerBomb6,
	};

	int num = sizeof(imageId) / sizeof(int);

	m_spriteAnime = new SpriteAnime();

	for (int i = 0; i < num; ++i)
	{
		core2d::Sprite* sprite = new core2d::Sprite(imageId[i]);
		sprite->setPriority(static_cast<unsigned int>(DrawPriority::Effect));
		m_sprites.push_back(sprite);

		m_spriteAnime->addSprite(sprite);
	}
}

void ExplosionEffect::playOnce()
{
	m_playFlag = PlayFlag::Once;
}

void ExplosionEffect::playOnceDestroy()
{
	m_playFlag = PlayFlag::OnceDestroy;
}

void ExplosionEffect::playLoop()
{
	m_playFlag = PlayFlag::Loop;
}

void ExplosionEffect::update()
{
	if (m_status == Status::Dead)
	{
		return;
	}

	if (m_onceDestroy == true
		&& m_spriteAnime->isEnd())
	{
		manager()->destroyGameObject(this);
		m_status = Status::Dead;
		m_onceDestroy = false;
		return;
	}

	if (m_playFlag != PlayFlag::None)
	{
		switch(m_playFlag)
		{
		case PlayFlag::Once:
			m_spriteAnime->playOnce(cEXPLOSION_SPRITE_START_INDEX, cEXPLOSION_SPRITE_END_INDEX, true);
			break;

		case PlayFlag::OnceDestroy:
			m_spriteAnime->playOnce(cEXPLOSION_SPRITE_START_INDEX, cEXPLOSION_SPRITE_END_INDEX, true);
			m_onceDestroy = true;
			break;

		case PlayFlag::Loop:
			m_spriteAnime->playLoop(cEXPLOSION_SPRITE_START_INDEX, cEXPLOSION_SPRITE_END_INDEX);
			break;
		}

		m_playFlag = PlayFlag::None;
	}

	setSpritesPosition(m_positionX, m_positionY);
	setSpritesScale(m_scaleX, m_scaleY);
	setSpritesRotate(m_rotation);

	m_spriteAnime->update();
}

void ExplosionEffect::setSpritesPosition(float x, float y)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setPosition(x, y);
	}
}

void ExplosionEffect::setSpritesScale(float x, float y)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setScale(x, y);
	}
}

void ExplosionEffect::setSpritesRotate(float degree)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setRotate(degree);
	}
}

void ExplosionEffect::setSpritesActive(bool active)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setActive(active);
	}
}

void ExplosionEffect::setSpritesColor(float r, float g, float b, float a)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		(*it)->setMaterialColor(r, g, b, a);
	}
}