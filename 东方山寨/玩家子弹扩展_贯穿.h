#pragma once
#include "游戏常量.h"
#include "玩家子弹基础.h"
namespace 东方山寨::玩家子弹 {
//==============================================================================
// 贯穿
//==============================================================================
class C贯穿 : public C玩家子弹 {
private:
	static constexpr float c长度上限 = c框架范围r * 2;
	static constexpr float c消失速度 = 4.f;
	static constexpr float c消失间隔 = 1.f / 30.f;
public:
	void f接口_初始化图形(C缓冲数组<I图形缓冲> &) override;
	void f接口_计算() override;
	void f接口_敌机判定(C敌机与玩家子弹判定 &) override;
	void f接口_命中敌机(const C敌机 &) override;
	float fg透明度() const;
	t向量2 fg末端() const;
	void f持续();
public:
	float m长度 = 0;
	float m消失 = 0;
	float m消失时间点 = -1;
};
}	//namespace 东方山寨::玩家子弹