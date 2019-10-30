#pragma once
#include "基础_数组.h"
#include "子弹图形接口.h"
#include "子弹基础.h"
namespace 东方山寨 {
class C射线激光 : public C子弹 {
private:
	enum E标记 {
		e移动 = C子弹::e自定义,
		e预警线,
		e变化_排序,	//节点表需要重新排序
		e变化_数量,	//数量需要重新计算
		e变化_循环,	//循环缓存重新计算
	};
	struct S消失段 : public C简单游戏对象 {	//记录消失的节点
		int v序号;
		int v下个段;
		数学::S范围<float> v范围;	//数字越大离发射点越远
		S子弹消失 v消失;
	};
	struct S段信息;	//在排序时使用
	static const float c消失段半长度;
	static const float c宽度缩放速度;
	static const float c预警线宽度;
	static const float c炸弹无敌时间;
public:
	C射线激光() = default;
	void f接口_初始化() override;
	void f接口_参数初始化(const S子弹参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_显示() const override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
	//初始化
	void f初始化_长宽(float = -1, float = -1);
	//动作
	void f动作_消失(bool);
	void f动作_预警线(bool);
public:	//扩展
	t向量2 f扩展_取固定端点(float, float = 1);
	float f扩展_g总长() const;
	t向量2 f扩展_g中点() const;
	t向量2 f扩展_g远点() const;
	t向量2 f扩展_g点(float) const;
	//消失段的操作
	void f消失段_新建(float 位置, float 半径 = 0);
	void f消失段_销毁(S消失段 &, int 上个段);
	void f消失段_排序();
	int f消失段_数量();
	//循环
	循环::C零散<std::vector<S消失段>> &f循环_消失段();
private:
	float m初始化_长, m初始化_宽;
	C动态数组<S消失段> ma消失段;
	int m开始段 = -1;	//表示一个消失段的序号
	int m数量 = -1;
	float m炸弹无敌;	//碰到炸弹后有一个无敌时间
	t向量2 m目标;
	S子弹出现 m出现;
	S子弹消失 m消失;
	循环::C零散<std::vector<S消失段>> m循环缓存_消失段;
	C子弹顶点::C直线::ta顶点 ma节点;
	tp子弹图形数据 m图形数据;
};
}