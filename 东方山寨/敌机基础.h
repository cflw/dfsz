#pragma once
#include "基础.h"
#include "基础_事件.h"
#include "图形_图片.h"
#include "动画接口.h"
#include "对象图形.h"
#include "数学_运动.h"
#include "判定处理_敌机与玩家子弹.h"
namespace 东方山寨 {
struct S顶点矩形;
class C游戏速度;
class C数组计数;
struct S敌机属性;
//==============================================================================
// 敌机类
//==============================================================================
class C敌机 : public I事件, public C复杂运动 {
public:
	static constexpr float c判定半径 = 16.f;
	enum E标志 {
		e使用,
		e无动作,	//不调用 f事件_执行
		e消失,	//敌机正在消失
		e王,	//击破后不会自动销毁
		e无敌,	//扩展生命给予目标敌机无敌, 和 m无敌时间 并列存在
	};
	C敌机();
	~C敌机();
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	//接口
	virtual void f接口_初始化();
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual bool f接口_玩家子弹判定(C敌机与玩家子弹判定 &);
	virtual void f接口_击破();
	//事件
	const t向量2 &f事件_g坐标() const override;
	//属性
	const S图片动画属性 &fg图片动画属性() const;
	float fg判定半径() const;
	t圆形 fg判定点() const;
	bool fi在窗口外() const;
	bool fi死亡() const;
	bool fi王() const;
	bool fi无敌() const;
	void fs生命值(float);
	void fs无敌时间(float);
	float fg透明度() const;	//由出现消失所决定的透明度
	bool fi消失中() const;
	//状态
	void f中弹(float 伤害);
	//动作
	void f动作_结束();
	void f动作_死亡();	//强制死亡,无视其它因素,会调用击破事件
	void f动作_消失(bool 动画 = true);	//离场,不会调用击破事件
public:
	t标志 m标志;
	const C游戏速度 *m游戏速度 = nullptr;
	C数组计数 *m计数指针 = nullptr;
	const S敌机属性 *m敌机属性 = nullptr;
	数学::S有限值<float> m生命值 = {1};
	float m无敌时间 = 0;
	float m透明度 = 1;
	std::unique_ptr<I对象图形<C敌机>> m图形;
};
//==============================================================================
// 敌机使用的结构
//==============================================================================
struct S敌机属性 : public S图片动画属性 {
	float m判定半径 = 0;	//和子弹交互
	float m碰撞半径 = 0;	//和自机交互
};
}	//namespace 东方山寨