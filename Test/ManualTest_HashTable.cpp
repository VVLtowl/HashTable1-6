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

	/*********************************************************
	* @brief		constのメソッドであるか
	* @details		ID:0-12
	* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
	********************************************************/
	TEST(HashTableCountTest, IsConst)
	{
#ifdef MANUAL_TEST_HASHTABLE_COUNT_IS_CONST
		const HashTable<int, int, HashFunc_IntMod, 8> hashTable;
		hashTable.Count();
#endif
		SUCCEED();
	}

	/*********************************************************
	* @brief		非constのメソッドであるか
	* @details		ID:0-18
	* 				constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
	********************************************************/
	TEST(HashTableCountTest, NotConst)
	{
#ifdef MANUAL_TEST_HASHTABLE_ADD_NOT_CONST
		const HashTable<int, int, HashFunc_IntMod, 8> hashTable;
		hashTable.Add(1, 1);
#endif
		SUCCEED();
	}

	/*********************************************************
	* @brief		非constのメソッドであるか
	* @details		ID:0-26
	* 				constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
	********************************************************/
	TEST(HashTableAddTest, NotConst)
	{
#ifdef MANUAL_TEST_HASHTABLE_REMOVE_NOT_CONST
		const HashTable<int, int, HashFunc_IntMod, 8> hashTable;
		hashTable.Remove(1);
#endif
		SUCCEED();
	}

	/*********************************************************
	* @brief		constのメソッドであるか
	* @details		ID:0-34
	* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
	********************************************************/
	TEST(HashTableTryGetValueTest, IsConst)
	{
#ifdef MANUAL_TEST_HASHTABLE_TRY_GET_VALUE_IS_CONST
		const HashTable<int, int, HashFunc_IntMod, 8> hashTable;
		
		int value;
		hashTable.TryGetValue(1, &value);
#endif
		SUCCEED();
	}

#pragma endregion



#endif 
}





