#pragma once
#include "标识.h"
namespace 东方山寨 {
class C关卡;
enum class E游戏模式 {
	e传统模式,
	e完美模式,
	e关卡练习,
	e弹幕练习,
	e录像回放,	//从录像文件输入按键
};
struct S游戏设置 {	//表示游戏初始设置,只能在游戏外修改,进入游戏后不可修改
	int m自机标识 = (int)E自机::e测试;
	int m子机标识 = (int)E子机::e测试;
	int m炸弹标识 = (int)E玩家发射::e测试炸弹;
	int m残机 = 2;
	int m炸弹 = 3;
	int m火力 = 1;
	int m最大点 = 10'0000;
	int m基础难度 = 1;
	int m增加难度 = 0;
	int m关卡编号 = 0;
	int m符卡编号 = 0;
	C关卡 *m关卡 = nullptr;
	C关卡 *const *ma关卡 = nullptr;
	size_t m关卡数量 = 1;
	E游戏模式 m游戏模式;
	//函数
	void fs自机(int);
	void fs子机(int);
	void fs炸弹(int);
	void fs基础难度(int 一);
	void fs增加难度(int 分子, int 分母 = 1);
	void fs关卡编号(int);
	void fs符卡编号(int);
	void fs进入关卡(C关卡 &);
	void fs进入关卡(C关卡 *const *, size_t 数量);
	void fs游戏模式(E游戏模式);
};
}	//namespace 东方山寨