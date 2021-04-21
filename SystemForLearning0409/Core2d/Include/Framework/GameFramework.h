#pragma once
#ifndef __GAMEFTAMEWORK_HEADER__
#define __GAMEFTAMEWORK_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GAMEFPAMEWORK_CLASS __declspec(dllexport)
#else
#define CORE2D_GAMEFPAMEWORK_CLASS __declspec(dllimport)
#endif

#include <Windows.h>

namespace core2d
{

	class CORE2D_GAMEFPAMEWORK_CLASS GameFramework
	{
	public:
		// �f�t�H���g�̃R���X�g���N�^���Ăяo���s��
		GameFramework(void) = delete;
		GameFramework(unsigned int fps);
	protected:
		virtual ~GameFramework(void);

	public:
		// �V�X�e���ƃQ�[���̏������Ăяo��
		bool initialize(HWND hwnd);
		// �V�X�e���ƃQ�[���̏I�������Ăяo��
		void finalize(void);
		// �V�X�e���ƃQ�[���̍X�V�����Ăяo��
		void step(void);

		// ��ʃT�C�Y���擾
		float getDisplayWidth(void);
		float getDisplayHeight(void);

	private:
		// ���[�U�[��`�̃Q�[������������
		virtual bool initializeGame(void) = 0;
		// ���[�U�[��`�̃Q�[���I������
		virtual void finalizeGame(void) = 0;
		// ���[�U�[��`�̃Q�[���X�V����
		virtual void updateGame(void) = 0;

	protected:
		GameFramework(const GameFramework&) = delete;
		GameFramework& operator=(const GameFramework&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif // __GAMEFTAMEWORK_HEADER__