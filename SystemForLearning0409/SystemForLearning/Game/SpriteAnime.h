#pragma once

#ifndef __SPRITE_ANIME_H__
#define __SPRITE_ANIME_H__

#include <vector>

/*============================================
* �X�v���C�g�A�j���[�V����(�؂�ւ��@�\)
=============================================*/
namespace core2d
{
	class Sprite;
}

class SpriteAnime
{
public:
	SpriteAnime();
	virtual ~SpriteAnime();

	//�X�v���C�g�̓o�^�B�o�^����Index���Ԃ��Ă���
	int addSprite(core2d::Sprite* sprite); 

	//�P�̉摜���ǂꂮ�炢�\�������邩�ݒ肷��
	void setWait(int wait) { m_wait = wait; }

	//�ŏ�����Ō�܂łP�x�����Đ�����BunenableWhenFinish��true�̏ꍇ�͍Đ��I����ɔ�\���ɂ���
	void playOnce(bool unenableWhenFinish = false);

	//start����end�܂łP�x�����Đ�����BunenableWhenFinish��true�̏ꍇ�͍Đ��I����ɔ�\���ɂ���
	void playOnce(int startIndex, int endIndex = -1, bool unenableWhenFinish = false);

	//���ׂẲ摜�����[�v�Đ�����
	void playLoop();
	void playLoop(int startIndex, int endIndex = -1);	//start����end�܂ł����[�v�Đ�����

	bool isEnd() { return m_end; } //�Đ��������������H(Loop�̏ꍇ�͏��false)

	void stop();	//�A�j���[�V�������~�߂�
	void restart();	//�~�߂��Ƃ��납��ĊJ����

	void update();	//�X�V�B������񂳂Ȃ��ƃX�v���C�g���؂�ւ��Ȃ�

public:

private:

	int m_startIndex;	//�Đ��J�nIndex
	int m_endIndex;		//�Đ��I��Index
	int m_nowIndex;		//���ݍĐ�����Index

	bool m_loop;		//���[�v�Đ��̏ꍇ��true
	bool m_end;			//�Đ��I������true
	bool m_unenableWhenFinish;	//�Đ��I�����ɔ�\���ɂ���ꍇ��true

	bool m_stop;

	int m_wait;

	int m_waitCount;

	std::vector<core2d::Sprite*> m_sprites;
};

#endif