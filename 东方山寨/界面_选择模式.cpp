#include <用户界面_布局.h>
#include "界面_选择模式.h"
#include "界面包含.h"
#include "关卡列表.h"
namespace 东方山寨 {
const std::pair<int, std::wstring> W选择模式::ca按钮文本[c数量] = {
	{e传统模式, L"gamemode.legacy"},
	{e完美模式, L"gamemode.perfect"},
	{e附加关卡, L"gamemode.extra"},
	{e附加关卡2, L"gamemode.extra2"},
	{e关卡练习, L"gamemode.stage"},
	{e弹幕练习, L"gamemode.barrage"},
};
W选择模式::W选择模式() {
	static const int va模式按钮[] = {
		e传统模式,
		e完美模式,
		e附加关卡,
		e关卡练习,
		e弹幕练习,
	};
	constexpr float c上 = 50;
	用户界面::C单向移动布局 v布局;
	v布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 20));
	v布局.f属性_s倍数移动(0, -1);
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	for (const int &v按钮序号 : va模式按钮) {
		const auto &[v标识, v文本标识] = ca按钮文本[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		const std::wstring &v模式文本 = va界面文本[v文本标识];
		v按钮->f属性_s文本(v模式文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择模式::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	auto &v游戏设置 = C游戏::fg设置();
	const auto &va关卡列表 = C关卡列表::fg列表();
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e传统模式:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs进入关卡(va关卡列表.data(), va关卡列表.size());
			break;
		case e完美模式:
			v游戏设置.fs游戏模式(E游戏模式::e完美模式);
			v游戏设置.fs进入关卡(C关卡列表::fg关卡(E关卡::e一));
			break;
		case e附加关卡:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs进入关卡(C关卡列表::fg关卡(E关卡::e附加));
			break;
		case e附加关卡2:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs进入关卡(C关卡列表::fg关卡(E关卡::e附加2));
			break;
		case e关卡练习:
			v游戏设置.fs游戏模式(E游戏模式::e关卡练习);
			break;
		case e弹幕练习:
			v游戏设置.fs游戏模式(E游戏模式::e弹幕练习);
			break;
		default:
			return;
		}
		C界面引擎::g这->f切换下个窗口(E窗口::e选择难度);
		break;
	case 用户界面::E按键::e取消:
		C界面引擎::g这->f切换上个窗口();
		break;
	}
}
void W选择模式::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
}	//namespace 东方山寨