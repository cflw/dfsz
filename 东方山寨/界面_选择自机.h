#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
class W选择自机 : public 用户界面::W窗口框架 {
public:
	enum E标识 {
		e测试,
		e灵梦诱导,
		e灵梦集中,
		e魔理沙贯穿,
		e魔理沙范围,
	};
	W选择自机();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};

}	//namespace 东方山寨