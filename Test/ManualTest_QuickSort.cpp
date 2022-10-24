/*********************************************************
* @brief		クイックソートのテスト(手動テスト)
* @date			2022/10/19
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/DoubleLinkedList.h"
#include "../HashTable/ScoreData.h"
#include "ManualTest_QuickSort.h"

//クイックソートの手動テスト実行
#define GT_MANUAL_TEST_SORT

namespace ex03_ListSort
{
#ifdef  GT_MANUAL_TEST_SORT
#pragma region ========== クイックソート ==========


	/*********************************************************
	* @brief		型などが不適切なキー指定が引数で渡された時の挙動
	* @details		ID:0-7
	*				型などが不適切なキー指定が引数で渡された時、
	*				コンパイルエラーをチェック。自動テスト化しない。
	********************************************************/
	TEST(QuickSortTest, WithoutComparator)
	{

#ifdef MANUAL_TEST_SORT_WITH_WRONG_COMPARATOR
		DoubleLinkedList<ScoreData> list;

		//キー指定をしなくて、ソートを行う
		list.Sort([]() {return true; });
#endif
		SUCCEED();
	}

	/*********************************************************
	* @brief		非constのメソッドであるか
	* @details		ID:0-8
	*				非constのメソッドであるかを確認。
	*				constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
	********************************************************/
	TEST(QuickSortTest, NotConst)
	{
#ifdef MANUAL_TEST_SORT_NOT_CONST
		const DoubleLinkedList<ScoreData> list;
		list.Sort([]() {return true; });
#endif
		SUCCEED();
	}


#pragma endregion



#endif //  GT_MANUAL_TEST_SORT
}





