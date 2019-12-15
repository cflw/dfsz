#pragma once
#include <vector>
#include <functional>
#include "基础_游戏对象.h"
namespace 东方山寨 {
//动态数组. 对std::vector的简单扩充
template<typename t> class C动态数组 : public std::vector<t> {
public:
	using value_type = t;
	using reference = t &;
	using const_reference = const t &;
	using t基 = std::vector<t>;
	C动态数组() = default;
	void f清空() {
		for (auto v = t基::begin(); v != t基::end(); ++v) {
			if (v->f对象_i使用()) {
				v->f对象_销毁();
			}
		}
	};
	void f新建(int a数量, const std::function<void(t &, int)> &af新建) {
		int v数量 = 0;
		for (int i = 0; i < t基::size(); ++i) {
			t &v = t基::operator[](i);
			if (!v.f对象_i使用()) {
				af新建(v, i);
				++v数量;
				if (v数量 >= a数量) {
					return;
				}
			}
		}
		for (; v数量 < a数量; ++v数量) {
			t v;
			af新建(v, t基::size());
			t基::push_back(v);
		}
	}
	int f连续新建(int a数量, const std::function<void(t &, int)> &af新建) {
		int v位置 = 0;
		int v数量 = 0;
		for (int i = 0; i < t基::size(); ++i) {
			t &v = t基::operator[](i);
			if (v.f对象_i使用()) {
				v位置 = i + 1;
			} else {
				++v数量;
				if (v数量 >= a数量) {
					break;
				}
			}
		}
		v数量 = 0;
		while (v数量 < a数量) {
			const int v当前位置 = v位置 + v数量;
			if (v当前位置 < t基::size()) {
				af新建(t基::operator[](v当前位置));
			} else {
				t v;
				af新建(v);
				t基::push_back(v);
			}
			++v数量;
		}
		return v位置;
	}
};
}	//namespace 东方山寨