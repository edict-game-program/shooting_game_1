#pragma once
#ifndef __CORE2D_GRAPHICSSYSTEM_HEADER__
#define __CORE2D_GRAPHICSSYSTEM_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GRAPHICSSYSTEM_CLASS	__declspec(dllexport)
#else
#define CORE2D_GRAPHICSSYSTEM_CLASS	__declspec(dllimport)
#endif

namespace core2d
{

	class DrawObject;

	// �`��V�X�e���̃V���O���g���N���X
	class CORE2D_GRAPHICSSYSTEM_CLASS GraphicsSystem
	{
	public:
		// �C���X�^���X��Ԃ��܂�
		static GraphicsSystem* getInst();
		// ����������
		static bool initialize();
		// �I������
		static void finalize();
		// �V�X�e���̗L�����m�F
		static bool isValid();

	private:
		GraphicsSystem();
		~GraphicsSystem();

		// �V�X�e���̏���������
		bool initializeImpl();
		// �V�X�e���̏I������
		void finalizeImpl();

	private:
		//�R�s�[�֎~
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;

	public:
		// �`�敨���V�X�e���ɓo�^���܂�
		void registerDrawObject(DrawObject* object);

		// �`�揈���𔭍s���܂�
		bool render();

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif // __CORE2D_GRAPHICSSYSTEM_HEADER__