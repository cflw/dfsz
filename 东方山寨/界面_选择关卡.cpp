#include <用户界面_布局.h>
#include "界面_选择关卡.h"
#include "界面包含.h"
#include "关卡列表.h"
#include "程序.h"
namespace 东方山寨 {
W选择关卡::W选择关卡() {
	const std::tuple<E关卡, std::wstring> va按钮[] = {
		{E关卡::e测试, L"测试"},
		{E关卡::e一, L"关卡1"},
		{E关卡::e二, L"关卡2"},
		{E关卡::e三, L"关卡3"},
		{E关卡::e四, L"关卡4"},
		{E关卡::e五, L"关卡5"},
		//{E关卡::e六, L"关卡6"},
	};
	constexpr float c上 = 50;
	用户界面::C单向移动布局 m布局;
	m布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 20));
	m布局.f属性_s倍数移动(0, -1);
	for (const auto &[v关卡, v文本] : va按钮) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(0, (int)v关卡);
		v按钮->f属性_s文本(v文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(m布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择关卡::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	auto &v游戏设置 = C游戏::fg设置();
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定:
		//设置
		v游戏设置.fs进入关卡(C关卡列表::fg关卡((E关卡)a窗口.m值));
		//下一界面
		switch (v游戏设置.m游戏模式) {
		case E游戏模式::e关卡练习:
			C程序::f切换游戏状态(E游戏状态::e游戏中);
			break;
		case E游戏模式::e弹幕练习:
			C界面引擎::g这->f切换下个窗口(E窗口::e选择弹幕);
			break;
		default:
			return;
		}
		break;
	case 用户界面::E按键::e取消:
		C界面引擎::g这->f切换上个窗口();
		break;
	}
}
void W选择关卡::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
}	//namespace 东方山寨