#include "游戏设置.h"
namespace 东方山寨 {
void C游戏设置::fs自机(int a) {
	m自机标识 = a;
}
void C游戏设置::fs子机(int a) {
	m子机标识 = a;
}
void C游戏设置::fs炸弹(int a) {
	m炸弹标识 = a;
}
void C游戏设置::fs基础难度(int a) {
	m基础难度 = a;
}
void C游戏设置::fs增加难度(int a分子, int a分母) {
	m增加难度 = a分子 * 100'0000 / a分母;
}
void C游戏设置::fs关卡编号(int a) {
	m关卡编号 = a;
}
void C游戏设置::fs符卡编号(int a) {
	m符卡编号 = a;
}
void C游戏设置::fs进入关卡(C关卡 &a关卡) {
	m关卡 = &a关卡;
	ma关卡 = &m关卡;
	m关卡数量 = 1;
}
void C游戏设置::fs进入关卡(C关卡 *const *aa关卡, size_t a数量) {
	m关卡 = aa关卡[0];
	ma关卡 = aa关卡;
	m关卡数量 = a数量;
}
void C游戏设置::fs游戏模式(E游戏模式 a游戏模式) {
	m游戏模式 = a游戏模式;
}
}	//namespace 东方山寨