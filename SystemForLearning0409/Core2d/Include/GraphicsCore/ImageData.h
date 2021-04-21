#pragma once
#ifndef __CORE2D_IMAGEDATA_HEADER__
#define __CORE2D_IMAGEDATA_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_IMAGEDATA_CLASS __declspec(dllexport)
#else
#define CORE2D_IMAGEDATA_CLASS __declspec(dllimport)
#endif

namespace core2d
{

	// 画像を読み込み、イメージデータを保持します
	class CORE2D_IMAGEDATA_CLASS ImageData
	{
	public:
		ImageData();
		~ImageData();

		bool load(const char* path);
		bool load(const wchar_t* path);

		unsigned int width() const;		// 幅(pixel)
		unsigned int height() const;	// 高さ(pixel)
		unsigned int stride() const;	// １行バイトサイズ
		unsigned char* data() const;
		unsigned int size() const;

	private:
		// コピー禁止
		ImageData(const ImageData&) = delete;
		ImageData& operator=(const ImageData&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_IMAGELOADER_HEADER__