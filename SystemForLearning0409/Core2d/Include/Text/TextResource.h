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

	//�t�H���g���
	struct CORE2D_TEXT_RESOURCE_CLASS FontInfo
	{
		int size;			//�x�[�X�ƂȂ����t�H���g�T�C�Y
		TEXTMETRIC tm;		//�����t�H���g�Ɋւ����{���
		GLYPHMETRICS gm;	//�����Z�����̃O���t�̔z�u������Ɋւ�����
		D3D11_TEXTURE2D_DESC		textureDesc;	//�e�N�X�`���ݒ�
		ID3D11Texture2D* texture;	//�e�N�X�`��
	};

	//�e�L�X�g�\���ɕK�v�ȃ��\�[�X
	class CORE2D_TEXT_RESOURCE_CLASS TextResource
	{
	public:
		static bool initialize(HWND hwnd);
		static void finalize(void);

		static TextResource* instance();

		//�V�F�[�_�[���\�[�X
		VertexShader* getVertexShader();
		PixelShader* getPixelShader();

		//�t�H���g���(�e�N�X�`���������ɓ����Ă���)
		const FontInfo* getFontInfo(UINT code);

	private:
		explicit TextResource(HWND hwnd);
		virtual ~TextResource();

		//�R�s�[�̋֎~
		TextResource(const TextResource&) = delete;
		TextResource& operator=(const TextResource&) = delete;

	private:
		class Impl;
		Impl* m_Impl;
	};
}

#endif