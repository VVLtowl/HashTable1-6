/*********************************************************
* @brief		�n�b�V���l�����߂�֐��̃w�b�_�[
* @date			2022/10/21
********************************************************/
#pragma once

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
class HashFunc_IntZero
{
public:
	int operator()(int key, int size)
	{
		return 0;
	}
};

// @brief		�L�[�̌^��int�A�L�[�̌^���n�b�V���l�Ƃ���
class HashFunc_IntKey
{
public:
	int operator()(int key, int size)
	{
		return 0;
	}
};

// @brief		�L�[�̌^��int�A�L�[�ƃT�C�Y����Z�̗]����n�b�V���l�Ƃ���
class HashFunc_IntMod
{
public:
	int operator()(int key, int size)
	{
		return key % size;
	}
};