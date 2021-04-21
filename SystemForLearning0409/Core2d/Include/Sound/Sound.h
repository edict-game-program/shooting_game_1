#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_SOUND_CLASS __declspec(dllexport)
#else
#define CORE2D_SOUND_CLASS __declspec(dllimport)
#endif

#include <stdint.h>

/* ================================================================
* �T�E���h�Đ��N���X
*
* XAudio2��p���čĐ�����
*
* 
===================================================================*/

namespace core2d
{
	/*---------------------------------------------------
	* Sound�S��
	-----------------------------------------------------*/
	class CORE2D_SOUND_CLASS SoundManager
	{
	public:
		static SoundManager* instance();

		// ������
		static bool initialize();
		// �I��
		static void finalize(void);


		//Wave�t�@�C���̃��[�h
		bool loadWave(int id, const wchar_t* waveFileName); //ID�ɕR�t������wave�f�[�^�����[�h���܂��B
		bool loadWave(int id, const char* waveFileName); //ID�ɕR�t������wave�f�[�^�����[�h���܂��B
		void releaseWave(int id); //wave�f�[�^��j�����܂�

		//SE��炷
		void startSe(int id, float volume = 1, float frequencyRatio = 1);	//SE�Ƃ��ĉ����f�[�^���Đ����܂��B(������ł��B)

		//BGM��炷
		void startBgm(int id, float volume = 1, float frequencyRatio = 1); //BGM�Ƃ��ĉ����f�[�^���Đ����܂��B(���[�v���܂��B)
		void restartBgm(); //BGM���~�߂��ꏊ����Đ����ĊJ���܂��B
		void stopBgm();		//BGM���~�߂܂��B

		//���Ȃ��Ă���SE��BGM�����ׂď���
		void stopAllSounds();

		//�X�V(���t���[���Ăяo��)
		void update();

	private:
		SoundManager();
		~SoundManager();

		bool init();
		void uninit();

	private:
		SoundManager(const SoundManager&) = delete;
		SoundManager& operator=(const SoundManager&) = delete;

	private:
		class Impl;
		Impl* m_Impl;

	};



}

#endif //__SOUND_H__