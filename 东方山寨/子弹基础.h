#pragma once
#include "图形包含.h"
#include "数学包含.h"
#include "基础.h"
#include "数学基础.h"
#include "基础_数组计数.h"
#include "基础_数组指针.h"
#include "判定处理_子弹与玩家炸弹.h"
#include "判定处理_自机与子弹.h"
#include "游戏常量.h"
#include "子弹制造机.h"
namespace 东方山寨 {
struct S子弹属性;
class I画子弹;
class C子弹图形缓冲;
struct S顶点矩形;
class I子弹图形数据;
using tp子弹图形数据 = std::unique_ptr<I子弹图形数据>;
//==============================================================================
// 基本子弹
//==============================================================================
class C子弹 : public I事件 {
public:
	static constexpr float c判定半径 = 1;
	static constexpr float c透明阀值 = 0.9f;
	enum E标志 {
		e使用,
		e无敌,
		e取消产生,	//在"I事件::f事件_初始化"中调用"C子弹::f初始化_取消产生"
		e动作,	//决定是否调用"I事件::f事件_执行"
		e停止炸弹判定,
		e自定义
	};
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	//子弹基础
	void f基础_计算运动();	//在扩展调用
	float f基础_计算方向();	//在扩展调用
	bool f基础_擦弹();	//在游戏调用
	t向量2 f基础_到点方位(const t向量2 &) const;
	bool f基础_i不透明判定(float = c透明阀值) const;
	//子弹扩展的接口
	template<typename t> static void f接口_具体类型初始化(const std::shared_ptr<t> &);
	virtual void f接口_初始化();
	virtual void f接口_参数初始化(const S子弹参数 &);
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_销毁();	//只能通过C子弹::f销毁()调用
	virtual void f接口_自机判定(C自机与子弹判定 &);
	virtual bool f接口_炸弹判定(C子弹与玩家炸弹判定 &);//在炸弹动作中调用
	virtual bool f接口_i在窗口外();
	virtual bool f接口_i可显示() const;
	virtual bool f接口_i停止炸弹判定() const;
	//在事件过程中调用的初始化函数
	void f初始化_样式(int);
	void f初始化_绘制(int);
	//子弹动作
	void f动作_空();
	void f动作_取消产生();
	void f动作_消失(bool);	//[需要覆盖]
	void f动作_旋转(float);
	bool f动作_限速(float, float, float, float = 1);
	void f动作_加速度(float, float = 1);
	void f动作_加速度(const t向量2 &, float = 1);
	void f动作_乘速度(float, float = 1);
	int f动作_屏幕反弹(int 方向, int 次数 = 1, const std::function<bool(int)> &判断 = nullptr);
	void f动作_透明(float, float = 1);
	//内部使用变量
	C数组计数 *m计数指针 = nullptr;
	const C游戏速度 *m游戏速度;
	C子弹图形缓冲 *m图形缓冲 = nullptr;
	const S子弹属性 *m子弹属性;
	int m初始化_样式 = -1;
	int m初始化_绘制 = -1;
	//外部使用变量
	t标志 m标志;
	float m动画帧;
	float m方向;
	float m擦弹间隔;
	//float m透明度 = 1;	//TODO：计划中
	//自由使用变量
	t向量2 m坐标;
	t向量2 m速度;
	t向量2 m缩放;
	t颜色 m颜色[2];
};
template<typename t> void C子弹::f接口_具体类型初始化(const std::shared_ptr<t> &) {
}
//==============================================================================
// 子弹使用的结构
//==============================================================================
struct S子弹属性 {
	static float f判定计算(float 原始, float 修正, float 倍数);
	float fg判定x(float = 1) const;
	float fg判定y(float = 1) const;
	t向量2 fg判定(const t向量2 &) const;
	float fg显示x(float = 1) const;
	float fg显示y(float = 1) const;
	t向量2 fg显示(const t向量2 &) const;
	bool fi圆形() const;
	bool fi矩形() const;
	t向量2 m判定;
	t向量2 m判定修正;
	t属性指针<tp纹理> m纹理;
	t属性指针<S顶点矩形> m顶点;
	int m动画帧数;
};
struct S子弹出现 {
	static constexpr float c速度 = 4 * c帧秒<float>;
	S子弹出现() = default;
	S子弹出现(S子弹出现&, S子弹出现&, float);
	void f初始化();
	void f计算();
	bool fi正在出现() const;
	bool fi出现完() const;
	float m帧;
};
struct S子弹消失 {
	static constexpr float c速度 = 2 * c帧秒<float>;
	S子弹消失() = default;
	S子弹消失(S子弹消失&, S子弹消失&, float);
	void f初始化(float = 0);
	void f计算();
	void f消失(float 目标 = 1);
	void f增加消失(float);
	void fs消失速度(float 差);
	bool fi消失() const;	//目标＞0
	bool fi全消失() const;	//目标≥1
	bool fi存在() const;
	bool fi半存在() const;	//目标＜1 且 帧＜1
	bool fi正在消失() const;	//帧＞0
	bool fi已经消失() const;	//帧≥1
	bool fi还没消失() const;
	float m帧;
	float m目标;
	float m速度;
};
}	//namespace 东方山寨