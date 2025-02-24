﻿export module 东方山寨.敌机图形;
export import "基础_缓冲数组.h";
export import "对象图形.h";
export import "图形_图片.h";
export import "预设图形.h";
import "敌机基础.h";
import "图层.h";
import "动画接口.h";
import "动画.h";
export namespace 东方山寨 {
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
module: private;
namespace 东方山寨 {
//==============================================================================
// 图片
//==============================================================================
C敌机图形_图片::C敌机图形_图片(const C敌机 &a对象, C缓冲数组<I图形缓冲> &aa图形缓冲):
	C对象图形<C敌机, C图片动画图形缓冲>(a对象, aa图形缓冲) {
	C图片动画图形::f初始化_父对象(&a对象);
	m图形缓冲->f初始化_图层((int)E图层::e敌机);
	m图形缓冲->f初始化_图形(*this);
}
void C敌机图形_图片::f计算() {
	m动画->f接口_动作(E动画动作::e水平移动, 数学::f取符号<float>(m对象->m速度.x, 1));
	m动画->f接口_计算();
}
void C敌机图形_图片::f更新() {
	m动画->f接口_更新();	//C角色动画
	*m图形缓冲 = m动画->fg动画缓冲();
	m图形缓冲->m坐标 += m对象->m坐标;
	m图形缓冲->m透明度 *= m对象->fg透明度();
}
const S图片动画属性 &C敌机图形_图片::fg图片动画属性() const {
	return *m对象->m敌机属性;
}
//==============================================================================
// 线条
//==============================================================================
C敌机图形_线条::C敌机图形_线条(const C敌机 &a对象, C缓冲数组<I图形缓冲> &aa图形缓冲):
	C对象图形<C敌机, 图形::C圆形::C图形缓冲>(a对象, aa图形缓冲) {
	m图形缓冲->f初始化_图层((int)E图层::e敌机);
}
void C敌机图形_线条::f计算() {
}
void C敌机图形_线条::f更新() {
	m图形缓冲->m颜色 = t颜色::c白;
	m图形缓冲->m颜色.a = m对象->fg透明度();
	m图形缓冲->m坐标 = m对象->m坐标;
	m图形缓冲->m半径 = 16;
}
}	//namespace 东方山寨