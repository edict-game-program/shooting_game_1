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
* �Q�[���p�b�h�N���X
* 
* XInput�𗘗p�����Q�[���p�b�h�̏����擾�ł���
* XInput�Ή��f�o�C�X�ł̂ݓ���
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

		// ������
		static bool initialize();
		// �I��
		static void finalize(void);

		//�C���X�^���X�̎擾
		static GamePad* instance();

		//�e�{�^���̏�Ԏ擾
		bool isButtonDown(unsigned short btn, Port port = Port::Port_Default); //�{�^����������Ă���ꍇ��true
		bool isButtonUp(unsigned short btn, Port port = Port::Port_Default);	//�{�^����������Ă����Ԃ����������true
		bool isButtonRepeat(unsigned short btn, Port port = Port::Port_Default);	//�{�^����������Ă���ԁA���Ԋu��true

		//�g���K�[�̏�(0�`255)
		BYTE getLeftTrigger(Port port = Port::Port_Default);
		BYTE getRightTrigger(Port port = Port::Port_Default);

		//�X�e�B�b�N�̏�(-32768 �` 32767)
		short getLeftThumbX(Port port = Port::Port_Default);
		short getLeftThumbY(Port port = Port::Port_Default);

		short getRightThumbX(Port port = Port::Port_Default);
		short getRightThumbY(Port port = Port::Port_Default);

		//�ڑ��󋵊m�F
		bool isConnected(Port port = Port::Port_Default);

		//GamePad�N���X�̗L���m�F
		void active(bool flag);
		bool isActive();

		//���s�[�g���m�Ԋu�̐ݒ�
		void setRepeatInterval(int repeatInterval);

		//�X�V
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