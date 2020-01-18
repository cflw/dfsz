#pragma once
#include "游戏常量.h"
#include "玩家子弹基础.h"
#include "基础_对象数组.h"
namespace 东方山寨::玩家子弹 {
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
	C对象数组<C敌机> *ma敌机 = nullptr;
};
}	//namespace 东方山寨::玩家子弹