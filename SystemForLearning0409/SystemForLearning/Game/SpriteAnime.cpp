#include "SpriteAnime.h"

#include <Sprite.h>

SpriteAnime::SpriteAnime():
	m_startIndex(0), m_endIndex(0), m_nowIndex(0)
	, m_loop(false), m_end(false), m_unenableWhenFinish(false), m_stop(false)
	, m_wait(5), m_waitCount(0)
	, m_sprites()
{

}

SpriteAnime::~SpriteAnime()
{
	m_sprites.clear();
}

int SpriteAnime::addSprite(core2d::Sprite* sprite)
{
	sprite->setActive(false); //”ñ•\Ž¦‚É‚µ‚Ä“o˜^‚·‚é

	m_sprites.push_back(sprite);

	return static_cast<int>(m_sprites.size() -1);
}


void SpriteAnime::playOnce(bool unenableWhenFinish)
{
	playOnce(0, -1, unenableWhenFinish);
}

void SpriteAnime::playOnce(int startIndex, int endIndex, bool unenableWhenFinish)
{
	m_sprites.at(m_nowIndex)->setActive(false);

	m_startIndex = startIndex;
	m_nowIndex = startIndex;
	if (endIndex < 0)
	{
		m_endIndex = static_cast<int>(m_sprites.size()-1);
	}
	else
	{
		m_endIndex = endIndex;
	}

	m_waitCount = 0;
	m_loop = false;
	m_end = false;

	m_unenableWhenFinish = unenableWhenFinish;

	m_sprites.at(m_nowIndex)->setActive(true);

	m_stop = false;

}

void SpriteAnime::playLoop()
{
	playLoop(0,-1);
}

void SpriteAnime::playLoop(int startIndex, int endIndex)
{
	playOnce(startIndex, endIndex, false);
	m_loop = true;
}

void SpriteAnime::stop()
{
	m_stop = true;
}

void SpriteAnime::restart()
{
	m_stop = false;
}

void SpriteAnime::update()
{
	if (m_end) return;

	if(m_stop) return;

	if (m_wait == m_waitCount)
	{
		if (m_nowIndex == m_endIndex)
		{
			if (m_loop)
			{
				m_sprites.at(m_nowIndex)->setActive(false);
				m_nowIndex = m_startIndex;
				m_sprites.at(m_nowIndex)->setActive(true);
			}
			else
			{
				m_end = true;
				if (m_unenableWhenFinish)
				{
					m_sprites.at(m_nowIndex)->setActive(false);
				}
			}
		}
		else
		{
			m_sprites.at(m_nowIndex)->setActive(false);
			++m_nowIndex;
			m_sprites.at(m_nowIndex)->setActive(true);
		}

		m_waitCount = 0;
	}

	++m_waitCount;
}