/*********************************************************
* @brief		ハッシュ値を求める関数のヘッダー
* @date			2022/10/21
********************************************************/
#pragma once

// @brief		引数がない
class HashFunc_NoArg
{
public:
	int operator()()
	{
		return 0;
	}
};

// @brief		キーの型はint、ずっと0をハッシュ値とする
class HashFunc_IntZero
{
public:
	int operator()(int key, int size)
	{
		return 0;
	}
};

// @brief		キーの型はint、キーの型をハッシュ値とする
class HashFunc_IntKey
{
public:
	int operator()(int key, int size)
	{
		return 0;
	}
};

// @brief		キーの型はint、キーとサイズ割り算の余りをハッシュ値とする
class HashFunc_IntMod
{
public:
	int operator()(int key, int size)
	{
		return key % size;
	}
};