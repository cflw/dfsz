module;
#include "界面包含.h"
#include "程序.h"
export module 东方山寨.界面_选择自机;
import 东方山寨.文本管理;
import 东方山寨.设置管理;
export namespace 东方山寨 {
class W选择自机 : public 用户界面::W窗口框架 {
public:
	enum E标识 {
		e测试,
		e灵梦诱导,
		e灵梦集中,
		e魔理沙贯穿,
		e魔理沙范围,
	};
	W选择自机() {
		const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
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
			v按钮->f属性_s文本(v文本, {16, 用户界面::e居左});
			v按钮->f属性_s布局(m布局.f计算生成矩形(0, v标识));
			v按钮->m标志[W窗口::e显示边框] = false;
			v按钮->m标志[W窗口::e显示背景] = false;
			ma按钮.push_back(std::move(v按钮));
		}
	}
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) override {
		auto &v设置 = C设置管理::fg实例().fg游戏设置();
		const auto f设置玩家 = [&](int a自机, int a子机, int a炸弹) {
			v设置.fs自机(a自机);
			v设置.fs子机(a子机);
			v设置.fs炸弹(a炸弹);
		};
		switch (a按键.m按键) {
		case 用户界面::E按键::e确定:
			//设置
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
			//下一界面
			switch (v设置.m游戏模式) {
			case E游戏模式::e传统模式:
				C游戏::fs游戏设置(v设置);
				C程序::f切换游戏状态(E游戏状态::e游戏中);
				break;
			case E游戏模式::e完美模式:
				C游戏::fs游戏设置(v设置);
				C程序::f切换游戏状态(E游戏状态::e游戏中);
				break;
			case E游戏模式::e关卡练习:
				C界面引擎::g这->f切换下个窗口(E窗口::e选择关卡);
				break;
			case E游戏模式::e弹幕练习:
				C界面引擎::g这->f切换下个窗口(E窗口::e选择关卡);
				break;
			}
			break;
		case 用户界面::E按键::e取消:
			C界面引擎::g这->f切换上个窗口();
			break;
		}
	}
	void f响应_初始化() override {
		for (auto &vp按钮 : ma按钮) {
			f动作_添加窗口(*vp按钮);
			vp按钮->f动作_显示();
		}
		f动作_显示();
	}
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
}	//namespace 东方山寨