/*********************************************************
* @brief		ハッシュ値を求める関数のヘッダー
* @date			2022/10/21
********************************************************/
#pragma once

#define TEST_BUCKET_SIZE (10)

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
class HashFunc_Zero
{
public:
	int operator()(int key)
	{
		return 0;
	}
};

// @brief		キーの型はint、キーの型をハッシュ値とする
class HashFunc_IntKey
{
public:
	int operator()(int key)
	{
		return key;
	}
};

// @brief		キーの型はint、キーとサイズ割り算の余りをハッシュ値とする
class HashFunc_IntMod
{
public:
	int operator()(int key)
	{
		return key % TEST_BUCKET_SIZE;
	}
};