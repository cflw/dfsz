#pragma once
#include <cflw工具_循环.h>
#include "基础_属性数组.h"
#include "子弹基础.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
class C大子弹 : public C子弹 {
private:
	enum E节点标志 {
		e判定,
		e道具,
	};
	struct S节点 {
		t标志 m标志;
		int m序号;
		S子弹消失 m消失;
	};
	static const float c细分半径;
	static const float c细分直径;
public:
	C大子弹() = default;
	C大子弹(float, float);
	void f接口_初始化() override;
	void f接口_参数初始化(const S子弹参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_i在窗口外() override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
	//初始化
	void f初始化_长宽(float, float = -1);
	//动作
	void f动作_消失(bool);
private:	//扩展
	std::pair<int, int> f扩展_计算限制长宽(int, int);
	void f扩展_节点消失(int);
	void f扩展_节点消失检查();	//如果有节点消失就调用这个
	S节点 &f扩展_取节点(int);
	const S节点 &f扩展_取节点(int) const;
	//节点属性
	int f节点_g一维序号(int, int);	//根据二维序号取一维序号
	std::pair<int, int> f节点_g二维序号(int);	//根据一维序号取二维序号
	t向量2 f节点_g相对坐标(int);	//相对于子弹本身
	t向量2 f节点_g坐标(int);	//根据序号取节点坐标
	int f节点_g坐标对应序号(const t向量2 &);	//根据坐标取节点序号
	float f节点_g相对方向(int);
	float f节点_g方向(int);
	//循环
	std::vector<S节点> &f循环_所有();
	循环::C零散<std::vector<S节点>> &f循环_周围(int);
	//属性
	static C属性数组<std::vector<bool>> ma节点判定;
	float m初始化_长 = 1, m初始化_宽 = 1;
	std::vector<S节点> ma节点;
	int m长数 = 0, m宽数 = 0, m数量 = 0;
	S子弹出现 m出现;
	int m循环缓存_周围节点序号 = -1;
	循环::C零散<std::vector<S节点>> m循环缓存_周围节点循环;
};
}