module;
#include <ranges>
#include "界面包含.h"
#include "程序设置.h"
export module 东方山寨.界面_选项;
import 东方山寨.设置管理;
import 东方山寨.文本管理;
export import 用户界面.控件;
export import 东方山寨.界面_选项.选项列表;
import 东方山寨.界面_选项.玩家账户;
import 东方山寨.界面_选项.语言设置;
import 东方山寨.界面_选项.图形设置;
import 东方山寨.界面语言;
export namespace 东方山寨 {
using t向量2 = cflw::数学::S向量2;
//==============================================================================
// 选项
//==============================================================================
class W选项 : public 用户界面::W窗口, public I跟踪界面语言 {
public:
	static constexpr float c宽 = 300;	//选项窗口宽高
	static constexpr float c高 = 250;
	enum E页标识 {
		e游戏,
		e图形,
		e声音,
		e手柄,
		e触摸,
	};
	enum E按钮 {
		e确定,
		e取消,
		e应用,
		e默认,
	};
	W选项() = default;
	void f响应_载入() override;
	void f响应_初始化() override;
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override;
	void f事件_刷新文本() override;
	用户界面::W选项卡组 w选项卡组;
	//W声音设置 w声音设置;
	//W手柄设置 w手柄设置;
	//W触摸设置 w触摸设置;
	std::vector<std::unique_ptr<W选项列表>> ma选项列表;
	std::vector<W选项列表 *> ma页;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;	//底部按钮
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void W选项::f响应_载入() {
	constexpr float c按钮高 = 30;
	w选项卡组.f属性_s布局({ t向量2::c零, t向量2(c宽, c高) });
	w选项卡组.f属性_s页按钮尺寸(t向量2(80, c按钮高));
	//w选项卡组.f属性_s文本大小(20);
	//选项卡
	const std::tuple<W选项列表 *, std::wstring_view> va页[] = {
		{new W玩家帐户(), L"{tab.player}"},
		{new W语言设置(), L"{tab.language}"},
		{new W图形设置(), L"{tab.graphic}"},
	};
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (const auto &[vp窗口, v标签] : va页) {
		ma选项列表.emplace_back(vp窗口);
		auto &v页 = ma页.emplace_back(vp窗口);
		w选项卡组.f动作_添加页(*vp窗口, v标签, va界面文本);
	}
	//按钮
	const std::tuple<int, std::wstring_view> va按钮[] = {
		{e确定, L"{button.ok}"},
		{e取消, L"{button.cancel}"},
		{e应用, L"{button.apply}"},
		{e默认, L"{button.default}"},
	};
	用户界面::C单向移动布局 v按钮布局;
	constexpr float c按钮栏左 = -c宽 * 0.5f;
	constexpr float c按钮栏右 = c宽 * 0.5f;
	constexpr float c按钮栏上 = -c高 * 0.5f;
	constexpr float c按钮栏下 = c按钮栏上 - c按钮高;
	const t矩形 v按钮栏 = t矩形::fc左上右下(c按钮栏左, c按钮栏上, c按钮栏右, c按钮栏下);
	v按钮布局.f属性_s网格布局(v按钮栏.fg中心(), v按钮栏.fg尺寸(), std::distance(std::begin(va按钮), std::end(va按钮)));
	v按钮布局.f属性_s倍数移动(1, 0);
	for (const auto &[v按钮标识, v按钮键名] : va按钮) {
		std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v按钮标识);
		v按钮->f属性_s布局(v按钮布局.f移动生成矩形());
		v按钮->f属性_s文本模板(v按钮键名, va界面文本);
		ma按钮.push_back(std::move(v按钮));
	}
}
void W选项::f响应_初始化() {
	f动作_添加窗口(w选项卡组);
	w选项卡组.f动作_显示();
	for (auto &vp按钮 : ma按钮) {
		f动作_添加窗口(*vp按钮, true);
	}
	f动作_显示();
}
void W选项::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	switch (a参数.m按键) {
	case 用户界面::E按键::e确定:
		switch (a窗口.m标识) {
		case e确定:
			for (auto &vp选项列表 : ma选项列表) {
				vp选项列表->f事件_确定();
			}
			//结束
			C界面引擎::g这->f切换上个窗口();
			break;
		case e取消:
			for (auto &vp选项列表 : ma选项列表) {
				vp选项列表->f事件_取消();
			}
			C界面引擎::g这->f切换上个窗口();
			break;
		}
	}
}
void W选项::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &vp按钮 : ma按钮) {
		vp按钮->f生成文本(va界面文本);
	}
	for (auto &v页 : w选项卡组.ma页) {
		v页.m按钮->f生成文本(va界面文本);
	}
	for (auto &vp选项列表 : ma选项列表) {
		vp选项列表->f事件_刷新文本();
	}
}
}	//namespace 东方山寨