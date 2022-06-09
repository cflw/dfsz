#include <cflw数学_分辨率.h>
#include "程序实现.h"
#include "边框常量.h"
namespace 东方山寨 {
namespace 数学 = cflw::数学;
//==============================================================================
// 程序
//==============================================================================
std::unique_ptr<C程序实现> C程序::m实现;
void C程序::f初始化(HINSTANCE p) {
	m实现 = std::make_unique<C程序实现>(p);
	m实现->f创建窗口();
	m实现->f初始化();
}
void C程序::f运行() {
	m实现->f运行();
}
void C程序::f销毁() {
	m实现.reset();
}
C游戏 &C程序::fg游戏() {
	return *m实现->m游戏;
}
C输入引擎 &C程序::fg输入() {
	return *m实现->m输入;
}
C图形引擎 &C程序::fg图形() {
	return *m实现->m图形;
}
C音频引擎 &C程序::fg音频() {
	return *m实现->m音频;
}
C界面图形控制 &C程序::fg界面图形() {
	return *m实现->m界面图形;
}
void C程序::f输入法开关(bool a) {
	m实现->f输入法开关(a);
}
int C程序::fg渲染间隔() {
	return m实现->m渲染间隔;
}
void C程序::f切换游戏状态(E游戏状态 a状态) {
	m实现->f切换游戏状态(a状态);
}
void C程序::f游戏中弹出菜单(E窗口 a窗口) {
	m实现->f游戏中弹出菜单(a窗口);
}
void C程序::fs游戏标志(int a标志, bool a值) {
	m实现->m标志[a标志] = a值;
}
void C程序::f日志(int a级别, const std::wstring &a文本) {
	m实现->f日志(a级别, a文本);
}
void C程序::fs全屏(bool a) {
	m实现->fs全屏(a);
}
void C程序::fs窗口大小(int a宽, int a高) {
	m实现->fs窗口大小(a宽, a高);
}
std::pair<int, int> C程序::fg窗口大小() {
	return {m实现->m窗口大小[0], m实现->m窗口大小[1]};
}
std::pair<float, float> C程序::fg标准窗口大小() {
	return 数学::分辨率::f小边相同({m实现->m窗口大小[0], m实现->m窗口大小[1]}, {c标准尺寸x, c标准尺寸y});
}
}	//namespace 东方山寨
//==============================================================================
// 主函数
//==============================================================================
using 东方山寨::C程序;
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int) {
	C程序::f初始化(hInst);
	C程序::f运行();
	C程序::f销毁();
}