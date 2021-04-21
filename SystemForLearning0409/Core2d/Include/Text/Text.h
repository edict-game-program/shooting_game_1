#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_TEXT_CLASS __declspec(dllexport)
#else
#define CORE2D_TEXT_CLASS __declspec(dllimport)
#endif

#include "DrawObject.h"


namespace core2d {

	/*
	* テキスト表示クラス
	*/
	class CORE2D_TEXT_CLASS Text : public DrawObject{
	public:

		static const int cDefaultFontSize = 32; //標準文字サイズ

		//原点の位置
		enum class OriginPosition
		{
			Center,	//中央
			Left,	//左端
			Right,	//右端

			Default = Center, //初期設定は中央原点
		};

		Text();
		explicit Text(const wchar_t* text);
		explicit Text(const char* text);

		static void destroy(Text* text);

		//文字サイズの設定
		void setFontSize(int fontSize);

		//テキストの設定
		void setText(const wchar_t* text);
		void setText(const char* text);

		//表示位置の設定
		void setPosition(float x, float y);

		//表示色の設定
		void setColor(float r, float g, float b, float a = 1.0f);

		//原点位置の設定
		void setOriginPosition(OriginPosition originPosition);

	public:
		bool render(Camera* scamera) override;

	private:
		virtual ~Text();

		//コピーの禁止
		Text(const Text&) = delete;
		Text& operator=(const Text&) = delete;

	protected:
		class Impl;
		Impl* m_Impl;

	};
}

#endif //__TEXT_H__