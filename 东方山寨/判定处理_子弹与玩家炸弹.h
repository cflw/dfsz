#pragma once
#include "数学包含.h"
namespace 东方山寨 {
class C子弹;
class C玩家;
class C玩家炸弹;
class C道具制造机;
class C子弹与玩家炸弹判定 {
public:
	typedef std::function<bool(const t向量2 &, float)> tf判定;
	void f绑定道具(C道具制造机 *);
	void f绑定子弹(C子弹 *);
	void f绑定炸弹(C玩家炸弹 *);
	void f计算判定();	//由引擎调用
	bool fi产生道具() const;	//跟据游戏状态确定是否可以产生道具
	bool f炸弹_提交判定(tf判定);
	bool f炸弹_提交判定(const t圆形 &);
	bool f子弹_提交判定(const t向量2 &, float) const;
	void f子弹_产生道具(const t向量2 &坐标, const t向量2 &速度) const;
private:
	C玩家 *m玩家 = nullptr;
	C子弹 *m子弹 = nullptr;
	C玩家炸弹 *m炸弹 = nullptr;
	C道具制造机 *m道具制造机 = nullptr;
	tf判定 mf判定 = nullptr;
};

}