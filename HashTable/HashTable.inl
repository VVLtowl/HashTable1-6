/*********************************************************
* @brief	ハッシュテーブルの詳細定義
* @date		2022/10/21
********************************************************/
#include "HashTable.h"
#include "DoubleLinkedList.h"

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
template<class ListType,class IteratorType>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Find(
	const KeyType key, 
	IteratorType* target, ListType*& targetList)
{
	//ハッシュ値に応じるリストに要素がない場合失敗
	HashFunc hash;
	int id = hash(key, m_BucketSize);
	targetList = &m_List[id];
	if (targetList->Count() == 0)
	{
		return false;
	}

	//キーに応じる要素がない場合探索失敗
	auto iter = targetList->Begin();
	auto end = targetList->CEnd();
	while (iter != end)
	{
		if ((*iter).key == key)//要素を見つけた
		{
			*target = iter;
			return true;
		}
		iter++;
	}
	return false;
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Add(KeyType key, ValueType value)
{
	HashFunc hash;
	int id = hash(key, m_BucketSize);
	
	auto list = &m_List[id];
	auto end = list->CEnd();
	return list->Insert(end, { key,value });
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::Remove(KeyType key)
{
	//空の場合失敗
	if (0 == Count())
	{
		return false;
	}



	//二重検索で要素を見つけ出す
	auto iter = m_List[0].Begin();
	auto list = &m_List[0];
	if (true == Find(key, &iter, list))
	{
		//要素が見つかった場合削除を行う
		return list->Remove(iter);
	}
	else
	{
		return false;
	}
}

template<class KeyType, class ValueType, class HashFunc, int bucketSize>
inline bool HashTable<KeyType, ValueType, HashFunc, bucketSize>::TryGetValue(KeyType key, ValueType* pOut)
{
	//空の場合失敗
	if (0 == Count())
	{
		return false;
	}

	//二重検索で要素を見つけ出す
	auto iter = m_List[0].Begin();
	auto list = &m_List[0];
	if (true == Find(key, &iter, list))
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
	int count=0;
	for (int i = 0; i < m_BucketSize; i++)
	{
		count += m_List[i].Count();
	}
	return count;
}
