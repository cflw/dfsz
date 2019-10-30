#pragma once
#include "数学包含.h"
#include "基础.h"
#include "基础_数组.h"
namespace 东方山寨 {
enum class E图层 {
	e底层 = 0,
	e敌机 = 10,
	e玩家 = 20,
	e道具 = 30,
	e图形 = 50,
	e子弹 = 60,
	e抬显 = 100,
	e顶层 = 700,
};
struct S图形参数;
//=============================================================================
// 图形对象
//=============================================================================
class I图形 {
public:
	enum E标志 {
		e使用,
		e结束,
		e自定义,
	};
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_显示() const = 0;
	virtual void f接口_初始化(const S图形参数 &);
	virtual bool f接口_i可销毁() const;
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用();
	void f动作_结束();//图形直接消失
public:
	int m图层 = 0;
	int m显示编号 = 0;
	t标志 m标志;
	const C游戏速度 *m游戏速度 = nullptr;
	C数组计数 *m计数指针 = nullptr;
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
//=============================================================================
// 预设图形
//=============================================================================
namespace 图形 {
class C圆形 : public I粒子 {
public:
	C圆形() = default;
	C圆形(float, float);
	void f接口_计算() override;
	void f接口_显示() const override;
	float fg当前半径() const;
public:
	float m开始半径 = 0;
	float m结束半径 = 100;
};
}
}