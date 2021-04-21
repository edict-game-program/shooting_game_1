#pragma once
#ifndef __CORE2D_GRAPHICSRESOURCEDEF_HEADER__
#define __CORE2D_GRAPHICSRESOURCEDEF_HEADER__

namespace core2d
{
	// �o�[�e�b�N�X�V�F�[�_�[���ʎq
	enum class VertexShaderID : int
	{
		ModelViewProjection,

		None = -1
	};

	// �s�N�Z���V�F�[�_�[���ʎq
	enum class PixelShaderID : int
	{
		MaterialColor,
		UVAnimation,

		None = -1
	};

	// �T���v���[�X�e�[�g���ʎq
	enum class SamplerID : int
	{
		Repeat,
		Clamp,

		None = -1,
	};
}

#endif