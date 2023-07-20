module;
#include <span>
#include "界面包含.h"
#include "程序.h"
export module 东方山寨.界面_游戏菜单;
import 东方山寨.文本管理;
import 东方山寨.游戏录像管理;
import 东方山寨.界面语言;
export namespace 东方山寨 {
class W游戏菜单 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static const 用户界面::S文本样式 c按钮文本样式;
	static const 用户界面::S文本样式 c菜单文本样式;
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
		e游戏通关,
	};
	W游戏菜单(E上下文 a上下文);
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override;
	void f事件_刷新文本() override;
	void f响应_初始化() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
	用户界面::W标签 w游戏标题;
	E上下文 m上下文;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W游戏菜单::c按钮文本样式 = {16, 用户界面::e居左};
const 用户界面::S文本样式 W游戏菜单::c菜单文本样式 = {24, 用户界面::e居左};
const std::tuple<int, std::wstring> ca按钮[] = {
	{W游戏菜单::e回到游戏, L"{main.returntogame}"},
	{W游戏菜单::e回到主菜单, L"{main.returntotitle}"},
	{W游戏菜单::e保存录像, L"{main.savereplay}"},
	{W游戏菜单::e重新开始游戏, L"{main.gamerestart}"},
	{W游戏菜单::e选项, L"{main.option}"},
};
const int ca游戏中按钮[] = {
	W游戏菜单::e回到游戏,
	W游戏菜单::e回到主菜单,
	W游戏菜单::e保存录像,
	W游戏菜单::e重新开始游戏,
	W游戏菜单::e选项,
};
const int ca游戏结束按钮[] = {
	W游戏菜单::e回到主菜单,
	W游戏菜单::e保存录像,
	W游戏菜单::e重新开始游戏,
	W游戏菜单::e选项,
};
const int ca游戏通关按钮[] = {
	W游戏菜单::e回到主菜单,
	W游戏菜单::e保存录像,
	W游戏菜单::e重新开始游戏,
	W游戏菜单::e选项,
};
const std::span<const int> ca目标按钮序号[] = {
	std::span(ca游戏中按钮),
	std::span(ca游戏结束按钮),
	std::span(ca游戏通关按钮),
};
const std::wstring ca菜单标题[] = {
	L"{menu.gamepause}",
	L"{menu.gameover}",
	L"{menu.gameclear}",
};
W游戏菜单::W游戏菜单(E上下文 a上下文):
	m上下文(a上下文) {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	用户界面::C单向移动布局 v布局;
	constexpr float c左对齐 = -120;
	v布局.f属性_s单格布局(t向量2(c左对齐, 50), t向量2(100, 30));
	v布局.f属性_s倍数移动(0, -1);
	for (const int v按钮序号 : ca目标按钮序号[a上下文]) {
		const auto &[v标识, v文本] = ca按钮[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		v按钮->f属性_s文本样式(c按钮文本样式);
		v按钮->f属性_s文本模板(v文本, va界面文本);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
	w游戏标题.f属性_s文本样式(c菜单文本样式);
	w游戏标题.f属性_s文本模板(ca菜单标题[a上下文], va界面文本);
	w游戏标题.f属性_s布局({t向量2(c左对齐, 100), t向量2(100, 20)});
}
void W游戏菜单::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case E标识::e回到游戏:
			C程序::f切换游戏状态(E游戏状态::e游戏中);
			break;
		case E标识::e回到主菜单:
			C程序::f切换游戏状态(E游戏状态::e主菜单);
			break;
		case E标识::e保存录像:
			C游戏录像管理::g这->f保存录像();
			break;
		case E标识::e选项:
			C界面引擎::g这->f切换下个窗口(E窗口::e选项);
			break;
		}
		break;
	case 用户界面::E按键::e取消:
		if (m上下文 != E上下文::e游戏暂停) {
			break;
		}
		if (a窗口.m标识 == E标识::e回到游戏) {
			C程序::f切换游戏状态(E游戏状态::e游戏中);
		} else {
			ma按钮[0]->f动作_获得焦点();
		}
		break;
	}
}
void W游戏菜单::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
}
void W游戏菜单::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_添加窗口(w游戏标题);
	w游戏标题.f动作_显示();
	f动作_显示();
}
}	//namespace 东方山寨