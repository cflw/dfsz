﻿#include "游戏.h"
#include "图形引擎.h"
#include "预设图形.h"
namespace 东方山寨::图形 {
//==============================================================================
// 圆形
//==============================================================================
void C圆形::C图形缓冲::f显示() const {
	auto &v画图形 = C游戏::fg图形().fg画图形();
	v画图形.fs颜色(m颜色);
	v画图形.fs线条宽度(m线条宽度);
	v画图形.f绘制圆形(t圆形(m坐标, m半径));
}
C圆形::C圆形(float a开始, float a结束) :
	m开始半径(a开始), m结束半径(a结束) {
}
void C圆形::f接口_计算() {
	f计算_生命();
}
void C圆形::f接口_更新() {
	C图形缓冲 *v图形缓冲 = (C图形缓冲 *)m图形缓冲;
	v图形缓冲->m半径 = fg当前半径();
	v图形缓冲->m颜色 = t颜色{1, 1, 1, fg反生命百分比()};
	v图形缓冲->m坐标 = m坐标;
}
float C圆形::fg当前半径() const {
	return 数学::f插值<float>(m开始半径, m结束半径, fg生命百分比());
}
//==============================================================================
// 十字
//==============================================================================
void C十字::C图形缓冲::f显示() const {
	auto &v画图形 = C游戏::fg图形().fg画图形();
	v画图形.fs颜色(m颜色);
	v画图形.fs线条宽度(m线条宽度);
	v画图形.f绘制线条(t线段(m坐标 + 数学::S向量2{m半径, 0}, m坐标 + 数学::S向量2{-m半径, 0}));
	v画图形.f绘制线条(t线段(m坐标 + 数学::S向量2{0, m半径}, m坐标 + 数学::S向量2{0, -m半径}));
}
C十字::C十字(float a开始, float a结束):
	m开始半径(a开始), m结束半径(a结束) {
}
void C十字::f接口_计算() {
	f计算_生命();
}
void C十字::f接口_更新() {
	C图形缓冲 *v图形缓冲 = (C图形缓冲 *)m图形缓冲;
	v图形缓冲->m半径 = fg当前半径();
	v图形缓冲->m颜色 = t颜色{1, 1, 1, fg反生命百分比()};
	v图形缓冲->m坐标 = m坐标;
}
float C十字::fg当前半径() const {
	return 数学::f插值<float>(m开始半径, m结束半径, fg生命百分比());
}
}	//namespace 东方山寨::图形