#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
class W选择关卡 : public 用户界面::W窗口框架 {
public:
	W选择关卡();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};

}	//namespace 东方山寨