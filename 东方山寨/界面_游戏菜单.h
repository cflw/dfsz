#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
class W游戏菜单 : public 用户界面::W窗口框架 {
public:
	enum E标识 {
		e回到游戏,
		e回到主菜单,
		e保存录像,
		e重新开始游戏,
		e选项,
	};
	enum E上下文 {
		e游戏暂停,
		e游戏结束,
	};
	W游戏菜单(E上下文);
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
	用户界面::W标签 w游戏标题;
};

}	//namespace 东方山寨