#pragma once
#include "数学包含.h"
#include "图形包含.h"
#include "基础.h"
#include "数学基础.h"
#include "基础_数组.h"
#include "判定处理_敌机与玩家子弹.h"
namespace 东方山寨 {
class C玩家;
struct S玩家子弹属性;
class C敌机;
struct S玩家子弹参数;
struct S顶点矩形;
class C玩家子弹 {
public:
	static constexpr float c判定半径 = 4;
	static constexpr float c透明度 = 0.5f;
	static constexpr float c出现透明度达到最大时间 = 0.1f;
	enum E标志 {
		e使用,
		e命中可销毁,
		//炸弹
		e炸弹,
		e产生道具,
		//自定义
		e自定义,
	};
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	const S玩家子弹属性 &f基础_g子弹属性() const;
	void f基础_计算运动();
	float f基础_计算方向();
	void f基础_计算时间();
	C复杂形状 f基础_g判定形状() const;
	bool f基础_i炸弹() const;
	int f属性_g伤害() const;
	float f基础_g出现透明度() const;
	virtual void f接口_初始化(const S玩家子弹参数 &);
	virtual void f接口_销毁();
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_显示() const;
	virtual void f接口_消失();
	virtual void f接口_敌机判定(C敌机与玩家子弹判定 &);
	virtual void f接口_命中敌机(const C敌机 &);
	virtual bool f接口_在窗口外();
	virtual float f接口_g判定半径() const;
public:
	t向量2 m坐标;
	t向量2 m速度;
	t标志 m标志;
	C玩家 *m玩家 = nullptr;
	const S玩家子弹属性 *m子弹属性 = nullptr;
	C数组计数 *m计数指针 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
	float m方向 = 0;
	float m动画帧 = 0;
	float m出现 = 0;
	t向量2 m缩放;
};
struct S玩家子弹属性 {
	t向量2 m判定;
	t向量2 m帧半尺寸;
	t属性指针<tp纹理> m纹理;
	t属性指针<tp纹理> m消失纹理;
	t属性指针<S顶点矩形> m顶点;
	t属性指针<S顶点矩形> m消失顶点;
	int m动画帧数 = 0;
	int m消失帧数 = 0;
	int m伤害 = 10;
};
}