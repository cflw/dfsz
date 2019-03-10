#pragma once
#include "玩家子弹基础.h"
namespace 东方山寨 {
namespace 玩家子弹 {
class C贯穿 : public C玩家子弹 {
private:
	struct S状态 : public C简单游戏对象 {
		t向量2 *v绑定坐标;
		t向量2 v相对坐标;	//相对于绑定坐标
		int v坐标序号;
		int v数量序号;
		float v长度;
		float v消失;
		void fs相对坐标(const t向量2 &);
		t向量2 fg实坐标() const;
	};
	C动态数组<S状态> v状态组;
	static const float c长度上限;
	static const float c消失速度;
public:
	void f接口_初始化() override;
	void f接口_销毁() override;
	void f接口_计算() override;
	void f接口_显示() override;
	void f接口_敌机判定(C敌机与玩家子弹判定 &) override;
	void f接口_发射() override;
private:
	S状态 &f扩展_状态();
	t向量2 fg末端();
};

}
}