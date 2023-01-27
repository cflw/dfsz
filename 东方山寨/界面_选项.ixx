module;
#include "界面包含.h"
#include "程序.h"
#define 分辨率(a宽, a高) e##a宽##x##a高
#define t分辨率(a宽, a高) {e##a宽##x##a高, a宽, a高}
export module 东方山寨.界面_选项;
import 东方山寨.文本管理;
import 用户界面.控件;
export namespace 东方山寨 {
using t向量2 = cflw::数学::S向量2;
constexpr float c选项窗口宽 = 300;
constexpr float c选项窗口高 = 250;
//==============================================================================
// 模板
//==============================================================================
class W选项列表 : public 用户界面::W窗口框架 {
public:
	static constexpr float c行高 = 20;
	static constexpr float c行距 = c行高 * 0.5f;
	struct S行 {
		std::unique_ptr<用户界面::W标签> w名称;
		std::unique_ptr<用户界面::W窗口> w控制;
	};
	W选项列表() {
	}
	void f响应_初始化() override {
		int i = 0;
		for (const auto &[vp名称, vp控制] : ma行) {
			用户界面::C表格排列布局 v列布局 = m行布局.fc生成排列布局(i++);
			const float v标签宽 = m尺寸.x * 0.5f;
			const float v控制宽 = m尺寸.x * 0.5f;
			vp名称->f属性_s布局(v列布局.f移动生成(v标签宽));
			vp控制->f属性_s布局(v列布局.f移动生成(v控制宽));
			f动作_添加窗口(*vp名称);
			f动作_添加窗口(*vp控制);
			vp名称->f动作_显示();
			vp控制->f动作_显示();
		}
	}
	void f属性_s布局(const 用户界面::S布局参数 &a参数) override {
		W窗口::f属性_s布局(a参数);
		m行布局.f属性_s行布局(t向量2::c零, a参数.m尺寸, c行高);
		m行布局.f属性_s行距(c行距);
	}
	void f添加行(const std::wstring_view &a标签, std::unique_ptr<用户界面::W窗口> &&a控制) {
		std::unique_ptr<用户界面::W标签> v标签 = std::make_unique<用户界面::W标签>();
		v标签->f属性_s文本(a标签, {16, 用户界面::E对齐::e居左});
		auto &v行 = ma行.emplace_back();
		v行.w名称 = std::move(v标签);
		v行.w控制 = std::move(a控制);
	}
	std::vector<S行> ma行;
	用户界面::C表格排行布局 m行布局;
};
//==============================================================================
// 详细选项
//==============================================================================
class W玩家帐户 : public W选项列表 {
public:
	W玩家帐户() {
		const auto &va界面文本 = C文本管理::fg实例().fg界面文本();
		f添加行(va界面文本[L"option.playername"], std::make_unique<用户界面::W文本框>());
	}
};
class W语言设置 : public W选项列表 {

};
class W图形设置 : public W选项列表 {
public:
	enum E分辨率 {
		//4:3
		分辨率(800, 600),
		分辨率(960, 720),
		分辨率(1024, 768),
		分辨率(1280, 960),
		//16:9
		分辨率(1280, 720),
		分辨率(1366, 768),
		分辨率(1440, 900),
		分辨率(1920, 1080),	//1080p
		分辨率(3840, 2160),	//4k
		分辨率(7680, 4320),	//8k
		//3:2
		分辨率(1800, 1200),	//surface go
		分辨率(2160, 1440),	//surface pro3
		分辨率(2736, 1824),	//surface pro4
		分辨率(3000, 2000),	//surface book 13.5英寸
		分辨率(3240, 2160),	//surface book 15英寸
	};
	enum E标识 {
		e分辨率,
	};
	W图形设置() {
		static const std::tuple<E分辨率, int, int> ca分辨率[] = {
			//4:3
			t分辨率(800, 600),
			t分辨率(960, 720),
			t分辨率(1024, 768),
			t分辨率(1280, 960),
			//16:9
			t分辨率(1280, 720),
			t分辨率(1366, 768),
			t分辨率(1440, 900),
			t分辨率(1920, 1080),	//1080p
		};
		const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
		auto w分辨率 = std::make_unique<用户界面::W横向选择列表>(e分辨率);
		for (const auto &[v枚举, v宽, v高] : ca分辨率) {
			const int v序号 = (int)w分辨率->ma文本.size();
			w分辨率->ma文本.push_back(std::to_wstring(v宽) + L"x" + std::to_wstring(v高));
			ma分辨率.emplace(v序号, std::make_pair(v宽, v高));
		}
		f添加行(va界面文本[L"option.resolution"], std::move(w分辨率));

	}
	void f事件_窗口值变化(用户界面::W窗口 &a窗口, const int &a前, int &a后) override {
		switch (a窗口.m标识) {
		case e分辨率:
			m分辨率 = a后;
			break;
		}
	}
	std::optional<std::pair<int, int>> fg分辨率() const {
		if (m分辨率 >= 0) {
			return ma分辨率.at(m分辨率);
		}
		return std::nullopt;
	}
	std::map<int, std::pair<int, int>> ma分辨率;
	int m分辨率 = -1;
};
class W声音设置 : public W选项列表 {
public:
};
class W手柄设备 : public W选项列表 {
public:

};
class W触摸设备 : public W选项列表 {
public:

};
//==============================================================================
// 选项
//==============================================================================
class W选项 : public 用户界面::W窗口 {
public:
	static constexpr float c宽 = c选项窗口宽;
	static constexpr float c高 = c选项窗口高;
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
	W选项() {
		constexpr float c按钮高 = 30;
		const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
		w选项卡组.f属性_s布局({t向量2::c零, t向量2(c宽, c高)});
		w选项卡组.f属性_s页按钮尺寸(t向量2(80, c按钮高));
		//w选项卡组.f属性_s文本大小(20);
		//选项卡
		const std::tuple<W选项列表 *, std::wstring_view> va页[] = {
			{&w玩家帐户, va界面文本[L"tab.player"]},
			{&w图形设置, va界面文本[L"tab.graphic"]},
		};
		for (const auto &[vp窗口, v标签] : va页) {
			auto &v页 = ma页.emplace_back(vp窗口);
			w选项卡组.f动作_添加页(*vp窗口, v标签);
		}
		//按钮
		const std::tuple<int, std::wstring_view> va按钮[] = {
			{e确定, va界面文本[L"button.ok"]},
			{e取消, va界面文本[L"button.cancel"]},
			{e应用, va界面文本[L"button.apply"]},
			{e默认, va界面文本[L"button.default"]},
		};
		用户界面::C单向移动布局 v按钮布局;
		constexpr float c按钮栏左 = -c宽 * 0.5f;
		constexpr float c按钮栏右 = c宽 * 0.5f;
		constexpr float c按钮栏上 = -c高 * 0.5f;
		constexpr float c按钮栏下 = c按钮栏上 - c按钮高;
		const t矩形 v按钮栏 = t矩形::fc左上右下(c按钮栏左, c按钮栏上, c按钮栏右, c按钮栏下);
		v按钮布局.f属性_s网格布局(v按钮栏.fg中心(), v按钮栏.fg尺寸(), std::distance(std::begin(va按钮), std::end(va按钮)));
		v按钮布局.f属性_s倍数移动(1, 0);
		for (const auto &[v按钮标识, v按钮文本] : va按钮) {
			std::unique_ptr<用户界面::W按钮> v按钮 = std::make_unique<用户界面::W按钮>(v按钮标识);
			v按钮->f属性_s布局(v按钮布局.f移动生成矩形());
			v按钮->f属性_s文本内容(v按钮文本);
			ma按钮.push_back(std::move(v按钮));
		}
	}
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override {
		switch (a参数.m按键) {
		case 用户界面::E按键::e确定:
			switch (a窗口.m标识) {
			case e确定:
				if (auto v分辨率 = w图形设置.fg分辨率()) {
					C程序::fs窗口大小(v分辨率->first, v分辨率->second);
				}
				C界面引擎::g这->f切换上个窗口();
				break;
			case e取消:
				C界面引擎::g这->f切换上个窗口();
				break;
			}
		}
	}
	void f响应_初始化() override {
		f动作_添加窗口(w选项卡组);
		w选项卡组.f动作_显示();
		for (auto &vp按钮 : ma按钮) {
			f动作_添加窗口(*vp按钮);
			vp按钮->f动作_显示();
		}
		f动作_显示();
	}
	用户界面::W选项卡组 w选项卡组;
	W玩家帐户 w玩家帐户;
	W图形设置 w图形设置;
	std::vector<W选项列表 *> ma页;
	std::vector<std::unique_ptr<用户界面::W按钮>> ma按钮;	//底部按钮
};
}	//namespace 东方山寨