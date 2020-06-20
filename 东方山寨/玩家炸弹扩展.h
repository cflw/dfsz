#pragma once
#include "玩家炸弹基础.h"
#include "边框常量.h"
namespace 东方山寨::玩家炸弹 {
class C全屏清弹 : public C玩家炸弹 {
public:
	static constexpr float c最大半径 = c框架范围r * 1.5f;
	C全屏清弹() = default;
	C全屏清弹(float, bool);
	void f接口_计算() override;
	float f接口_g判定半径() const override;
	bool f接口_i产生道具() const override;
private:	//扩展
	float m扩散速度 = c最大半径;
	float m半径 = 0;
	float m寿命 = 1;
	bool m道具 = false;
};
//测试用炸弹
class C风神录 : public C玩家炸弹 {
public:
	static constexpr float c判定半径 = 128;
	static constexpr float c寿命 = 3;
	static constexpr float c速度y = 64;
	void f接口_计算() override;
	void f接口_初始化(const S玩家子弹参数 &) override;
	float f接口_g判定半径() const override;
	float m寿命 = c寿命;
};
}	//namespace 东方山寨::玩家炸弹