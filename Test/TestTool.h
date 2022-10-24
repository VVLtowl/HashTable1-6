/*********************************************************
* @brief		テスト補助のクラスと関数
* @date			2022/10/12
********************************************************/
#pragma once

#include "gtest/gtest.h"
#include "../HashTable/DoubleLinkedList.h"
#include "../HashTable/HashTable.h"
#include "../HashTable/ScoreData.h"
#include "../HashTable/HashFunc.h"

#pragma region ========== List ==========

/*********************************************************
* @brief		指定要素数のリストのフィクスチャ
********************************************************/
class ListFixture : public ::testing::Test
{
protected:
	// @brief		テスト用リスト
	DoubleLinkedList<ScoreData> list;

	// @brief		先頭要素を指すイテレータ
	DoubleLinkedList<ScoreData>::Iterator headIter;

	// @brief		中間要素を指すイテレータ
	DoubleLinkedList<ScoreData>::Iterator middleIter;

	// @brief		最後の要素を指すイテレータ
	DoubleLinkedList<ScoreData>::Iterator tailIter;

	// @brief		末尾要素を指すイテレータ
	DoubleLinkedList<ScoreData>::Iterator endIter;

protected:
	virtual void SetUp(void)
	{
		//list = new DoubleLinkedList();
	}

	virtual void TearDown(void)
	{
		//delete list;
	}

	/*********************************************************
	* @brief		要素を1つだけ入れる
	********************************************************/
	void InputOneData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//テスト用イテレータの準備
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;
		tailIter = list.End(); --tailIter;
		endIter = list.End();

		UpdateIterator();
	}

	/*********************************************************
	* @brief		要素を2つ入れる
	********************************************************/
	void InputTwoData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		data.score = 11;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		//テスト用イテレータの準備
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;
		tailIter = list.End(); --tailIter;
		endIter = list.End();

		UpdateIterator();
	}

	/*********************************************************
	* @brief		要素を3つ入れる
	********************************************************/
	void InputThreeData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		data.score = 11;
		data.name = "middle";
		end = list.End();
		list.Insert(end, data);

		data.score = 12;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		UpdateIterator();
	}

	/*********************************************************
	* @brief		2つ以上、指定要素数で入れる
	* @param		count: 要素数[2,5]
	********************************************************/
	void InputDatas(int count)
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;
		int dataNum = count;

		//作成数を制限
		if (dataNum < 2)dataNum = 2;
		if (dataNum > 5)dataNum = 5;

		//先頭を作成し、リストに入れる
		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//中間を作成し、リストに入れる
		for (int i = 1; i < dataNum - 1; i++)
		{
			data.score = 10 + i;
			data.name = "middle" + std::to_string(i - 1);//名前で区別させる
			end = list.End();
			list.Insert(end, data);
		}

		//最後の要素を作成し、リストに入れる
		data.score = 10 + dataNum - 1;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		UpdateIterator();
	}

	/*********************************************************
	* @brief		テスト用の先頭、中間、最後の要素、末尾イテレータの準備
	********************************************************/
	void UpdateIterator()
	{
		//リストが空である場合、設置しない
		if (list.Count() == 0)
			return;

		//テスト用イテレータの準備
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;//中間要素を取得
		tailIter = list.End(); --tailIter;//最後の要素を取得
		endIter = list.End();
	}

	/*********************************************************
	* @brief		リストを空くする
	********************************************************/
	void ClearList()
	{
		//空の場合終了
		if (list.Count() == 0)
		{
			return;
		}

		//末尾から全部削除
		auto iter = list.End();
		iter--;
		auto del = iter;
		while (del != list.Begin())
		{
			iter--;
			list.Remove(del);
			del = iter;
		}
		list.Remove(del);//先頭を削除
	}
};

/*********************************************************
* @brief		要素は期待される値であるかの確認
* @details		期待される値の配列を渡してリスト内の要素が一致するかと、
*				要素数が合ってるかを判定する。
* @param		datas: 期待される値の配列
* @param		count: 値の個数
* @param		list: 比較するリスト
********************************************************/
inline void CheckListValueAndCount(const ScoreData* datas, const int count, const DoubleLinkedList<ScoreData>& list)
{
	auto iter = list.CBegin();
	EXPECT_EQ(count, list.Count());

	//期待される値ではない場合falseで終了
	{
		for (int i = 0; i < count; i++, iter++)
		{
			EXPECT_EQ(datas[i].name, (*iter).name);
			EXPECT_EQ(datas[i].score, (*iter).score);
		}
	}
}

