#pragma once
#include "敌机基础.h"
namespace 东方山寨 {
//敌机扩展生命,可以套娃
class C敌机扩展生命 : public C敌机 {
public:
	static constexpr float c判定半径 = 64;
	static const S敌机属性 c属性;
	C敌机扩展生命(C敌机 &, bool 目标无敌 = true);
	void f接口_计算() override;
	bool f接口_玩家子弹判定(C敌机与玩家子弹判定 &);
	void f接口_初始化() override;
	void f接口_击破() override;
	C敌机 *m目标 = nullptr;	//指向前一个,可能是 C敌机扩展生命
	C敌机 *m源头 = nullptr;	//总是指向一开始的敌机,节省循环开销
	bool m目标无敌 = true;
};
}	//namespace 东方山寨