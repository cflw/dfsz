#pragma once
#include "数学包含.h"
namespace 东方山寨 {
class C敌机;
class C玩家子弹;
class C敌机与玩家子弹判定 {
public:
	typedef std::function<bool(const t圆形 &)> tf判定;
	void f绑定敌机(C敌机 &);
	void f绑定玩家子弹(C玩家子弹 &);
	void f绑定游戏速度(float);
	void f计算判定();
	bool f敌机_提交判定(const t圆形 &);
	bool f玩家子弹_提交判定(const tf判定 &);
	bool f玩家子弹_提交判定(const t圆形 &);
	bool f玩家子弹_提交判定(const t旋转矩形 &);
	float f结算_g造成伤害() const;
	C敌机 *m敌机 = nullptr;
	C玩家子弹 *m子弹 = nullptr;
	float m游戏速度;
	t圆形 m敌机判定;
	int m造成伤害 = 0;
};
}	//namespace 东方山寨