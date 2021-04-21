#pragma once
#ifndef __CORE2D_BUFFER_HEADER__
#define __CORE2D_BUFFER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_BUFFER_CLASS __declspec(dllexport)
#else
#define CORE2D_BUFFER_CLASS __declspec(dllimport)
#endif

namespace core2d
{
	class GraphicsCore;

	// 定数バッファクラス
	class CORE2D_BUFFER_CLASS ConstantBuffer
	{
	public:
		ConstantBuffer(void);
		~ConstantBuffer(void);

		bool initialize(unsigned int dataSize);

		// バッファの中身を更新します
		void update(const void* data);

		// シェーダーへデータを送信
		void setToVertexShader(unsigned int slot = 0, unsigned int bufferCount = 1);
		void setToPixelShader(unsigned int slot = 0, unsigned int bufferCount = 1);

	private:
		//コピー禁止
		ConstantBuffer(const ConstantBuffer&) = delete;
		ConstantBuffer& operator=(const ConstantBuffer&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif