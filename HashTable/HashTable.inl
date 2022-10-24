/*********************************************************
* @brief	ハッシュテーブルの詳細定義
* @date		2022/10/21
********************************************************/
#include "HashTable.h"
#include "DoubleLinkedList.h"

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
//template<class IteratorType>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Find(
	const KeyType& key, const int listID,typename ListIterator* targetIter)const
{
	//ハッシュ値に応じるリストに要素がない場合、見つかないとする
	auto list = &m_List[listID];
	if (list->Count() == 0)
	{
		//要素が見つかなかった場合末尾イテレータを返す
		if (targetIter != nullptr)
		{
			*targetIter = list->CEnd();
		}
		return false;
	}

	//キーに応じる要素がない場合探索失敗
	auto iter = list->CBegin();
	auto end = list->CEnd();
	while (iter != end)
	{
		if ((*iter).key == key)//要素を見つけた
		{
			if (targetIter != nullptr)
			{
				*targetIter = iter;
			}
			return true;
		}
		iter++;
	}

	//要素が見つかなかった場合末尾イテレータを返す
	if (targetIter != nullptr)
	{
		*targetIter = iter;
	}
	return false;
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline int HashTable<KeyType, ValueType, HashFunc, bucketSize>::GetListID(const KeyType& key)const
{
	//ハッシュ値がバケットサイズを超えないようにする
	return HashFunc()(key) % bucketSize;
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Add(const KeyType& key, ValueType value)
{
	//所属するリストの末尾イテレータを取得
	ListIterator end;
	int listID = GetListID(key);
	if (true == Find(key, listID, &end))
	{
		//同じキーはもう存在している場合挿入失敗
		return false;
	}

	return m_List[listID].Insert(end, { key,value });
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Remove(const KeyType& key)
{
	//空の場合失敗
	if (0 == Count())
	{
		return false;
	}

	//二重検索で要素を見つけ出す
	ListIterator iter;
	int listID = GetListID(key);
	if (true == Find(key, listID, &iter))
	{
		//要素が見つかった場合削除を行う
		return m_List[listID].Remove(iter);
	}
	else
	{
		return false;
	}
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::TryGetValue(const KeyType& key, ValueType* pOut)const
{
	//空の場合失敗
	if (0 == Count())
	{
		return false;
	}

	//二重検索で要素を見つけ出す
	ListIterator iter;
	int listID = GetListID(key);
	if (true == Find(key, listID, &iter))
	{
		//要素が見つかった場合値をコピーで代入
		if (pOut != nullptr)
		{
			*pOut = (*iter).value;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline const int HashTable<KeyType, ValueType, HashFunc, bucketSize>::Count() const
{
	int count = 0;
	for (int i = 0; i < bucketSize; i++)
	{
		count += m_List[i].Count();
	}
	return count;
}
