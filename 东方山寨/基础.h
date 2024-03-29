﻿#pragma once
#include <bitset>
#include <atomic>
namespace 东方山寨 {
typedef std::bitset<32> t标志;
//方向
enum E方向 {
	e左 = 0x01,
	e上 = 0x02,
	e右 = 0x04,
	e下 = 0x08,
	e左右 = e左 | e右,
	e上下 = e上 | e下,
	e上下左右 = e上 | e下 | e左 | e右,
};
//==============================================================================
// 自动编号
//==============================================================================
class C自动编号 {
public:
	std::atomic<int> m编号 = 0;
	void f重置();
	int f新编号();
};
//==============================================================================
// 游戏速度
//==============================================================================
class C游戏速度 {
private:
	float m速度;
	float m秒;
	float m帧;
public:
	C游戏速度(float 速度 = 1);
	void f内部计算();
	void fs速度(float 速度);
	float fg速度() const;
	float fg秒() const;
	float fg帧() const;	//等于fg速度
	float fg渲染秒() const;
	float fg渲染帧() const;
};
//==============================================================================
// 事件过程
//==============================================================================
class I事件 {
public:
	virtual void f事件_初始化() {}	//工厂创建对象并赋值后调用
	virtual void f事件_执行() {}	//每帧调用一次,可以与其它对象交互,小心数据竞争. 在 f接口_计算 之前调用
	virtual void f事件_结算() {}	//计算结束后调用,不与其它对象交互.用来避开并行计算过程中存在的顺序问题, 在 f接口_结算 之前调用
	virtual void f事件_销毁() {}	//即将从内存中销毁时调用. 在 f接口_销毁 之前调用
	virtual void f事件_结束() {}	//关卡事件结束时,敌机离场时
	virtual void f事件_击破() {}	//敌机被击破时调用
};
//==============================================================================
// 循环计算
//==============================================================================
class C循环计算 {
public:
	enum E标志 {
		e首次自增,
		e去除末尾,	//要配合百分比
		e居中,
		e小数,	//[0,1]
	};
	static const t标志 c标准计数, c自然计数, c中间插值, c小数, c小数居中, c计数居中, c圆形;
	static t标志 fc标准(bool 首次 = false, bool 居中 = false, bool 小数 = false);
	static t标志 fc插值(bool 头 = true, bool 尾 = true);
	static t标志 fc居中(bool 小数 = false);
	static unsigned int f计算位(int);
	static unsigned int f计算位(bool, int);
	static float f计算(int 计数, int 总数, t标志);
};
}	//namespace 东方山寨