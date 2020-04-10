#pragma once
#include <cflw工具_循环.h>
#include "子弹基础.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
class C曲线激光 : public C子弹 {
public:
	static constexpr float c默认长度 = 20;
	static constexpr float c默认精度 = 0.25f;
	static constexpr float c默认计算周期 = 1.f / c默认精度;
	struct S节点 {
		int m序号 = -1;
		t向量2 m原坐标;
		t向量2 m坐标;
		t向量2 m速度;
		float m方向 = 0;
		t颜色 m颜色;
		S子弹消失 m消失;
		bool mi道具 = true;
		void f更新(const t向量2 &, const t向量2 &, float, const t颜色 &);
	};
	void f接口_初始化() override;
	void f接口_参数初始化(const S子弹参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_i在窗口外() override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
	//初始化
	void f初始化_长宽(float, float = 1);
	void f初始化_精度(float);
	//动作
	void f动作_消失(bool);
	//扩展
	S节点 &f扩展_取节点(int);
	const S节点 &f扩展_取节点(int) const;
	S节点 &f扩展_取头节点();
	S节点 &f扩展_取尾节点();
	void f扩展_更新头节点();
	void f扩展_节点消失(int);
	void f扩展_节点消失检查();	//如果有节点消失就调用这个
	std::vector<S节点> &f循环_全部();
	循环::C范围<std::vector<S节点>> f循环_范围(int, int);
	循环::C零散<std::vector<S节点>> f循环_周围(int 节点序号);
	//属性
	float m初始化_长度 = c默认长度, m初始化_宽度 = 1, m初始化_精度 = c默认精度;
	std::vector<S节点> ma节点;
	S子弹出现 m出现;
	float m计算计时 = 0;
	float m计算周期 = c默认计算周期;
};
}	//namespace 东方山寨