#pragma once
#ifndef __CORE2D_CAMERA_HEADER__
#define __CORE2D_CAMERA_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_CAMERA_CLASS __declspec(dllexport)
#else
#define CORE2D_CAMERA_CLASS __declspec(dllimport)
#endif

#include <DirectXMath.h>

namespace core2d
{

	class CORE2D_CAMERA_CLASS Camera
	{
	public:
		Camera();
		~Camera();

		// �J�����̍��W��ݒ�
		void setPosition(float x, float y, float z);
		// �J�����̌��Ă�����W��ݒ�
		void setLookAt(float x, float y, float z);
		// ���[���h��Ԃ̏������ݒ�
		void setUp(float x, float y, float z);

		// �J�������������Ԃ�ݒ�
		void setViewVolume(float width, float height, float clipNear, float clipFar);

		// �]�u�ς݃J�������W�ϊ��s����擾
		inline DirectX::XMFLOAT4X4 getViewMatrix() const;
		// �]�u�ςݎˉe�ϊ��s����擾
		inline DirectX::XMFLOAT4X4 getProjectionMatrix() const;

		// �ϊ��s����X�V���܂�
		void updateMatrix();

		// �J�������W�ϊ��s����쐬���܂�
		static DirectX::XMFLOAT4X4 createViewMatrix(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 lookAt, DirectX::XMFLOAT3 up);
		// ������W�n�̕��s���e�ϊ��s����쐬���܂�
		static DirectX::XMFLOAT4X4 createOrthoMatrixLH(float width, float height, float clipNear, float clipFar);
		// �E����W�n�̕��s���e�ϊ��s����쐬���܂�
		static DirectX::XMFLOAT4X4 createOrthoMatrixRH(float width, float height, float clipNear, float clipFar);

	protected:
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_CAMERA_HEADER__