#pragma once
#ifndef __CORE2D_GRAPHICSRESOURCEDEF_HEADER__
#define __CORE2D_GRAPHICSRESOURCEDEF_HEADER__

namespace core2d
{
	// バーテックスシェーダー識別子
	enum class VertexShaderID : int
	{
		ModelViewProjection,

		None = -1
	};

	// ピクセルシェーダー識別子
	enum class PixelShaderID : int
	{
		MaterialColor,
		UVAnimation,

		None = -1
	};

	// サンプラーステート識別子
	enum class SamplerID : int
	{
		Repeat,
		Clamp,

		None = -1,
	};
}

#endif