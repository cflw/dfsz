﻿#include "子机图形.h"
#include "子机.h"
namespace 东方山寨 {
//==============================================================================
// 子机图片
//==============================================================================
C子机图形_图片::C子机图形_图片(const C子机 &a对象, C缓冲数组<I图形缓冲> &aa图形缓冲) :
	C对象图形<C子机, C图片动画图形缓冲>(a对象, aa图形缓冲) {
	C图片动画图形::f初始化_父对象(&a对象);
	m图形缓冲->f初始化_图层((int)E图层::e玩家);
	m图形缓冲->f初始化_图形(*this);
}
void C子机图形_图片::f计算() {
	m动画->f接口_计算();
}
void C子机图形_图片::f更新() {
	m动画->f接口_更新();
	*m图形缓冲 = *m动画;
	m图形缓冲->m坐标 = m对象->m坐标;
	m图形缓冲->m透明度 = m对象->fg透明度();
}
const S图片动画属性 &C子机图形_图片::fg图片动画属性() const {
	return *m对象->m子机属性;
}
//==============================================================================
// 子机线条
//==============================================================================
C子机图形_线条::C子机图形_线条(const C子机 &a对象, C缓冲数组<I图形缓冲> &aa图形缓冲) :
	C对象图形<C子机, 图形::C十字::C图形缓冲>(a对象, aa图形缓冲) {
	m图形缓冲->f初始化_图层((int)E图层::e玩家);
}
void C子机图形_线条::f计算() {
}
void C子机图形_线条::f更新() {
	m图形缓冲->m坐标 = m对象->m坐标;
}
}	//namespace 东方山寨