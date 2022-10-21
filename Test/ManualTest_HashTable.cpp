/*********************************************************
* @brief		ハッシュテーブルのテスト(手動テスト)
* @date			2022/10/21
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/HashTable.h"
#include "../HashTable/HashFunc.h"
#include "ManualTest_HashTable.h"

//ハッシュテーブルの手動テスト実行
#define GT_MANUAL_TEST_HASHTABLE



namespace ex01_HashTable
{
#ifdef  GT_MANUAL_TEST_HASHTABLE

#pragma region ========== HashTable ==========

	/*********************************************************
	* @brief		不適切なハッシュ関数がテンプレート引数で渡された時
	* @details		ID:0-0
	* 				コンパイルエラーをチェック。自動テスト化しない。
	********************************************************/
	TEST(HashTableClassTest, WrongHashFunc)
	{
#ifdef MANUAL_TEST_HASHTABLE_WRONG_HASHFUNC
#if 1
		//引数のない関数は不適切
		{
			HashTable<int, int, HashFunc_NoArg, 8> hashTable;
			hashTable.Add(1, 2);
		}
#endif
#if 1
		//引数の型はキーの型と異なる関数は不適切
		{
			HashTable<std::string, int, HashFunc_IntZero, 8> hashTable;
			hashTable.Add("A", 2);
		}
#endif
#endif // MANUAL_TEST_HASHTABLE_WRONG_HASHFUNC
		SUCCEED();
	}

#pragma endregion



#endif 
}





