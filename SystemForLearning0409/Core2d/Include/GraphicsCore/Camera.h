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

		// カメラの座標を設定
		void setPosition(float x, float y, float z);
		// カメラの見ている座標を設定
		void setLookAt(float x, float y, float z);
		// ワールド空間の上方向を設定
		void setUp(float x, float y, float z);

		// カメラが捉える空間を設定
		void setViewVolume(float width, float height, float clipNear, float clipFar);

		// 転置済みカメラ座標変換行列を取得
		inline DirectX::XMFLOAT4X4 getViewMatrix() const;
		// 転置済み射影変換行列を取得
		inline DirectX::XMFLOAT4X4 getProjectionMatrix() const;

		// 変換行列を更新します
		void updateMatrix();

		// カメラ座標変換行列を作成します
		static DirectX::XMFLOAT4X4 createViewMatrix(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 lookAt, DirectX::XMFLOAT3 up);
		// 左手座標系の平行投影変換行列を作成します
		static DirectX::XMFLOAT4X4 createOrthoMatrixLH(float width, float height, float clipNear, float clipFar);
		// 右手座標系の平行投影変換行列を作成します
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