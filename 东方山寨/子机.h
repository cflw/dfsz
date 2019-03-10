#pragma once
#include <boost/rational.hpp>
#include "基础.h"
#include "基础_数组.h"
#include "图形_图片.h"
#include "玩家子弹发射基础.h"
#include "子机移动接口.h"
namespace 东方山寨 {
class C玩家;
class C玩家子弹发射器;
struct S子机属性;
class I子机移动;
class C子机 : public C内置图片动画 {
public:
	void f坐标_移动(const t向量2 &目标);
	void f坐标_重置(const t向量2 &目标);
	void f计算();
	void f更新();
	void f显示() const;
	const t向量2 &fg坐标() const;
	const S图片动画属性 &fg图片动画属性() const;
	void f动画_出现();
	void f动画_消失();
	void f动画_s透明度(float);
public:
	t向量2 m坐标, m目标坐标;
	float m动画帧;
	const C游戏速度 *m游戏速度;
	const S子机属性 *m子机属性;
	std::unique_ptr<C玩家子弹发射器> m发射;
};
class C子机组 {
public:
	void fs子机属性(const S子机属性 *);
	const S子机属性 &f子机属性() const;
	void f关卡初始化();
	void f发射_发射子弹();
	void f发射_停止发射子弹();
	void f计算();
	void f更新();
	void f显示() const;
	void f绑定玩家(C玩家 &);
	void f复活();
	int fg目标子机数() const;
	循环::C范围<std::vector<C子机>> fe使用();
	循环::C范围<const std::vector<C子机>> fe使用c() const;
public:
	std::vector<C子机> ma子机;
	const S子机属性 *m子机属性;
	std::unique_ptr<I子机移动> m子机移动;
	int m数量;
	const boost::rational<int> *m火力;	//指向C玩家::S成绩::m火力
};
struct S子机属性 : public S图片动画属性 {
	int m数量上限;
	t扩展指针<I工厂<C玩家子弹发射器>> m发射;
	t扩展指针<I工厂<I子机移动>> m移动;
	t属性指针<S玩家子弹属性> m子弹属性;
};

}