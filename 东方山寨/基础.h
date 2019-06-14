#pragma once
#include <bitset>
#include <atomic>
#include <memory>
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
// 游戏对象
//==============================================================================
// 游戏对象不用继承,但是方法要自已实现.因为这涉及到静态/动态数组对游戏对象的管理
class C游戏对象 {
public:
	virtual void f对象_使用() = 0;
	virtual void f对象_销毁() = 0;
	virtual bool f对象_i使用() const = 0;
};
/*
template<typename t> concept T游戏对象 = requires(T a) {
	a.f对象_使用();
	a.f对象_销毁();
	{a.f对象_i使用()}->bool;
}
*/
//简单游戏对象在偷懒时可以直接继承
class C简单游戏对象 {
public:
	C简单游戏对象() = default;
	void f对象_使用() {
		m使用 = true;
	}
	void f对象_销毁() {
		m使用 = false;
	}
	bool f对象_i使用() const {
		return m使用;
	}
private:
	bool m使用 = false;
};
//==============================================================================
// 事件过程
//==============================================================================
class I事件 {
public:
	virtual void f事件_初始化() {}	//工厂创建对象并赋值后调用
	virtual void f事件_执行() {}	//每帧调用一次
	virtual void f事件_销毁() {}	//即将从内存中销毁时调用
	virtual void f事件_结束() {}	//关卡事件结束时,敌机离场时调用
	virtual void f事件_击破() {}	//敌机被击破时调用
};
//==============================================================================
// 图形管线
//==============================================================================
class I图形管线 {
public:
	virtual void f准备() = 0;
	virtual void f刷新() = 0;
	void f自动准备();
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
//==============================================================================
// 计时器
//==============================================================================
class C计时器 {
public:
	C计时器(float a时间 = 1);
	bool f滴答();
	void f停止();
	void f重置(float);
private:
	float m滴答;
	float m计时;
};
//滴答一次后就停止的计时器
class C单次计时器 {
public:
	C单次计时器(float 时间 = 1);
	bool f滴答();
	void f重置(float);
private:
	float m滴答;
	float m计时;
};
//==============================================================================
// 工厂
//==============================================================================
template<typename t> class I工厂 {
public:
	virtual t *f接口_新建() const = 0;	//创建对象，返回裸指针，小心内存泄露
	std::unique_ptr<t> f新建u() const {
		return std::unique_ptr<t>(this->f接口_新建());
	}
	std::shared_ptr<t> f新建s() const {
		return std::shared_ptr<t>(this->f接口_新建());
	}
};
template<typename t基类, typename t派生类 = t基类> class C简单工厂 : public I工厂<t基类> {
public:
	static_assert(std::is_base_of<t基类, t派生类>::value, "");
	t基类 *f接口_新建() const override {
		return new t派生类();
	}
};
}	//namespace 东方山寨