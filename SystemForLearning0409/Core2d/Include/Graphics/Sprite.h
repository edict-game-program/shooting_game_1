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

	// WVPマトリックス情報
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// スクロールと色情報
	struct UVAnimConstantBuffer
	{
		DirectX::XMFLOAT4X4 transform;		// uv変形行列
		DirectX::XMFLOAT4 materialColor;	// マテリアルカラー
	};

	// 頂点シェーダーへの頂点ごとのデータの送信に使用します。
	struct VertexPT
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 coord;
	};

	// スプライトクラス
	// スケールに負の値を設定すると反転表示
	class CORE2D_SPRITE_CLASS Sprite : public DrawObject
	{
	public:
		static const unsigned int cDefaultSpriteSize = 64;

	public:
		// スプライトを破棄
		static void destroy(Sprite* p);

		// 画像無しスプライトを作成
		Sprite(void);

		// 画像無しで指定サイズのスプライトを作成
		Sprite(unsigned int width, unsigned int height);

		// 画像指定で画像サイズのスプライトを作成
		Sprite(int imageId);

		// 画像指定で指定サイズのスプライトを作成
		Sprite(int imageId, unsigned int width, unsigned int height);

	private:
		virtual ~Sprite(void);

		// コピー禁止
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		// 描画の記述をオーバーライド
		bool render(Camera* camera)  final;

	public:
		// スプライトの基本サイズを取得
		float getWidth(void);
		float getHeight(void);

		// 座標の設定・取得
		void setPosition(float x, float y);
		void setPositionX(float x);
		void setPositionY(float y);

		void getPosition(float* x, float* y);
		float getPositionX(void);
		float getPositionY(void);
		
		// スケールの設定・取得
		void setScale(float x, float y);
		void setScaleX(float x);
		void setScaleY(float y);

		void getScale(float* x, float* y);
		float getScaleX(void);
		float getScaleY(void);

		// 角度の設定・取得
		void setRotate(float degree);
		float getRotate(void);

		// スプライトの色を設定
		void setMaterialColor(float r, float g, float b, float a = 1.0f);

		// スクロールアニメーションを設定し初期化
		void setScrollAnim(float shiftU, float shiftV, float speedU, float speedV);

		// スクロールスピードを変更
		void changeScrollSpeed(float speedU, float speedV);

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_SPRITE_HEADER__