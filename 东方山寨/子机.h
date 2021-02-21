#pragma once
#include <boost/rational.hpp>
#include "基础.h"
#include "基础_扩展数组.h"
#include "基础_属性数组.h"
#include "基础_对象工厂.h"
#include "图形_图片.h"
#include "玩家子弹发射基础.h"
#include "子机移动接口.h"
#include "对象图形.h"
namespace 东方山寨 {
class C玩家;
class C玩家子弹发射器;
struct S子机属性;
class I子机移动;
class C子机 {
public:
	C子机();
	void f坐标_移动(const t向量2 &目标);
	void f坐标_重置(const t向量2 &目标);
	void f计算();
	void f更新();
	const t向量2 &fg坐标() const;
	float fg透明度() const;
	void f出现();
public:
	t向量2 m坐标, m目标坐标;
	float m出生时间 = 0;
	const C游戏速度 *m游戏速度 = nullptr;
	const S子机属性 *m子机属性 = nullptr;
	std::unique_ptr<C玩家子弹发射器> m发射;
	std::unique_ptr<I对象图形<C子机>> m图形;
};
class C子机组 {
public:
	C子机组();
	void f初始化_在关卡开始();
	void f初始化_图形(C缓冲数组<I图形缓冲> &);
	void fs子机属性(const S子机属性 *);
	const S子机属性 &f子机属性() const;
	void f发射_发射子弹();
	void f发射_停止发射子弹();
	void f计算();
	void f更新();
	void f绑定玩家(C玩家 &);
	void f复活();
	int fg目标子机数() const;	//根据火力计算出当前数量
	int fg子机数上限() const;	//子机属性里的上限
	循环::C范围<std::vector<C子机>> fe使用();
	循环::C范围<const std::vector<C子机>> fe使用c() const;
public:
	std::vector<C子机> ma子机;
	const S子机属性 *m子机属性 = nullptr;
	std::unique_ptr<I子机移动> m子机移动;
	int m数量 = 0;
	const boost::rational<int> *m火力 = nullptr;	//指向C玩家::S成绩::m火力
};
struct S子机属性 : public S图片动画属性 {
	int m数量上限;
	t扩展指针<I工厂<C玩家子弹发射器>> m发射;
	t扩展指针<I工厂<I子机移动>> m移动;
	t属性指针<S玩家子弹属性> m子弹属性;
};
}	//namespace 东方山寨