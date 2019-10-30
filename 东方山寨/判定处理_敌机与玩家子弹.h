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
	bool f玩家子弹_提交判定(const tf判定 &);
	bool f玩家子弹_提交判定(const t圆形 &);
	bool f玩家子弹_提交判定(const t旋转矩形 &);
	C敌机 *m敌机 = nullptr;
	C玩家子弹 *m子弹 = nullptr;
};

}