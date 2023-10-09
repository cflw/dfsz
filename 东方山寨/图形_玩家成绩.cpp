﻿#include "图形_玩家成绩.h"
#include "游戏.h"
import 东方山寨.抬显;
namespace 东方山寨 {
//==============================================================================
// 画成绩
//==============================================================================
C画玩家成绩::C画玩家成绩(二维::C二维 &a二维):
	m二维(&a二维), m文本工厂(&a二维.fg文本工厂()) {
}
二维::tp画文本 C画玩家成绩::fc画文本() const {
	return m二维->fc画文本();
}
二维::tp文本效果 C画玩家成绩::fc文本效果(const 数学::S颜色 &a) const {
	return m二维->fc文本效果(a, 数学::S颜色::c白);
}
二维::tp文本布局 C画玩家成绩::fc文本布局(const std::wstring &a文本, 二维::tp文本格式 a格式) const {
	return m文本工厂->fc文本布局(a文本, a格式.Get());
}
二维::tp文本布局 C画玩家成绩::fc文本布局_小数(double a小数, int a小数位数, 二维::tp文本格式 a格式) const {
	return m文本工厂->fc文本布局_小数(a小数, a小数位数, a格式.Get());
}
//==============================================================================
// 实现
//==============================================================================
void C玩家成绩图形实现::f初始化环境(const C画玩家成绩 &a) {
	m画成绩 = &a;
}
void C玩家成绩图形实现::f值变化了() {
	m变化 = 1;
	m文本变化 = true;
}
void C玩家成绩图形实现::f计算() {
	const float v过秒 = C游戏::fg内容().fg游戏速度().fg秒();
	if (m变化 > 0) {
		m变化 -= v过秒;
	}
}
float C玩家成绩图形实现::fg透明度() const {
	return 数学::f插值<float>(0.3f, 1, m变化) * C抬显控制::fg全局透明度();
}
//==============================================================================
// 图形缓冲
//==============================================================================
void C玩家成绩图形缓冲::f初始化(const C画玩家成绩 &a画成绩, float y, 二维::tp文本格式 a格式, const t颜色 &a颜色) {
	m画文本 = a画成绩.fc画文本();
	m文本格式 = a格式;
	m画文本->fs区域(C画玩家成绩::c坐标x, y);
	m画文本->fs颜色(数学::f插值<t颜色>(a颜色, t颜色::c白, 0.5f));
}
void C玩家成绩图形缓冲::f显示() const {
	m画文本->f绘制文本布局(m文本布局.Get());
}
//==============================================================================
// 工厂
//==============================================================================
C玩家成绩图形工厂::C玩家成绩图形工厂(const C图形工厂 &a工厂, const C画玩家成绩 &a画, std::vector<std::shared_ptr<I图形>> &a成绩组):
	m图形工厂(a工厂), m画玩家成绩(&a画), ma玩家成绩(&a成绩组), m图形参数(t图形参数::c游戏抬显) {
}
}	//namespace 东方山寨