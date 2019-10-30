#include <boost/rational.hpp>
#include "游戏.h"
#include "道具.h"
#include "玩家.h"
#include "计算.h"
namespace 东方山寨 {
//==============================================================================
// 道具
//==============================================================================
void C道具::f对象_使用() {
	m标志[e使用] = true;
	m计数指针->f加计数();
	//初始化
	m动画 = m道具属性->fc动画(this);
	m速度.x = 0;
	m速度.y = -c最大下落速度;
	m速度插值 = 0;
}
void C道具::f对象_销毁() {
	assert(m标志[e使用]);	//禁止重复销毁
	m标志.reset();
	m计数指针->f减计数();
	m动画 = nullptr;
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
		if (C边界::c边框.f左边判断(m坐标, 0)) {
			m速度.x += c侧移加速度 * v秒;
		} else if (C边界::c边框.f右边判断(m坐标, 0)) {
			m速度.x -= c侧移加速度 * v秒;
		}
		//限速
		if (m速度.fg大小() > c最大下落速度) {
			m速度.fs大小(c最大下落速度);
		}
	}
	m速度插值 = 数学::f线性渐变<float>(m速度插值, 1, v秒 / c初始速度渐变时间);
	f计算运动();
	m动画->f接口_计算();
}
void C道具::f显示() const {
	if (fi纹理()) {
		f显示图片();
	} else {
		f显示线条();
	}
}
void C道具::f显示线条() const {
	auto &v画图形 = C游戏::fg图形().fg画图形();
	if (m跟随玩家) {
		v画图形.fs颜色({0, 0, 1, 1});
	} else {
		v画图形.fs颜色({1, 1, 1, 1});
	}
	v画图形.fs线条宽度(1);
	v画图形.f绘制圆形(t圆形(m坐标, 3));
}
const S图片动画属性 &C道具::fg图片动画属性() const {
	return fg道具属性();
}
const t向量2 &C道具::fg坐标() const {
	return m坐标;
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
	return C边界::c窗口.f下边判断(m坐标, v道具属性.m判定半径);
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
bool C道具::fw跟随() const {
	return m跟随玩家 != nullptr;
}
void C道具::f计算运动() {
	const t向量2 v实际速度 = 数学::f插值<t向量2>(m初始速度, m速度, m速度插值);
	计算::f基本运动计算(m坐标, v实际速度, m游戏速度->fg秒());
}
//==============================================================================
// 道具制造机
//==============================================================================
void C道具制造机::S参数::fs属性(int a) {
	m道具属性 = a;
}
void C道具制造机::C实现::f初始化_环境(const C游戏速度 &a) {
	m游戏速度 = &a;
}
void C道具制造机::C实现::f初始化_数组(C对象数组<C道具> &a) {
	ma道具 = &a;
}
void C道具制造机::C实现::f初始化_资源(const C属性数组<S道具属性> &a) {
	ma道具属性 = &a;
}
void C道具制造机::C实现::f产生道具(S参数 &a) {
	if (a.m道具属性.fi需编译()) {
		ma道具属性->f编译(a.m道具属性);
	}
	std::shared_ptr<C道具> v道具 = std::make_shared<C道具>();
	v道具->m坐标 = a.m坐标;
	v道具->m初始速度 = a.m速度;
	v道具->m道具属性 = a.m道具属性.m指针;
	if (a.m跟随玩家) {
		v道具->fs跟随(a.m跟随玩家, 1);
	}
	v道具->m游戏速度 = m游戏速度;
	v道具->m计数指针 = &ma道具->m计数;
	v道具->f对象_使用();
	ma道具->f添加(v道具);
}
bool C道具制造机::C实现::fi有空(const t道具数量 a) {
	return ma道具->fi有空(a);
}
C道具制造机::C道具制造机(C实现 &a):
	m实现{&a} {
}
void C道具制造机::f产生道具() {
	if (m实现->fi有空()) {
		m实现->f产生道具(m参数);
	}
}
void C道具制造机::f产生道具(t道具数量 a数量) {
	if (m实现->fi有空(a数量)) {
		const float v最大半径 = log((float)a数量) * C道具::c道具组半径;
		const float v最小半径 = v最大半径 / log(v最大半径);
		const float v间隔弧度 = 数学::c二π<float> / (float)a数量;
		const std::function<float()> fc大小 = C游戏::g内容.f工厂_随机数f(std::uniform_real_distribution<float>(v最小半径, v最大半径));
		float v方向 = C游戏::g内容.f工厂_随机数f(数学::f圆周分布r<float>())();
		for (size_t i = 0; i != a数量; ++i) {
			m参数.m速度 = t向量2::fc方向r(fc大小(), v方向);
			m参数.m速度.y += C道具::c初始上升速度;
			m实现->f产生道具(m参数);
			v方向 += v间隔弧度;
		}
	}
}
void C道具制造机::f产生道具(const t道具组 &a) {
	for (const auto &[v属性, v数量] : a) {
		m参数.fs属性((int)v属性);
		f产生道具(v数量);
	}
}
//==============================================================================
// 道具效果
//==============================================================================
namespace 道具效果 {
void f得分_固定(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m得分 += a属性.m值;
}
void f得分_最大点(const S道具属性 &a属性, C玩家 &a玩家) {
	a玩家.m成绩.m得分 += a玩家.m成绩.m最大点 * a属性.m值;
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