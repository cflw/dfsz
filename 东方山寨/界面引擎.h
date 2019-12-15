#pragma once
#include <stack>
#include <用户界面_基础.h>
namespace 东方山寨 {
class C图形引擎;
class C输入引擎;
class C音频引擎;
enum class E窗口 {
	e主菜单,
	e选择难度,
	e选择飞机,
	e选项,
	e游戏暂停,
	e游戏结束,
};
class C界面引擎 {
public:
	static C界面引擎 *g这;
	C界面引擎();
	~C界面引擎();
	void f初始化0(C图形引擎 &, C输入引擎 &);	//在程序启动时调用
	void f初始化0_图形(C图形引擎 &);
	void f初始化1(C音频引擎 &);	//载入完成时调用
	void f输入_接收字符(wchar_t);//在窗口过程WM_CHAR消息中调用
	void f计算();
	void f更新();
	void f显示();
	void fs时钟频率(float, float);
	void f切换下个窗口(E窗口);
	void f切换上个窗口();
	void f关闭窗口();
private:
	class C实现;
	std::unique_ptr<C实现> m实现;
	std::stack<用户界面::W窗口 *> m窗口栈;
};
}	//namespace 东方山寨