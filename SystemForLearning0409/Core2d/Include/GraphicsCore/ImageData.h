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

	// �摜��ǂݍ��݁A�C���[�W�f�[�^��ێ����܂�
	class CORE2D_IMAGEDATA_CLASS ImageData
	{
	public:
		ImageData();
		~ImageData();

		bool load(const char* path);
		bool load(const wchar_t* path);

		unsigned int width() const;		// ��(pixel)
		unsigned int height() const;	// ����(pixel)
		unsigned int stride() const;	// �P�s�o�C�g�T�C�Y
		unsigned char* data() const;
		unsigned int size() const;

	private:
		// �R�s�[�֎~
		ImageData(const ImageData&) = delete;
		ImageData& operator=(const ImageData&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_IMAGELOADER_HEADER__