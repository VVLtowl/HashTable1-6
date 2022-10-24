/*********************************************************
* @brief		�n�b�V���l�����߂�֐��̃w�b�_�[
* @date			2022/10/21
********************************************************/
#pragma once

#define TEST_BUCKET_SIZE (10)

// @brief		�������Ȃ�
class HashFunc_NoArg
{
public:
	int operator()()
	{
		return 0;
	}
};

// @brief		�L�[�̌^��int�A������0���n�b�V���l�Ƃ���
class HashFunc_Zero
{
public:
	int operator()(int key)
	{
		return 0;
	}
};

// @brief		�L�[�̌^��int�A�L�[�̌^���n�b�V���l�Ƃ���
class HashFunc_IntKey
{
public:
	int operator()(int key)
	{
		return key;
	}
};

// @brief		�L�[�̌^��int�A�L�[�ƃT�C�Y����Z�̗]����n�b�V���l�Ƃ���
class HashFunc_IntMod
{
public:
	int operator()(int key)
	{
		return key % TEST_BUCKET_SIZE;
	}
};