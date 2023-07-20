module;
#include "界面包含.h"
#include "关卡.h"
#include "程序.h"
export module 东方山寨.界面_选择符卡;
import 东方山寨.关卡标识;
import 东方山寨.设置管理;
import 东方山寨.文本管理;
export import 东方山寨.界面语言;
export namespace 东方山寨 {
class W选择符卡 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static const 用户界面::S文本样式 c按钮文本样式;
	W选择符卡();
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override;
	void f响应_初始化() override;
	void f事件_刷新文本() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W选择符卡::c按钮文本样式 = {16, 用户界面::e居左};
W选择符卡::W选择符卡() {
	const std::tuple<int, std::wstring> va按钮[] = {
		{0, L"测试"},
		{1, L"测试1"},
		{2, L"测试2"},
		{3, L"测试3"},
		{4, L"测试4"},
		{5, L"测试5"},
	};
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	constexpr float c上 = 50;
	用户界面::C单向移动布局 m布局;
	m布局.f属性_s单格布局(t向量2(-200, c上), t向量2(100, 20));
	m布局.f属性_s倍数移动(0, -1);
	for (const auto &[v关卡, v文本] : va按钮) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(0, (int)v关卡);
		v按钮->f属性_s文本样式(c按钮文本样式);
		v按钮->f属性_s文本模板(v文本, va界面文本);
		v按钮->f属性_s布局(m布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选择符卡::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	S游戏设置 &v游戏设置 = C设置管理::fg实例().fg游戏设置();
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case 0:	//符卡
			//v游戏设置.fs符卡编号(a窗口.m值);
			v游戏设置.fs关卡((int)E关卡::e符卡 + a窗口.m值);
			C程序::f切换游戏状态(E游戏状态::e游戏中);
			break;
		}
		break;
	case 用户界面::E按键::e取消:
		C界面引擎::g这->f切换上个窗口();
		break;
	}
}
void W选择符卡::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
void W选择符卡::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
}
}	//namespace 东方山寨