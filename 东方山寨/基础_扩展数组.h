#pragma once
#include <cassert>
#include <vector>
#include <map>
#include "基础_数组指针.h"
#include "游戏_名称标识.h"
namespace 东方山寨 {
template<typename t值> class C扩展数组 : public std::map<int, std::unique_ptr<t值>> {
public:
	using value_type = t值;
	using reference = t值 &;
	using const_reference = const t值 &;

	typedef std::map<int, std::unique_ptr<t值>> t基类;
	typedef t扩展指针<t值> t指针;
	typedef C缓存指针<const t值> t缓存指针;
	C扩展数组() {
		f添加(0, nullptr);
	}
	void f添加(int a键, t值 *a值) {
		if (a键 == 0) {
			assert(t基类::operator[](a键) == nullptr);
		} else {
			assert(!fi存在(a键));
		}
		t基类::operator[](a键).reset(a值);
	}
	template<typename t派生, typename...t参数>
	void f构造(int a键, t参数 &&...a参数) {
		static_assert(std::is_base_of<t值, t派生>::value, "t派生 必须是 t值 的基类");
		f添加(a键, new t派生(a参数...));
	}
	std::unique_ptr<t值> &f取空(int a键) {
		assert(t基类::find(a键) == t基类::end());
		return t基类::operator[](a键);
	}
	t指针 f找(int a键) const {
		assert(fi存在(a键));
		return t指针(a键, fg扩展(a键));
	}
	t值 *fg扩展(int a键) const {
		assert(fi存在(a键));
		return t基类::at(a键).get();
	}
	bool fi存在(int a键) const {
		return t基类::find(a键) != t基类::end();
	}
	void f编译(t指针 &a指针) {
		if (a指针.fi需解析名称()) {
			a指针.m整数 = C全局名称标识::f解析(a指针.m名称);
		}
		a指针.m指针 = fg扩展(a指针.m整数);
	}
};
}	//namespace 东方山寨