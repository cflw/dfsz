#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
class W主菜单 : public 用户界面::W窗口框架 {
public:
	enum E标识 {
		//标题
		e开始游戏,
		e录像回放,
		e选项,
		e退出,
		c数量,
	};
	static const std::pair<int, std::wstring> ca按钮文本[c数量];
	static const std::wstring c游戏名称标识;
	W主菜单();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
	用户界面::W标签 w游戏标题;
};
}	//namespace 东方山寨