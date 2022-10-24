/*********************************************************
* @brief	�n�b�V���e�[�u���̃w�b�_�[�t�@�C��
* @date		2022/10/21
********************************************************/
#pragma once
#include "DoubleLinkedList.h"



/*********************************************************
* @brief		�n�b�V���e�[�u��
* @details		�f�[�^�\���̈�ŁA�W���i�L�[�Fkey�j�ƑΉ�����l�ivalue�j�̃y�A��P�ʂƂ��ăf�[�^���i�[���A
*				�L�[���w�肷��ƑΉ�����l�������Ɏ擾�ł���\���B
* @tparam		KeyType: �L�[�^
* @tparam		ValueType: �l�^
* @tparam		Hash: �n�b�V���֐�
*				�E������KeyType�^�̃L�[
*				�E�߂�l�̌^��int
* @tparam		bucketSize: �o�P�b�g�̐�
********************************************************/
template <class KeyType,class ValueType, class HashFunc,int bucketSize>
class HashTable
{
private:
	/*********************************************************
	* @brief	�y�A
	********************************************************/
	struct Pair
	{
		// @brief		�L�[
		KeyType key;

		// @brief		�l
		ValueType value;
	};


private:
	//! �����Ŏg�p���郊�X�g�̃C�e���[�^�̕ʖ�
	using ListIterator = typename DoubleLinkedList<Pair>::ConstIterator;

	// @brief		�`�F�C���@�Ŏg���o�P�b�g
	DoubleLinkedList<Pair> m_List[bucketSize];

private:
	/*********************************************************
	* @brief		��d�T���ŗv�f���擾
	* @details		�n�b�V���l�ƃL�[�ɂ���āA�v�f�������o���B
	* @param[in]	key: �v�f�̃L�[�A�n�b�V���l�Z�o�p
	* @param[in]	listID: �ڕW�v�f���i�[���Ă��郊�X�g�̓Y����
	* @param[out]	targetIter: �ڕW�v�f���i�[���߂̃C�e���[�^(�ڕW�Ȃ��ꍇ���̃��X�g�̖����C�e���[�^��Ԃ�)
	* @retval		true: �v�f���������ꍇ
	* @retval		false: �v�f�����Ȃ��ꍇ
	********************************************************/
	bool Find(const KeyType& key,const int listID, ListIterator* targetIter=nullptr)const;

	/*********************************************************
	* @brief		�n�b�V���l�Ń��X�g�̓Y�������擾
	* @param[in]	key: �v�f�̃L�[�A�n�b�V���l�Z�o�p
	* @return		�L�[�ɉ����郊�X�g�̓Y����
	********************************************************/
	int GetListID(const KeyType& key)const;

public:
	/*********************************************************
	* @brief	�f�[�^�}��
	* @details	���X�g�ɗv�f���ǉ������B
	*			�����n�b�V���l�̗v�f�̃`�F�C���������ō쐬�����B
	* @param	key: �v�f�̃L�[�A�n�b�V���l�Z�o�p
	* @param	value: �v�f�̒l
	* @retval	true: �}�������̏ꍇ	
	* @retval	false: �}�����s�̏ꍇ
	********************************************************/
	bool Add(const KeyType& key,const ValueType value);

	/*********************************************************
	* @brief		�f�[�^�폜
	* @details		�n�b�V���֐����Ăяo���Ċi�[�ʒu�𒲂ׂāA
	*				���̈ʒu�ɂ���A�����X�g�����ǂ邱�ƂŁA
	*				�ړI�̗v�f�������o���č폜����B(��d�T��)
	*				��ł���ꍇ�Ɏ��s�B
	* @param		key: �v�f�̃L�[�A�n�b�V���l�Z�o�p
	* @retval		true: �폜�����̏ꍇ
	* @retval		false: �폜���s�̏ꍇ
	********************************************************/
	bool Remove(const KeyType& key);

	/*********************************************************
	* @brief		�f�[�^����
	* @details		�n�b�V���֐����Ăяo���Ċi�[�ʒu�𒲂ׂāA
	*				���̈ʒu�ɂ���A�����X�g�����ǂ邱�ƂŁA
	*				�ړI�̗v�f�������o���č폜����B(��d�T��)
	* @param[in]	key: �v�f�̃L�[�A�n�b�V���l�Z�o�p
	* @param[out]	pOut: �v�f���擾���邽�߂̃|�C���^
	* @retval		true: ���������̏ꍇ
	* @retval		false: �������s�̏ꍇ
	********************************************************/
	bool TryGetValue(const KeyType& key, ValueType* pOut = nullptr)const;

	//const ���\�b�h

	/*********************************************************
	* @brief	�v�f�����擾����
	* @return	�v�f����Ԃ�
	********************************************************/
	const int Count() const;

};

#include "HashTable.inl"

