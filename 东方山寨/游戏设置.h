#pragma once
#include "标识.h"
namespace 东方山寨 {
struct S游戏设置 {
	void fs自机(int);
	void fs子机(int);
	void fs炸弹(int);
	void fs基础难度(int 一);
	void fs增加难度(int 分子, int 分母 = 1);
	int m自机标识 = (int)E自机::e测试;
	int m子机标识 = (int)E子机::e测试;
	int m炸弹标识 = (int)E玩家发射::e测试炸弹;
	int m残机 = 2;
	int m炸弹 = 3;
	int m火力 = 1;
	int m最大点 = 10'0000;
	int m基础难度 = 1;
	int m增加难度 = 0;
};
}