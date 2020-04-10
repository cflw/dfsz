#pragma once
#include <cassert>
#include <atomic>
namespace 东方山寨 {
//对象数组计数
class C数组计数 {
public:
	C数组计数(size_t a数量) : m数量(a数量) {
		m计数 = 0;
	}
	void f加计数() {
		//assert(m计数 < m段数量);
		++m计数;
		m加变化 = true;
	}
	void f减计数() {
		assert(m计数 > 0);
		--m计数;
		m减变化 = true;
	}
	size_t fg计数() const {
		return m计数;
	}
	bool fi变化() const {
		return m加变化 || m减变化;
	}
	bool fi加变化() const {
		return m加变化;
	}
	bool fi减变化() const {
		return m减变化;
	}
	void f无变化() {
		m加变化 = false;
		m减变化 = false;
	}
	void f无加变化() {
		m加变化 = false;
	}
	void f无减变化() {
		m减变化 = false;
	}
	void f重置() {
		m计数 = 0;
		f无变化();
	}
	operator size_t() {
		return m计数;
	}
private:
	const size_t m数量;
	std::atomic<size_t> m计数;
	bool m加变化 = false, m减变化 = false;
};
}	//namespace 东方山寨