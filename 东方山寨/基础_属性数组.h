#pragma once
#include <cassert>
#include <vector>
#include <map>
#include <memory>
#include <wrl.h>
#include "基础_数组指针.h"
#include "游戏_名称标识.h"
namespace 东方山寨 {
using Microsoft::WRL::ComPtr;
template<typename t值> class C属性数组;
template<typename t> const ComPtr<t> &f取属性数组数据指针(const C属性数组<ComPtr<t>> &, int);
template<typename t> const std::shared_ptr<t> &f取属性数组数据指针(const C属性数组<std::shared_ptr<t>> &, int);
template<typename t> const t *f取属性数组数据指针(const C属性数组<t> &, int);
template<typename t值> class C属性数组 {
public:
	using value_type = t值;
	using reference = t值 &;
	using const_reference = const t值 &;
	using t指针 = t属性指针<t值>;
	C属性数组() = default;
	auto operator [](const std::wstring &) const->decltype(f取属性数组数据指针(std::declval<C属性数组<t值>>(), 0));
	void f添加(int a键, const t值 &a值) {
		assert(fi不存在(a键));
		ma映射.emplace(a键, ma数据.size());
		ma数据.push_back(a值);
	}
	//void f添加(int a键, const std::initializer_list<t值> &aa值) {
	//	assert(fi不存在(a键));
	//	int i = 0;
	//	for (const auto &v值 : aa值) {
	//		ma映射.emplace(计算::f键(a键, i++), ma数据.size());
	//		ma数据.push_back(v值);
	//	}
	//}
	template<typename...t参数>
	void f构造(int a键, t参数 &&...a参数) {
		assert(fi不存在(a键));
		ma映射.emplace(a键, ma数据.size());
		ma数据.emplace_back(a参数...);
	}
	void f引用(int a键0, int a键1) {
		assert(fi不存在(a键0));
		ma映射.emplace(a键0, ma映射.at(a键1));
	}
	t值 &f取空(int a键) {
		assert(fi不存在(a键));
		ma映射[a键] = ma数据.size();
		ma数据.emplace_back();
		return ma数据.back();
	}
	t指针 f找(int a键) const {
		if (a键) {
			assert(fi存在(a键));
			return t指针(a键, fg指针(a键));
		} else {
			return t指针{};
		}
	}
	const t值 &fg数据(int a键) const {
		assert(fi存在(a键));
		const int v位置 = ma映射.at(a键);
		return ma数据[v位置];
	}
	const t值 *fg指针(int a键) const {
		if (a键) {
			assert(fi存在(a键));
			const int v位置 = ma映射.at(a键);
			return ma数据.data() + v位置;
		} else {
			return nullptr;
		}
	}
	bool fi存在(int a键) const {
		return ma映射.find(a键) != ma映射.end();
	};
	bool fi不存在(int a键) const {
		return ma映射.find(a键) == ma映射.end();
	}
	void f编译(t指针 &a指针) const {
		if (a指针.fi需解析名称()) {
			a指针.m整数 = C名称标识::f解析名称(a指针.m名称);
		}
		if (a指针.m整数) {
			a指针.m指针 = fg指针(a指针.m整数);
		} else {
			a指针.m指针 = nullptr;
		}
	}
	void f清空() {
		ma映射.clear();
		ma数据.clear();
	}
public:
	std::map<int, int> ma映射;	//标识到序号
	std::vector<t值> ma数据;
};
template<typename t>
const ComPtr<t> &f取属性数组数据指针(const C属性数组<ComPtr<t>> &a数组, int a标识) {
	if (auto v指针 = a数组.f找(a标识)) {
		return *v指针;
	} else {
		return nullptr;
	}
}
template<typename t>
const std::shared_ptr<t> &f取属性数组数据指针(const C属性数组<std::shared_ptr<t>> &a数组, int a标识) {
	if (auto v指针 = a数组.f找(a标识)) {
		return *v指针;
	} else {
		return nullptr;
	}
}
template<typename t>
const t *f取属性数组数据指针(const C属性数组<t> &a数组, int a标识) {
	return a数组.fg指针(a标识);
}
int f取全局标识(const std::wstring &);	//定义在"游戏.cpp"
template<typename t值>
auto C属性数组<t值>::operator [](const std::wstring &a) const
->decltype(f取属性数组数据指针(std::declval<C属性数组<t值>>(), 0)) {
	return f取属性数组数据指针(*this, f取全局标识(a));
}
}	//namespace 东方山寨