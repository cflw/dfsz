﻿module;
#include "界面包含.h"
export module 东方山寨.界面_选择难度;
import 东方山寨.文本管理;
import 东方山寨.设置管理;
export import 东方山寨.界面语言;
export namespace 东方山寨 {
class W选择难度 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static const 用户界面::S文本样式 c按钮文本样式;
	W选择难度();
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) override;
	void f响应_初始化() override;
	void f事件_刷新文本() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W选择难度::c按钮文本样式 = {16, 用户界面::e居左};
W选择难度::W选择难度() {
	const std::wstring va难度文本[] = {
		L"{difficulty.easy}",
		L"{difficulty.normal}",
		L"{difficulty.hard}",
		L"{difficulty.lunatic}",
		L"{difficulty.torture}",
		L"{difficulty.torture}2",
		L"{difficulty.torture}3",
		L"{difficulty.torture}4",
		L"{difficulty.torture}5",
		L"{difficulty.torture}6",
	};
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	constexpr float c上 = 50;
	用户界面::C单向移动布局 v布局;
	v布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 20));
	v布局.f属性_s倍数移动(1, -1);
	constexpr int v难度上限 = 10;
	for (int i = 0; i != v难度上限; ++i) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(0, i + 1);
		v按钮->f属性_s文本样式(c按钮文本样式);
		v按钮->f属性_s文本模板(va难度文本[i], va界面文本);
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
			C设置管理::fg实例().fg游戏设置().fs基础难度(a窗口.m值);
			break;
		default:
			return;
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
void W选择难度::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
}
}	//namespace 东方山寨