﻿#include "游戏常量.h"
#include "敌机制造机.h"
#include "敌机基础.h"
#include "游戏.h"
namespace 东方山寨 {
//==============================================================================
// 参数
//==============================================================================
void C敌机制造机::S参数::fs坐标(const t向量2 &a坐标) {
	const float c向外 = 32;
	bool v无移动 = false;
	m目标 = a坐标;
	if (a坐标.x == -c框架范围x) {
		m坐标.x = -c框架范围x - c向外;
		m目标.x = -c框架范围x + c向外;
	} else if (a坐标.x == c框架范围x) {
		m坐标.x = c框架范围x + c向外;
		m目标.x = c框架范围x - c向外;
	} else if (a坐标.x == -c边框范围x) {
		m坐标.x = -c边框范围x - c向外;
		m目标.x = -c边框范围x + c向外;
	} else if (a坐标.x == -c边框范围x) {
		m坐标.x = c边框范围x + c向外;
		m目标.x = c边框范围x + c向外;
	} else {
		m坐标.x = a坐标.x;
		v无移动 = true;
	}
	if (a坐标.y == -c框架范围y) {
		m坐标.y = -c框架范围y - c向外;
		m目标.y = -c框架范围y + c向外;
	} else if (a坐标.y == c框架范围y) {
		m坐标.y = c框架范围y + c向外;
		m目标.y = c框架范围y - c向外;
	} else if (a坐标.y == -c边框范围y) {
		m坐标.y = -c边框范围y - c向外;
		m目标.y = -c边框范围y + c向外;
	} else if (a坐标.y == -c边框范围y) {
		m坐标.y = c边框范围x + c向外;
		m目标.y = c边框范围y - c向外;
	} else {
		m坐标.y = a坐标.y;
		v无移动 &= true;
	}
	if (v无移动) {
		m移动时间 = 0;
	} else {
		m移动时间 = 1;
	}
}
void C敌机制造机::S参数::fs速度(const t向量2 &a速度, float a时间) {
	m速度 = a速度;
	m移动时间 = a时间;
}
void C敌机制造机::S参数::fs目标(const t向量2 &a目标, float a时间) {
	m速度 = t向量2::c零;
	m目标 = a目标;
	m移动时间 = a时间;
}
//==============================================================================
// 实现
//==============================================================================
void C敌机制造机::C实现::f初始化_环境(const C游戏速度 &a) {
	m游戏速度 = &a;
}
void C敌机制造机::C实现::f初始化_数组(C对象数组<C敌机> &aa) {
	ma敌机 = &aa;
}
void C敌机制造机::C实现::f初始化_资源(const C属性数组<S敌机属性> &aa) {
	ma敌机属性 = &aa;
}
void C敌机制造机::C实现::f产生敌机(std::shared_ptr<C敌机> a敌机, S参数 &a参数) {
	a敌机->m坐标 = a参数.m坐标;
	a敌机->m计数指针 = &ma敌机->m计数;
	a敌机->m游戏速度 = m游戏速度;
	if (a参数.m移动时间 > 0) {
		if (a参数.m速度.fg大小() > 0) {
			a敌机->f运动_速度(a参数.m速度, a参数.m移动时间);
		} else {
			a敌机->f运动_平滑移动到(a参数.m目标, a参数.m移动时间, 0, a参数.m移动时间 / 2);
		}
	} else {
		a敌机->f运动_速度(t向量2::c零, 0);
	}
	auto &v样式 = a参数.m样式;
	if (v样式.fi需编译()) {
		ma敌机属性->f编译(v样式);
	}
	a敌机->m敌机属性 = v样式.m指针;
	a敌机->m动画 = v样式->m动画->f新建u();
	a敌机->fs生命值(a参数.m生命值);
	a敌机->f事件_初始化();
	assert(a敌机->m生命值.m当前 > 0);
	a敌机->f对象_使用();
	ma敌机->f添加(a敌机);
}
bool C敌机制造机::C实现::fi有空() const {
	return ma敌机->fi有空();
}
//==============================================================================
// 外壳
//==============================================================================
C敌机制造机::C敌机制造机(C实现 &a) :
	m实现{&a} {
}
std::shared_ptr<C敌机> C敌机制造机::f产生王() {
	std::shared_ptr<C敌机> v王 = f产生敌机<C敌机>();
	if (v王) {
		v王->m标志[C敌机::E标志::e王] = true;
	}
	return v王;
}
}