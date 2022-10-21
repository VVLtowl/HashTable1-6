/*********************************************************
* @brief	双方向リストの詳細定義
* @date		2022/10/11
********************************************************/
#include <assert.h>
#include "DoubleLinkedList.h"


//==========  コンストイテレータ ==========

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//リストの参照があるか
	bool sameList = (m_pList == list);//同じリストであるか

	return hasReference && sameList;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != &m_pList->m_Dummy && "pre decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != &m_pList->m_Dummy && "pre increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != &m_pList->m_Dummy && "post decrement: begin cant decrement");// 先頭ノードではないかの確認

	ConstIterator iter(*this);//運算前のイテレータをコピー
	m_pNode = m_pNode->pPrev;

	return iter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != &m_pList->m_Dummy && "post increment: dummy cant increment");// ダミーではないかの確認

	ConstIterator iter(*this);//運算前のイテレータをコピー
	m_pNode = m_pNode->pNext;

	return iter;
}

template <typename DataType>
DoubleLinkedList<DataType>::ConstIterator::ConstIterator(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator=(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;

	return *this;
}

template <typename DataType>
typename const DataType& DoubleLinkedList<DataType>::ConstIterator::operator*() const
{
	assert(m_pNode && m_pList && "constIterator: no reference");//リストの参照があるかの確認
	assert(m_pNode != &m_pList->m_Dummy && "constIterator: is dummy");//ダミーではないかの確認

	return (*m_pNode).data;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::operator==(const ConstIterator& iter)const
{
	return m_pNode == iter.m_pNode;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::operator!=(const ConstIterator& iter)const
{
	return m_pNode != iter.m_pNode;
}


//==========  イテレータ ==========

template <typename DataType>
DataType& DoubleLinkedList<DataType>::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");//リストの参照があるかの確認
	assert(m_pNode != &m_pList->m_Dummy && "iterator: is dummy");//ダミーではないかの確認

	return (*m_pNode).data;
}


//==========  双方向リスト ==========

template<typename DataType>
template<typename Comparator>
inline void DoubleLinkedList<DataType>::QuickSort(Iterator head, Iterator tail, Comparator& greater)
{
	//有効なイテレータでない場合、失敗
	if (head.IsVaild(this) == false || tail.IsVaild(this) == false)
	{
		return;
	}

	//同じ要素の場合、完了
	if (head == tail)
	{
		return;
	}

	//test
	//std::cout << "quick sort\n";

	//tailがループで交換しないための準備
	if (true == greater(*head, *tail))
	{
		Swap(head, tail);
	}

	Iterator& pivot = head;//先頭の要素を標準にする
	Iterator left = head;//2番目の要素から後ろに向かって、左部分で検索を行う
	++left;
	Iterator right = tail;//最後の要素から前に向かって、右部分で検索を行う


	while (1)
	{
		//右部分に、標準値pivotより小さい要素を見つけ出す
		while (false == greater(*pivot, *right) && right != left)
		{
			right--;
		}

		//左部分に、標準値pivotより大きい要素を見つけ出す
		while (false == greater(*left, *pivot) && left != right)
		{
			left++;
		}

		//test
		//std::cout << "found two\n";

		//左部分に大きい要素を、右部分に小さい要素と位置交換する
		if (left != right)
		{
			Swap(left, right);
		}
		// 二つの要素が同じ要素である場合、
		// 左右部分を「任意左要素 < 任意右要素」でソート完了し、ループから抜く
		else
		{
			break;
		}
	}

	if (greater(*pivot, *left))//最後に、標準要素を正しい位置に移動
	{
		//std::cout << "pivot left swap\n";
		Swap(pivot, left);
		right = left;
	}


	//左部分を引き続きソートする
	--left;
	QuickSort(head, left, greater);

	//右部分を引き続きソートする
	QuickSort(right, tail, greater);

}

template<typename DataType>
inline void DoubleLinkedList<DataType>::Swap(Iterator& l, Iterator& r)
{
	//コピーで交換
#if 0
	{
		auto copyData = (*l);
		(*l) = (*r);
		(*r) = copyData;
	}
#endif



	//ムーブで交換
#if 1
	{
		DataType moveData= std::move(*l);
		//auto moveData{ std::move(*l) };
		(*l) = std::move(*r);
		(*r) = std::move(moveData);
	}
#endif

	//ノードポインタで交換
#if 0
	{
		Node* left = l.m_pNode;
		Node* right = r.m_pNode;

		//test
		//std::cout<< left->pPrev<<" <-> " << left << " <-> " <<left->pNext <<"..."
		//	<< right->pPrev <<" <-> " <<right <<" <-> "<< right->pNext<< "\n";

		if (left->pNext == right)
		{
			//head left right tail
			Node* head = left->pPrev;
			Node* tail = right->pNext;

			//head right left tail
			left->pPrev = right;
			right->pNext = left;
			left->pNext = tail;
			tail->pPrev = left;
			right->pPrev = head;
			head->pNext = right;
		}
		else
		{
			Node* tempPrev = left->pPrev;
			Node* tempNext = left->pNext;

			left->pPrev = right->pPrev;
			left->pPrev->pNext = left;
			left->pNext = right->pNext;
			left->pNext->pPrev = left;

			right->pPrev = tempPrev;
			right->pPrev->pNext = right;
			right->pNext = tempNext;
			right->pNext->pPrev = right;
		}

		l.m_pNode = right;
		r.m_pNode = left;

		//test
		//right = b.m_pNode;
		//left = a.m_pNode;
		//std::cout << left->pPrev << " <-> " << left << " <-> " << left->pNext << "..."
		//	<< right->pPrev << " <-> " << right << " <-> " << right->pNext << " dummy: " << &m_Dummy << "\n\n";
	}
#endif

}

template <typename DataType>
DoubleLinkedList<DataType>::~DoubleLinkedList()
{
	//末尾から、先頭までノードを削除
	while (m_Count > 0)
	{
		auto tail = End();
		tail--;
		Remove(tail);
	}

	//test
	//std::cout << "after destructor count: " << m_Count << std::endl;
}

template <typename DataType>
DoubleLinkedList<DataType>::DoubleLinkedList()
{
	m_Count = 0;
	m_Dummy.pPrev = &m_Dummy;
	m_Dummy.pNext = &m_Dummy;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Insert(ConstIterator& positionIter, const DataType& data)
{
	//空参照の場合失敗
	if (&data == nullptr)
	{
		return false;
	}

	//新要素のノードを作成
	Node* newNode = new Node();
	newNode->data = data;

	//イテレータ有効であるかの確認
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//挿入を行う
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode;
	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;
	m_Count++;
	return true;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Remove(ConstIterator& positionIter)
{
	//リストが空の場合、削除失敗
	if (Count() == 0)
	{
		return false;
	}

	//イテレータ有効ではない場合、削除失敗
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//ダミーノードを指す場合、削除失敗
	if (positionIter.m_pNode == &m_Dummy)
	{
		return false;
	}

	//削除を行う
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode->pNext;
	prev->pNext = next;
	next->pPrev = prev;

	delete positionIter.m_pNode;
	m_Count--;
	return true;
}

template<typename DataType>
template<typename Comparator>
inline void DoubleLinkedList<DataType>::Sort(Comparator compare)
{
	//複数の要素数ではない場合、ソートはしない
	if (m_Count < 2)
	{
		return;
	}

	Iterator head = Begin();
	Iterator tail = End();
	--tail;
	QuickSort(head, tail, compare);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::Iterator DoubleLinkedList<DataType>::Begin()
{
	Iterator iter;
	iter.m_pNode = m_Dummy.pNext;
	iter.m_pList = this;
	return iter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::Iterator DoubleLinkedList<DataType>::End()
{
	Iterator iter;
	iter.m_pNode = &m_Dummy;
	iter.m_pList = this;
	return iter;
}

template <typename DataType>
int DoubleLinkedList<DataType>::Count() const
{
	return m_Count;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::CBegin() const
{
	ConstIterator constIter;
	constIter.m_pNode = m_Dummy.pNext;
	constIter.m_pList = this;
	return constIter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::CEnd() const
{
	ConstIterator constIter;
	constIter.m_pNode = (Node*)(&m_Dummy);
	constIter.m_pList = this;
	return constIter;
}
