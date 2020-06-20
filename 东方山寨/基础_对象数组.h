#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <iterator>
#include <mutex>
#include <execution>
#include "基础_数组计数.h"
namespace 东方山寨 {
//对象数组: 存放最复杂的计算对象
template<typename t> class C对象数组 {
public:
	using value_type = t;
	using reference = t &;
	using const_reference = const t &;
	using t指针 = std::shared_ptr<t>;
	C对象数组(size_t a数量) : m计数(a数量), m数量上限(a数量) {
		ma对象.reserve(a数量);
	}
	~C对象数组() {
	}
	void f清空() {
		ma对象.clear();
		ma新建.clear();
		m计数.f重置();
		f更新数量();
	}
	void f添加(const t指针 &ap) {
		std::lock_guard<std::mutex> v锁(m互斥锁);
		ma新建.push_back(ap);
	}
	bool fi有空(size_t a数量 = 1) const {
		return m当前数量 + a数量 <= fg上限();
	}
	bool fi无空() const {
		return m当前数量 >= fg上限();
	}
	size_t fg计数() const {
		return m当前数量;
	}
	size_t fg上限() const {
		return m数量上限;
	}
	bool fi变化() const {
		return m计数.fi变化();
	}
	void fe使用(std::function<void(t &)> af) {
		std::for_each(std::execution::seq, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(*ap对象);
			}
		});
	}
	void fe使用p(std::function<void(t指针)> af) {
		std::for_each(std::execution::seq, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(ap对象);
			}
		});
	}
	void fe使用_并行(std::function<void(t &)> af) {
		std::for_each(std::execution::par, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(*ap对象);
			}
		});
	}
	void f更新() {
		f更新_删除不使用对象();
		f更新_合并新对象();
		f更新数量();
		assert(m当前数量 == ma对象.size());
	}
	void f更新_删除不使用对象() {
		if (m计数.fi减变化()) {
			ma对象.erase(std::remove_if(ma对象.begin(), ma对象.end(), [](const t指针 &a指针)->bool {
				return !a指针->f对象_i使用();
				}), ma对象.end());
			m计数.f无减变化();
		}
	}
	void f更新_合并新对象() {
		if (m计数.fi加变化()) {
			assert(!ma新建.empty());
			std::move(ma新建.begin(), ma新建.end(), std::back_inserter(ma对象));
			ma新建.clear();
			m计数.f无加变化();
		} else {
			assert(ma新建.empty());
		}
	}
	void f更新数量() {
		m当前数量 = m计数.fg计数();
	}
	std::vector<t指针> ma对象;
	std::vector<t指针> ma新建;
	const size_t m数量上限;
	size_t m当前数量 = 0;
	C数组计数 m计数;
	std::mutex m互斥锁;
};
}	//namespace 东方山寨