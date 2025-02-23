module;
#include "界面包含.h"
export module 东方山寨.界面_选择模式;
import 东方山寨.关卡;
import 东方山寨.文本管理;
import 东方山寨.关卡标识;
import 东方山寨.设置管理;
export import 东方山寨.界面语言;
enum class E游戏模式;
export namespace 东方山寨 {
class W选择模式 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static const 用户界面::S文本样式 c按钮文本样式;
	enum E标识 {
		e传统模式,
		e完美模式,
		e附加关卡,
		e附加关卡2,
		e关卡练习,
		e弹幕练习,
	};
	W选择模式();
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override;
	void f响应_初始化() override;
	void f事件_刷新文本() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W选择模式::c按钮文本样式 = {16, 用户界面::e居左};
const std::pair<int, std::wstring> ca按钮文本[] = {
	{W选择模式::e传统模式, L"{gamemode.legacy}"},
	{W选择模式::e完美模式, L"{gamemode.perfect}"},
	{W选择模式::e附加关卡, L"{gamemode.extra}"},
	{W选择模式::e附加关卡2, L"{gamemode.extra2}"},
	{W选择模式::e关卡练习, L"{gamemode.stage}"},
	{W选择模式::e弹幕练习, L"{gamemode.barrage}"},
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
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (const int &v按钮序号 : va模式按钮) {
		const auto &[v标识, v文本标识] = ca按钮文本[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		v按钮->f属性_s文本样式(c按钮文本样式);
		v按钮->f属性_s文本模板(v文本标识, va界面文本);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择模式::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	auto &v游戏设置 = C设置管理::fg实例().fg游戏设置();
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e传统模式:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs关卡((int)E关卡::e正式 + 1);	//TODO:增加关卡列表
			break;
		case e完美模式:
			v游戏设置.fs游戏模式(E游戏模式::e完美模式);
			v游戏设置.fs关卡((int)E关卡::e正式 + 1);
			break;
		case e附加关卡:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs关卡((int)E关卡::e正式 + 7);
			break;
		case e附加关卡2:
			v游戏设置.fs游戏模式(E游戏模式::e传统模式);
			v游戏设置.fs关卡((int)E关卡::e正式 + 8);
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
void W选择模式::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
}
}	//namespace 东方山寨