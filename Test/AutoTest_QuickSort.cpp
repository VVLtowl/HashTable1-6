/*********************************************************
* @brief		双方向リストのソートのテスト
* @date			2022/10/18
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/DoubleLinkedList.h"
#include "../HashTable/ScoreData.h"
#include "../HashTable/CompareScoreData.h"
#include "TestTool.h"

//双方向リストのソートのテスト実行
//#define GT_AUTO_TEST_LIST_SORT


/*********************************************************
* @brief		型付けテスト用
********************************************************/
template<typename T>
class QuickSortTestFixture : public ListFixture
{
};

typedef ::testing::Types<ScoreGreater,ScoreLess,NameGreater,NameLess> Comparator;
TYPED_TEST_CASE(QuickSortTestFixture, Comparator);





namespace ex03_ListSort
{
#ifdef GT_AUTO_TEST_LIST_SORT

/*********************************************************
* @brief		クイックソートのテスト
* @details		ソートが実行されるテスト全てで、全てのキー・降順昇順を網羅して実行させる
********************************************************/
#pragma region ========== クイックソート ==========
	/*********************************************************
	* @brief		要素を持たないリストにソートを実行した時の挙動
	* @details		ID:0-0
	*				要素を持たないリストにソートを実行した時、
	*				何も起こらないかを確認。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, WhenEmptyList)
	{
		//実行前後リスト内変化したかを確認
		//m_pDummyとm_Countで確認
		EXPECT_TRUE(list.CBegin()==list.CEnd());
		EXPECT_EQ(0, list.Count());

		TypeParam cmp;
		list.Sort(cmp);

		EXPECT_TRUE(list.CBegin() == list.CEnd());
		EXPECT_EQ(0, list.Count());
	}

	/*********************************************************
	* @brief		要素を1つだけ持つリストにソートを実行した時の挙動
	* @details		ID:0-1
	*				要素を1つだけ持つリストにソートを実行した時、
	*				何も起こらないかを確認。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, WhenOneElement)
	{
		InputOneData();

		//実行前後リスト内変化したかを確認
		//値で比較
		ScoreData datas[] = {
			{10,"head"},
		};
		CheckListValueAndCount(datas, 1, list);

		TypeParam cmp;
		list.Sort(cmp);

		CheckListValueAndCount(datas, 1, list);
	}

	/*********************************************************
	* @brief		2つ以上要素を持つリストにソートを実行した時の挙動
	* @details		ID:0-２
	*				2つ以上要素を持つリストにソートを実行した時、
	*				要素が指定したキーに準じて指定した順に並ぶかを確認。
	*				先頭から順にイテレータで確認し、
	*				ノードの差し替えが正常に行えているかチェック。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, WhenManyElement)
	{
		ScoreData datas[] = {
			{8,"B"},
			{4,"Z"},
			{3,"C"},
			{7,"A"},
			{6,"Y"},
			{5,"X"},
			{2,"W"},
			{1,"D"},
		};
		InputDatasToList(datas, 8, list);

		//実行前リスト要素の順番を確認
		CheckListValueAndCount(datas, 8, list);

		//実行後リスト要素の順番を確認
		TypeParam cmp;
		list.Sort(cmp);
		SortDatas(datas, 8, cmp);//正解の順の配列を用意
		CheckListValueAndCount(datas, 8, list);
	}

	/*********************************************************
	* @brief		同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時の挙動
	* @details		ID:0-3
	*				同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時、
	*				要素がソートされて並ぶが、同じ要素の順序は保証されない。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, ElementsHaveSameKey)
	{
		DoubleLinkedList<ScoreData> list1, list2;
		
		//すべての要素が同じだが、同じキーがある場合、
		//最初の順番は違うと、ソートの結果に影響する
		const int count = 4;
		ScoreData datas1[count] = {
			{5,"B"},
			{3,"A"},
			{4,"A"},
			{4,"C"},
		};
		InputDatasToList(datas1, count, list1);
		ScoreData datas2[count] = {
			{4,"C"},
			{4,"A"},
			{3,"A"},
			{5,"B"},
		};
		InputDatasToList(datas2, count, list2);

		//ソートを行う
		TypeParam cmp;
		list1.Sort(cmp);
		list2.Sort(cmp);

		//要素は全部同じだが、整列結果が違う可能性がある
		EXPECT_FALSE(IsSameOrder(list1, list2));

		//test リスト出力
		PrintList(list1);
		PrintList(list2);
	}

	/*********************************************************
	* @brief		整列済みリストにソートを実行した時の挙動
	* @details		ID:0-4
	*				整列済みリストにソートを実行した時、
	*				同じキーの要素の間以外の順番が変動しないかをチェック。
	*				重複要素なしの整列済みリストを使う。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, AfterSort)
	{
		DoubleLinkedList<ScoreData> list1, list2;
		TypeParam cmp;

		//整列済みリストを2つ用意
		const int count = 4;
		ScoreData datas[count] = {
			{5,"B"},
			{3,"A"},
			{2,"D"},
			{4,"C"},
		};
		InputDatasToList(datas, count, list1);
		InputDatasToList(datas, count, list2);
		list1.Sort(cmp);
		list2.Sort(cmp);
		//整列の後ソートされて並ぶかをチェック
		SortDatas(datas, count, cmp);
		CheckListValueAndCount(datas, count, list1);
		//整列の後リストの順番が同じかをチェック
		EXPECT_TRUE(IsSameOrder(list1, list2));

		//ソート済みのlist1にソートを行う
		list1.Sort(cmp);

		//list2で、list1の順番が変動しないかをチェック
		EXPECT_TRUE(IsSameOrder(list1, list2));
	}

	/*********************************************************
	* @brief		一度整列したリストの各所に挿入し、再度ソートを実行した時の挙動
	* @details		ID:0-5
	*				一度整列したリストの各所に挿入し、再度ソートを実行した時、
	*				要素がソートされて並ぶかをチェック。
	*				重複要素なしの整列済みリストを使う。
	********************************************************/
	TYPED_TEST(QuickSortTestFixture, AfterSortAndInsert)
	{
		TypeParam cmp;

		//一度整列したリストを用意
		const int count = 4;
		ScoreData datas[count] = {
			{5,"B"},
			{3,"A"},
			{1,"E"},
			{4,"C"},
		};
		InputDatasToList(datas, count, list);
		list.Sort(cmp);
		//整列の後ソートされて並ぶかをチェック
		SortDatas(datas, count, cmp);
		CheckListValueAndCount(datas, count, list);

		//挿入を行う
		UpdateIterator();
		list.Insert(middleIter, { 2,"D" });

		//再びソートを行う
		list.Sort(cmp);

		//再整列の後ソートされて並ぶかをチェック
		const int count2 = list.Count();
		ScoreData datas2[] = {
			{ 5,"B" },
			{ 3,"A" },
			{ 1,"E" },
			{ 4,"C" },
			{ 2,"D" },
		};
		SortDatas(datas2, count2, cmp);
		CheckListValueAndCount(datas2, count2, list);
	}

	/*********************************************************
	* @brief		キー指定をしなかった(nullptrを渡した)時の挙動
	* @details		ID:0-6
	*				キー指定をしなかった(nullptrを渡した)時、
	*				エラー含めて、何も起こらないかをチェック。
	********************************************************/
	TEST(QuickSortTest, WithoutKeyCompare)
	{
		DoubleLinkedList<ScoreData> list;

		const int count = 5;
		ScoreData datas[count] = {
			{ 5,"B" },
			{ 3,"A" },
			{ 1,"E" },
			{ 4,"C" },
			{ 2,"D" },
		};
		InputDatasToList(datas, count, list);

		//キー指定をしなくて、ソートを行う
		list.Sort([](const ScoreData& left, const ScoreData& right)
			{return false; });
		
		//test
		//list.Sort([](const ScoreData& left, const ScoreData& right)
		//	{return true; });

		CheckListValueAndCount(datas, count, list);
	}

#pragma endregion

#endif
}
