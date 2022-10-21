/*********************************************************
* @brief		ソートのルールのヘッダー
* @date			2022/10/17
********************************************************/
#pragma once
#include "ScoreData.h"

/*********************************************************
* @brief	スコア比較のファンクタ(昇順)
********************************************************/
class ScoreGreater
{
public:
	inline bool operator()(const ScoreData& left, const ScoreData& right) {
		return left.score > right.score;
	}
};

/*********************************************************
* @brief	スコア比較のファンクタ(降順)
********************************************************/
class ScoreLess
{
public:
	inline bool operator()(const ScoreData& left, const ScoreData& right) {
		return left.score < right.score;
	}
};

/*********************************************************
* @brief	名前比較のファンクタ(昇順)
********************************************************/
class NameGreater
{
public:
	inline bool operator()(const ScoreData& left, const ScoreData& right) {
		return left.name > right.name;
	}
};

/*********************************************************
* @brief	名前比較のファンクタ(降順)
********************************************************/
class NameLess
{
public:
	inline bool operator()(const ScoreData& left, const ScoreData& right) {
		return left.name < right.name;
	}
};
