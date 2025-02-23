#pragma once
#include "基础.h"
#include "基础_对象数组.h"
#include "基础_属性数组.h"
#include "基础_缓冲数组.h"
#include "敌机基础.h"
namespace 东方山寨 {
class C敌机;
class C游戏速度;
class I图形缓冲;
struct S敌机参数;
class C敌机制造机;
using t敌机参数 = S敌机参数;
using t敌机工厂 = C敌机制造机;
using tp敌机属性 = t属性指针<S敌机属性>;
//==============================================================================
// 敌机制造机
//==============================================================================
struct S敌机参数 {
	t向量2 m坐标;
	t向量2 m速度;
	t向量2 m目标;
	float m生命值 = 1;
	float m移动时间 = 0;	//0表示无限移动
	float m无敌时间 = 0.5f;	//防止瞬间击破
	t属性指针<S敌机属性> m样式;
	void fs坐标(const t向量2 &坐标);	//敌机产生时的坐标
	void fs坐标_边框外(const t向量2 &坐标);		//设置一个坐标,计算最近的边框外坐标
	void fs边框外进场(const t向量2 &开始坐标);	//设置一个坐标,计算从边框外进入边框内所需的坐标和目标
	void fs进场(const t向量2 &开始, const t向量2 &结束, float 时间 = 1);
	void fs移动速度(const t向量2 &速度, float 时间 = -1);
	void fs移动到_时间(const t向量2 &目标, float 时间 = 1);
	void fs移动到_速度(const t向量2 &目标, float 速度);
};
class C敌机制造机 {
public:
	void f初始化_环境(const C游戏速度 &);
	void f初始化_数组(C对象数组<C敌机> &, C缓冲数组<I图形缓冲> &);
	void f初始化_资源(const C属性数组<S敌机属性> &);
	void f编译参数(S敌机参数 &) const;
	void f产生敌机0(const std::shared_ptr<C敌机> &, const S敌机参数 &) const;
	bool fi有空() const;
	template<typename t, typename...t参数> std::shared_ptr<t> f产生敌机(S敌机参数 &, t参数 &&...) const;
	std::shared_ptr<C敌机> f产生王(S敌机参数 &) const;
private:
	C对象数组<C敌机> *ma敌机 = nullptr;
	C缓冲数组<I图形缓冲> *ma图形缓冲 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
	const C属性数组<S敌机属性> *ma敌机属性 = nullptr;
};
//产生敌机函数实现
template<typename t, typename...t参数> std::shared_ptr<t> C敌机制造机::f产生敌机(S敌机参数 &a敌机参数, t参数 &&...a构造参数) const {
	static_assert(std::is_base_of<C敌机, t>::value, "错误:t必需继承自敌机");
	f编译参数(a敌机参数);
	//创建
	if (fi有空()) {
		std::shared_ptr<t> v指针 = std::make_shared<t>(a构造参数...);
		f产生敌机0(v指针, a敌机参数);
		return v指针;
	}
	return nullptr;
}
}	//namespace 东方山寨