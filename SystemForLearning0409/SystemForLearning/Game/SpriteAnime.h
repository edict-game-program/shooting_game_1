#pragma once

#ifndef __SPRITE_ANIME_H__
#define __SPRITE_ANIME_H__

#include <vector>

/*============================================
* スプライトアニメーション(切り替え機能)
=============================================*/
namespace core2d
{
	class Sprite;
}

class SpriteAnime
{
public:
	SpriteAnime();
	virtual ~SpriteAnime();

	//スプライトの登録。登録時のIndexが返ってくる
	int addSprite(core2d::Sprite* sprite); 

	//１つの画像をどれぐらい表示させるか設定する
	void setWait(int wait) { m_wait = wait; }

	//最初から最後まで１度だけ再生する。unenableWhenFinishがtrueの場合は再生終了後に非表示にする
	void playOnce(bool unenableWhenFinish = false);

	//startからendまで１度だけ再生する。unenableWhenFinishがtrueの場合は再生終了後に非表示にする
	void playOnce(int startIndex, int endIndex = -1, bool unenableWhenFinish = false);

	//すべての画像をループ再生する
	void playLoop();
	void playLoop(int startIndex, int endIndex = -1);	//startからendまでをループ再生する

	bool isEnd() { return m_end; } //再生が完了したか？(Loopの場合は常にfalse)

	void stop();	//アニメーションを止める
	void restart();	//止めたところから再開する

	void update();	//更新。これを回さないとスプライトが切り替わらない

public:

private:

	int m_startIndex;	//再生開始Index
	int m_endIndex;		//再生終了Index
	int m_nowIndex;		//現在再生中のIndex

	bool m_loop;		//ループ再生の場合はtrue
	bool m_end;			//再生終了時はtrue
	bool m_unenableWhenFinish;	//再生終了時に非表示にする場合はtrue

	bool m_stop;

	int m_wait;

	int m_waitCount;

	std::vector<core2d::Sprite*> m_sprites;
};

#endif