#include "游戏设置.h"
namespace 东方山寨 {
constexpr int c初始残机 = 2;
constexpr int c初始炸弹 = 3;
constexpr int c初始最大点 = 10'0000;
S游戏设置 S游戏设置::fc测试() {
	S游戏设置 v;
	v.m自机标识 = (int)E自机::e测试;
	v.m子机标识 = (int)E子机::e测试;
	v.m炸弹标识 = (int)E玩家发射::e测试炸弹;
	v.m残机 = 9;
	v.m炸弹 = 9;
	v.m火力 = 4;
	v.m最大点 = c初始最大点;
	v.m基础难度 = 1;
	v.m增加难度 = 0;
	v.m关卡 = 0;
	v.m关卡组 = 0;
	v.m游戏模式 = E游戏模式::e无;
	return v;
}
S游戏设置 S游戏设置::fc默认() {
	S游戏设置 v;
	v.m自机标识 = (int)E自机::e测试;
	v.m子机标识 = (int)E子机::e测试;
	v.m炸弹标识 = (int)E玩家发射::e测试炸弹;
	v.m残机 = c初始残机;
	v.m炸弹 = c初始炸弹;
	v.m火力 = 1;
	v.m最大点 = c初始最大点;
	v.m基础难度 = 1;
	v.m增加难度 = 0;
	v.m关卡 = 0;
	v.m关卡组 = 0;
	v.m游戏模式 = E游戏模式::e无;
	return v;
}
void S游戏设置::fs自机(int a) {
	m自机标识 = a;
}
void S游戏设置::fs子机(int a) {
	m子机标识 = a;
}
void S游戏设置::fs炸弹(int a) {
	m炸弹标识 = a;
}
void S游戏设置::fs基础难度(int a) {
	m基础难度 = a;
}
void S游戏设置::fs增加难度(int a分子, int a分母) {
	m增加难度 = a分子 * 100'0000 / a分母;
}
void S游戏设置::fs关卡(int a) {
	m关卡 = a;
}
void S游戏设置::fs关卡组(int a) {
	m关卡组 = a;
	m关卡 = 0;
}
void S游戏设置::fs游戏模式(E游戏模式 a游戏模式) {
	m游戏模式 = a游戏模式;
}
}	//namespace 东方山寨