#pragma once
#ifndef __CORE2D_WINDOW_HEADER__
#define __CORE2D_WINDOW_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_WINDOW_CLASS __declspec(dllexport)
#else
#define CORE2D_WINDOW_CLASS __declspec(dllimport)
#endif

#include <Windows.h>

namespace core2d
{

	// Windowについてデータを持つためのクラス
	class CORE2D_WINDOW_CLASS Window
	{
	public:
		Window();

		// HWNDクライアント領域のwidth, heightを保存
		void cacheWindow(HWND hwnd);
		int getWidth() const;
		int getHeight() const;

	protected:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};

} // core2d

#endif // __CORE2D_WINDOW_HEADER__