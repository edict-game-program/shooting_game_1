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
	// �ȈՃ^�C�}�[�N���X
	class CORE2D_SIMPLETIMER_CLASS SimpleTimer
	{
	public:
		SimpleTimer(unsigned int interval);
		~SimpleTimer(void);

		// �J��Ԃ������������ꍇ��true��Ԃ��܂�
		bool updateRepeat();

		// �J��Ԃ��ɂ����������Ԃ�Ԃ��܂�
		float getDeltaTime();

	private:
		//�R�s�[�֎~
		SimpleTimer(const SimpleTimer&) = delete;
		SimpleTimer& operator=(const SimpleTimer&) = delete;

	private:
		class Impl;
		Impl* m_impl;

	};
}

#endif // __CORE2D_SIMPLETIMER_HEADER__