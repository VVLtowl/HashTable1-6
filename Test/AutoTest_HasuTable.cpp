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
			HashTable<int, std::string, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

			//�}��
			EXPECT_TRUE(table.Add(1, "val1"));
			EXPECT_TRUE(table.Add(2, "val2"));
			//����
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_FALSE(table.TryGetValue(3));
			//�폜
			EXPECT_FALSE(table.Remove(3));
			EXPECT_TRUE(table.Remove(1));
		}

		//����Z�ł��܂�l���n�b�V���l�Ƃ���
		{
			HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;

			//�}��
			EXPECT_TRUE(table.Add(1, "val1"));
			EXPECT_TRUE(table.Add(2, "val2"));
			//����
			EXPECT_TRUE(table.TryGetValue(1));
			EXPECT_TRUE(table.TryGetValue(2));
			//�폜
			EXPECT_TRUE(table.Remove(2));
			EXPECT_TRUE(table.Remove(1));
		}

		SUCCEED();
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
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}


	/*********************************************************
	* @brief		�v�f��}��������̖߂�l
	* @details		ID:0-3
	* 				�v�f��}��������̖߂�l��1�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, AfterAdd)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		table.Add(1, 1);
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�v�f��}�����A���̃L�[�ō폜������̖߂�l
	* @details		ID:0-4
	* 				�v�f��}�����A���̃L�[�ō폜������̖߂�l��0�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, AfterAddAndRemove)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 2);
		EXPECT_EQ(1, table.Count());

		table.Remove(1);
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���ɑ��݂���L�[�ŗv�f�̑}���������s������̖߂�l
	* @details		ID:0-5
	* 				���ɑ��݂���L�[�ŗv�f�̑}���������s������̖߂�l��1�ł��邩���`�F�b�N�B
	*				�P��}��������A���̃L�[�ōēx�}������B
	********************************************************/
	TEST(HashTableCountTest, WhenAddFailedWithSameKey)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 2);
		EXPECT_EQ(1, table.Count());
		EXPECT_FALSE(table.Add(1, 3));
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɗv�f�����鎞�ɑ��݂��Ȃ��L�[���w�肵�v�f�̍폜�Ɏ��s�����ۂ̖߂�l
	* @details		ID:0-6
	* 				���X�g�ɗv�f�����鎞�ɑ��݂��Ȃ��L�[���w�肵�v�f�̍폜�Ɏ��s�����ۂ̖߂�l��1�ł��邩���`�F�b�N�B
	*				�P��}��������A�قȂ�L�[�ō폜����B
	********************************************************/
	TEST(HashTableCountTest, WhenRemoveFailedWithWrongKey)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		table.Add(1, 1);
		EXPECT_FALSE(table.Remove(2));
		EXPECT_EQ(1, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g����ł���ꍇ�ɁA�폜���s������̖߂�l
	* @details		ID:0-7
	* 				���X�g����ł���ꍇ�ɁA�폜���s������̖߂�l��0�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, WhenEmptyList_RemoveFailed)
	{
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		EXPECT_FALSE(table.Remove(1));
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����̖߂�l
	* @details		ID:0-8
	* 				�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����̖߂�l��2�ł��邩���`�F�b�N�B
	*				�`�F�C���ɂ���ėv�f���������ω����Ȃ����Ƃ��`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, TwoElementsNotChain)
	{
		//�L�[�̒l���̂܂܃n�b�V���l�Ƃ���
		HashTable<int, int, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

		//�����n�b�V���l�o�Ȃ��悤�ȃL�[�Œǉ�
		table.Add(1, 1);
		table.Add(2, 2);
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����Ɉ�����폜������̖߂�l
	* @details		ID:0-9
	* 				�v�f�Q�������Ń`�F�C���ɂȂ��Ă��Ȃ����Ɉ�����폜������̖߂�l��1�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableCountTest, TwoElementsNotChain_AfterRemove)
	{
		//�L�[�̒l���̂܂܃n�b�V���l�Ƃ���
		HashTable<int, int, HashFunc_IntKey, TEST_BUCKET_SIZE> table;

		//�����n�b�V���l�o�Ȃ��悤�ȃL�[�Œǉ�
		table.Add(1, 1);
		table.Add(2, 2);
		EXPECT_EQ(2, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(1, table.Count());
		SUCCEED();
	}

	/*********************************************************
	* @brief		�v�f�Q�������Ń`�F�C���ɂȂ�����̖߂�l
	* @details		ID:0-10
	* 				�v�f�Q�������Ń`�F�C���ɂȂ�����̖߂�l��2�ł��邩���`�F�b�N�B
	*				�`�F�C����H��Ă��Ȃ��ꍇ��1���Ԃ��Ă���͂��B
	*				�����n�b�V���l�̕ʃL�[��}���B
	********************************************************/
	TEST(HashTableCountTest, TwoElementsChain)
	{
		//0���n�b�V���l�Ƃ���
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		//�`�F�C���ɂȂ�v�f��p��
		table.Add(1, 1);//�n�b�V���l��0
		table.Add(2, 2);//�n�b�V���l��0
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�v�f�Q�������Ń`�F�C���ɂȂ��Ă��鎞�Ɉ�����폜������̖߂�l
	* @details		ID:0-11
	* 				�v�f�Q�������Ń`�F�C���ɂȂ��Ă��鎞�Ɉ�����폜������̖߂�l��1�ł��邩���`�F�b�N�B
	*				�`�F�C����H��Ă��Ȃ��ꍇ��1���Ԃ��Ă���͂��B
	*				�����n�b�V���l�̕ʃL�[��}���B
	********************************************************/
	TEST(HashTableCountTest, TwoElementsChain_AfterRemove)
	{
		//0���n�b�V���l�Ƃ���
		HashTable<int, int, HashFunc_Zero, TEST_BUCKET_SIZE> table;

		//�`�F�C���ɂȂ�v�f��p��
		table.Add(1, 1);//�n�b�V���l��0
		table.Add(2, 2);//�n�b�V���l��0
		EXPECT_EQ(2, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(1, table.Count());
		SUCCEED();
	}
#pragma endregion

#pragma region ========== �f�[�^�̑}�� ==========
	
	using HashTableAddTest_F = HashTableFixture;

	/*********************************************************
	* @brief		���X�g����ł���ꍇ�ɁA�}�������ۂ̋���
	* @details		ID:0-13
	*				���X�g����ł���ꍇ�ɁA�}�������ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�A
	*				���X�g�ɗv�f���ǉ�����邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableAddTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());
		
		EXPECT_TRUE(table.Add(1, "val1"));
		
		EXPECT_TRUE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����Ȃ��ő}�������ۂ̋���
	* @details		ID:0-14
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����Ȃ��ő}�������ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�A
	*				���X�g�ɗv�f���ǉ�����邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_NotDuplicate)
	{
		EXPECT_TRUE(table.Add(4, "val4"));
		
		EXPECT_TRUE(table.TryGetValue(4));

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����đ}�����悤�Ƃ����ۂ̋���
	* @details		ID:0-15
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA�L�[���d�����đ}�����悤�Ƃ����ہA
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_Duplicate)
	{
		EXPECT_FALSE(table.Add(2, "val4"));
		
		std::string value;
		EXPECT_TRUE(table.TryGetValue(2,&value));
		EXPECT_EQ("val2", value);

		SUCCEED();
	}

	/*********************************************************
	* @brief		���Ƀ��X�g�ɂ���v�f�ƃn�b�V���l�������ɂȂ�L�[�ő}�������ۂ̋���
	* @details		ID:0-16
	*				���Ƀ��X�g�ɂ���v�f�ƃn�b�V���l�������ɂȂ�L�[�ő}�������ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�A
	*				���X�g�ɗv�f���ǉ�����邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableAddTest_F, WhenManyElements_SameHash)
	{
		EXPECT_EQ(3, HashFunc_IntMod()(13));//�n�b�V���l��3
		EXPECT_TRUE(table.Add(13, "val4"));
		
		EXPECT_TRUE(table.TryGetValue(13));

		SUCCEED();
	}

	/*********************************************************
	* @brief		��x�}�����A�폜������ēx�����L�[�ő}�������ۂ̋���
	* @details		ID:0-17
	*				��x�}�����A�폜������ēx�����L�[�ő}�������ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�A
	*				�폜�R��Ƃ���O�������ςɓ����Ă��Ȃ����m�F�B
	********************************************************/
	TEST_F(HashTableAddTest_F, AfterAddAndRemove)
	{
		EXPECT_TRUE(table.Add(4, "val4"));
		EXPECT_TRUE(table.Remove(4));

		EXPECT_FALSE(table.TryGetValue(4));

		EXPECT_TRUE(table.Add(4, "val4"));
		EXPECT_TRUE(table.TryGetValue(4));

		SUCCEED();
	}

#pragma endregion

#pragma region ========== �f�[�^�̍폜 ==========

	using HashTableRemoveTest_F = HashTableFixture;

	/*********************************************************
	* @brief		���X�g����ł���ꍇ�ɁA�폜��������悤�Ƃ����ۂ̋���
	* @details		ID:0-19
	*				���X�g����ł���ꍇ�ɁA�폜��������悤�Ƃ����ہA
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableRemoveTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_IntMod, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, table.Count());

		EXPECT_FALSE(table.Remove(1));

		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�č폜�����ۂ̋���
	* @details		ID:0-20
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�č폜�����ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableRemoveTest_F, WhenManyElements)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		EXPECT_TRUE(table.Remove(1));
		EXPECT_FALSE(table.TryGetValue(1));
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�č폜���悤�Ƃ����ۂ̋���
	* @details		ID:0-21
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�č폜���悤�Ƃ����ہA
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableRemoveTest_F, WhenManyElements_NonexistentKey)
	{
		EXPECT_EQ(3, table.Count());

		EXPECT_FALSE(table.TryGetValue(4));
		EXPECT_FALSE(table.Remove(4));//���݂��Ȃ��L�[
		
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		��x�폜�����L�[�ōēx�폜���悤�Ƃ����ۂ̋���
	* @details		ID:0-22
	*				��x�폜�����L�[�ōēx�폜���悤�Ƃ����ہA
	*				�폜�R�ꓙ�̃~�X���Ȃ����`�F�b�N�B
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveAgain)
	{
		EXPECT_EQ(3, table.Count());
		EXPECT_TRUE(table.TryGetValue(3));

		//�폜�����L�[�ōēx�폜
		EXPECT_TRUE(table.Remove(3));
		EXPECT_FALSE(table.Remove(3));

		EXPECT_FALSE(table.TryGetValue(3));
		EXPECT_EQ(2, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�`�F�C���ɂȂ��Ă���v�f������1�̃L�[���w�肵�č폜�����ۂ̋���
	* @details		ID:0-23
	*				�`�F�C���ɂȂ��Ă���v�f������1�̃L�[���w�肵�č폜�����ہA
	*				�w�肵���v�f�������폜����A�`�F�C�����q���Ȃ������B
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveChainElement)
	{
		//�����n�b�V���l�̃L�[�ŁA�`�F�C�������
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13,"val4"));
		EXPECT_EQ(4, table.Count());

		EXPECT_TRUE(table.TryGetValue(3));
		EXPECT_TRUE(table.Remove(3));

		EXPECT_TRUE(table.TryGetValue(13));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�`�F�C���ɂȂ��Ă���v�f�ƃn�b�V���l�����������A���݂��Ȃ��L�[���w�肵�č폜�����ۂ̋���
	* @details		ID:0-24
	*				�`�F�C���ɂȂ��Ă���v�f�ƃn�b�V���l�����������A���݂��Ȃ��L�[���w�肵�č폜�����ہA
	*				�n�b�V���l�ƃL�[�ɂ���d�������@�\���Ă��邩�`�F�b�N�B
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableRemoveTest_F, RemoveChainElement_NonexistentKey)
	{
		//�����n�b�V���l�̃L�[�ŁA�`�F�C�������
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		//�`�F�C���ɂȂ��Ă���v�f�ƃn�b�V���l�����������A���݂��Ȃ��L�[
		EXPECT_EQ(HashFunc_IntMod()(23), HashFunc_IntMod()(3));
		EXPECT_FALSE(table.TryGetValue(23));
		EXPECT_FALSE(table.Remove(23));

		EXPECT_EQ(4, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		�`�F�C���ɂȂ��Ă���v�f�����ɍ폜���Ă������ۂ̋���
	* @details		ID:0-25
	*				�`�F�C���ɂȂ��Ă���v�f�����ɍ폜���Ă������ہA
	*				�`�F�C�����O�ꂽ�肵�č폜�ł��Ȃ���ԂɂȂ�Ȃ����ǂ����A
	*				�S�Đ���ɗv�f���폜����邩���`�F�b�N�B
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableRemoveTest, RemoveChainElement_NonexistentKey)
	{
		//0���n�b�V���l�Ƃ���A�`�F�C���ɂȂ�v�f��p��
		HashTable<int, std::string, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_EQ(0, HashFunc_Zero()(1));
		EXPECT_TRUE(table.Add(1, "val1"));
		EXPECT_EQ(0, HashFunc_Zero()(2));
		EXPECT_TRUE(table.Add(2, "val2"));
		EXPECT_EQ(0, HashFunc_Zero()(3));
		EXPECT_TRUE(table.Add(3, "val3"));
		EXPECT_EQ(3, table.Count());

		//���ɍ폜
		EXPECT_TRUE(table.Remove(1));
		EXPECT_TRUE(table.Remove(2));
		EXPECT_TRUE(table.Remove(3));
		EXPECT_EQ(0, table.Count());

		SUCCEED();
	}

#pragma endregion

#pragma region ========== �f�[�^�̌��� ==========

	using HashTableTryGetValueTest_F = HashTableFixture;

	/*********************************************************
	* @brief		���X�g����ł���ꍇ�ɁA�L�[���w�肵�Č��������ۂ̋���
	* @details		ID:0-27
	*				���X�g����ł���ꍇ�ɁA�L�[���w�肵�Č��������ہA
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST(HashTableTryGetValueTest, WhenEmptyList)
	{
		HashTable<int, std::string, HashFunc_Zero, TEST_BUCKET_SIZE> table;
		EXPECT_FALSE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�Č��������ۂ̋���
	* @details		ID:0-28
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA���݂���L�[�Ŏw�肵�Č��������ہA
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, WhenManyElements)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�Č��������ۂ̋���
	* @details		ID:0-29
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA���݂��Ȃ��L�[�Ŏw�肵�Č��������ہA
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, WhenManyElements_NonexistentKey)
	{
		EXPECT_FALSE(table.TryGetValue(4));//���݂��Ȃ��L�[4
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���X�g�ɕ����̗v�f������ꍇ�ɁA�����L�[��2�A���Ō��������ۂ̋���
	* @details		ID:0-30
	*				���X�g�ɕ����̗v�f������ꍇ�ɁA�����L�[��2�A���Ō��������ہA
	*				�����v�f��2��Ƃ������o�R�œn�����A�ςɍ폜����Ă����肵�Ȃ����`�F�b�N�B
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, TryGetValueAgain)
	{
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_TRUE(table.TryGetValue(1));
		EXPECT_EQ(3, table.Count());

		SUCCEED();
	}

	/*********************************************************
	* @brief		���ɍ폜���ꂽ�L�[�Ō��������ۂ̋���
	* @details		ID:0-31
	*				���ɍ폜���ꂽ�L�[�Ō��������ہA
	*				�폜�R��Ƃ����Ȃ����`�F�b�N�B
	* 				�߂�l��false�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, AfterRemove)
	{
		EXPECT_TRUE(table.Remove(1));
		EXPECT_EQ(2, table.Count());

		EXPECT_FALSE(table.TryGetValue(1));

		SUCCEED();
	}

	/*********************************************************
	* @brief		�`�F�C���ɂȂ��Ă���v�f�̓���1�̃L�[���w�肵�Č��������ۂ̋���
	* @details		ID:0-32
	*				�`�F�C���ɂȂ��Ă���v�f�̓���1�̃L�[���w�肵�Č��������ہA
	*				�w�肵���L�[�̗v�f�������o�R�œn����āA
	*				�n�b�V���l�ƃL�[�ɂ���d�������@�\���Ă��邩�`�F�b�N�B
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, ChainElement)
	{
		//�����n�b�V���l�̃L�[�ŁA�`�F�C�������
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		std::string value;
		EXPECT_TRUE(table.TryGetValue(13, &value));

		EXPECT_EQ("val4", value);

		SUCCEED();
	}

	/*********************************************************
	* @brief		�`�F�C���ɂȂ��Ă���v�f������1�̍폜������ɁA�c���Ă���v�f�����������ۂ̋���
	* @details		ID:0-33
	*				�`�F�C���ɂȂ��Ă���v�f������1�̍폜������ɁA�c���Ă���v�f�����������ہA
	*				�w�肵���L�[�̗v�f�������o�R�œn����邩���`�F�b�N�B
	* 				�߂�l��true�ł��邩���`�F�b�N�B
	********************************************************/
	TEST_F(HashTableTryGetValueTest_F, AfterRemove_OtherElementInSameChain)
	{
		//�����n�b�V���l�̃L�[�ŁA�`�F�C�������
		EXPECT_EQ(HashFunc_IntMod()(13), HashFunc_IntMod()(3));
		EXPECT_TRUE(table.Add(13, "val4"));
		EXPECT_EQ(4, table.Count());

		//�`�F�C���ɂȂ��Ă���v�f������1�̍폜
		EXPECT_TRUE(table.Remove(3));

		//�c���Ă���v�f������
		std::string value;
		EXPECT_TRUE(table.TryGetValue(13, &value));

		EXPECT_EQ("val4", value);

		SUCCEED();
	}

#pragma endregion

#endif
}