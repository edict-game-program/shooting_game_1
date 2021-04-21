#pragma once
#ifndef __CORE2D_BUFFER_HEADER__
#define __CORE2D_BUFFER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_BUFFER_CLASS __declspec(dllexport)
#else
#define CORE2D_BUFFER_CLASS __declspec(dllimport)
#endif

namespace core2d
{
	class GraphicsCore;

	// �萔�o�b�t�@�N���X
	class CORE2D_BUFFER_CLASS ConstantBuffer
	{
	public:
		ConstantBuffer(void);
		~ConstantBuffer(void);

		bool initialize(unsigned int dataSize);

		// �o�b�t�@�̒��g���X�V���܂�
		void update(const void* data);

		// �V�F�[�_�[�փf�[�^�𑗐M
		void setToVertexShader(unsigned int slot = 0, unsigned int bufferCount = 1);
		void setToPixelShader(unsigned int slot = 0, unsigned int bufferCount = 1);

	private:
		//�R�s�[�֎~
		ConstantBuffer(const ConstantBuffer&) = delete;
		ConstantBuffer& operator=(const ConstantBuffer&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif