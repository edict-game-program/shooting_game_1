#pragma once


#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_GAMEPAD_CLASS __declspec(dllexport)
#else
#define CORE2D_GAMEPAD_CLASS __declspec(dllimport)
#endif


#include <Windows.h>
#include <Xinput.h>
#include <map>

/* ================================================================
* ゲームパッドクラス
* 
* XInputを利用したゲームパッドの情報を取得できる
* XInput対応デバイスでのみ動作
* 
* 
===================================================================*/
namespace core2d {

	/*
#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

	*/

	class CORE2D_GAMEPAD_CLASS GamePad
	{
	public:
		enum class Port : int
		{
			Port0 = 0,
			Port1,
			Port2,
			Port3,

			Port_Max,

			Port_Default = Port0,
		};

	public:

		// 初期化
		static bool initialize();
		// 終了
		static void finalize(void);

		//インスタンスの取得
		static GamePad* instance();

		//各ボタンの状態取得
		bool isButtonDown(unsigned short btn, Port port = Port::Port_Default); //ボタンが押されている場合にtrue
		bool isButtonUp(unsigned short btn, Port port = Port::Port_Default);	//ボタンが押されている状態から放されるとtrue
		bool isButtonRepeat(unsigned short btn, Port port = Port::Port_Default);	//ボタンが押されている間、一定間隔でtrue

		//トリガーの状況(0～255)
		BYTE getLeftTrigger(Port port = Port::Port_Default);
		BYTE getRightTrigger(Port port = Port::Port_Default);

		//スティックの状況(-32768 ～ 32767)
		short getLeftThumbX(Port port = Port::Port_Default);
		short getLeftThumbY(Port port = Port::Port_Default);

		short getRightThumbX(Port port = Port::Port_Default);
		short getRightThumbY(Port port = Port::Port_Default);

		//接続状況確認
		bool isConnected(Port port = Port::Port_Default);

		//GamePadクラスの有効確認
		void active(bool flag);
		bool isActive();

		//リピート検知間隔の設定
		void setRepeatInterval(int repeatInterval);

		//更新
		void update();

	private:
		GamePad();
		~GamePad();

		bool init();
		void uninit();

		bool isValidPortNumber(Port port);

	private:
		GamePad(const GamePad&) = delete;
		GamePad& operator=(const GamePad&) = delete;

	private:
		class Impl;
		Impl* m_Impl;



	};
}

#endif //__GAMEPAD_H__