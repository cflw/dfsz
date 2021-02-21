#pragma once
#include "数学包含.h"
#include "图形资源.h"
#include "数学_形状.h"
#include "基础.h"
#include "基础_数组计数.h"
#include "基础_数组指针.h"
#include "判定处理_子弹与玩家炸弹.h"
#include "判定处理_自机与子弹.h"
#include "游戏常量.h"
#include "子弹制造机.h"
#include "边框常量.h"
#include "边框形状.h"
namespace 东方山寨 {
struct S子弹属性;
class I画子弹;
class C子弹图形缓冲;
struct S顶点矩形;
class I子弹图形数据;
using tp子弹图形数据 = std::unique_ptr<I子弹图形数据>;
class I遮罩;
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
	bool f基础_i动作() const;	//return m标志[e动作];
	//初始化, 只能在 f接口_参数初始化 中调用
	void f初始化_长度到缩放(float);	//把长宽转换成缩放
	void f初始化_宽度到缩放(float);
	void f初始化_长宽到缩放(const t向量2 &);
	//子弹扩展的接口
	template<typename t> static void f接口_具体类型初始化(const std::shared_ptr<t> &);
	virtual void f接口_初始化();
	virtual void f接口_参数初始化(const S子弹参数 &);
	virtual void f接口_计算();
	virtual void f接口_结算();	//计算后的计算
	virtual void f接口_更新();	//更新图形数据
	virtual void f接口_销毁();	//只能通过C子弹::f销毁()调用
	virtual void f接口_自机判定(C自机与子弹判定 &);
	virtual bool f接口_炸弹判定(C子弹与玩家炸弹判定 &);//在炸弹动作中调用
	virtual bool f接口_i在窗口外();
	virtual bool f接口_i可显示() const;
	virtual bool f接口_i停止炸弹判定() const;
	//子弹扩展事件
	virtual void f事件_遮罩(I遮罩 &);
	//子弹动作
	void f动作_结束();	//停止执行动作
	void f动作_取消产生();
	void f动作_消失(bool);	//[需要覆盖]
	void f动作_旋转d(float);
	void f动作_旋转r(float);
	bool f动作_限速(float 小, float 大, float 变化, float 时间 = 1);
	void f动作_加速度(float, float = 1);
	void f动作_加速度(const t向量2 &, float = 1);
	void f动作_乘速度(float, float = 1);
	int f动作_屏幕反弹(int 方向, int 次数 = 1, const std::function<bool(int)> &判断 = nullptr);
	void f动作_透明(float, float = 1);
	//内部使用变量
	C数组计数 *m计数指针 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
	C子弹图形缓冲 *m图形缓冲 = nullptr;
	const S子弹属性 *m子弹属性 = nullptr;
	//外部使用变量
	t标志 m标志;
	float m动画帧 = 0;
	float m方向 = 0;
	float m擦弹间隔 = 0;
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
	float fg判定x(float 缩放 = 1) const;
	float fg判定y(float 缩放 = 1) const;
	t向量2 fg判定(const t向量2 &缩放) const;
	float fg显示x(float 缩放 = 1) const;
	float fg显示y(float 缩放 = 1) const;
	t向量2 fg显示(const t向量2 &) const;
	float fg缩放x(float 像素 = 0) const;	//根据实际长度计算缩放
	float fg缩放y(float 像素 = 0) const;
	t向量2 fg缩放(const t向量2 &) const;
	bool fi圆形() const;
	bool fi矩形() const;
	t向量2 m判定;
	t向量2 m判定修正;
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m顶点;
	int m动画帧数 = 0;
};
struct S子弹出现 {
	static constexpr float c速度 = 4 * c帧秒<float>;
	static constexpr float c未出现 = 0;
	static constexpr float c已出现 = 1;
	S子弹出现() = default;
	void f初始化(float 初始帧 = c未出现);
	void f计算();
	bool fi正在出现() const;
	bool fi出现完() const;
	float m帧 = 0;
};
struct S子弹消失 {
	static constexpr float c速度 = 4 * c帧秒<float>;
	S子弹消失() = default;
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
	float m帧 = 0;
	float m目标 = 0;
	float m速度 = 0;
};
enum class E相对长度 {
	e倍数,	//原尺寸基础上直接缩放
	e图形,	//相对图形尺寸缩放
	e判定,	//相对判定尺寸缩放
};
struct S相对长度 {
	float m值 = 1;
	E相对长度 m相对 = E相对长度::e倍数;
};
}	//namespace 东方山寨
namespace cflw::数学 {
template<> 东方山寨::S子弹出现 f插值<东方山寨::S子弹出现>(const 东方山寨::S子弹出现 &, const 东方山寨::S子弹出现 &, float);
template<> 东方山寨::S子弹消失 f插值<东方山寨::S子弹消失>(const 东方山寨::S子弹消失 &, const 东方山寨::S子弹消失 &, float);
}	//namespace cflw::数学