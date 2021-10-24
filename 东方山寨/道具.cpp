#include <boost/rational.hpp>
#include "道具.h"
#include "玩家.h"
#include "计算.h"
#include "预设图形.h"
#include "道具图形.h"
#include "边框形状.h"
namespace 东方山寨 {
//==============================================================================
// 道具
//==============================================================================
C道具::C道具() {
}
C道具::~C道具() {
}
void C道具::f对象_使用() {
	m标志[e使用] = true;
	m计数指针->f加计数();
	//初始化
	m速度.x = 0;
	m速度.y = -c最大下落速度;
	m速度插值 = 0;
}
void C道具::f对象_销毁() {
	assert(m标志[e使用]);	//禁止重复销毁
	m标志.reset();
	m计数指针->f减计数();
	m图形->fg图形缓冲().f对象_销毁();
}
bool C道具::f对象_i使用() {
	return m标志[e使用];
}
void C道具::f计算() {
	const float v秒 = m游戏速度->fg秒();
	if (m跟随玩家) {	//跟随
		m跟随进度 += m跟随速度 * v秒;
		const t向量2 &v自机坐标 = m跟随玩家->m自机.m坐标;
		const float v方向 = m坐标.f到点方向r(v自机坐标);
		const t向量2 v目标速度 = t向量2::fc方向r(c跟随加速度 * m跟随进度, v方向);
		m速度 = v目标速度;
	} else {	//非跟随
		m速度.y -= c下落加速度 * v秒;
		if (边框::C矩形::c标准.f左边判断(m坐标, 0)) {
			m速度.x += c侧移加速度 * v秒;
		} else if (边框::C矩形::c标准.f右边判断(m坐标, 0)) {
			m速度.x -= c侧移加速度 * v秒;
		}
		//限速
		if (m速度.fg大小() > c最大下落速度) {
			m速度.fs大小(c最大下落速度);
		}
	}
	m速度插值 = 数学::f线性渐变<float>(m速度插值, 1, v秒 / c初始速度渐变时间);
	f计算运动();
	m图形->f计算();
}
void C道具::f更新() {
	m图形->f更新();
}
t圆形 C道具::fg判定点() const {
	auto &v道具属性 = fg道具属性();
	return t圆形{m坐标, v道具属性.m判定半径};
}
const S道具属性 &C道具::fg道具属性() const {
	return *m道具属性;
}
void C道具::f效果(C玩家 &a玩家) {
	auto &v道具属性 = fg道具属性();
	std::lock_guard<std::mutex> v锁(a玩家.m成绩锁);
	v道具属性.mf效果(v道具属性, a玩家);
}
bool C道具::fi在窗口外() const {
	auto &v道具属性 = fg道具属性();
	return 边框::C矩形::c窗口.f下边判断(m坐标, v道具属性.m判定半径);
}
void C道具::fs跟随(C玩家 *a玩家, float a时间) {
	m跟随玩家 = a玩家;
	if (a时间 <= 0) {
		m跟随进度 = 1;
		m跟随速度 = 1;
	} else {
		m跟随进度 = 0.5f;
		m跟随速度 = 1 * a时间;
	}
}
bool C道具::fi跟随() const {
	return m跟随玩家 != nullptr;
}
void C道具::f计算运动() {
	const t向量2 v实际速度 = 数学::f插值<t向量2>(m初始速度, m速度, m速度插值);
	计算::f基本运动计算(m坐标, v实际速度, m游戏速度->fg秒());
}
//==============================================================================
// 道具效果
//==============================================================================
namespace 道具效果 {
void f得分_固定(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m得分 += a属性.m值;
}
void f得分_最大点(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m得分 += static_cast<long long>(a玩家.m成绩.m最大点) * a属性.m值;
}
void f残机_十分之一(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m残机 += boost::rational<int>(a属性.m值, 10);
}
void f炸弹_十分之一(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m炸弹 += boost::rational<int>(a属性.m值, 10);
}
void f火力_百分之一(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m火力 += boost::rational<int>(a属性.m值, 100);
}
void f最大点(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m最大点 += a属性.m值;
}
}	//namespace 道具效果
}	//namespace 东方山寨