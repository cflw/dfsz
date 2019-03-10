#pragma once
#include "玩家子弹基础.h"
namespace 东方山寨 {
namespace 玩家子弹 {
//诱导子弹, 自动跟踪敌机
class C诱导 : public C玩家子弹 {
private:
	struct S状态 : public C简单游戏对象 {
		C敌机 *v目标;
		float v生命;	//子弹产生后存在的时间
	};
	C动态数组<S状态> v状态组;
	C静态数组<C敌机> *va敌机;
	static const float c初始生命;
public:	//接口
	void f接口_初始化() override;
	void f接口_销毁() override;
	void f接口_计算() override;
private:	//扩展
	S状态 &f扩展_状态();
	C敌机 *f扩展_寻找目标();
};

}
}