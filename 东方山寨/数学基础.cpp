#include "常量.h"
#include "数学基础.h"
namespace 东方山寨 {
//=============================================================================
// 边界
//=============================================================================
const C边界 C边界::c边框 = C边界::fc中心矩形(c边框范围x, c边框范围y);
const C边界 C边界::c窗口 = C边界::fc中心矩形(c屏幕范围x, c屏幕范围y);
const C边界 C边界::c自机 = C边界::fc中心矩形(c移动范围x, c移动范围y);
//构造
C边界::C边界(float a左, float a上, float a右, float a下) :
	m左{a左}, m上{a上}, m右{a右}, m下{a下} {
}
C边界 C边界::fc中心矩形(float x, float y) {
	return {-x, y, x, -y};
}
//属性
float C边界::fg宽度() const {
	return m右 - m左;
}
float C边界::fg高度() const {
	return m上 - m下;
}
float C边界::fg斜边() const {
	return hypot(fg宽度(), fg高度());
}
float C边界::fg半宽度() const {
	return fg宽度() / 2;
}
float C边界::fg半高度() const {
	return fg高度() / 2;
}
float C边界::fg半斜边() const {
	return fg斜边() / 2;
}
//判断
bool C边界::f左边判断(const t向量2 &a坐标, float d) const {
	return a坐标.x < m左 - d;
}
bool C边界::f右边判断(const t向量2 &a坐标, float d) const {
	return a坐标.x > m右 + d;
}
bool C边界::f上边判断(const t向量2 &a坐标, float d) const {
	return a坐标.y > m上 + d;
}
bool C边界::f下边判断(const t向量2 &a坐标, float d) const {
	return a坐标.y < m下 - d;
}
bool C边界::f外边判断(const t向量2 &a坐标, float d) const {
	return f左边判断(a坐标, d) || f右边判断(a坐标, d) || f上边判断(a坐标, d) || f下边判断(a坐标, d);
}
//限制
bool C边界::f左边限制(t向量2 &a坐标, float d) const {
	const float v边界 = m左 - d;
	if (a坐标.x < v边界) {
		a坐标.x = v边界;
		return true;
	} else {
		return false;
	}
}
bool C边界::f右边限制(t向量2 &a坐标, float d) const {
	const float v边界 = m右 + d;
	if (a坐标.x > v边界) {
		a坐标.x = v边界;
		return true;
	} else {
		return false;
	}
}
bool C边界::f上边限制(t向量2 &a坐标, float d) const {
	const float v边界 = m上 + d;
	if (a坐标.y > v边界) {
		a坐标.y = v边界;
		return true;
	} else {
		return false;
	}
}
bool C边界::f下边限制(t向量2 &a坐标, float d) const {
	const float v边界 = m下 - d;
	if (a坐标.y < v边界) {
		a坐标.y = v边界;
		return true;
	} else {
		return false;
	}
}
bool C边界::f左右限制(t向量2 &a坐标, float d) const {
	return f左边限制(a坐标, d) || f右边限制(a坐标, d);
}
bool C边界::f上下限制(t向量2 &a坐标, float d) const {
	return f上边限制(a坐标, d) || f下边限制(a坐标, d);
}
bool C边界::f边界限制(t向量2 &a坐标, float d) const {
	return f左边限制(a坐标, d) || f右边限制(a坐标, d) || f上边限制(a坐标, d) || f下边限制(a坐标, d);
}
//反弹
bool C边界::f左边反弹(t向量2 &a坐标, float d) const {
	const float v边界 = m左 - d;
	if (a坐标.x < v边界) {
		a坐标.x = 数学::f翻折(a坐标.x, v边界);
		return true;
	} else {
		return false;
	}
}
bool C边界::f右边反弹(t向量2 &a坐标, float d) const {
	const float v边界 = m右 + d;
	if (a坐标.x > v边界) {
		a坐标.x = 数学::f翻折(a坐标.x, v边界);
		return true;
	} else {
		return false;
	}
}
bool C边界::f上边反弹(t向量2 &a坐标, float d) const {
	const float v边界 = m上 + d;
	if (a坐标.y > v边界) {
		a坐标.y = 数学::f翻折(a坐标.y, v边界);
		return true;
	} else {
		return false;
	}
}
bool C边界::f下边反弹(t向量2 &a坐标, float d) const {
	const float v边界 = m下 - d;
	if (a坐标.y < v边界) {
		a坐标.y = 数学::f翻折(a坐标.y, v边界);
		return true;
	} else {
		return false;
	}
}
bool C边界::f左右反弹(t向量2 &a坐标, float d) const {
	return f左边反弹(a坐标, d) || f右边反弹(a坐标, d);
}
bool C边界::f上下反弹(t向量2 &a坐标, float d) const {
	return f上边反弹(a坐标, d) || f下边反弹(a坐标, d);
}
bool C边界::f边界反弹(t向量2 &a坐标, float d) const {
	return f左边反弹(a坐标, d) || f右边反弹(a坐标, d) || f上边反弹(a坐标, d) || f下边反弹(a坐标, d);
}
//=============================================================================
// 复杂形状
//=============================================================================
C复杂形状::C复杂形状(const t向量2 &a坐标, const t向量2 &a半尺寸, float a方向) : m坐标(a坐标), m半尺寸(a半尺寸), m方向(a方向), mi矩形(true) {}
C复杂形状::C复杂形状(const t向量2 &a坐标, float a半径) : m坐标(a坐标), m半尺寸(a半径, 0), m方向(0), mi矩形(false) {}
C复杂形状 C复杂形状::fc自动(const t向量2 &a坐标, const t向量2 &a判定, const t向量2 &a缩放, float a方向) {
	if (a判定.y > 0) {	//矩形
		return {a坐标, a判定.f分量乘(a缩放), a方向};
	} else {
		if (a缩放.fi分量相等()) {	//圆形
			return {a坐标, a判定.x * a缩放.x};
		} else {	//矩形
			return {a坐标, t向量2::fc相同(a判定.x).f分量乘(a缩放), a方向};
		}
	}
}
C复杂形状 C复杂形状::fc最大圆(const t向量2 &a坐标, const t向量2 &a判定, const t向量2 &a缩放) {
	const float v判定x = a判定.x * a缩放.x;
	const float v判定y = a判定.y * a缩放.y;
	const float v最大 = std::max(v判定x, v判定y);
	return {a坐标, v最大};
}
C复杂形状 C复杂形状::fc最小圆(const t向量2 &a坐标, const t向量2 &a判定, const t向量2 &a缩放) {
	const float v判定x = a判定.x * a缩放.x;
	const float v判定y = a判定.y * a缩放.y;
	const float v最小 = std::max(v判定x, v判定y);
	return {a坐标, v最小};
}
bool C复杂形状::f相交判定(const t圆形 &a圆形) const {
	if (mi矩形) {
		return 数学::f圆形旋转矩形相交判定(a圆形.m坐标, a圆形.m半径, m坐标, m半尺寸, m方向);
	} else {
		return 数学::f圆形相交判定(a圆形.m坐标, a圆形.m半径, m坐标, m半尺寸.x);
	}
}
bool C复杂形状::fi圆形() const {
	return !mi矩形;
}
bool C复杂形状::fi矩形() const {
	return mi矩形;
}
t圆形 C复杂形状::fg圆形() const {
	return t圆形(m坐标, m半尺寸.x);
}
t旋转矩形 C复杂形状::fg旋转矩形() const {
	return t旋转矩形(m坐标, m半尺寸, m方向);
}
}	//namespace 东方山寨