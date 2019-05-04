#pragma once
#include <optional>
#include <用户界面_控件.h>
#include <用户界面_布局.h>
namespace 东方山寨 {
using t向量2 = cflw::数学::S向量2;
constexpr float c选项窗口宽 = 300;
constexpr float c选项窗口高 = 250;
//==============================================================================
// 模板
//==============================================================================
class W选项列表 : public 用户界面::W窗口 {
public:
	static constexpr float c行高 = 20;
	static constexpr float c行距 = c行高 * 0.5f;
	struct S行 {
		std::unique_ptr<用户界面::W标签> w名称;
		std::unique_ptr<用户界面::W窗口> w控制;
	};
	W选项列表();
	void f响应_初始化() override;
	void f属性_s布局(const 用户界面::S布局参数 &) override;
	void f添加行(const std::wstring_view &, std::unique_ptr<用户界面::W窗口> &&);
	std::vector<S行> ma行;
	用户界面::C表格排行布局 m行布局;
};
//==============================================================================
// 详细选项
//==============================================================================
class W玩家帐户 : public W选项列表 {
public:
	W玩家帐户();
};
class W语言设置 : public W选项列表 {

};
class W图形设置 : public W选项列表 {
public:
	enum E标识 {
		e分辨率,
	};
	enum E分辨率 {
		//4:3
		e800x600,
		e960x720,
		e1024x768,
		e1280x960,
		//16:9
		e1280x720,
		e1366x768,
		e1440x900,
		e1920x1080,	//1080p
		e3840x2160,	//4k
		e7680x4320,	//8k
		//3:2
		e1800x1200,	//surface go
		e2160x1440,	//surface pro3
		e2736x1824,	//surface pro4
		e3000x2000,	//surface book 13.5英寸
		e3240x2160,	//surface book 15英寸
	};
	W图形设置();
	void f事件_窗口值变化(用户界面::W窗口 &, const int &, int &) override;
	std::optional<std::pair<int, int>> fg分辨率() const;
	std::map<int, std::pair<int, int>> ma分辨率;
	int m分辨率 = -1;
};
class W声音设置 : public W选项列表 {
public:
};
class W手柄设备 : public W选项列表 {
public:

};
class W触摸设备 : public W选项列表 {
public:

};
//==============================================================================
// 选项
//==============================================================================
class W选项 : public 用户界面::W窗口 {
public:
	static constexpr float c宽 = c选项窗口宽;
	static constexpr float c高 = c选项窗口高;
	enum E页标识 {
		e游戏,
		e图形,
		e声音,
		e手柄,
		e触摸,
	};
	enum E按钮 {
		e确定,
		e取消,
		e应用,
		e默认,
	};
	W选项();
	void f事件_按键(用户界面::W窗口 &, const 用户界面::S按键参数 &) override;
	void f响应_初始化() override;
	用户界面::W选项卡组 w选项卡组;
	W玩家帐户 w玩家帐户;
	W图形设置 w图形设置;
	std::vector<W选项列表 *> ma页;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;	//底部按钮
};

}