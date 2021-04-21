#pragma once
#ifndef __CORE2D_DRAWOBJECT_HEADER__
#define __CORE2D_DRAWOBJECT_HEADER__

#ifdef CORE2D_EXPORTS
#define CORE2D_DRAWOBJECT_CLASS	__declspec(dllexport)
#else
#define CORE2D_DRAWOBJECT_CLASS	__declspec(dllimport)
#endif

namespace core2d
{
	// ‘O•ûéŒ¾
	class Camera;

	// •`‰æ•¨‚ÌŠî’êƒNƒ‰ƒX
	class CORE2D_DRAWOBJECT_CLASS DrawObject
	{
	protected:
		DrawObject();
		virtual ~DrawObject();

		// Œp³æ‚Å•`‰æˆ—‚Ì’†g‚ğ‹Lq
		virtual bool render(Camera* camera) = 0;

	public:
		// ¶¬”Ô†‚ğæ“¾
		unsigned long long getGenNo(void);
		// •`‰æ—Dæ“x‚ğİ’è
		void setPriority(unsigned int priority);
		// •`‰æ—Dæ“x‚ğæ“¾
		unsigned int getPriority(void);
		// •`‰æÀsƒtƒ‰ƒO‚ğİ’è
		void setActive(bool flag = true);
		// •`‰æÀs‚Ìó‘Ô‚ğæ“¾
		bool isActive(void);
		// ”jŠü‚ğ—\–ñ
		void reserveDestroy(void);
		// ”jŠü‚ª—\–ñ‚³‚ê‚Ä‚¢‚é‚©‚ğæ“¾
		bool isReservedDestroy(void);

	protected:
		// ”äŠrŠÖ”
		static bool compare(DrawObject* lhs, DrawObject* rhs);

		// ZÀ•W‚ğæ“¾
		float getZ(void);

		// ƒRƒs[‹Ö~
		DrawObject(const DrawObject&) = delete;
		DrawObject& operator=(const DrawObject&) = delete;

	private:
		class Impl;
		Impl* m_impl;

		friend class GraphicsSystem;
	};

}

#endif // __CORE2D_DRAWOBJECT_HEADER__