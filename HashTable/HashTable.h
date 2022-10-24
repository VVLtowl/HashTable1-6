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
* @tparam		KeyType: キー型
* @tparam		ValueType: 値型
* @tparam		Hash: ハッシュ関数
*				・引数はKeyType型のキー
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
	//! 内部で使用するリストのイテレータの別名
	using ListIterator = typename DoubleLinkedList<Pair>::ConstIterator;

	// @brief		チェイン法で使うバケット
	DoubleLinkedList<Pair> m_List[bucketSize];

private:
	/*********************************************************
	* @brief		二重探索で要素を取得
	* @details		ハッシュ値とキーによって、要素を見つけ出す。
	* @param[in]	key: 要素のキー、ハッシュ値算出用
	* @param[in]	listID: 目標要素を格納しているリストの添え字
	* @param[out]	targetIter: 目標要素を格納ためのイテレータ(目標ない場合そのリストの末尾イテレータを返す)
	* @retval		true: 要素見つかった場合
	* @retval		false: 要素見つかない場合
	********************************************************/
	bool Find(const KeyType& key,const int listID, ListIterator* targetIter=nullptr)const;

	/*********************************************************
	* @brief		ハッシュ値でリストの添え字を取得
	* @param[in]	key: 要素のキー、ハッシュ値算出用
	* @return		キーに応じるリストの添え字
	********************************************************/
	int GetListID(const KeyType& key)const;

public:
	/*********************************************************
	* @brief	データ挿入
	* @details	リストに要素が追加される。
	*			同じハッシュ値の要素のチェインが内部で作成される。
	* @param	key: 要素のキー、ハッシュ値算出用
	* @param	value: 要素の値
	* @retval	true: 挿入成功の場合	
	* @retval	false: 挿入失敗の場合
	********************************************************/
	bool Add(const KeyType& key,const ValueType value);

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
	bool Remove(const KeyType& key);

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
	bool TryGetValue(const KeyType& key, ValueType* pOut = nullptr)const;

	//const メソッド

	/*********************************************************
	* @brief	要素数を取得する
	* @return	要素数を返す
	********************************************************/
	const int Count() const;

};

#include "HashTable.inl"

