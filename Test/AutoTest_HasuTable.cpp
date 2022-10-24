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
			HashTable<int, std::string, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

			//挿入
			EXPECT_TRUE(table.Add(1, "val1"));
			EXPECT_TRUE(table.Add(2, "val2"));
			//検索
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_FALSE(table.TryGetValue(3));
			//削除
			EXPECT_FALSE(table.Remove(3));
			EXPECT_TRUE(table.Remove(1));
		}

		//割り算であまり値をハッシュ値とする
		{
			HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;

			//挿入
			EXPECT_TRUE(table.Add(1, "val1"));
			EXPECT_TRUE(table.Add(2, "val2"));
			//検索
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_TRUE(table.TryGetValue(2));
			//削除
			EXPECT_TRUE(table.Remove(2));
			EXPECT_TRUE(table.Remove(1));
		}

		SUCCEED();
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
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}


	/*********************************************************
	* @brief		要素を挿入した後の戻り値
	* @details		ID:0-3
	* 				要素を挿入した後の戻り値は1であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, AfterAdd)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		table.Add(1, 1);
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		要素を挿入し、そのキーで削除した後の戻り値
	* @details		ID:0-4
	* 				要素を挿入し、そのキーで削除した後の戻り値は0であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, AfterAddAndRemove)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 2);
		EXPECT_EQ(1, table.Count());

		table.Remove(1);
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		既に存在するキーで要素の挿入をし失敗した後の戻り値
	* @details		ID:0-5
	* 				既に存在するキーで要素の挿入をし失敗した後の戻り値は1であるかをチェック。
	*				１回挿入した後、そのキーで再度挿入する。
	********************************************************/
	TEST(HashTableCountTest, WhenAddFailedWithSameKey)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 2);
		EXPECT_EQ(1, table.Count());
		EXPECT_FALSE(table.Add(1, 3));
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに要素がある時に存在しないキーを指定し要素の削除に失敗した際の戻り値
	* @details		ID:0-6
	* 				リストに要素がある時に存在しないキーを指定し要素の削除に失敗した際の戻り値は1であるかをチェック。
	*				１回挿入した後、異なるキーで削除する。
	********************************************************/
	TEST(HashTableCountTest, WhenRemoveFailedWithWrongKey)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 1);
		EXPECT_FALSE(table.Remove(2));
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストが空である場合に、削除を行った後の戻り値
	* @details		ID:0-7
	* 				リストが空である場合に、削除を行った後の戻り値は0であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, WhenEmptyList_RemoveFailed)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		EXPECT_FALSE(table.Remove(1));
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		要素２つが内部でチェインになっていない時の戻り値
	* @details		ID:0-8
	* 				要素２つが内部でチェインになっていない時の戻り値は2であるかをチェック。
	*				チェインによって要素数処理が変化しないことをチェック。
	********************************************************/
	TEST(HashTableCountTest, TwoElementsNotChain)
	{
		//キーの値そのままハッシュ値とする
		HashTable<int, int, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

		//同じハッシュ値出ないようなキーで追加
		table.Add(1, 1);
		table.Add(2, 2);
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		要素２つが内部でチェインになっていない時に一方を削除した後の戻り値
	* @details		ID:0-9
	* 				要素２つが内部でチェインになっていない時に一方を削除した後の戻り値は1であるかをチェック。
	********************************************************/
	TEST(HashTableCountTest, TwoElementsNotChain_AfterRemove)
	{
		//キーの値そのままハッシュ値とする
		HashTable<int, int, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

		//同じハッシュ値出ないようなキーで追加
		table.Add(1, 1);
		table.Add(2, 2);
		EXPECT_EQ(2, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(1, table.Count());
		SUCCEED();
	}

	/*********************************************************
	* @brief		要素２つが内部でチェインになった後の戻り値
	* @details		ID:0-10
	* 				要素２つが内部でチェインになった後の戻り値は2であるかをチェック。
	*				チェインを辿れていない場合は1が返ってくるはず。
	*				同じハッシュ値の別キーを挿入。
	********************************************************/
	TEST(HashTableCountTest, TwoElementsChain)
	{
		//0をハッシュ値とする
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		//チェインになる要素を用意
		table.Add(1, 1);//ハッシュ値は0
		table.Add(2, 2);//ハッシュ値は0
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		要素２つが内部でチェインになっている時に一方を削除した後の戻り値
	* @details		ID:0-11
	* 				要素２つが内部でチェインになっている時に一方を削除した後の戻り値は1であるかをチェック。
	*				チェインを辿れていない場合は1が返ってくるはず。
	*				同じハッシュ値の別キーを挿入。
	********************************************************/
	TEST(HashTableCountTest, TwoElementsChain_AfterRemove)
	{
		//0をハッシュ値とする
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		//チェインになる要素を用意
		table.Add(1, 1);//ハッシュ値は0
		table.Add(2, 2);//ハッシュ値は0
		EXPECT_EQ(2, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(1, table.Count());
		SUCCEED();
	}
#pragma endregion

#pragma region ========== データの挿入 ==========
	
	using HashTableAddTest_F = HashTableFixture;

	/*********************************************************
	* @brief		リストが空である場合に、挿入した際の挙動
	* @details		ID:0-13
	*				リストが空である場合に、挿入した際、
	* 				戻り値はtrueであるかをチェック、
	*				リストに要素が追加されるかをチェック。
	********************************************************/
	TEST(HashTableAddTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());
		
		EXPECT_TRUE(table.Add(1, "val1"));
		
		EXPECT_TRUE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、キーが重複しないで挿入した際の挙動
	* @details		ID:0-14
	*				リストに複数の要素がある場合に、キーが重複しないで挿入した際、
	* 				戻り値はtrueであるかをチェック、
	*				リストに要素が追加されるかをチェック。
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_NotDuplicate)
	{
		EXPECT_TRUE(table.Add(4, "val4"));
		
		EXPECT_TRUE(table.TryGetValue(4));

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、キーが重複して挿入しようとした際の挙動
	* @details		ID:0-15
	*				リストに複数の要素がある場合に、キーが重複して挿入しようとした際、
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_Duplicate)
	{
		EXPECT_FALSE(table.Add(2, "val4"));
		
		std::string value;
		EXPECT_TRUE(table.TryGetValue(2,&value));
		EXPECT_EQ("val2", value);

		SUCCEED();
	}

	/*********************************************************
	* @brief		既にリストにある要素とハッシュ値が同じになるキーで挿入した際の挙動
	* @details		ID:0-16
	*				既にリストにある要素とハッシュ値が同じになるキーで挿入した際、
	* 				戻り値はtrueであるかをチェック、
	*				リストに要素が追加されるかをチェック。
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_SameHash)
	{
		EXPECT_EQ(3, HashFunc_IntMod()(13));//ハッシュ値は3
		EXPECT_TRUE(table.Add(13, "val4"));
		
		EXPECT_TRUE(table.TryGetValue(13));

		SUCCEED();
	}

	/*********************************************************
	* @brief		一度挿入し、削除した後再度同じキーで挿入した際の挙動
	* @details		ID:0-17
	*				一度挿入し、削除した後再度同じキーで挿入した際、
	* 				戻り値はtrueであるかをチェック、
	*				削除漏れとか例外処理が変に動いていないか確認。
	********************************************************/
	TEST_F(HashTableAddTest_F, AfterAddAndRemove)
	{
		EXPECT_TRUE(table.Add(4, "val4"));
		EXPECT_TRUE(table.Remove(4));

		EXPECT_FALSE(table.TryGetValue(4));

		EXPECT_TRUE(table.Add(4, "val4"));
		EXPECT_TRUE(table.TryGetValue(4));

		SUCCEED();
	}

#pragma endregion

#pragma region ========== データの削除 ==========

	using HashTableRemoveTest_F = HashTableFixture;

	/*********************************************************
	* @brief		リストが空である場合に、削除操作をしようとした際の挙動
	* @details		ID:0-19
	*				リストが空である場合に、削除操作をしようとした際、
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST(HashTableRemoveTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());

		EXPECT_FALSE(table.Remove(1));

		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、存在するキーで指定して削除した際の挙動
	* @details		ID:0-20
	*				リストに複数の要素がある場合に、存在するキーで指定して削除した際、
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableRemoveTest_F, WhenManyElements)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_FALSE(table.TryGetValue(1));
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、存在しないキーで指定して削除しようとした際の挙動
	* @details		ID:0-21
	*				リストに複数の要素がある場合に、存在しないキーで指定して削除しようとした際、
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableRemoveTest_F, WhenManyElements_NonexistentKey)
	{
		EXPECT_EQ(3, table.Count());

		EXPECT_FALSE(table.TryGetValue(4));
		EXPECT_FALSE(table.Remove(4));//存在しないキー
		
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		一度削除したキーで再度削除しようとした際の挙動
	* @details		ID:0-22
	*				一度削除したキーで再度削除しようとした際、
	*				削除漏れ等のミスがないかチェック。
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveAgain)
	{
		EXPECT_EQ(3, table.Count());
		EXPECT_TRUE(table.TryGetValue(3));

		//削除したキーで再度削除
		EXPECT_TRUE(table.Remove(3));
		EXPECT_FALSE(table.Remove(3));

		EXPECT_FALSE(table.TryGetValue(3));
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		チェインになっている要素うちの1つのキーを指定して削除した際の挙動
	* @details		ID:0-23
	*				チェインになっている要素うちの1つのキーを指定して削除した際、
	*				指定した要素だけが削除され、チェインが繋ぎなおされる。
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveChainElement)
	{
		//同じハッシュ値のキーで、チェインを作る
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13,"val4"));
		EXPECT_EQ(4, table.Count());

		EXPECT_TRUE(table.TryGetValue(3));
		EXPECT_TRUE(table.Remove(3));

		EXPECT_TRUE(table.TryGetValue(13));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		チェインになっている要素とハッシュ値が同じだが、存在しないキーを指定して削除した際の挙動
	* @details		ID:0-24
	*				チェインになっている要素とハッシュ値が同じだが、存在しないキーを指定して削除した際、
	*				ハッシュ値とキーによる二重検索が機能しているかチェック。
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveChainElement_NonexistentKey)
	{
		//同じハッシュ値のキーで、チェインを作る
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		//チェインになっている要素とハッシュ値が同じだが、存在しないキー
		EXPECT_EQ(HashFunc_IntMod()(23), HashFunc_IntMod()(3));
		EXPECT_FALSE(table.TryGetValue(23));
		EXPECT_FALSE(table.Remove(23));

		EXPECT_EQ(4, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		チェインになっている要素を順に削除していった際の挙動
	* @details		ID:0-25
	*				チェインになっている要素を順に削除していった際、
	*				チェインが外れたりして削除できない状態にならないかどうか、
	*				全て正常に要素が削除されるかをチェック。
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST(HashTableRemoveTest, RemoveChainElement_NonexistentKey)
	{
		//0をハッシュ値とする、チェインになる要素を用意
		HashTable<int, std::string, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, HashFunc_Zero()(1));
		EXPECT_TRUE(table.Add(1, "val1"));
		EXPECT_EQ(0, HashFunc_Zero()(2));
		EXPECT_TRUE(table.Add(2, "val2"));
		EXPECT_EQ(0, HashFunc_Zero()(3));
		EXPECT_TRUE(table.Add(3, "val3"));
		EXPECT_EQ(3, table.Count());

		//順に削除
		EXPECT_TRUE(table.Remove(1));
		EXPECT_TRUE(table.Remove(2));
		EXPECT_TRUE(table.Remove(3));
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

#pragma endregion

#pragma region ========== データの検索 ==========

	using HashTableTryGetValueTest_F = HashTableFixture;

	/*********************************************************
	* @brief		リストが空である場合に、キーを指定して検索した際の挙動
	* @details		ID:0-27
	*				リストが空である場合に、キーを指定して検索した際、
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST(HashTableTryGetValueTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_FALSE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、存在するキーで指定して検索した際の挙動
	* @details		ID:0-28
	*				リストに複数の要素がある場合に、存在するキーで指定して検索した際、
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, WhenManyElements)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、存在しないキーで指定して検索した際の挙動
	* @details		ID:0-29
	*				リストに複数の要素がある場合に、存在しないキーで指定して検索した際、
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, WhenManyElements_NonexistentKey)
	{
		EXPECT_FALSE(table.TryGetValue(4));//存在しないキー4
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、同じキーで2連続で検索した際の挙動
	* @details		ID:0-30
	*				リストに複数の要素がある場合に、同じキーで2連続で検索した際、
	*				同じ要素が2回とも引数経由で渡される、変に削除されていたりしないかチェック。
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, TryGetValueAgain)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		既に削除されたキーで検索した際の挙動
	* @details		ID:0-31
	*				既に削除されたキーで検索した際、
	*				削除漏れとかがないかチェック。
	* 				戻り値はfalseであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, AfterRemove)
	{
		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(2, table.Count());

		EXPECT_FALSE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		チェインになっている要素の内の1つのキーを指定して検索した際の挙動
	* @details		ID:0-32
	*				チェインになっている要素の内の1つのキーを指定して検索した際、
	*				指定したキーの要素が引数経由で渡されて、
	*				ハッシュ値とキーによる二重検索が機能しているかチェック。
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, ChainElement)
	{
		//同じハッシュ値のキーで、チェインを作る
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		std::string value;
		EXPECT_TRUE(table.TryGetValue(13, &value));

		EXPECT_EQ("val4", value);

		SUCCEED();
	}

	/*********************************************************
	* @brief		チェインになっている要素うちの1つの削除した後に、残っている要素を検索した際の挙動
	* @details		ID:0-33
	*				チェインになっている要素うちの1つの削除した後に、残っている要素を検索した際、
	*				指定したキーの要素が引数経由で渡されるかをチェック。
	* 				戻り値はtrueであるかをチェック。
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, AfterRemove_OtherElementInSameChain)
	{
		//同じハッシュ値のキーで、チェインを作る
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		//チェインになっている要素うちの1つの削除
		EXPECT_TRUE(table.Remove(3));

		//残っている要素を検索
		std::string value;
		EXPECT_TRUE(table.TryGetValue(13, &value));

		EXPECT_EQ("val4", value);

		SUCCEED();
	}

#pragma endregion

#endif
}