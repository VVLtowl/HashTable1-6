/*********************************************************
* @brief	ハッシュテーブルのヘッダーファイル
* @date		2022/10/21
********************************************************/
#pragma once
#include "DoubleLinkedList.h"



/*********************************************************
* @brief		ハッシュテーブル
* @details		データ構造の一つで、標識（キー：key）と対応する値（value）のペアを単位としてデータを格納し、
*				キーを指定すると対応する値を高速に取得できる構造。
*				[バケットサイズ]。
* @tparam		KeyType: キー型
* @tparam		ValueType: 値型
* @tparam		Hash: ハッシュ関数
*				・引数はKeyType型のキーとint型のバケットサイズ
*				・戻り値の型はint
* @tparam		bucketSize: バケットの数
********************************************************/
template <class KeyType,class ValueType, class HashFunc,int bucketSize>
class HashTable
{
private:
	/*********************************************************
	* @brief	ペア
	********************************************************/
	struct Pair
	{
		// @brief		キー
		KeyType key;

		// @brief		値
		ValueType value;
	};


private:
	//friend DoubleLinkedList<Pair>;

	// @brief		チェイン法で使うバケット
	DoubleLinkedList<Pair> m_List[bucketSize];

	// @brief		バケットサイズ
	int	m_BucketSize = bucketSize;

private:
	/*********************************************************
	* @brief		二重探索で要素を取得
	* @details		ハッシュ値とキーによって、要素を見つけ出す。
	* @param[in]	key: 要素のキー、ハッシュ値算出用
	* @param[out]	targetList: 目標要素を格納しているリスト
	* @param[out]	target: 目標要素を格納ためのイテレータ
	* @retval		true: 要素見つかった場合
	* @retval		false: 要素見つかない場合
	********************************************************/
	template <class ListType ,class IteratorType>
	bool Find(const KeyType key,IteratorType* target, ListType*& targetList = nullptr);

public:

	/*********************************************************
	* @brief	コンストラクタ削除
	********************************************************/
	//HashTable() = delete;

	/*********************************************************
	* @brief	デストラクタ削除
	********************************************************/
	//virtual ~HashTable()=delete;

	/*********************************************************
	* @brief	データ挿入
	* @details	リストに要素が追加される。
	*			同じハッシュ値の要素のチェインが内部で作成される。
	* @param	key: 要素のキー、ハッシュ値算出用
	* @param	value: 要素の値
	* @retval	true: 挿入成功の場合	
	* @retval	false: 挿入失敗の場合
	********************************************************/
	bool Add(const KeyType key,const ValueType value);

	/*********************************************************
	* @brief		データ削除
	* @details		ハッシュ関数を呼び出して格納位置を調べて、
	*				その位置にある連結リストをたどることで、
	*				目的の要素を見つけ出せて削除する。(二重探索)
	*				空である場合に失敗。
	* @param		key: 要素のキー、ハッシュ値算出用
	* @retval		true: 削除成功の場合
	* @retval		false: 削除失敗の場合
	********************************************************/
	bool Remove(const KeyType key);

	/*********************************************************
	* @brief		データ検索
	* @details		ハッシュ関数を呼び出して格納位置を調べて、
	*				その位置にある連結リストをたどることで、
	*				目的の要素を見つけ出せて削除する。(二重探索)
	* @param[in]	key: 要素のキー、ハッシュ値算出用
	* @param[out]	pOut: 要素を取得するためのポインタ
	* @retval		true: 検索成功の場合
	* @retval		false: 検索失敗の場合
	********************************************************/
	bool TryGetValue(const KeyType key,ValueType* pOut=nullptr);

	//const メソッド

	/*********************************************************
	* @brief	要素数を取得する
	* @return	要素数を返す
	********************************************************/
	const int Count() const;

	//test
#if 1
	void Print()
	{
		std::cout << "=========== print hashtable ==========" << std::endl;
		for (int i = 0; i < m_BucketSize; i++)
		{
			std::cout << "[" << i << "]: ";
			auto& list = m_List[i];
			auto iter = list.Begin();
			auto end = list.CEnd();
			while (iter != end)
			{
				std::cout
					<<"{"
					<< (*iter).key
					<< ","
					<< (*iter).value
					<< "} ";
				iter++;
			}
			std::cout << std::endl;
		}
		std::cout << "======================================" << std::endl;
	}
#endif
};

#include "HashTable.inl"

