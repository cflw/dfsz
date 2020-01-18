#pragma once
#include "动画接口.h"
namespace 东方山寨 {
class C道具;
struct S道具属性;
class C道具动画 : public I动画 {
public:
	t向量3 f接口_g缩放() const override;
	void f接口_s父对象(const void *) override;
	void f接口_计算() override;
	void f接口_更新() override;
	float f接口_g透明度() const override;
	const C游戏速度 *f接口_g游戏速度() const override;
	const C道具 *m道具 = nullptr;	//只能在计算中访问
	const S道具属性 *m道具属性 = nullptr;
	float m计算插值 = 0;
	float m渲染插值 = 0;
};
}