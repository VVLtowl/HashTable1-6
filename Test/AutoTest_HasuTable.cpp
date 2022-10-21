/*********************************************************
* @brief		�n�b�V���e�[�u���̒P�̃e�X�g
* @date			2022/10/21
********************************************************/
#include "gtest/gtest.h"
#include "../HashTable/HashTable.h"
#include "../HashTable/ScoreData.h"
#include "../HashTable/HashFunc.h"
#include "TestTool.h"


//�n�b�V���e�[�u���̒P�̃e�X�g���s
#define GT_AUTO_TEST_HASHTABLE

namespace ex01_HashTable
{
#if defined GT_AUTO_TEST_HASHTABLE

#pragma region ========== �N���X�̋��� ==========


	/*********************************************************
	* @brief		�Z�o���@�̈قȂ�K�؂ȃn�b�V���֐���n�����Ƃ��̂��ꂼ��̋���
	* @details		ID:0-1
	* 				�}���A�����A�폜���s���A�S�Ă̖߂�l��TRUE�ɂȂ邩�`�F�b�N�B
	********************************************************/
	TEST(HashTableClassTest, CorrectHashFunc)
	{
		//�L�[�̒l���̂܂܃n�b�V���l�Ƃ���
		{
			HashTable<int, int, HashFunc_IntKey, 8> table;

			//�}��
			EXPECT_TRUE(table.Add(1, 1));
			EXPECT_TRUE(table.Add(2, 2));
			//����
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_FALSE(table.TryGetValue(3));
			//�폜
			EXPECT_FALSE(table.Remove(3));
			EXPECT_TRUE(table.Remove(1));
		}

		//����Z�ł��܂�l���n�b�V���l�Ƃ���
		{
			HashTable<int, int, HashFunc_IntMod, 8> table;

			//�}��
			EXPECT_TRUE(table.Add(1, 1));
			EXPECT_TRUE(table.Add(2, 2));
			//����
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_TRUE(table.TryGetValue(2));
			//�폜
			EXPECT_TRUE(table.Count()==2);
			EXPECT_TRUE(table.Remove(2));
			EXPECT_TRUE(table.Remove(1));
		}
	}

#pragma endregion

#pragma region ========== �f�[�^���̎擾 ==========

	/*********************************************************
	* @brief		���X�g����ł���ꍇ�̖߂�l
	* @details		ID:0-2
	* 				���X�g����ł���ꍇ�̖߂�l��0�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, WhenEmptyList)
	{
		SUCCEED();
	}


	/*********************************************************
	* @brief		�v�f��}��������̖߂�l
	* @details		ID:0-3
	* 				�v�f��}��������̖߂�l��1�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, AfterAdd)
	{
		SUCCEED();
	}

#pragma endregion

#endif
}