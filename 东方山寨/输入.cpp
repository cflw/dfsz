#include "输入.h"
#include "数学包含.h"
namespace 东方山寨 {
C输入引擎::C输入引擎() {
}
void C输入引擎::f初始化(HWND a窗口, float a缩放) {
	m输入w.f初始化(a窗口, a缩放);
	m输入w.f创建键盘(m键盘);
	m输入w.f创建鼠标(m鼠标);
	m输入x.f创建手柄(m手柄);
	//键盘映射
	m方向键[0].fs正反键((输入::t索引)E按键::e右, (输入::t索引)E按键::e左);
	m方向键[1].fs正反键((输入::t索引)E按键::e上, (输入::t索引)E按键::e下);
	for (const auto &[v输出, v输入] : ca键盘映射) {
		m键盘映射[(输入::t索引)v输出] = (输入::t索引)v输入;
	}
	for (const auto &[v输出, v输入] : ca手柄映射) {
		m手柄映射[(输入::t索引)v输出] = (输入::t索引)v输入;
	}
}
void C输入引擎::f更新() {
	m输入w.f更新();
	m输入x.f更新();
	//按键
	m按键组.f覆盖上次();
	m按键组.f清空这次();
	输入::C按键映射::f更新关联l(m按键组, *m键盘, m键盘映射.begin(), m键盘映射.end());
	输入::C按键映射::f更新关联l(m按键组, *m手柄, m手柄映射.begin(), m手柄映射.end());
	//方向
	m方向键[0].f更新(m按键组);
	m方向键[1].f更新(m按键组);
	m手柄方向 = m手柄->f方向((int)输入x::E手柄方向::e左摇杆);
}
const 输入::C按键组 &C输入引擎::fg按键组() const {
	return m按键组;
}
输入::S方向 C输入引擎::fg方向() const {
	const float x = 数学::f绝对值最大值(m方向键[0].m方向, m手柄方向.x);
	const float y = 数学::f绝对值最大值(m方向键[1].m方向, m手柄方向.y);
	if (输入::fi死区3(x, y, 0, m死区)) {
		return {0, 0, 0};
	} else {
		return {x, y, 0};
	}
}
void C输入引擎::fs缩放(float a) {
	m输入w.fs缩放(a);
}
void C输入引擎::fs死区(float a) {
	m死区 = a;
}
}	//namespace 东方山寨