#include "游戏设置.h"
namespace 东方山寨 {
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
	m关卡标识 = a;
}
void S游戏设置::fs游戏模式(E游戏模式 a游戏模式) {
	m游戏模式 = a游戏模式;
}
}	//namespace 东方山寨