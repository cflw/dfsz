#include <span>
#include "界面_游戏菜单.h"
#include "界面包含.h"
#include "程序.h"
namespace 东方山寨 {
W游戏菜单::W游戏菜单(E上下文 a上下文) {
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	using t按钮元组 = std::tuple<int, std::wstring>;
	const t按钮元组 va按钮[] = {
		{e回到游戏, va界面文本[L"main.returntogame"]},
		{e回到主菜单, va界面文本[L"main.returntotitle"]},
		{e保存录像, va界面文本[L"main.savereplay"]},
		{e重新开始游戏, va界面文本[L"main.gamerestart"]},
		{e选项, va界面文本[L"main.option"]},
	};
	const int va游戏中按钮[] = {
		e回到游戏,
		e回到主菜单,
		e保存录像,
		e重新开始游戏,
		e选项,
	};
	const int va游戏结束按钮[] = {
		e回到游戏,
		e回到主菜单,
		e保存录像,
		e重新开始游戏,
		e选项,
	};
	const std::span<const int> va目标按钮序号[] = {
		std::span(va游戏中按钮),
		std::span(va游戏结束按钮),
	};
	const std::wstring va菜单标题[] = {
		va界面文本[L"menu.gamepause"],
		va界面文本[L"menu.gameover"],
	};
	用户界面::C单向移动布局 v布局;
	constexpr float c左对齐 = -120;
	v布局.f属性_s单格布局(t向量2(c左对齐, 50), t向量2(100, 30));
	v布局.f属性_s倍数移动(0, -1);
	for (const int v按钮序号 : va目标按钮序号[a上下文]) {
		const auto &[v标识, v文本] = va按钮[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		v按钮->f属性_s文本(v文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
	w游戏标题.f属性_s文本(va菜单标题[a上下文], 24, 用户界面::e居左);
	w游戏标题.f属性_s布局({t向量2(c左对齐, 100), t向量2(100, 20)});
}
void W游戏菜单::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	if (a参数.m按键 == 用户界面::E按键::e确定) {
		switch (a窗口.m标识) {
		case E标识::e回到游戏:
			C程序::f切换游戏状态(E游戏状态::e游戏中);
			break;
		case E标识::e回到主菜单:
			C程序::f切换游戏状态(E游戏状态::e主菜单);
			break;
		case E标识::e选项:
			C界面引擎::g这->f切换下个窗口(E窗口::e选项);
			break;
		}
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