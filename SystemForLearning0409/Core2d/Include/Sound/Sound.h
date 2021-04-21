#pragma once

#ifndef __SOUND_H__
#define __SOUND_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_SOUND_CLASS __declspec(dllexport)
#else
#define CORE2D_SOUND_CLASS __declspec(dllimport)
#endif

#include <stdint.h>

/* ================================================================
* サウンド再生クラス
*
* XAudio2を用いて再生する
*
* 
===================================================================*/

namespace core2d
{
	/*---------------------------------------------------
	* Sound全般
	-----------------------------------------------------*/
	class CORE2D_SOUND_CLASS SoundManager
	{
	public:
		static SoundManager* instance();

		// 初期化
		static bool initialize();
		// 終了
		static void finalize(void);


		//Waveファイルのロード
		bool loadWave(int id, const wchar_t* waveFileName); //IDに紐付けしてwaveデータをロードします。
		bool loadWave(int id, const char* waveFileName); //IDに紐付けしてwaveデータをロードします。
		void releaseWave(int id); //waveデータを破棄します

		//SEを鳴らす
		void startSe(int id, float volume = 1, float frequencyRatio = 1);	//SEとして音声データを再生します。(一回限りです。)

		//BGMを鳴らす
		void startBgm(int id, float volume = 1, float frequencyRatio = 1); //BGMとして音声データを再生します。(ループします。)
		void restartBgm(); //BGMを止めた場所から再生を再開します。
		void stopBgm();		//BGMを止めます。

		//今なっているSEやBGMをすべて消す
		void stopAllSounds();

		//更新(毎フレーム呼び出す)
		void update();

	private:
		SoundManager();
		~SoundManager();

		bool init();
		void uninit();

	private:
		SoundManager(const SoundManager&) = delete;
		SoundManager& operator=(const SoundManager&) = delete;

	private:
		class Impl;
		Impl* m_Impl;

	};



}

#endif //__SOUND_H__