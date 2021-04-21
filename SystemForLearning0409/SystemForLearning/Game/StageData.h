#pragma once
#ifndef __STAGEDATA_HEADER__
#define __STAGEDATA_HEADER__

// 一つのグループに含むことのできるオブジェクトの最大数
static const int cGroupObjectMax = 6;

// フレームの特徴
enum class FrameKey : int
{
	None = 0,
	End = 1
};

// GameObjectの種類
enum class GameObjectType : int
{
	Player,
	Enemy,
	SpecialEnemy,
};

// ステージ番号
enum class StageIndex : int
{
	Stage1,
	Boss,
};

// １つのオブジェクト情報構造体
struct ObjectInfo
{
	GameObjectType objectType;		// 生成オブジェクトの種類
	// 以下ザコ敵でのみ適用
	int behaviorType;				// ザコ敵の行動パターン
	int itemType;					// 強化アイテムの有無：0:無、1:主武器強化、2:補助１切り替えと強化、3:補助２切り替えと強化
};

// グループ情報構造体
struct GroupInfo
{
	struct Item
	{
		int id;
		float x, y;
	} object[cGroupObjectMax];		// オブジェクト番号、配置場所(x, y)
};

// フレーム情報構造体
struct FrameInfo
{
	int frameCount;					// 対応フレーム番号
	int groupId;					// 配置するグループ番号
	float x;						// 生成基準点 x
	float y;						// 生成基準点 y
	FrameKey key;					// 何もなければ0それ以外は任意の値
};

// ------------------------------------------------------------------------
// 取得関数
// ------------------------------------------------------------------------
// GameObjetデータを取得
ObjectInfo getObjectData(int index);

// グループデータへのポインタを取得
const GroupInfo* getGroupData(int index);

// マップデータ(フレーム情報配列)へのポインタを取得
const FrameInfo* getStageData(StageIndex index);

#endif // __GAMEMAP_HEADER__