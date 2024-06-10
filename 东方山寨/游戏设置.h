#pragma once
#include "标识.h"
namespace 东方山寨 {
enum class E游戏模式 {
	e无,
	e传统模式,
	e完美模式,
	e关卡练习,
	e弹幕练习,
	e录像回放,	//从录像文件输入按键
};
struct S游戏设置 {	//表示游戏初始设置,只能在游戏外修改,进入游戏后不可修改
	int m自机标识;
	int m子机标识;
	int m炸弹标识;
	int m残机;
	int m炸弹;
	int m火力;
	int m最大点;
	int m基础难度;
	int m增加难度;
	int m关卡;	//进入关卡,和关卡组同时有值时优先选择单个关卡
	int m关卡组;
	E游戏模式 m游戏模式;
	//函数
	S游戏设置() = default;	//空
	static S游戏设置 fc测试();
	static S游戏设置 fc默认();
	void fs自机(int);
	void fs子机(int);
	void fs炸弹(int);
	void fs基础难度(int 一);
	void fs增加难度(int 分子, int 分母 = 1);
	void fs关卡(int 标识);
	void fs关卡组(int 标识);
	void fs游戏模式(E游戏模式);
};
}	//namespace 东方山寨