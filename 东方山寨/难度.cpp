#include <cflw工具_运算.h>
#include <cflw数学_函数方程.h>
#include "数学包含.h"
#include "难度.h"
namespace 东方山寨 {
namespace 工具 = cflw::工具;
namespace 数学 = cflw::数学;
//==============================================================================
// 计算
//==============================================================================
namespace 难度 {
bool f单调(float e, float h, float t, float t6) {
	const auto f全比较 = [&](bool (*af比较)(const float &, const float &)) {
		return af比较(e, h) && af比较(h, t) && af比较(t, t6);
	};
	if (e == t6) {
		return false;
	} else if (e > t6) {	//单调递减
		return f全比较(工具::f大于<float>);
	} else {	//单调递增
		return f全比较(工具::f小于<float>);
	}
}
tf难度 F常数(float a) {
	return [a](float)->float {
		return a;
	};
}
tf难度 F一次(float e, float t6) {
	//y = kx + b
	return 数学::F一次函数::fc两点({c简单, e}, {c折磨6, t6});
}
tf难度 F二次(float e, float t, float t6) {
	//y = ax^2 + bx + c
	return 数学::F二次函数::fc三点({c简单, e}, {c折磨, t}, {c折磨6, t6});
}
//tf难度 F四次(float e, float h, float t, float t6) {
//
//}
//tf难度 F指数(float e, float t, float t6) {
//	//y = a^x * b + c
//
//}
//tf难度 F反(float e, float t, float t6) {
//	//y = a / (bx + c)
//}
tf难度 F线性插值(float e, float h, float t, float t6) {
	const float k1 = (t - e) / (c折磨 - c简单);
	const float k5 = (t6 - t) / (c折磨6 - c折磨);
	const float k10a = (std::abs(k1) < std::abs(k5)) ? (k5 * 2) : (k5 * 0.5f);	//t6之后的斜率
	const float t16 = t6 + k10a * 10;	//t16时(x=20)的值
	const float k10 = (t16 < 0) ? (t6 * 0.1f) : k10a;	//矫正后的斜率，确保x=20内y是正数
	return [=](float x)->float {
		if (x <= c困难) {	//简单~困难
			return 数学::f插值2<float>(c简单, e, c困难, h, x);
		} else if (x <= c折磨) {	//困难~折磨
			return 数学::f插值2<float>(c困难, h, c折磨, t, x);
		} else if (x <= c折磨6) {	//折磨~折磨6
			return 数学::f插值2<float>(c折磨, t, c折磨6, t6, x);
		} else {	//折磨6~
			return t6 + k10 * (x - c折磨6);
		}
	};
}
tf难度 F线性插值(std::optional<float> e, std::optional<float> h, std::optional<float> t, std::optional<float> t6) {
	const bool v有e = e.has_value();
	const bool v有h = h.has_value();
	const bool v有t = t.has_value();
	const bool v有t6 = t6.has_value();
	if (v有e) {
		if (v有h) {
			if (v有t) {
				if (v有t6) {	//oooo, 有重载,应该不会成立
					throw;
					//return F线性插值(*e, *h, *t, *t6);
				} else {	//ooox
					const float k3 = (*t - *h) / (c折磨 - c困难);
					const float _t6 = *t + 10 * k3;
					return F线性插值(*e, *h, *t, _t6);
				}
			} else {
				if (v有t6) {	//ooxo
					const float k3 = (*t6 - *h) / (c折磨6 - c困难);
					const float _t = *h + 2 * k3;
					return F线性插值(*e, *h, _t, *t6);
				} else {	//ooxx
					return 数学::F一次函数::fc两点({c简单, *e}, {c困难, *h});
				}
			}
		} else {
			if (v有t) {
				if (v有t6) {	//oxoo
					const float k1 = (*t - *e) / (c折磨 - c简单);
					const float _h = *e + 2 * k1;
					return F线性插值(*e, _h, *t, *t6);
				} else {	//oxox
					return 数学::F一次函数::fc两点({c简单, *e}, {c折磨, *t});
				}
			} else {
				if (v有t6) {	//oxxo
					return 数学::F一次函数::fc两点({c简单, *e}, {c折磨6, *t6});
				} else {	//oxxx
					return F常数(*e);
				}
			}
		}
	} else {
		if (v有h) {
			if (v有t) {
				if (v有t6) {	//xooo
					const float k3 = (*t - *h) / (c折磨 - c困难);
					const float _e = *h - 2 * k3;
					return F线性插值(_e, *h, *t, *t6);
				} else {	//xoox
					return 数学::F一次函数::fc两点({c困难, *h}, {c折磨, *t});
				}
			} else {
				if (v有t6) {	//xoxo
					return 数学::F一次函数::fc两点({c困难, *h}, {c折磨6, *t6});
				} else {	//xoxx
					return F常数(*h);
				}
			}
		} else {
			if (v有t) {
				if (v有t6) {	//xxoo
					return 数学::F一次函数::fc两点({c折磨, *t}, {c折磨6, *t6});
				} else {	//xxox
					return F常数(*t);
				}
			} else {
				if (v有t6) {	//xxxo
					return F常数(*t6);
				} else {	//xxxx
					throw;
				}
			}
		}
	}
}
}	//namespace 难度
//==============================================================================
// 控制
//==============================================================================
void C难度::f增加难度(const boost::rational<int> &a) {
	m增加难度 += boost::rational_cast<int>(a * 100'0000);
}
void C难度::f增加难度_最大点(int a) {
	m增加难度 += a;
}
void C难度::f减少难度() {
	//减10%,最多减0.1难度
	if (m增加难度 < 1000000) {
		m增加难度 = m增加难度 * 9 / 10;
	} else {
		m增加难度 -= 100000;
	}
}
float C难度::fg基础难度() const {
	return (float)m基础难度;
}
float C难度::fg动态难度() const {
	return (float)m基础难度 + (float)m增加难度 / 100'0000.f;
}
//==============================================================================
// 难度值
//==============================================================================
C难度值::C难度值(const tf难度 &af计算):
	mf计算(af计算) {
}
void C难度值::operator ()(float a难度) {
	m值 = mf计算(a难度);
}
C难度值::operator float() const {
	return m值;
}

}	//namespace 东方山寨