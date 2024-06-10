module;
#include <cassert>
#include "游戏常量.h"
export module 东方山寨.基础_计时器;
export namespace 东方山寨 {
class C计时器 {
public:
	static constexpr float c立即滴答 = 9999;
	C计时器(float a时间 = 1, float a滴答 = 0):
		m滴答(a滴答), m计时(a时间) {
		assert(a时间 > 0);
	}
	bool f滴答() {
		m滴答 += c帧秒<float>;
		if (m滴答 >= m计时) {
			m滴答 = 0;
			return true;
		} else {
			return false;
		}
	}
	void f停止() {
		m计时 = 999;
	}
	void f重置(float a时间, float a滴答 = 0) {
		assert(a时间 > 0);
		m滴答 = a滴答;
		m计时 = a时间;
	}
	void f单次等待(float a等待) {	//等待一个时间后滴答,之后恢复到正常时间
		m滴答 = m计时 - a等待;
	}
private:
	float m滴答;
	float m计时;
};
//滴答一次后就停止的计时器
class C单次计时器 {
public:
	C单次计时器(float a时间 = 1):
		m滴答(0), m计时(a时间) {
	}
	bool f滴答() {
		if (m滴答 < m计时) {
			m滴答 += c帧秒<float>;
			return m滴答 >= m计时;
		} else {
			return false;
		}
	}
	void f重置(float a时间) {
		m滴答 = 0;
		m计时 = a时间;
	}
private:
	float m滴答;
	float m计时;
};
}	//namespace 东方山寨