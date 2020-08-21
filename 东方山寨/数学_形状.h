#pragma once
#include "数学包含.h"
namespace 东方山寨 {
//==============================================================================
// 复杂形状
//==============================================================================
class C复杂形状 {
public:
	C复杂形状(const t向量2 &坐标, const t向量2 &半尺寸, float 方向);	//矩形
	C复杂形状(const t向量2 &坐标, float 半径);	//圆
	static C复杂形状 fc自动(const t向量2 &坐标, const t向量2 &原始判定, const t向量2 &缩放, float 方向);
	static C复杂形状 fc最大圆(const t向量2 &坐标, const t向量2 &原始判定, const t向量2 &缩放);
	static C复杂形状 fc最小圆(const t向量2 &坐标, const t向量2 &原始判定, const t向量2 &缩放);
	bool f相交判定(const t圆形 &) const;
	bool fi圆形() const;
	bool fi矩形() const;
	t圆形 fg圆形() const;
	t旋转矩形 fg旋转矩形() const;
public:
	t向量2 m坐标;
	t向量2 m半尺寸;
	float m方向;
	bool mi矩形;
};
}