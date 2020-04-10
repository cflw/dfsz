﻿#include "游戏.h"
#include "图形_图片.h"
#include "图形工厂.h"
#include "图形_画图片.h"
namespace 东方山寨 {
void C画图片动画::f显示图片(const t向量2 &a坐标, const tp纹理 &a纹理, const S顶点矩形 *a顶点, const I动画 &a动画) {	//废弃
	f显示图片3(a纹理, a顶点[a动画.f接口_g顶点序号()], a坐标, a动画.f接口_g旋转(), a动画.f接口_g缩放(), a动画.f接口_g透明度());
}
void C画图片动画::f显示图片(const t向量2 &a坐标, const tp纹理 &a纹理, const S顶点矩形 *a顶点, const S动画缓冲 &a动画) {
	f显示图片3(a纹理, a顶点[a动画.m顶点序号], a坐标, a动画.m旋转, a动画.m缩放, a动画.m透明度);
}
void C画图片动画::f显示图片2(const tp纹理 &a纹理, const S顶点矩形 &a顶点, const t向量2 &a平移, float a旋转, const t向量2 &a缩放, float a透明) {
	auto &v画图片 = C游戏::fg图形().fg画图片();
	v画图片.fs纹理(a纹理);
	v画图片.fs坐标(a平移);
	v画图片.fs透明度(a透明);
	v画图片.f变换_重置();
	v画图片.f变换_旋转(a旋转);
	v画图片.f变换_缩放(a缩放.x, a缩放.y);
	v画图片.f画图片(a顶点);
}
void C画图片动画::f显示图片3(const tp纹理 &a纹理, const S顶点矩形 &a顶点, const t向量2 &a平移, const t向量3 &a旋转, const t向量3 &a缩放, float a透明) {
	auto &v画图片 = C游戏::fg图形().fg画图片();
	v画图片.fs纹理(a纹理);
	v画图片.fs坐标(a平移);
	v画图片.fs透明度(a透明);
	v画图片.f变换_重置();
	v画图片.f变换_旋转(a旋转);
	v画图片.f变换_缩放(a缩放.x, a缩放.y);
	v画图片.f画图片(a顶点);
}
//==============================================================================
// 顶点动画
//==============================================================================
void C图片动画图形::f初始化_父对象(const void *a父) {
	const S图片动画属性 &v属性 = fg图片动画属性();
	m动画 = v属性.fc动画(a父);
}
const S顶点矩形 &C图片动画图形::fg顶点矩形() const {
	const S图片动画属性 &v属性 = fg图片动画属性();
	return v属性.m顶点[m动画->f接口_g顶点序号()];
}
//==============================================================================
// 图形缓冲
//==============================================================================
C图片动画图形缓冲::C图片动画图形缓冲() {
}
C图片动画图形缓冲::C图片动画图形缓冲(const C图片动画图形 &a):
	m属性(&a.fg图片动画属性()) {
}
void C图片动画图形缓冲::f初始化_图形(const C图片动画图形 &a) {
	m属性 = &a.fg图片动画属性();
}
void C图片动画图形缓冲::f显示() const {
	C画图片动画::f显示图片(m坐标, *m属性->m纹理, m属性->m顶点.m指针, *this);
}
//==============================================================================
// 顶点动画属性
//==============================================================================
std::shared_ptr<I动画> S图片动画属性::fc动画(const void *a父) const {
	std::shared_ptr<I动画> v = m动画->f接口_新建s();
	if (a父) {
		v->f接口_s父对象(a父);
	}
	return v;
}
//==============================================================================
// 快速图片动画
//==============================================================================
void C二维图片图形::f接口_计算() {
	this->f事件_执行();
	f计算_运动();
	f计算_生命();
}
void C二维图片图形::f兼容显示() const {
	f显示图片();
}
void C二维图片图形::f接口_初始化(const S图形参数 &a参数) {
	I粒子::f接口_初始化(a参数);
	m纹理 = a参数.m纹理.m指针;
	assert(m纹理);
	m顶点 = a参数.m顶点.m指针;
}
t向量3 C二维图片图形::f接口_g旋转() const {
	return {0, 0, m旋转};
}
t向量3 C二维图片图形::f接口_g缩放() const {
	return {m缩放.x, m缩放.y, 1};
}
float C二维图片图形::f接口_g透明度() const {
	return fg反生命百分比();
}
bool C二维图片图形::fi纹理() const {
	return m纹理 != nullptr;
}
const S顶点矩形 &C二维图片图形::fg顶点矩形() const {
	return m顶点[0];
}
void C二维图片图形::f显示图片() const {
	C画图片动画::f显示图片(m坐标, *m纹理, m顶点, *this);
}
//==============================================================================
// 快速图片动画
//==============================================================================
void C三维图片图形::f接口_计算() {
	this->f事件_执行();
	f计算_运动();
	f计算_生命();
}
void C三维图片图形::f兼容显示() const {
	f显示图片();
}
void C三维图片图形::f接口_初始化(const S图形参数 &a参数) {
	I粒子::f接口_初始化(a参数);
	m纹理 = a参数.m纹理.m指针;
	assert(m纹理);
	m顶点 = a参数.m顶点.m指针;
}
t向量3 C三维图片图形::f接口_g旋转() const {
	return m旋转;
}
t向量3 C三维图片图形::f接口_g缩放() const {
	return m缩放;
}
float C三维图片图形::f接口_g透明度() const {
	return fg反生命百分比();
}
bool C三维图片图形::fi纹理() const {
	return m纹理 != nullptr;
}
const S顶点矩形 &C三维图片图形::fg顶点矩形() const {
	return m顶点[0];
}
void C三维图片图形::f显示图片() const {
	C画图片动画::f显示图片(m坐标, *m纹理, m顶点, *this);
}
}