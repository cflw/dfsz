#include "边框常量.h"
#include "敌机制造机.h"
#include "敌机基础.h"
import 东方山寨.敌机图形;
namespace 东方山寨 {
constexpr int c敌机标识 = 660212840;	//0x275a0c68
//==============================================================================
// 参数
//==============================================================================
void S敌机参数::fs坐标(const t向量2 &a坐标) {
	m坐标 = a坐标;
}
void S敌机参数::fs坐标_边框外(const t向量2 &a坐标) {
	constexpr float c向外 = 32;
	if (a坐标.x >= 0) {
		m坐标.x = c边框范围x + c向外;
	} else {
		m坐标.x = -c边框范围x - c向外;
	}
	if (a坐标.y >= 0) {
		m坐标.y = c边框范围y + c向外;
	} else {
		m坐标.y = -c边框范围y - c向外;
	}
}
void S敌机参数::fs边框外进场(const t向量2 &a坐标) {
	constexpr float c向外 = 32;
	bool v无移动 = false;
	m目标 = a坐标;
	if (a坐标.x <= -c框架范围x) {
		m坐标.x = -c框架范围x - c向外;
		m目标.x = -c框架范围x + c向外;
	} else if (a坐标.x >= c框架范围x) {
		m坐标.x = c框架范围x + c向外;
		m目标.x = c框架范围x - c向外;
	} else if (a坐标.x <= -c边框范围x) {
		m坐标.x = -c边框范围x - c向外;
		m目标.x = -c边框范围x + c向外;
	} else if (a坐标.x >= -c边框范围x) {
		m坐标.x = c边框范围x + c向外;
		m目标.x = c边框范围x + c向外;
	} else {
		m坐标.x = a坐标.x;
		v无移动 = true;
	}
	if (a坐标.y <= -c框架范围y) {
		m坐标.y = -c框架范围y - c向外;
		m目标.y = -c框架范围y + c向外;
	} else if (a坐标.y >= c框架范围y) {
		m坐标.y = c框架范围y + c向外;
		m目标.y = c框架范围y - c向外;
	} else if (a坐标.y <= -c边框范围y) {
		m坐标.y = -c边框范围y - c向外;
		m目标.y = -c边框范围y + c向外;
	} else if (a坐标.y >= c边框范围y) {
		m坐标.y = c边框范围x + c向外;
		m目标.y = c边框范围y - c向外;
	} else {
		m坐标.y = a坐标.y;
		v无移动 |= true;
	}
	if (v无移动) {
		m移动时间 = 0;
	} else {
		m移动时间 = 1;
	}
}
void S敌机参数::fs进场(const t向量2 &a开始, const t向量2 &a结束, float a时间) {
	m坐标 = a开始;
	const t向量2 v坐标差 = a结束 - a开始;
	m速度 = v坐标差 / a时间;
	m移动时间 = a时间;
}
void S敌机参数::fs移动速度(const t向量2 &a速度, float a时间) {
	m速度 = a速度;
	m移动时间 = a时间;
}
void S敌机参数::fs移动到_时间(const t向量2 &a目标, float a时间) {
	m速度 = t向量2::c零;
	m目标 = a目标;
	m移动时间 = a时间;
}
void S敌机参数::fs移动到_速度(const t向量2 &a目标, float a速度) {
	m目标 = t向量2::c零;
	const t向量2 v坐标差 = a目标 - m坐标;
	m移动时间 = v坐标差.fg大小() / a速度;
	m速度 = v坐标差 / m移动时间;
}
//==============================================================================
// 实现
//==============================================================================
void C敌机制造机::f初始化_环境(const C游戏速度 &a) {
	m游戏速度 = &a;
}
void C敌机制造机::f初始化_数组(C对象数组<C敌机> &aa敌机, C缓冲数组<I图形缓冲> &aa缓冲) {
	ma敌机 = &aa敌机;
	ma图形缓冲 = &aa缓冲;
}
void C敌机制造机::f初始化_资源(const C属性数组<S敌机属性> &aa属性) {
	ma敌机属性 = &aa属性;
}
void C敌机制造机::f编译参数(S敌机参数 &a参数) const {
	auto &v样式 = a参数.m样式;
	if (v样式.fi需编译()) {
		ma敌机属性->f编译(v样式);
	}
	if (!v样式) {	//没有指定样式,使用默认样式
		v样式.m指针 = ma敌机属性->fg指针(c敌机标识);
	}
}
void C敌机制造机::f产生敌机0(const std::shared_ptr<C敌机> &a敌机, const S敌机参数 &a参数) const {
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
		a敌机->f运动_速度(a参数.m速度, 0);
	}
	auto &v样式 = a参数.m样式;
	a敌机->m敌机属性 = v样式.m指针;
	a敌机->fs生命值(a参数.m生命值);
	a敌机->fs无敌时间(a参数.m无敌时间);
	a敌机->f事件_初始化();
	assert(a敌机->m生命值.m当前 > 0);
	if (v样式->m纹理.m指针) {
		a敌机->m图形 = std::make_unique<C敌机图形_图片>(*a敌机, *ma图形缓冲);
	} else {
		a敌机->m图形 = std::make_unique<C敌机图形_线条>(*a敌机, *ma图形缓冲);
	}
	a敌机->f对象_使用();
	ma敌机->f添加(a敌机);
}
bool C敌机制造机::fi有空() const {
	return ma敌机->fi有空();
}
std::shared_ptr<C敌机> C敌机制造机::f产生王(S敌机参数 &a敌机参数) const {
	std::shared_ptr<C敌机> v王 = f产生敌机<C敌机>(a敌机参数);
	if (v王) {
		v王->m标志[C敌机::E标志::e王] = true;
	}
	return v王;
}
}	//namespace 东方山寨