#pragma once
#include <vector>
#include <functional>
#include <mutex>
#include <algorithm>
#include <iterator>
#include "基础.h"
namespace 东方山寨 {
template<typename t值>
class C缓冲数组 {
public:
	using t指针 = std::unique_ptr<t值>;
	void f清空() {
		ma缓冲.clear();
		ma新建.clear();
	}
	template<typename t派生 = t值, typename...t参数>
	t派生 *f新建(t参数&&...a参数) {
		std::unique_ptr<t派生> v指针0 = std::make_unique<t派生>(std::forward<t参数>(a参数)...);
		t派生 *const v指针1 = v指针0.get();
		std::lock_guard<std::mutex> v锁(m新建锁);
		ma新建.push_back(std::move(v指针0));
		return v指针1;
	}
	void f更新() {
		f更新_删除不使用对象();
		f更新_合并新对象();
	}
	void f更新_删除不使用对象() {
		ma缓冲.erase(std::remove_if(ma缓冲.begin(), ma缓冲.end(), [](const t指针 &a指针)->bool {
			return !a指针->f对象_i使用();
			}), ma缓冲.end());
	}
	void f更新_合并新对象() {
		std::move(ma新建.begin(), ma新建.end(), std::back_inserter(ma缓冲));
		ma新建.clear();
	}
	void f排序() {
		std::sort(ma缓冲.begin(), ma缓冲.end());
	}
	void f排序(const std::function<bool(const t值 &, const t值 &)> &af比较) {
		std::sort(ma缓冲.begin(), ma缓冲.end(), [&af比较](const t指针 &a, const t指针 &b)->bool {
			return af比较(*a, *b);
		});
	}
	std::vector<t指针> ma缓冲;
	std::vector<t指针> ma新建;
	std::mutex m新建锁;
};
}