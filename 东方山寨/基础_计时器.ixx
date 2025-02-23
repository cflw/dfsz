module;
#include <cassert>
#include "游戏常量.h"
export module 东方山寨.基础_计时器;
export namespace 东方山寨 {
//重复滴答的计时器
class C计时器 {
public:
	static constexpr float c立即滴答 = 9999;
	C计时器(float a间隔 = 1, float a开始 = 0):
		m计时(a开始), m间隔(a间隔) {
		assert(a间隔 > 0);
	}
	bool f滴答() {
		m计时 += c帧秒<float>;
		if (m计时 >= m间隔) {
			m计时 = 0;
			return true;
		} else {
			return false;
		}
	}
	void f停止() {
		m间隔 = 999;
	}
	void f重置(float a时间, float a滴答 = 0) {
		assert(a时间 > 0);
		m计时 = a滴答;
		m间隔 = a时间;
	}
	void f单次等待(float a等待) {	//等待一个时间后滴答,之后恢复到正常时间
		m计时 = m间隔 - a等待;
	}
private:
	float m计时;
	float m间隔;
};
//滴答一次后就停止的计时器,可以通过重置来实现重复使用
class C单次计时器 {
public:
	C单次计时器(float a时间 = 1):
		m计时(0), m到期(a时间) {
	}
	bool f滴答() {
		if (m计时 < m到期) {
			m计时 += c帧秒<float>;
			return m计时 >= m到期;
		} else {
			return false;
		}
	}
	void f重置(float a时间) {
		m计时 = 0;
		m到期 = a时间;
	}
private:
	float m计时;
	float m到期;
};
}	//namespace 东方山寨