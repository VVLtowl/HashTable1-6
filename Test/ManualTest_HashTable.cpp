/*********************************************************
* @brief		�n�b�V���e�[�u���̃e�X�g(�蓮�e�X�g)
* @date			2022/10/21
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/HashTable.h"
#include "../HashTable/HashFunc.h"
#include "ManualTest_HashTable.h"

//�n�b�V���e�[�u���̎蓮�e�X�g���s
#define GT_MANUAL_TEST_HASHTABLE



namespace ex01_HashTable
{
#ifdef  GT_MANUAL_TEST_HASHTABLE

#pragma region ========== HashTable ==========

	/*********************************************************
	* @brief		�s�K�؂ȃn�b�V���֐����e���v���[�g�����œn���ꂽ��
	* @details		ID:0-0
	* 				�R���p�C���G���[���`�F�b�N�B�����e�X�g�����Ȃ��B
	********************************************************/
	TEST(HashTableClassTest, WrongHashFunc)
	{
#ifdef MANUAL_TEST_HASHTABLE_WRONG_HASHFUNC
#if 1
		//�����̂Ȃ��֐��͕s�K��
		{
			HashTable<int, int, HashFunc_NoArg, 8> hashTable;
			hashTable.Add(1, 2);
		}
#endif
#if 1
		//�����̌^�̓L�[�̌^�ƈقȂ�֐��͕s�K��
		{
			HashTable<std::string, int, HashFunc_IntZero, 8> hashTable;
			hashTable.Add("A", 2);
		}
#endif
#endif // MANUAL_TEST_HASHTABLE_WRONG_HASHFUNC
		SUCCEED();
	}

	/*********************************************************
	* @brief		const�̃��\�b�h�ł��邩
	* @details		ID:0-12
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N�B�����e�X�g�����Ȃ��Ă悢�B
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
	* @brief		��const�̃��\�b�h�ł��邩
	* @details		ID:0-18
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ邩���`�F�b�N�B�����e�X�g�����Ȃ��Ă悢�B
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
	* @brief		��const�̃��\�b�h�ł��邩
	* @details		ID:0-26
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ邩���`�F�b�N�B�����e�X�g�����Ȃ��Ă悢�B
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
	* @brief		const�̃��\�b�h�ł��邩
	* @details		ID:0-34
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N�B�����e�X�g�����Ȃ��Ă悢�B
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





