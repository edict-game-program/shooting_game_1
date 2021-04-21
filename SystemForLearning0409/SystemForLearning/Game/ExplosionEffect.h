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
* ���j�G�t�F�N�g�\���N���X
====================================================*/
class ExplosionEffect : public GameObject
{
public:
	explicit ExplosionEffect(ShootingGame* manager);

	virtual ~ExplosionEffect();

	void update() override;

	void playOnce();		//��x�����Đ�
	void playOnceDestroy();	//��x�����Đ�������A�폜�B
	void playLoop();		//���[�v�Đ�

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