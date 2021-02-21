#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
enum class E游戏模式;
class W选择模式 : public 用户界面::W窗口框架 {
public:
	enum E标识 {
		e传统模式,
		e完美模式,
		e附加关卡,
		e附加关卡2,
		e关卡练习,
		e弹幕练习,
		c数量,
	};
	static const std::pair<int, std::wstring> ca按钮文本[c数量];
	W选择模式();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};

}	//namespace 东方山寨