#pragma once
#ifndef __CORE2D_TEXTURE_HEADER__
#define __CORE2D_TEXTURE_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_TEXTURE_CLASS __declspec(dllexport)
#else
#define CORE2D_TEXTURE_CLASS __declspec(dllimport)
#endif

struct ID3D11ShaderResourceView;

namespace core2d
{
	class ImageData;

	// ImageData����D3D�e�N�X�`���𐶐��E�ێ�����N���X
	class CORE2D_TEXTURE_CLASS Texture
	{
	public:
		Texture(void);
		~Texture(void);

		bool create(ImageData* image);

		ID3D11ShaderResourceView* getShaderResourceView(void);
		ID3D11ShaderResourceView** getAddressOfShaderResourceView(void);
		unsigned int getWidth(void);
		unsigned int getHeight(void);

	private:
		//�R�s�[�֎~
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif