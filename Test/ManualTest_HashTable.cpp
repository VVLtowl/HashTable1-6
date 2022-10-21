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

#pragma endregion



#endif 
}





