#include <span>
#include <用户界面_布局.h>
#include "界面_窗口类.h"
#include "界面引擎.h"
#include "程序.h"
#include "游戏.h"
#include "游戏设置.h"
#include "标识.h"
#include "取文本.h"
#include "界面图形.h"
namespace 东方山寨 {
using t向量2 = cflw::数学::S向量2;
//==============================================================================
// 主菜单
//==============================================================================
W主菜单::W主菜单() {
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	using t按钮元组 = std::tuple<int, std::wstring>;
	const t按钮元组 va按钮[] = {
		{e开始游戏, va界面文本[L"main.gamestart"]},
		{e录像回放, va界面文本[L"main.replay"]},
		{e选项, va界面文本[L"main.option"]},
		{e退出, va界面文本[L"main.quit"]},
	};
	const int va标题按钮[] = {
		e开始游戏,
		//e录像回放,
		e选项,
		e退出,
	};
	用户界面::C单向移动布局 v布局;
	constexpr float c左对齐 = -200;
	v布局.f属性_s单格布局(t向量2(c左对齐, 50), t向量2(100, 30));
	v布局.f属性_s倍数移动(0, -1);
	for (const int v按钮序号 : va标题按钮) {
		const auto &[v标识, v文本] = va按钮[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		v按钮->f属性_s文本(v文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
	w游戏标题.f属性_s文本(va界面文本[L"gamename"], 24, 用户界面::e居左);
	w游戏标题.f属性_s布局({t向量2(c左对齐, 100), t向量2(100, 20)});
}
void W主菜单::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	if (a按键.m按键 == 用户界面::E按键::e确定) {
		auto &v界面图形 = C程序::fg界面图形();
		bool vi界面图形 = true;
		switch (a窗口.m标识) {
		case e开始游戏:
			C界面引擎::g这->f切换下个窗口(E窗口::e选择难度);
			//C程序::f切换游戏状态(E游戏状态::e游戏中);
			vi界面图形 = false;
			break;
		case e选项:
			C界面引擎::g这->f切换下个窗口(E窗口::e选项);
			vi界面图形 = false;
			break;
		case e退出:
			C程序::f切换游戏状态(E游戏状态::e退出);
			break;
		}
		v界面图形.f标题人物(vi界面图形);
		v界面图形.f云(vi界面图形);
	}
}
void W主菜单::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_添加窗口(w游戏标题);
	w游戏标题.f动作_显示();
	f动作_显示();
	auto &v界面图形 = C程序::fg界面图形();
	v界面图形.f标题人物(true);
	v界面图形.f背景(true);
	v界面图形.f云(true);
}
//==============================================================================
// 游戏菜单
//==============================================================================
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
		std::make_span(va游戏中按钮),
		std::make_span(va游戏结束按钮),
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
//==============================================================================
// 选择难度
//==============================================================================
W选择难度::W选择难度() {
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	const std::wstring va难度文本[] = {
		va界面文本[L"difficulty.easy"],
		va界面文本[L"difficulty.normal"],
		va界面文本[L"difficulty.hard"],
		va界面文本[L"difficulty.lunatic"],
		va界面文本[L"difficulty.torture"],
		va界面文本[L"difficulty.torture"] + L"2",
		va界面文本[L"difficulty.torture"] + L"3",
		va界面文本[L"difficulty.torture"] + L"4",
		va界面文本[L"difficulty.torture"] + L"5",
		va界面文本[L"difficulty.torture"] + L"6",
	};
	constexpr float c上 = 50;
	用户界面::C单向移动布局 v布局;
	v布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 20));
	v布局.f属性_s倍数移动(1, -1);
	const int v难度上限 = 10;
	for (int i = 0; i != v难度上限; ++i) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(0, i + 1);
		v按钮->f属性_s文本(va难度文本[i], 16, 用户界面::e居左);
		v按钮->f属性_s布局(v布局.f计算生成矩形(i / 5, i % 5));
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择难度::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case 0:
			C游戏::fg设置().fs基础难度(a窗口.m值);
			break;
		}
		C界面引擎::g这->f切换下个窗口(E窗口::e选择飞机);
		break;
	case 用户界面::E按键::e取消:
		C界面引擎::g这->f切换上个窗口();
		break;
	}
}
void W选择难度::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
//==============================================================================
// 选择自机
//==============================================================================
W选择自机::W选择自机() {
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	const std::tuple<int, std::wstring> va按钮[] = {
		{e测试, L"测试"},
		{e灵梦诱导, va界面文本[L"character.reimu"] + L"\n    " + va界面文本[L"character.reimu0"]},
		{e灵梦集中, va界面文本[L"character.reimu"] + L"\n    " + va界面文本[L"character.reimu1"]},
		{e魔理沙贯穿, va界面文本[L"character.marisa"] + L"\n    " + va界面文本[L"character.marisa0"]},
		{e魔理沙范围, va界面文本[L"character.marisa"] + L"\n    " + va界面文本[L"character.marisa1"]},
	};
	constexpr float c上 = 50;
	用户界面::C单向移动布局 m布局;
	m布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 40));
	m布局.f属性_s倍数移动(1, -1);
	for (const auto &[v标识, v文本] : va按钮) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		v按钮->f属性_s文本(v文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(m布局.f计算生成矩形(0, v标识));
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择自机::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e测试:
			f设置玩家((int)E自机::e测试, (int)E子机::e测试, (int)E玩家发射::e测试炸弹);
			break;
		case e灵梦诱导:
			f设置玩家((int)E自机::e灵梦, (int)E子机::e灵梦诱导, (int)E玩家发射::e测试炸弹);
			break;
		case e灵梦集中:
			f设置玩家((int)E自机::e灵梦, (int)E子机::e灵梦集中, (int)E玩家发射::e测试炸弹);
			break;
		case e魔理沙贯穿:
			f设置玩家((int)E自机::e魔理沙, (int)E子机::e魔理沙贯穿, (int)E玩家发射::e测试炸弹);
			break;
		case e魔理沙范围:
			f设置玩家((int)E自机::e魔理沙, (int)E子机::e魔理沙范围, (int)E玩家发射::e测试炸弹);
			break;
		}
		C程序::f切换游戏状态(E游戏状态::e游戏中);
		break;
	case 用户界面::E按键::e取消:
		C界面引擎::g这->f切换上个窗口();
		break;
	}
}
void W选择自机::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
void W选择自机::f设置玩家(int a自机, int a子机, int a炸弹) {
	auto &v设置 = C游戏::fg设置();
	v设置.fs自机(a自机);
	v设置.fs子机(a子机);
	v设置.fs炸弹(a炸弹);
}

}	//namespace 东方山寨