#pragma once
#include <用户界面_基础.h>
#include "图形包含.h"
#include "输入.h"
namespace 东方山寨 {
enum class E窗口 {
	e主菜单,
	e选择难度,
	e选择玩家,
};
class C界面引擎 {
public:
	static C界面引擎 *g这;
	C界面引擎();
	~C界面引擎();
	void f初始化(二维::C二维 &, C输入引擎 &);
	void f计算();
	void f更新();
	void f显示();
	void fs时钟频率(float, float);
	void f切换窗口(E窗口);
	void f关闭窗口();
private:
	class C实现;
	std::unique_ptr<C实现> m实现;
};
}	//namespace 东方山寨