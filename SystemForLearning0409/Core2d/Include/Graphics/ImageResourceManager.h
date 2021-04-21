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

	// �C���[�W�t�@�C���\����
	struct ImageInfo
	{
		int id;					// ���ʔԍ�
		const char* file;	// �t�@�C���p�X
	};
	struct ImageInfoWide
	{
		int id;					// ���ʔԍ�
		const wchar_t* file;	// �t�@�C���p�X
	};

	// �摜�C���[�W�f�[�^�̃��[�h�Ɣj�����s���V���O���g���N���X
	// �X�v���C�g�̐����O��load���Ă����K�v������܂�
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
		//�R�s�[�֎~
		ImageResourceManager(const ImageResourceManager&) = delete;
		ImageResourceManager& operator=(const ImageResourceManager&) = delete;

	public:
		// �w�莯�ʔԍ��ŉ摜�C���[�W��ǂݍ���
		// ���ʔԍ��ɂ�0�ȏ���w�肵�ĉ�����
		// �d���������ʎq�͖����ɂȂ�܂�
		bool loadImage(int id, const char* file);
		bool loadImage(ImageInfo info[], int infoCount);
		bool loadImage(int id, const wchar_t* file);
		bool loadImage(ImageInfoWide info[], int infoCount);

		// �摜�C���[�W��j��
		void unloadImage(int id);
		void unloadImage(int id[], int idCount);
		void unloadImage(ImageInfo info[], int infoCount);
		void unloadImage(ImageInfoWide info[], int infoCount);
		// �S�Ẳ摜�C���[�W��j��
		void unloadAllImage(void);

		// �摜�f�[�^���擾
		ImageData* getImage(int id);

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif