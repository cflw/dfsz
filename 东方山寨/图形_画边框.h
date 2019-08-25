﻿#pragma once
#include "图形包含.h"
#include "数学包含.h"
namespace 东方山寨 {
class C图形引擎;
//==============================================================================
// 画边框
//==============================================================================
class C画边框 {
public:
	C画边框(C图形引擎 &, 二维::C二维 &);
	void f画矩形边框(float 半宽, float 半高) const;
	void f画圆形边框(float 半径) const;
	void f画框架() const;
	void fs颜色(const t颜色 &);
	void fs标准尺寸(float, float);	//在窗口尺寸发生变化时调用
	std::shared_ptr<二维::C画图形> m画边框;
	float m标准半宽 = 640;
	float m标准半高 = 480;
};
}