#pragma once
#include "游戏常量.h"
#include "玩家子弹基础.h"
#include "游戏.h"
namespace 东方山寨 {
namespace 玩家子弹 {
//==============================================================================
// 诱导子弹, 自动跟踪敌机
//==============================================================================
class C诱导 : public C玩家子弹 {
private:
	static constexpr float c初始生命 = 2;
	static constexpr float c角速度 = 数学::c二π<float> / c计算频率;
public:
	C诱导();
	//接口
	void f接口_计算() override;
private:	//扩展
	std::shared_ptr<C敌机> f寻找目标();
	std::weak_ptr<C敌机> m目标;
	float m生命 = c初始生命;	//子弹产生后存在的时间
	C对象数组<C敌机> *ma敌机;
};
//==============================================================================
// 贯穿
//==============================================================================
class C贯穿 : public C玩家子弹 {
private:
	static constexpr float c长度上限 = c屏幕范围r * 2;
	static constexpr float c消失速度 = 4.f;
	static constexpr float c消失间隔 = 1.f / 30.f;
public:
	void f接口_计算() override;
	void f接口_显示() const override;
	void f接口_敌机判定(C敌机与玩家子弹判定 &) override;
	void f接口_命中敌机(const C敌机 &) override;
	t向量2 fg末端() const;
	void f持续();
private:
	float m长度 = 0;
	float m消失 = 0;
	float m消失时间点 = -1;
};

}
}