#include <cflw工具_运算.h>
#include <cflw数学_函数方程.h>
#include "数学基础.h"
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
	} else if (e < t6) {	//单调递增
		return f全比较(工具::f小于<float>);
	}
}
tf难度 F一次(float e, float t6) {
	//y = kx + b
	return 数学::F一次函数::fc两点({c简单, e}, {c折磨6, t6});
}
//tf难度 F二次(float e, float t, float t6) {
//	//y = ax^2 + bx + c
//	return 数学::F二次函数::fc三点({c简单, e}, {c折磨, t}, {c折磨6, t6});
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
	const float k10 = (std::abs(k1) < std::abs(k5)) ? (k5 * 2) : (k5 * 0.5f);
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
//tf难度 F自动(float e, float h, float t, float t6) {
	//const auto f一次 = F一次(e, t6);
	//const auto f二次 = F二次(e, t, t6);
	//const auto f指数 = F指数(e, t, t6);
	//const auto f反 = F反(e, t, t6);
	//const auto f线性插值 = F线性插值(e, h, t, t6);
	//const float v一次差 = std::abs(f一次(h));
	//const float v二次差 = std::abs(f一次(h));
	//const float v指数差 = std::abs(f一次(h));
	//const float v反差 = std::abs(f一次(h));
	//const float v插值差 = std::abs(f线性插值(h));
	//const std::pair<const float &, const tf难度 &> va[] = {
		//{v一次差, f一次},
		//{v二次差, f二次},
		//{v指数差, f指数},
		//{v反差, f反},
		//{v插值差, f线性插值},
	//};
	//const std::pair<const float &, const tf难度 &> *v选择 = &va[0];
	//for (const auto &v : va) {
	//	if (v选择->first > v.first) {
	//		v选择 = &v;
	//	}
	//}
	//return v选择->second;
//}
}	//namespace 难度
//==============================================================================
// 控制
//==============================================================================
void C难度::f增加难度(const boost::rational<int> &p) {
	m增加难度 += boost::rational_cast<int>(p * 100'0000);
}
void C难度::f增加难度_最大点(int p) {
	m增加难度 += p;
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

}	//namespace 东方山寨