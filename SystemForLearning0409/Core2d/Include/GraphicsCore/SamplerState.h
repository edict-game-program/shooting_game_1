#pragma once
#ifndef __CORE2D_SAMPLERSTATE_HEADER__
#define __CORE2D_SAMPLERSTATE_HEADER__

struct ID3D11SamplerState;

namespace core2d
{

	enum class AddressMode
	{
		Wrap,
		Clmap,
		Mirror,
		Border,
	};

	// SamplerStateラッパークラス
	class SamplerState
	{
	public:
		SamplerState(void);
		~SamplerState(void);

		bool create(AddressMode mode);

		ID3D11SamplerState** getSamplerState(void);

	private:
		//コピー禁止
		SamplerState(const SamplerState&) = delete;
		SamplerState& operator=(const SamplerState&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

}

#endif