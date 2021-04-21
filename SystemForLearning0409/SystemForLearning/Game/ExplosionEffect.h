#pragma once

#ifndef __EXPLOSION_EFFECT_H__
#define __EXPLOSION_EFFECT_H__

#include <vector>
#include "GameObject.h"

namespace core2d
{
	class Sprite;
}

class SpriteAnime;

/*===================================================
* 爆破エフェクト表示クラス
====================================================*/
class ExplosionEffect : public GameObject
{
public:
	explicit ExplosionEffect(ShootingGame* manager);

	virtual ~ExplosionEffect();

	void update() override;

	void playOnce();		//一度だけ再生
	void playOnceDestroy();	//一度だけ再生した後、削除。
	void playLoop();		//ループ再生

protected:
	void onFirstUpdate() override;

	void setSpritesPosition(float x, float y);
	void setSpritesScale(float x, float y);
	void setSpritesRotate(float degree);
	void setSpritesActive(bool active);
	void setSpritesColor(float r, float g, float b, float a = 1.0f);

protected:
	enum class PlayFlag 
	{
		None = 0,
		Once,
		OnceDestroy,
		Loop,
	};

	PlayFlag m_playFlag;

	enum class Status
	{
		None = 0,
		Dead,
	};

	Status m_status;

	bool m_onceDestroy;
	std::vector<core2d::Sprite*> m_sprites;
	SpriteAnime* m_spriteAnime;
};

#endif