export module 东方山寨.界面_选择关卡;
export import "界面包含.h";
import "程序.h";
import 东方山寨.关卡;
import 东方山寨.关卡标识;
import 东方山寨.设置管理;
import 东方山寨.文本管理;
import 东方山寨.界面语言;
export namespace 东方山寨 {
class W选择关卡 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static const 用户界面::S文本样式 c按钮文本样式;
	W选择关卡();
	void f响应_初始化() override;
	void f事件_按键(用户界面::W窗口 & a窗口, const 用户界面::S按键参数 & a按键) override;
	void f事件_刷新文本() override;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W选择关卡::c按钮文本样式 = {16, 用户界面::e居左};
W选择关卡::W选择关卡() {
	const std::tuple<int, std::wstring> va按钮[] = {
		{(int)E关卡::e测试, L"测试"},
		{(int)E关卡::e正式 + 1, L"关卡1"},
		{(int)E关卡::e正式 + 2, L"关卡2"},
		{(int)E关卡::e正式 + 3, L"关卡3"},
		{(int)E关卡::e正式 + 4, L"关卡4"},
		{(int)E关卡::e正式 + 5, L"关卡5"},
		//{(int)E关卡::e正式+6, L"关卡6"},
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
void W选择关卡::f响应_初始化() {
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮);
		vp按钮->f动作_显示();
	}
	f动作_显示();
}
void W选择关卡::f事件_按键(用户界面::W窗口 & a窗口, const 用户界面::S按键参数 & a按键) {
	S游戏设置 &v游戏设置 = C设置管理::fg实例().fg游戏设置();
	switch (a按键.m按键) {
	case 用户界面::E按键::e确定:
		//下一界面
		switch (v游戏设置.m游戏模式) {
		case E游戏模式::e关卡练习:
			v游戏设置.fs关卡(a窗口.m值);
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
void W选择关卡::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
}
}	//namespace 东方山寨