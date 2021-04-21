#pragma once
#ifndef __CORE2D_IMAGERESOURCEMANAGER_HEADER__
#define __CORE2D_IMAGERESOURCEMANAGER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_IMAGERESOURCEMANAGER_CLASS __declspec(dllexport)
#else
#define CORE2D_IMAGERESOURCEMANAGER_CLASS __declspec(dllimport)
#endif


namespace core2d
{
	class ImageData;

	// イメージファイル構造体
	struct ImageInfo
	{
		int id;					// 識別番号
		const char* file;	// ファイルパス
	};
	struct ImageInfoWide
	{
		int id;					// 識別番号
		const wchar_t* file;	// ファイルパス
	};

	// 画像イメージデータのロードと破棄を行うシングルトンクラス
	// スプライトの生成前にloadしておく必要があります
	class CORE2D_IMAGERESOURCEMANAGER_CLASS ImageResourceManager
	{
	public:
		static ImageResourceManager* instance();
		static bool initialzie(void);
		static void finalize(void);

	private:
		ImageResourceManager(void);
		~ImageResourceManager(void);

	private:
		//コピー禁止
		ImageResourceManager(const ImageResourceManager&) = delete;
		ImageResourceManager& operator=(const ImageResourceManager&) = delete;

	public:
		// 指定識別番号で画像イメージを読み込み
		// 識別番号には0以上を指定して下さい
		// 重複した識別子は無効になります
		bool loadImage(int id, const char* file);
		bool loadImage(ImageInfo info[], int infoCount);
		bool loadImage(int id, const wchar_t* file);
		bool loadImage(ImageInfoWide info[], int infoCount);

		// 画像イメージを破棄
		void unloadImage(int id);
		void unloadImage(int id[], int idCount);
		void unloadImage(ImageInfo info[], int infoCount);
		void unloadImage(ImageInfoWide info[], int infoCount);
		// 全ての画像イメージを破棄
		void unloadAllImage(void);

		// 画像データを取得
		ImageData* getImage(int id);

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif