#pragma once
#include "子弹基础.h"
namespace 东方山寨 {
class C普通子弹 : public C子弹 {
public:
	void f接口_初始化() override;
	void f接口_参数初始化(const S子弹参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_i在窗口外() override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
	//动作
	void f动作_消失(bool 动画 = true);
	//属性
	S子弹出现 m出现;
	S子弹消失 m消失;
};
}	//namespace 东方山寨