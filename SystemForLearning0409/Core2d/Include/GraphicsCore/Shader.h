#pragma once
#ifndef __CORE2D_SHADER_HEADER__
#define __CORE2D_SHADER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_SHADER_CLASS __declspec(dllexport)
#else
#define CORE2D_SHADER_CLASS __declspec(dllimport)
#endif

struct ID3D11VertexShader;
struct ID3D11InputLayout;
struct ID3D11PixelShader;

namespace core2d
{

	// 頂点シェーダクラス
	class CORE2D_SHADER_CLASS VertexShader
	{
	public:
		VertexShader(void);
		~VertexShader(void);

		// 頂点シェーダーを作成
		bool create(const void* data, size_t byteLength);

		// 取得
		ID3D11VertexShader* getShader(void);
		ID3D11InputLayout* getInpuLayout(void);

	protected:
		VertexShader(const VertexShader&) = delete;
		VertexShader& operator=(const VertexShader&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};
	
	// ピクセルシェーダクラス
	class CORE2D_SHADER_CLASS PixelShader
	{
	public:
		PixelShader();
		~PixelShader();

		// ピクセルシェーダーを生成
		bool create(const void* data, size_t byteLength);

		// 取得
		ID3D11PixelShader* getShader(void);

	protected:
		PixelShader(const PixelShader&) = delete;
		PixelShader& operator=(const PixelShader&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};
}

#endif