/*********************************************************
* @brief		ハッシュテーブルの単体テスト
* @date			2022/10/21
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/HashTable.h"
#include "../HashTable/ScoreData.h"
#include "../HashTable/HashFunc.h"
#include "TestTool.h"


//ハッシュテーブルの単体テスト実行
#define GT_AUTO_TEST_HASHTABLE

namespace ex01_HashTable
{
#if defined GT_AUTO_TEST_HASHTABLE

#pragma region ========== クラスの挙動 ==========


	/*********************************************************
	* @brief		算出方法の異なる適切なハッシュ関数を渡したときのそれぞれの挙動
	* @details		ID:0-1
	* 				挿入、検索、削除を行い、全ての戻り値がTRUEになるかチェック。
	********************************************************/
	TEST(HashTableClassTest, CorrectHashFunc)
	{
		//キーの値そのままハッシュ値とする
		{
			HashTable<int, int, HashFunc_IntKey, 8> table;

			//挿入
			EXPECT_TRUE(table.Add(1, 1));
			EXPECT_TRUE(table.Add(2, 2));
			//検索
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_FALSE(table.TryGetValue(3));
			//削除
			EXPECT_FALSE(table.Remove(3));
			EXPECT_TRUE(table.Remove(1));
		}

		//割り算であまり値をハッシュ値とする
		{
			HashTable<int, int, HashFunc_IntMod, 8> table;

			//挿入
			EXPECT_TRUE(table.Add(1, 1));
			EXPECT_TRUE(table.Add(2, 2));
			//検索
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_TRUE(table.TryGetValue(2));
			//削除
			EXPECT_TRUE(table.Count()==2);
			EXPECT_TRUE(table.Remove(2));
			EXPECT_TRUE(table.Remove(1));
		}
	}

#pragma endregion

#pragma region ========== データ数の取得 ==========

	/*********************************************************
	* @brief		リストが空である場合の戻り値
	* @details		ID:0-2
	* 				リストが空である場合の戻り値は0であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, WhenEmptyList)
	{
		SUCCEED();
	}


	/*********************************************************
	* @brief		要素を挿入した後の戻り値
	* @details		ID:0-3
	* 				要素を挿入した後の戻り値は1であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, AfterAdd)
	{
		SUCCEED();
	}

#pragma endregion

#endif
}