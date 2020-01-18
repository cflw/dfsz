#pragma once
#include "基础_缓冲数组.h"
#include "对象图形.h"
#include "图形_图片.h"
#include "预设图形.h"
namespace 东方山寨 {
class C敌机;
class C敌机图形_图片 : public C对象图形<C敌机, C图片动画图形缓冲>, public C图片动画图形 {
public:
	C敌机图形_图片(const C敌机 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
	const S图片动画属性 &fg图片动画属性() const override;
};
class C敌机图形_线条 : public C对象图形<C敌机, 图形::C圆形::C图形缓冲> {
public:
	C敌机图形_线条(const C敌机 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
};
}	//namespace 东方山寨