﻿#pragma once
#include "数学包含.h"
#include "基础.h"
#include "基础_数组计数.h"
namespace 东方山寨 {
struct S图形参数;
class I图形缓冲;
//==============================================================================
// 图形对象
//==============================================================================
class I图形 {
public:
	enum E标志 {
		e使用,
		e结束,
		e自定义,
	};
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_初始化(const S图形参数 &);
	virtual bool f接口_i可销毁() const;
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用();
	void f动作_结束();//图形直接消失
public:
	t标志 m标志;
	const C游戏速度 *m游戏速度 = nullptr;
	C数组计数 *m计数指针 = nullptr;
	I图形缓冲 *m图形缓冲 = nullptr;
};
class I粒子 : public I图形 {
public:
	void f接口_初始化(const S图形参数 &) override;
	bool f接口_i可销毁() const override;
	void f计算_运动();
	void f计算_生命();
	float fg生命百分比() const;
	float fg反生命百分比() const;
	bool fi死亡() const;
public:
	t向量2 m坐标;
	t向量2 m速度;
	float m寿命;	//固定
	float m生命 = 0;	//存活的时间
};
//概念
template<typename t> concept T图形 = std::is_base_of<I图形, t>::value;
}	//namespace 东方山寨