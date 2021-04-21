#pragma once
#ifndef __CORE2D_SPRITE_HEADER__
#define __CORE2D_SPRITE_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_SPRITE_CLASS __declspec(dllexport)
#else
#define CORE2D_SPRITE_CLASS __declspec(dllimport)
#endif

#include <DirectXMath.h>

#include "DrawObject.h"

#include "GraphicsResourceDef.h"

namespace core2d
{

	// WVP�}�g���b�N�X���
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// �X�N���[���ƐF���
	struct UVAnimConstantBuffer
	{
		DirectX::XMFLOAT4X4 transform;		// uv�ό`�s��
		DirectX::XMFLOAT4 materialColor;	// �}�e���A���J���[
	};

	// ���_�V�F�[�_�[�ւ̒��_���Ƃ̃f�[�^�̑��M�Ɏg�p���܂��B
	struct VertexPT
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 coord;
	};

	// �X�v���C�g�N���X
	// �X�P�[���ɕ��̒l��ݒ肷��Ɣ��]�\��
	class CORE2D_SPRITE_CLASS Sprite : public DrawObject
	{
	public:
		static const unsigned int cDefaultSpriteSize = 64;

	public:
		// �X�v���C�g��j��
		static void destroy(Sprite* p);

		// �摜�����X�v���C�g���쐬
		Sprite(void);

		// �摜�����Ŏw��T�C�Y�̃X�v���C�g���쐬
		Sprite(unsigned int width, unsigned int height);

		// �摜�w��ŉ摜�T�C�Y�̃X�v���C�g���쐬
		Sprite(int imageId);

		// �摜�w��Ŏw��T�C�Y�̃X�v���C�g���쐬
		Sprite(int imageId, unsigned int width, unsigned int height);

	private:
		virtual ~Sprite(void);

		// �R�s�[�֎~
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		// �`��̋L�q���I�[�o�[���C�h
		bool render(Camera* camera)  final;

	public:
		// �X�v���C�g�̊�{�T�C�Y���擾
		float getWidth(void);
		float getHeight(void);

		// ���W�̐ݒ�E�擾
		void setPosition(float x, float y);
		void setPositionX(float x);
		void setPositionY(float y);

		void getPosition(float* x, float* y);
		float getPositionX(void);
		float getPositionY(void);
		
		// �X�P�[���̐ݒ�E�擾
		void setScale(float x, float y);
		void setScaleX(float x);
		void setScaleY(float y);

		void getScale(float* x, float* y);
		float getScaleX(void);
		float getScaleY(void);

		// �p�x�̐ݒ�E�擾
		void setRotate(float degree);
		float getRotate(void);

		// �X�v���C�g�̐F��ݒ�
		void setMaterialColor(float r, float g, float b, float a = 1.0f);

		// �X�N���[���A�j���[�V������ݒ肵������
		void setScrollAnim(float shiftU, float shiftV, float speedU, float speedV);

		// �X�N���[���X�s�[�h��ύX
		void changeScrollSpeed(float speedU, float speedV);

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_SPRITE_HEADER__