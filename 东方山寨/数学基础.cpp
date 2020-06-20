#include "游戏常量.h"
#include "数学基础.h"
namespace 东方山寨 {
//==============================================================================
// 复杂形状
//==============================================================================
C复杂形状::C复杂形状(const t向量2 &a坐标, const t向量2 &a半尺寸, float a方向) : 
	m坐标(a坐标), m半尺寸(a半尺寸), m方向(a方向), mi矩形(true) {
}
C复杂形状::C复杂形状(const t向量2 &a坐标, float a半径) : 
	m坐标(a坐标), m半尺寸(a半径, 0), m方向(0), mi矩形(false) {
}
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