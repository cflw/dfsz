#pragma once
#include "基础_缓冲数组.h"
#include "对象图形.h"
#include "图形_图片.h"
#include "预设图形.h"
namespace 东方山寨 {
class C自机;
class C自机图形_图片 : public C对象图形<C自机, C图片动画图形缓冲>, public C图片动画图形 {
public:
	C自机图形_图片(const C自机 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
	const S图片动画属性 &fg图片动画属性() const override;
};
class C自机图形_线条 : public C对象图形<C自机, 图形::C十字::C图形缓冲> {
public:
	C自机图形_线条(const C自机 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
};
}	//namespace 东方山寨