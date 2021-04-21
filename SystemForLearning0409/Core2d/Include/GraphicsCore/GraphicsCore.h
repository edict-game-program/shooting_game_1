#pragma once
#ifndef __CORE2D_GRAPHICSCORE_HEADER__
#define __CORE2D_GRAPHICSCORE_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GRAPHICSCORE_CLASS __declspec(dllexport)
#else
#define CORE2D_GRAPHICSCORE_CLASS __declspec(dllimport)
#endif

struct ID3D11Device3;
struct ID3D11DeviceContext3;
struct IDXGISwapChain3;

namespace core2d
{

	// �O���錾
	class GraphicsResourceManager;

	// �V���O���g���N���X
	class CORE2D_GRAPHICSCORE_CLASS GraphicsCore
	{
	public:
		// �R�A�̏�����
		static bool initialize(HWND hwnd);
		// �R�A�̏I������
		static void finalize(void);
		// �C���X�^���X�̎擾
		static GraphicsCore* get(void);

	private:
		GraphicsCore(void);
		~GraphicsCore(void);

		// ���������������s���܂�
		bool initializeImpl(HWND hwnd);
		// �I�����������s���܂�
		void finalizeImpl();

	public:
		// �o�b�N�o�b�t�@���N���A���܂�
		void clear();
		// ��ʂ̃t���b�v���s���܂�
		void present();

	public:
		ID3D11Device3* getDevice();				// �f�o�C�X���擾
		ID3D11DeviceContext3* getContext();		// 3D�`��R���e�L�X�g���擾
		IDXGISwapChain3* getSwapChain();		// �X���b�v�`�F�C�����擾
		GraphicsResourceManager* getGraphicsResourceManager();	// ���\�[�X�Ǘ��N���X���擾

		unsigned int getWindowWidth();		// �E�C���h�E�̕����擾
		unsigned int getWindowHeight();		// �E�C���h�E�̍������擾

	private:
		//�R�s�[�֎~
		GraphicsCore(const GraphicsCore&) = delete;
		GraphicsCore& operator=(const GraphicsCore&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_GRAPHICSCORE_HEADER__