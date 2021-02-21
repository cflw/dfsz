#pragma once
#include "图形资源.h"
#include "对象图形.h"
#include "图形_图片.h"
#include "预设图形.h"
#include "基础_缓冲数组.h"
namespace 东方山寨 {
class C玩家子弹;
struct S玩家子弹属性;
namespace 玩家子弹 {
class C贯穿激光图形_图片 : public I对象图形<C玩家子弹> {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标;
		S顶点矩形 m矩形;
		const S玩家子弹属性 *m属性 = nullptr;
		float m方向 = 0;
		float m透明度 = 0;
	};
	C贯穿激光图形_图片(const C玩家子弹 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
	I图形缓冲 &fg图形缓冲() const override;
	C图形缓冲 *m图形缓冲 = nullptr;
};
class C贯穿激光图形_线条 : public I对象图形<C玩家子弹> {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标, m末端;
		const S玩家子弹属性 *m属性 = nullptr;
		float m透明度 = 0;
	};
	C贯穿激光图形_线条(const C玩家子弹 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
	I图形缓冲 &fg图形缓冲() const override;
	C图形缓冲 *m图形缓冲 = nullptr;
};
}	//namespace 玩家子弹
}	//namespace 东方山寨