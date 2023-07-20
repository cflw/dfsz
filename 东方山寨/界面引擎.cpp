#include <用户界面_引擎.h>
#include <用户界面_窗口.h>
#include <用户界面接口实现_图形d2d.h>
#include <用户界面接口实现_输入w.h>
#include <用户界面接口实现_输入x.h>
#include "界面引擎.h"
#include "界面音频.h"
#include "图形引擎.h"
#include "输入.h"
#include "音频引擎.h"
import 东方山寨.界面_主菜单;
import 东方山寨.界面_游戏菜单;
import 东方山寨.界面_选择模式;
import 东方山寨.界面_选择难度;
import 东方山寨.界面_选择自机;
import 东方山寨.界面_选择关卡;
import 东方山寨.界面_选项;
import 东方山寨.界面_选择符卡;
import 东方山寨.界面_选择录像;
import 东方山寨.界面语言;
namespace 东方山寨 {
//==============================================================================
// 引擎
//==============================================================================
class C界面引擎::C实现 {
public:
	void f初始化图形(二维::C二维 &a二维) {
		m图形.f初始化(a二维);
		m用户界面.fs图形(m图形);
	}
	void f初始化输入(C输入引擎 &a输入) {
		m键盘.f初始化(*a输入.m键盘);
		m鼠标.f初始化(*a输入.m鼠标);
		//m触摸.f初始化(*a输入.m触摸);
		m手柄.f初始化(*a输入.m手柄);
		m用户界面.f输入_s键盘接口(m键盘);
		m用户界面.f输入_s鼠标接口(m鼠标);
		//m用户界面.f输入_s触摸接口(m触摸);
		m用户界面.f输入_s手柄接口(m手柄);
	}
	void f初始化音频(C音频引擎 &a音频) {
		m音频.f初始化(a音频);
		m用户界面.fs音频(m音频);
	}
	void f初始化窗口实例() {
		ma窗口.emplace(E窗口::e主菜单, std::make_unique<W主菜单>());
		ma窗口.emplace(E窗口::e游戏暂停, std::make_unique<W游戏菜单>(W游戏菜单::E上下文::e游戏暂停));
		ma窗口.emplace(E窗口::e游戏结束, std::make_unique<W游戏菜单>(W游戏菜单::E上下文::e游戏结束));
		ma窗口.emplace(E窗口::e游戏通关, std::make_unique<W游戏菜单>(W游戏菜单::E上下文::e游戏通关));
		ma窗口.emplace(E窗口::e选择模式, std::make_unique<W选择模式>());
		ma窗口.emplace(E窗口::e选择难度, std::make_unique<W选择难度>());
		ma窗口.emplace(E窗口::e选择飞机, std::make_unique<W选择自机>());
		ma窗口.emplace(E窗口::e选择关卡, std::make_unique<W选择关卡>());
		ma窗口.emplace(E窗口::e选择弹幕, std::make_unique<W选择符卡>());
		ma窗口.emplace(E窗口::e选择录像, std::make_unique<W选择录像>());
		ma窗口.emplace(E窗口::e选项, std::make_unique<W选项>());
	}
	void f更新输入() {
		m键盘.f更新();
		m鼠标.f更新();
		//m触摸.f更新();
		m手柄.f更新();
	}
	用户界面::C用户界面 m用户界面;
	用户界面::接口实现::d2d::C图形 m图形;
	用户界面::接口实现::win::C键盘 m键盘;
	用户界面::接口实现::win::C鼠标 m鼠标;
	用户界面::接口实现::win::C触摸 m触摸;
	用户界面::接口实现::xi::C手柄 m手柄;
	C界面音频 m音频;
	std::map<E窗口, std::unique_ptr<用户界面::W窗口>> ma窗口;
};
//接口
C界面引擎 *C界面引擎::g这 = nullptr;
C界面引擎::C界面引擎() {
	assert(g这 == nullptr);
	g这 = this;
}
C界面引擎::~C界面引擎() {
}
C界面引擎 &C界面引擎::fg实例() {
	return *g这;
}
void C界面引擎::f初始化0(C图形引擎 &a图形, C输入引擎 &a输入) {
	m实现 = std::make_unique<C实现>();
	m实现->f初始化图形(a图形.fg二维());
	m实现->f初始化输入(a输入);
	m实现->f初始化窗口实例();
}
void C界面引擎::f初始化0_图形(C图形引擎 &a图形) {
	m实现->f初始化图形(a图形.fg二维());
}
void C界面引擎::f初始化1(C音频引擎 &a音频) {
	m实现->f初始化音频(a音频);
}
void C界面引擎::f输入_接收字符(wchar_t a字符) {
	m实现->m用户界面.f输入_接收字符(a字符);
}
void C界面引擎::f计算() {
	m实现->f更新输入();
	m实现->m用户界面.f计算();
}
void C界面引擎::f更新() {
	m实现->m用户界面.f更新();
}
void C界面引擎::f显示() {
	m实现->m用户界面.f显示();
}
void C界面引擎::fs时钟频率(float a计算, float a渲染) {
	m实现->m用户界面.fs时钟频率(a计算, a渲染);
}
void C界面引擎::f切换下个窗口(E窗口 a窗口) {
	auto &v窗口 = *m实现->ma窗口[a窗口];
	m实现->m用户界面.f切换窗口(v窗口);
	m窗口栈.push(&v窗口);
}
void C界面引擎::f切换上个窗口() {
	m窗口栈.pop();
	auto vp窗口 = m窗口栈.top();
	m实现->m用户界面.f切换窗口(*vp窗口);
}
void C界面引擎::f关闭窗口() {
	if (用户界面::W窗口 *v活动窗口 = m实现->m用户界面.m活动窗口) {
		v活动窗口->f动作_关闭();
	}
}
void C界面引擎::f更新界面语言() {
	for (auto &[v标识, vp窗口0] : m实现->ma窗口) {
		if (auto vp窗口1 = dynamic_cast<I跟踪界面语言*>(vp窗口0.get())) {
			vp窗口1->f事件_刷新文本();
		}
	}
}
}	//namespace 东方山寨