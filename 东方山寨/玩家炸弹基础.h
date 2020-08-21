#pragma once
#include "玩家子弹基础.h"
#include "玩家子弹发射基础.h"
#include "判定处理_子弹与玩家炸弹.h"
namespace 东方山寨 {
//玩家炸弹接口
class C玩家炸弹 : public C玩家子弹 {
public:
	static constexpr float c判定半径 = 16;
	//炸弹事件
	float f接口_g判定半径() const override;	//如是派生类不是圆形判定就不用重写
	bool f接口_敌机判定(C敌机与玩家子弹判定 &) override;	//如是派生类是圆形判定就不用重写
	virtual bool f接口_子弹判定(C子弹与玩家炸弹判定 &);	//如是派生类是圆形判定就不用重写
	virtual bool f接口_i产生道具() const;
};
//发射并控制炸弹
class C玩家炸弹发射器 : public C玩家子弹发射器 {
public:
	void f接口_初始化() override;
	void f接口_计算() override;
};
//按一次x发射一次炸弹的发射器
template<typename t玩家炸弹>
class C玩家炸弹简单发射器 : public C玩家炸弹发射器 {
public:
	void f接口_产生子弹() override {
		m子弹制造机->m参数.m坐标 = m发射环境->fg发射坐标();
		m子弹制造机->f产生炸弹<t玩家炸弹>();
	}
};
}