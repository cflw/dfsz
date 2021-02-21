#include "界面_主菜单.h"
#include "界面包含.h"
#include "程序.h"
#include "程序常量.h"
#include "界面图形.h"
namespace 东方山寨 {
using t向量2 = cflw::数学::S向量2;
//==============================================================================
// 主菜单
//==============================================================================
const std::pair<int, std::wstring> W主菜单::ca按钮文本[c数量] = {
	{e开始游戏, L"main.gamestart"},
	{e录像回放, L"main.replay"},
	{e选项, L"main.option"},
	{e退出, L"main.quit"},
};
const std::wstring W主菜单::c游戏名称标识 = L"gamename";
W主菜单::W主菜单() {
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
	const auto &va界面文本 = C游戏::fg资源().fg界面文本();
	for (const int v按钮序号 : va标题按钮) {
		const auto &[v标识, v文本标识] = ca按钮文本[v按钮序号];
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v标识, 0);
		const std::wstring v文本 = va界面文本[v文本标识];
		v按钮->f属性_s文本(v文本, 16, 用户界面::e居左);
		v按钮->f属性_s布局(v布局.f移动生成矩形());
		v按钮->m标志[W窗口::e显示边框] = false;
		v按钮->m标志[W窗口::e显示背景] = false;
		ma按钮.push_back(std::move(v按钮));
	}
	w游戏标题.f属性_s文本(va界面文本[c游戏名称标识], 24, 用户界面::e居左);
	w游戏标题.f属性_s布局({t向量2(c左对齐, 100), t向量2(100, 20)});
}
void W主菜单::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a按键) {
	if (a按键.m按键 == 用户界面::E按键::e确定) {
		auto &v界面图形 = C程序::fg界面图形();
		bool vi界面图形 = true;
		switch (a窗口.m标识) {
		case e开始游戏:
			C界面引擎::g这->f切换下个窗口(E窗口::e选择模式);
			//C程序::f切换游戏状态(E游戏状态::e游戏中);
			vi界面图形 = false;
			break;
		case e选项:
			C界面引擎::g这->f切换下个窗口(E窗口::e选项);
			vi界面图形 = false;
			break;
		case e退出:
			C程序::f切换游戏状态(E游戏状态::e退出程序);
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
}	//namespace 东方山寨