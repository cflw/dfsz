#include <用户界面_引擎.h>
#include <用户界面接口实现_画界面.h>
#include <用户界面接口实现_输入w.h>
#include <用户界面接口实现_输入x.h>
#include "界面引擎.h"
#include "界面_窗口类.h"
#include "界面_选项.h"
namespace 东方山寨 {
//实现
class C界面引擎::C实现 {
public:
	void f绑定() {
		m用户界面.fs画界面(m画界面);
		m用户界面.f输入_s键盘接口(m键盘);
		m用户界面.f输入_s鼠标接口(m鼠标);
		//m用户界面.f输入_s触摸接口(m触摸);
		m用户界面.f输入_s手柄接口(m手柄);
	}
	void f初始化图形(二维::C二维 &a二维) {
		m画界面.f初始化(a二维);
	}
	void f初始化输入(C输入引擎 &a输入) {
		m键盘.f初始化(*a输入.m键盘);
		m鼠标.f初始化(*a输入.m鼠标);
		//m触摸.f初始化(*a输入.m触摸);
		m手柄.f初始化(*a输入.m手柄);
	}
	void f初始化窗口实例() {
		ma窗口.emplace(E窗口::e主菜单, std::make_unique<W主菜单>());
		ma窗口.emplace(E窗口::e选择难度, std::make_unique<W选择难度>());
		ma窗口.emplace(E窗口::e选择飞机, std::make_unique<W选择自机>());
		ma窗口.emplace(E窗口::e选项, std::make_unique<W选项>());
	}
	void f更新输入() {
		m键盘.f更新();
		m鼠标.f更新();
		//m触摸.f更新();
		m手柄.f更新();
	}
	用户界面::C用户界面 m用户界面;
	用户界面::接口实现::C画界面 m画界面;
	用户界面::接口实现::C键盘w m键盘;
	用户界面::接口实现::C鼠标w m鼠标;
	用户界面::接口实现::C触摸w m触摸;
	用户界面::接口实现::C手柄x m手柄;
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
void C界面引擎::f初始化(二维::C二维 &a二维, C输入引擎 &a输入) {
	m实现 = std::make_unique<C实现>();
	m实现->f绑定();
	m实现->f初始化图形(a二维);
	m实现->f初始化输入(a输入);
	m实现->f初始化窗口实例();
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
void C界面引擎::f切换窗口(E窗口 a) {
	auto &v窗口 = *m实现->ma窗口[a];
	m实现->m用户界面.f切换窗口(v窗口);
}
void C界面引擎::f关闭窗口() {
	if (用户界面::W窗口 *v活动窗口 = m实现->m用户界面.m活动窗口) {
		v活动窗口->f动作_关闭();
	}
}

}