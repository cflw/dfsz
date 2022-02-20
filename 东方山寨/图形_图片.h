#pragma once
#include "基础_数组指针.h"
#include "基础_对象工厂.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "图形资源.h"
#include "动画接口.h"
namespace 东方山寨 {
struct S图形参数;
struct S图片动画属性;
//==============================================================================
// 实现
//==============================================================================
class C画图片动画 {
public:
	static void f显示图片(const S纹理 &纹理, const S顶点矩形 *顶点, const S动画缓冲 &动画);
	static void f显示图片2(const S纹理 &纹理, const S顶点矩形 &顶点, const t向量2 &平移, float 旋转, const t向量2 &缩放, float 透明);
	static void f显示图片3(const S纹理 &纹理, const S顶点矩形 &顶点, const t向量2 &平移, const t向量3 &旋转, const t向量3 &缩放, float 透明);
};
//==============================================================================
// 顶点动画,整合画图片的代码
//==============================================================================
struct S图片动画属性 {
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m顶点;
	t扩展指针<I工厂<I动画>> m动画;
	std::shared_ptr<I动画> fc动画(const void *父 = nullptr) const;
};
class C图片动画图形 {
public:
	//属性
	virtual const S图片动画属性 &fg图片动画属性() const = 0;
	void f初始化_父对象(const void *父);
	const S纹理 *fg属性纹理() const;
	const S顶点矩形 *fg属性顶点矩形() const;
	const S顶点矩形 &fg当前顶点矩形() const;
public:
	std::shared_ptr<I动画> m动画 = nullptr;
};
class C图片动画图形缓冲 : public I图形缓冲, public S动画缓冲 {
public:
	C图片动画图形缓冲();
	C图片动画图形缓冲(const C图片动画图形 &);
	using S动画缓冲::operator=;
	void f初始化_图形(const C图片动画图形 &);
	void f显示() const override;
	const S纹理 *m纹理 = nullptr;
	const S顶点矩形 *m顶点 = nullptr;
};
//==============================================================================
// 图片图形
//==============================================================================
class C二维图片图形 : public I粒子, public I事件, public I动画 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标 = t向量2::c零;
		t向量2 m缩放 = t向量2::c一;
		float m旋转 = 0;
		float m透明 = 1;
		const S纹理 *m纹理 = nullptr;
		const S顶点矩形 *m顶点 = nullptr;
	};
	using t图形缓冲 = C图形缓冲;
	C二维图片图形() = default;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_初始化(const S图形参数 &) override;
	t向量3 f接口_g旋转() const override;
	t向量3 f接口_g缩放() const override;
	float f接口_g透明度() const override;
	bool fi纹理() const;
	const S顶点矩形 &fg顶点矩形() const;
protected:
	float m旋转 = 0;
	t向量2 m缩放 = t向量2::c一;
	const S纹理 *m纹理 = nullptr;
	const S顶点矩形 *m顶点 = nullptr;
};
//三维
class C三维图片图形 : public I粒子, public I事件, public I动画 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标 = t向量2::c零;
		t向量3 m缩放 = t向量3::c一;
		t向量3 m旋转 = t向量3::c零;
		float m透明 = 1;
		const S纹理 *m纹理 = nullptr;
		const S顶点矩形 *m顶点 = nullptr;
	};
	using t图形缓冲 = C图形缓冲;
	C三维图片图形() = default;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_初始化(const S图形参数 &) override;
	t向量3 f接口_g旋转() const override;
	t向量3 f接口_g缩放() const override;
	float f接口_g透明度() const override;
	bool fi纹理() const;
	const S顶点矩形 &fg顶点矩形() const;
protected:
	t向量3 m旋转 = t向量3::c零;
	t向量3 m缩放 = t向量3::c一;
	const S纹理 *m纹理 = nullptr;
	const S顶点矩形 *m顶点 = nullptr;
};
}	//namespace 东方山寨