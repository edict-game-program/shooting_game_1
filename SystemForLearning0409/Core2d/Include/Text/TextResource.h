#pragma once

#ifdef CORE2D_EXPORTS
#define CORE2D_TEXT_RESOURCE_CLASS __declspec(dllexport)
#else
#define CORE2D_TEXT_RESOURCE_CLASS __declspec(dllimport)
#endif

#ifndef __TEXT_RESOURCE_H__
#define __TEXT_RESOURCE_H__

#include <Windows.h>
#include <d3d11_3.h>
#include <wrl/client.h>

namespace core2d
{
	class VertexShader;
	class PixelShader;

	//フォント情報
	struct CORE2D_TEXT_RESOURCE_CLASS FontInfo
	{
		int size;			//ベースとなったフォントサイズ
		TEXTMETRIC tm;		//物理フォントに関する基本情報
		GLYPHMETRICS gm;	//文字セル内のグリフの配置や向きに関する情報
		D3D11_TEXTURE2D_DESC		textureDesc;	//テクスチャ設定
		ID3D11Texture2D* texture;	//テクスチャ
	};

	//テキスト表示に必要なリソース
	class CORE2D_TEXT_RESOURCE_CLASS TextResource
	{
	public:
		static bool initialize(HWND hwnd);
		static void finalize(void);

		static TextResource* instance();

		//シェーダーリソース
		VertexShader* getVertexShader();
		PixelShader* getPixelShader();

		//フォント情報(テクスチャもここに入っている)
		const FontInfo* getFontInfo(UINT code);

	private:
		explicit TextResource(HWND hwnd);
		virtual ~TextResource();

		//コピーの禁止
		TextResource(const TextResource&) = delete;
		TextResource& operator=(const TextResource&) = delete;

	private:
		class Impl;
		Impl* m_Impl;
	};
}

#endif