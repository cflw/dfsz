#pragma once
#include "动画接口.h"
namespace 东方山寨 {
//=============================================================================
// 角色动画
//=============================================================================
class C角色动画 : public I动画 {
public:
	struct S属性 {
		struct S动画方向 {
			int m序号;
			int m循环;
			int m帧数;
			float m变化速度;
			float m循环速度;
			bool m境像;
		};
		S动画方向 m正常, m左移, m右移;
	};
	class C工厂 : public I工厂<I动画> {
	public:
		C工厂(const std::shared_ptr<S属性> &);
		I动画 *f接口_新建() const override;
		std::shared_ptr<S属性> m属性;
	};
	C角色动画(const std::shared_ptr<S属性> &);
	void f接口_更新() override;
	void f接口_动作(const E动画动作 &, const t动画动作值 &) override;
	int f接口_g顶点序号() const override;
	t向量3 f接口_g缩放() const override;
	float f接口_g透明度() const override;
	void f动作_正常();
	void f动作_水平移动(float);
	void f动作_左移();
	void f动作_右移();
	void f动作_透明度(float);
private:
	std::shared_ptr<S属性> m属性 = nullptr;
	float m动画帧 = 0;
	float m透明度 = 0;
	const S属性::S动画方向 *m动画方向 = nullptr;
	const S属性::S动画方向 *m目标方向 = nullptr;
};
//=============================================================================
// 变换动画
//=============================================================================
class C二维变换动画 : public I动画 {
public:
	using tf计算 = std::function<void(C二维变换动画 &)>;
	C二维变换动画() = default;
	C二维变换动画(float a旋转, const t向量2 &a缩放, const tf计算 &af计算);
	void f接口_计算() override;
	t向量3 f接口_g旋转() const override;
	t向量3 f接口_g缩放() const override;
public:
	float m旋转 = 0;
	t向量2 m缩放 = t向量2::c一;
	tf计算 mf计算 = nullptr;
};
class C三维变换动画 : public I动画 {
public:
	using tf计算 = std::function<void(C三维变换动画 &)>;
	C三维变换动画() = default;
	C三维变换动画(const t向量3 &a旋转, const t向量3 &a缩放, const tf计算 &a计算);
	void f接口_计算() override;
	t向量3 f接口_g旋转() const override;
	t向量3 f接口_g缩放() const override;
public:
	t向量3 m旋转 = t向量3::c零;
	t向量3 m缩放 = t向量3::c一;
	tf计算 mf计算 = nullptr;
};

}