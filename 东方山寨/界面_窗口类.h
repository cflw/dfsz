#pragma once
#include <用户界面_控件.h>
namespace 东方山寨 {
class W主菜单 : public 用户界面::W窗口 {
public:
	enum E标识 {
		e开始游戏,
		e录像回放,
		e设置,
		e退出,
	};
	W主菜单();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
class W选择模式 : public 用户界面::W窗口 {
public:
	enum E标识 {
		e传统模式,
		e附加关卡,
		e关卡练习,
		e符卡练习,
	};
};
class W选择难度 : public 用户界面::W窗口 {
public:
	W选择难度();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
class W选择自机 : public 用户界面::W窗口 {
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
	void f设置玩家(int, int, int);
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
class W设置 : public 用户界面::W窗口 {
public:
	enum E标识 {
		e游戏,
		e图形,
		e声音,
		e手柄,
		e触摸,
	};
};
class W玩家身份 : public 用户界面::W窗口 {
public:
};
class W语言设置 : public 用户界面::W窗口 {

};
class W图形设置 : public 用户界面::W窗口 {
public:
};
class W声音设置 : public 用户界面::W窗口 {
public:
};
class W手柄设备 : public 用户界面::W窗口 {
public:

};
class W触摸设备 : public 用户界面::W窗口 {
public:

};

}