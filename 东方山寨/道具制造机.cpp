#include "游戏.h"
#include "道具制造机.h"
#include "道具图形.h"
namespace 东方山寨 {
//==============================================================================
// 道具制造机
//==============================================================================
void C道具制造机::S参数::fs属性(int a) {
	m道具属性 = a;
}
void C道具制造机::C实现::f初始化_环境(const C游戏速度 &a) {
	m游戏速度 = &a;
}
void C道具制造机::C实现::f初始化_数组(C对象数组<C道具> &aa道具, C缓冲数组<I图形缓冲> &aa图形缓冲) {
	ma道具 = &aa道具;
	ma图形缓冲 = &aa图形缓冲;
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
	if (v道具->m道具属性->m纹理) {	//使用图片
		v道具->m图形 = std::make_unique<C道具图形_图片>(*v道具, *ma图形缓冲);
	} else {	//使用圆形
		v道具->m图形 = std::make_unique<C道具图形_线条>(*v道具, *ma图形缓冲);
	}
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
C道具制造机::C道具制造机(C实现 &a) :
	m实现(&a) {
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
		auto v随机数 = C游戏::fg内容().f工厂_随机数引擎();
		const auto v半径分布 = std::uniform_real_distribution<float>(v最小半径, v最大半径);
		const auto v圆周分布 = 数学::c圆周分布r<float>;
		float v方向 = v圆周分布(v随机数);
		for (size_t i = 0; i != a数量; ++i) {
			m参数.m速度 = t向量2::fc方向r(v半径分布(v随机数), v方向);
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
}	//namespace 东方山寨