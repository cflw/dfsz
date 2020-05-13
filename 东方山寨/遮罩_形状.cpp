﻿#include "遮罩_形状.h"
namespace 东方山寨::遮罩 {
//==============================================================================
// 圆形遮罩
//==============================================================================
C圆形::C圆形(const t圆形 &a圆形):
	m圆形(a圆形) {
}
bool C圆形::f判定_点(const t向量2 &a点) const {
	return m圆形.fi包含点(a点);
}
//==============================================================================
// 旋转矩形遮罩
//==============================================================================
C旋转矩形::C旋转矩形(const t旋转矩形 &a旋转矩形):
	m旋转矩形(a旋转矩形) {
}
bool C旋转矩形::f判定_点(const t向量2 &a点) const {
	return m旋转矩形.fi包含点(a点);
}
//==============================================================================
// 左遮罩
//==============================================================================
C左::C左(float X):
	x(X) {
}
bool C左::f判定_点(const t向量2 &a点) const {
	return a点.x <= x;
}
//==============================================================================
// 右遮罩
//==============================================================================
C右::C右(float X):
	x(X) {
}
bool C右::f判定_点(const t向量2 &a点) const {
	return a点.x >= x;
}
//==============================================================================
// 上遮罩
//==============================================================================
C上::C上(float Y):
	y(Y) {
}
bool C上::f判定_点(const t向量2 &a点) const {
	return a点.y >= y;
}
//==============================================================================
// 下遮罩
//==============================================================================
C下::C下(float Y):
	y(Y) {
}
bool C下::f判定_点(const t向量2 &a点) const {
	return a点.y <= y;
}
}	//namespace 东方山寨::遮罩