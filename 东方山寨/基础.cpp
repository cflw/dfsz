﻿#include "游戏常量.h"
#include "基础.h"
#include "游戏.h"
#include "程序.h"
namespace 东方山寨 {
//=============================================================================
// 自动编号
//=============================================================================
void C自动编号::f重置() {
	m编号 = 0;
}
int C自动编号::f新编号() {
	return ++m编号;
}
//=============================================================================
// 经过的时间
//=============================================================================
C游戏速度::C游戏速度(float a速度) : m速度{a速度} {
	f内部计算();
}
void C游戏速度::f内部计算() {
	m秒 = c帧秒<float> * m速度;
}
void C游戏速度::fs速度(float a速度) {
	m速度 = a速度;
	f内部计算();
}
float C游戏速度::fg速度() const {
	return m速度;
}
float C游戏速度::fg秒() const {
	return m秒;
}
float C游戏速度::fg帧() const {
	return m速度;
}
float C游戏速度::fg渲染秒() const {
	return m秒 * C程序::fg渲染间隔();
}
float C游戏速度::fg渲染帧() const {
	return m速度 * C程序::fg渲染间隔();
}
//=============================================================================
// 循环计算
//=============================================================================
const t标志 C循环计算::c标准计数{};
const t标志 C循环计算::c自然计数{f计算位(e首次自增)};
const t标志 C循环计算::c中间插值{f计算位(e首次自增) + f计算位(e小数) + f计算位(e去除末尾)};
const t标志 C循环计算::c小数{f计算位(e小数)};	//包含头尾
const t标志 C循环计算::c小数居中{f计算位(e小数) + f计算位(e居中)};	//[-0.5, 0.5]
const t标志 C循环计算::c计数居中{f计算位(e居中)};
const t标志 C循环计算::c圆形{f计算位(e首次自增) + f计算位(e小数)};
t标志 C循环计算::fc标准(bool a首次, bool a居中, bool a百分比) {
	return t标志{f计算位(a首次, e首次自增) + f计算位(a居中, e居中) + f计算位(a百分比)};
}
t标志 C循环计算::fc插值(bool a头, bool a尾) {
	return t标志{f计算位(e小数) + f计算位(!a头, e首次自增) + f计算位(!a尾, e去除末尾)};
}
t标志 C循环计算::fc居中(bool a百分比) {
	return t标志{f计算位(e居中) + f计算位(a百分比, e小数)};
}
unsigned int C循环计算::f计算位(int i) {
	return 1u << i;
}
unsigned int C循环计算::f计算位(bool w, int i) {
	if (w) {
		return f计算位(i);
	}
	return 0;
}
float C循环计算::f计算(int a计数, int a总数, t标志 a标志) {
	float v循环 = (float)a总数;
	float v = (float)a计数;
	if (a标志[e首次自增]) {
		v += 1;
	} else {
		v循环 -= 1;
	}
	if (a标志[e去除末尾]) {
		v循环 += 1;
	}
	if (a标志[e居中]) {
		v -= v循环 / 2;
	}
	if (a标志[e小数]) {
		v /= v循环;
	}
	return v;
}
//=============================================================================
// 基础
//=============================================================================
C计时器::C计时器(float a时间, float a滴答):
	m滴答(a滴答), m计时(a时间) {
}
bool C计时器::f滴答() {
	m滴答 += c帧秒<float>;
	if (m滴答 >= m计时) {
		m滴答 = 0;
		return true;
	} else {
		return false;
	}
}
void C计时器::f停止() {
	m计时 = 999;
}
void C计时器::f重置(float a时间, float a滴答) {
	m滴答 = a滴答;
	m计时 = a时间;
}
C单次计时器::C单次计时器(float a时间):
	m滴答(0), m计时(a时间) {
}
bool C单次计时器::f滴答() {
	if (m滴答 < m计时) {
		m滴答 += c帧秒<float>;
		return m滴答 >= m计时;
	} else {
		return false;
	}
}
void C单次计时器::f重置(float a时间) {
	m滴答 = 0;
	m计时 = a时间;
}

}	//namespace 东方山寨