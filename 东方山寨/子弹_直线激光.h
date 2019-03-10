#pragma once

#include "子弹基础.h"
namespace 东方山寨 {
class C直线激光 : public C子弹 {
public:
	struct S节点 {
		S子弹消失 v消失;
	};
	void f接口_初始化() override;
	void f接口_参数初始化(const S子弹参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_显示() const override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_i在窗口外() override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
	//初始化
	void f初始化_长宽(float, float = 1);
	//动作
	void f动作_消失(bool);
	//扩展
	t向量2 f扩展_取固定端点(float, float);
	t向量2 f扩展_取显示端点(float);
	t向量2 f扩展_取判定端点(float);
	t向量2 f扩展_取节点坐标(int);
	S节点 &f扩展_取节点(int);
	S节点 &f扩展_取坐标最近节点(const t向量2 &);
	//属性
	t向量2 m初始化_长宽;
	std::vector<S节点> ma节点;	//从后到前
	S子弹出现 m出现;
	t向量2 m目标;
	tp子弹图形数据 m图形数据;
};
}	//namespace 东方山寨