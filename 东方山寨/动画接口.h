﻿#pragma once
#include <variant>
#include "数学包含.h"
#include "基础.h"
namespace 东方山寨 {
//=============================================================================
// 动画接口
//=============================================================================
typedef std::variant<int, float, bool> t动画动作值;
enum class E动画动作 {
	e正常,
	e水平移动,
	e动作,
	e固定帧,
	e透明度,
};
struct S动画缓冲 {
	t向量2 m坐标 = t向量2::c零;
	t向量3 m旋转 = t向量3::c零;
	t向量3 m缩放 = t向量3::c一;
	int m顶点序号 = 0;
	float m透明度 = 0;
	S动画缓冲() = default;
	S动画缓冲(const S动画缓冲 &) = default;
	S动画缓冲(S动画缓冲 &&) = default;
	S动画缓冲 &operator =(const S动画缓冲 &) = default;
	S动画缓冲 &operator =(S动画缓冲 &&) = default;
};
class I动画 {
public:
	virtual void f接口_s父对象(const void *);	//初始化时调用
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_动作(const E动画动作 &, const t动画动作值 & = {});
	virtual int f接口_g顶点序号() const;
	virtual t向量2 f接口_g坐标() const;
	virtual t向量3 f接口_g旋转() const;
	virtual t向量3 f接口_g缩放() const;
	virtual float f接口_g透明度() const;
	virtual const C游戏速度 *f接口_g游戏速度() const;	//动画所处环境的游戏速度
	S动画缓冲 fg动画缓冲() const;
	static int fg动作值i(const t动画动作值 &);
	static float fg动作值f(const t动画动作值 &);
	static bool fg动作值b(const t动画动作值 &);
};
}	//namespace 东方山寨