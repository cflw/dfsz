﻿#pragma once
#include <deque>
#include "数学基础.h"
namespace 东方山寨 {
class C轨迹 {
public:
	void f添加坐标(const t向量2 &);
	void f填充坐标(const t向量2 &);
	t向量2 fg平均速度(float 秒 = 1) const;
	std::deque<t向量2> ma坐标;
};
//总是记录
class C实时轨迹 : public C轨迹 {
public:
	void f记录坐标(const t向量2 &);
};
//有移动才记录
class C移动轨迹 : public C轨迹 {
public:
	void f记录坐标(const t向量2 &);
};
}	//namespace 东方山寨