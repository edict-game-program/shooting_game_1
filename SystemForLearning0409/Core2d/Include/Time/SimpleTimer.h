#pragma once
#ifndef __CORE2D_SIMPLETIMER_HEADER__
#define __CORE2D_SIMPLETIMER_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_SIMPLETIMER_CLASS __declspec(dllexport)
#else
#define CORE2D_SIMPLETIMER_CLASS __declspec(dllimport)
#endif

namespace core2d
{
	// 簡易タイマークラス
	class CORE2D_SIMPLETIMER_CLASS SimpleTimer
	{
	public:
		SimpleTimer(unsigned int interval);
		~SimpleTimer(void);

		// 繰り返しが発生した場合にtrueを返します
		bool updateRepeat();

		// 繰り返しにかかった時間を返します
		float getDeltaTime();

	private:
		//コピー禁止
		SimpleTimer(const SimpleTimer&) = delete;
		SimpleTimer& operator=(const SimpleTimer&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};
}

#endif // __CORE2D_SIMPLETIMER_HEADER__