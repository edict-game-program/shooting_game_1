#pragma once
#ifndef __CORE2D_GRAPHICSRESOURCEMANAGER_HEADER__
#define __CORE2D_GRAPHICSRESOURCEMANAGER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_GRAPHICSRESOURCEMANAER_CLASS __declspec(dllexport)
#else
#define CORE2D_GRAPHICSRESOURCEMANAER_CLASS __declspec(dllimport)
#endif

#include "GraphicsResourceDef.h"

namespace core2d
{

	class VertexShader;
	class PixelShader;
	class Texture;
	//class BlendState;
	class SamplerState;
	class ImageData;

	// ���\�[�X�Ǘ��N���X
	class CORE2D_GRAPHICSRESOURCEMANAER_CLASS GraphicsResourceManager
	{
	public:
		GraphicsResourceManager(void);
		~GraphicsResourceManager(void);

		// �쐬
		size_t createVertexShader(VertexShaderID shaderId);
		size_t createPixelShader(PixelShaderID shaderId);
		size_t createTexture(int imageId);
		size_t createSamplerState(SamplerID samplerId);

		// �擾
		VertexShader* getVertexShader(size_t id);
		PixelShader* getPixelShader(size_t id);
		Texture* getTexture(size_t id);
		SamplerState* getSamplerState(size_t id);

		// �ԋp
		void releaseVertexShader(size_t id);
		void releasePixelShader(size_t id);
		void releaseTexture(size_t id);
		void releaseSamplerState(size_t id);

	private:
		//�R�s�[�֎~
		GraphicsResourceManager(const GraphicsResourceManager&) = delete;
		GraphicsResourceManager& operator=(const GraphicsResourceManager&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};
}


#endif