#pragma once
#include "对象图形.h"
#include "图形_图片.h"
#include "预设图形.h"
#include "基础_缓冲数组.h"
namespace 东方山寨 {
class C玩家子弹;
struct S玩家子弹属性;
class C玩家子弹图形_图片 : public I对象图形<C玩家子弹> {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标;
		const S玩家子弹属性 *m属性 = nullptr;
		float m方向 = 0;
		float m透明度 = 0;
	};
	using t图形缓冲 = C图形缓冲;
	C玩家子弹图形_图片(const C玩家子弹 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
	I图形缓冲 &fg图形缓冲() const override;
	C图形缓冲 *m图形缓冲 = nullptr;
};
class C玩家子弹图形_线条 : public C对象图形<C玩家子弹, 图形::C圆形::C图形缓冲> {
public:
	C玩家子弹图形_线条(const C玩家子弹 &, C缓冲数组<I图形缓冲> &);
	void f计算() override;
	void f更新() override;
};
}	//namespace 东方山寨