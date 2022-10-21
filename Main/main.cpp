/*********************************************************
* @brief	クイックソートの後表示
* @date		2022/10/17
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "../HashTable/DoubleLinkedList.h"
#include "../HashTable/ScoreData.h"
#include "../HashTable/CompareScoreData.h"

/*********************************************************
* @brief	イテレートして「格納した順で」標準出力
* @param	list: 表示したいScoreDataの双方向リスト
********************************************************/
void PrintList(const DoubleLinkedList<ScoreData>& list)
{
	auto it = list.CBegin();
	auto end = list.CEnd();

	for (; it != end; ++it)
	{
		std::cout
			<< (*it).name
			<< ((*it).name.size() < 8 ? "\t\t:" : "\t:")//整列するためです
			<< (*it).score
			<< std::endl;
	}
}

/*********************************************************
* @brief	メイン関数
********************************************************/
int main(void)
{
	//データを格納するためのリストを用意
	DoubleLinkedList<ScoreData> list;	

	//ファイルを読み込み、データを格納 
	{
		FILE* fp; 
		char fileName[] = "Scores.txt";

		//ファイルを開く、失敗すると終了
		{
			fp = fopen(fileName, "r");
			if (fp == NULL) {
				std::cout << fileName << "file open error!" << std::endl;
				return -1;
			}
			else {
				std::cout << fileName << "file opened!" << std::endl;
			}
		}

		
		//ループで1行ずつ読み取った内容をデータに格納、
		//内容が取らない場合ループ終了
		{
			int score;					//スコアデータを一時格納用
			char name[WORD_SIZE];		//名前データを一時格納用

			while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
#if 0
				//1行ずつ読み取った内容を確認
				std::cout << name << ":" << score << std::endl;//test
#endif

				//スコアデータを作成して、データを格納
				ScoreData data(score, name);
				auto iter = list.End();
				list.Insert(iter, data);
			}
		}
		

		//ファイルを閉じる
		fclose(fp);
	}

	//スコア昇順でソート
	{
		std::cout << "\n\n========== スコア昇順 ==========\n\n";
		list.Sort(ScoreGreater());

		//イテレートして「格納した順で」標準出力に表示
		PrintList(list);
	}

	


	//スコア降順でソート
	{
		std::cout << "\n\n========== スコア降順 ==========\n\n";
		list.Sort(ScoreLess());

		//イテレートして「格納した順で」標準出力に表示
		PrintList(list);
	}

	//名前昇順でソート
	{
		std::cout << "\n\n========== 名前昇順 ==========\n\n";
		list.Sort(NameGreater());

		//イテレートして「格納した順で」標準出力に表示
		PrintList(list);
	}

	//名前降順でソート
	{
		std::cout << "\n\n========== 名前降順 ==========\n\n";
		list.Sort(NameLess());

		//イテレートして「格納した順で」標準出力に表示
		PrintList(list);
	}

	//エンターキーを押して終了
	(void)getchar();
	return 0;
}