/*********************************************************
* @brief		末尾イテレータであるかを確認
* @details		一つ前の要素が末尾要素であることを確認する
* @param		iter: 判断したいイテレータ
* @param		tail: 末尾要素のデータ
********************************************************/
inline void CheckIsEndIterator(DoubleLinkedList<ScoreData>::ConstIterator iter, const ScoreData& tail)
{
	iter--;

	EXPECT_EQ(tail.name, (*iter).name);
	EXPECT_EQ(tail.score, (*iter).score);
}

/*********************************************************
* @brief		指定した要素を入れる
* @param		datas: 指定した要素
* @param		count: 要素数[2,10]
* @param		list: 使うリスト
********************************************************/
inline void InputDatasToList(ScoreData* datas, int count, DoubleLinkedList<ScoreData>& list)
{
	ScoreData data;
	DoubleLinkedList<ScoreData>::Iterator end;
	int dataNum = count;

	//作成数を制限
	if (dataNum < 2)dataNum = 2;
	if (dataNum > 10)dataNum = 10;

	for (int i = 0; i < dataNum; i++)
	{
		data.score = datas[i].score;
		data.name = datas[i].name;
		end = list.End();
		list.Insert(end, data);
	}
}

/*********************************************************
* @brief		リストを表示
* @param		list: リスト
********************************************************/
inline void PrintList(const DoubleLinkedList<ScoreData>& list)
{
	std::cout << "print list:" << std::endl;
	auto iter = list.CBegin();
	auto end = list.CEnd();
	for (; iter != end; iter++)
	{
		std::cout << (*iter).name << ":" << (*iter).score << std::endl;
	}
}

/*********************************************************
* @brief		データ配列を並べ替え
* @details		挿入ソートでデータ配列を並べ替え
* @param		datas: ソートさせたい配列
* @param		count: 要素の個数
* @param		greater: ソートのルール
********************************************************/
template <typename Comparator>
inline void SortDatas(ScoreData* datas, const int count, Comparator greater)
{
	ScoreData temp;
	int finishCount, i, j;
	for (finishCount = 0; finishCount < count; finishCount++)
	{
		for (j = finishCount, i = finishCount - 1; i >= 0; i--, j--)
		{
			if (greater(datas[i], datas[j]))
			{
				temp = datas[i];
				datas[i] = datas[j];
				datas[j] = temp;
			}
			else
			{
				break;
			}
		}
	}

	//test
#if 0 
	for (i = 0; i < count; i++)
	{
		std::cout << datas[i].name << ":" << datas[i].score << std::endl;
	}
#endif // 1

}

/*********************************************************
* @brief		2つリストに、要素の順番が同じであるかのチェック
* @param		list1: 比較するリスト1
* @param		list2: 比較するリスト2
* @retval		false: 順番が全部同じではない場合
* @retval		true: 順番が全部同じの場合
********************************************************/
inline bool IsSameOrder(const DoubleLinkedList<ScoreData>& list1, const DoubleLinkedList<ScoreData>& list2)
{
	bool isSame = true;//順番全部同じの場合true
	auto iter1 = list1.CBegin();
	auto iter2 = list2.CBegin();
	auto end = list1.CEnd();
	for (; iter1 != end; iter1++, iter2++)
	{
		if ((*iter1).name != (*iter2).name ||
			(*iter1).score != (*iter2).score)
		{
			isSame = false;
			break;
		}
	}
	return isSame;
}

#pragma endregion

#pragma region ========== HashTable ==========

/*********************************************************
* @brief		ハッシュテーブルのフィクスチャ
********************************************************/
class HashTableFixture : public ::testing::Test
{
protected:
	// @brief		テスト用ハッシュテーブル
	HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;

protected:
	virtual void SetUp(void)
	{
		EXPECT_TRUE(table.Add(1, "val1"));
		EXPECT_TRUE(table.Add(2, "val2"));
		EXPECT_TRUE(table.Add(3, "val3"));
	}

	virtual void TearDown(void)
	{
	}
};

#pragma endregion