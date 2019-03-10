#include "对话.h"
#include "图形_对话.h"
#include "游戏.h"
#include "图形工厂.h"
#include "输入.h"
#include "关卡.h"
namespace 东方山寨 {
//==============================================================================
// 对话控制
//==============================================================================
void C对话控制::f初始化_环境(C关卡控制 &p关卡) {
	m关卡 = &p关卡;
}
void C对话控制::f计算() {
	m跳过等待 -= c帧秒;
	m自动等待 += c帧秒;
	if (m跳过等待 <= 0) {	//防止同时间内调用下一个
		if (m自动等待 > m自动间隔) {
			f内部_执行对话事件();
		}
	}
}
void C对话控制::f输入按键(const 输入::C按键组 &p) {
	const auto v确定键 = p.f按键((输入::t索引)E按键::e确定);
	if (v确定键.f按下()) {
		m输入_确定时间 += c帧秒;
		if (v确定键.f刚按下()) {
			f按键控制_下一个();
			return;
		}
		if (m输入_确定时间 >= c按住确定跳过的等待时间) {
			f按键控制_跳过();
			return;
		}
	} else {
		m输入_确定时间 = 0;
	}
	const auto v跳过键 = p.f按键((输入::t索引)E按键::e跳过);
	if (v跳过键.f按下()) {
		f按键控制_跳过();
		return;
	}
}
void C对话控制::f开始(tp对话脚本 p) {
	m对话脚本 = p;
	m当前对话 = m对话脚本->cbegin();
	f内部_执行对话事件();
	fg对话标记() = true;
	m跳过等待 = c跳过间隔;
}
void C对话控制::f结束() {
	//对话框
	f内部_结束对话框();
	//立绘
	for (const auto &[v标识, v立绘] : ma对话立绘) {
		v立绘->f动作_结束();
	}
	ma对话立绘.clear();
	//标记
	fg对话标记() = false;
}
void C对话控制::f按键控制_下一个() {
	f内部_执行对话事件();
}
void C对话控制::f按键控制_跳过() {
	if (m跳过等待 <= 0) {	//防止同时间内调用下一个
		f内部_执行对话事件();
	}
}
t标志::reference C对话控制::fg对话标记() {
	return m关卡->m标志[C关卡控制::E标志::e对话];
}
bool C对话控制::fg对话标记() const {
	return m关卡->m标志[C关卡控制::E标志::e对话];
}
bool C对话控制::fi对话中() const {
	return fg对话标记();
}
bool C对话控制::fw结束() const {
	return !fg对话标记();
}
void C对话控制::f控制_新对话框(const S对话参数_对话 &p) {
	f内部_结束对话框();
	auto v图形工厂 = C游戏::fg资源().f工厂_图形();
	m当前对话框 = v图形工厂.f产生图形<C对话框>(p);
}
void C对话控制::f控制_显示立绘(const S对话参数_显示立绘 &p) {
	assert(ma对话立绘.find(p.m标识) == ma对话立绘.end());	//必须没有
	auto v图形工厂 = C游戏::fg资源().f工厂_图形();
	v图形工厂.m参数.m标志[I对话立绘::E初始化标记::e方向] = p.m方向;
	auto v图形 = v图形工厂.f产生图形(*p.m立绘工厂);
	assert(v图形 != nullptr);	//可能因为达到图形上限而导致异常
	ma对话立绘[p.m标识] = v图形;
	f内部_立绘焦点(v图形.get());
}
void C对话控制::f控制_立绘状态(const S对话参数_立绘状态 &p) {
	auto v立绘 = ma对话立绘.at(p.m标识).get();
	switch (p.m状态) {
	case E立绘状态::e聚焦:
		f内部_立绘焦点(v立绘);
		break;
	case E立绘状态::e消失:
		v立绘->f动作_结束();
		ma对话立绘.erase(p.m标识);
		break;
	default:
		throw;
	}
}
void C对话控制::f控制_等待() {
	m等待 = true;
}
void C对话控制::f控制_继续() {
	m等待 = false;
}
void C对话控制::f内部_执行对话事件() {
	m等待 = false;
	//循环脚本
	if (m当前对话 == m对话脚本->cend()) {
		f结束();
		return;
	}
	while (m当前对话 != m对话脚本->cend()) {
		(*m当前对话)->f接口_触发(*this);
		++m当前对话;
		if (m等待) {
			break;
		}
	}
	//其它
	m跳过等待 = c跳过间隔;
	m自动等待 = 0;
}
void C对话控制::f内部_结束对话框() {
	if (m当前对话框) {
		m当前对话框->f动作_结束();
		m当前对话框 = nullptr;
	}
}
void C对话控制::f内部_立绘焦点(I对话立绘 *p) {
	if (m当前立绘) {
		m当前立绘->f动作_失焦();
	}
	p->f动作_聚焦();
	m当前立绘 = p;
}
//==============================================================================
// 对话脚本
//==============================================================================
C对话脚本::operator tp对话脚本() const {
	return ma对话事件;
}
C对话脚本 &C对话脚本::f对话(const std::wstring &a文本, bool a方向) {
	ma对话事件->push_back(std::make_unique<对话事件::C对话>(S对话参数_对话{a文本, a方向}));
	return *this;
}
C对话脚本 &C对话脚本::f显示立绘(const I工厂<I对话立绘> &a立绘, int a标识, bool a方向) {
	ma对话事件->push_back(std::make_unique<对话事件::C显示立绘>(S对话参数_显示立绘{&a立绘, a标识, a方向}));
	return *this;
}
C对话脚本 &C对话脚本::f立绘聚焦(int a标识) {
	ma对话事件->push_back(std::make_unique<对话事件::C立绘状态>(S对话参数_立绘状态{a标识, E立绘状态::e聚焦}));
	return *this;
}
C对话脚本 &C对话脚本::f立绘消失(int a标识) {
	ma对话事件->push_back(std::make_unique<对话事件::C立绘状态>(S对话参数_立绘状态{a标识, E立绘状态::e消失}));
	return *this;
}
//==============================================================================
// 对话事件
//==============================================================================
namespace 对话事件 {
//对话
C对话::C对话(S对话参数_对话 &&a对话):
	m参数(std::move(a对话)) {
}
void C对话::f接口_触发(C对话控制 &a对话) {
	a对话.f控制_新对话框(m参数);
	a对话.f控制_等待();
}
//显示立绘
C显示立绘::C显示立绘(S对话参数_显示立绘 &&a显示立绘):
	m参数(std::move(a显示立绘)) {
}
void C显示立绘::f接口_触发(C对话控制 &a对话) {
	a对话.f控制_显示立绘(m参数);
	a对话.f控制_继续();
}
//立绘状态
C立绘状态::C立绘状态(S对话参数_立绘状态 &&p):
	m参数(std::move(p)) {
}
void C立绘状态::f接口_触发(C对话控制 &a对话) {
	a对话.f控制_立绘状态(m参数);
	a对话.f控制_继续();
}
}	//namespace 对话事件
}	//namespace 东方山寨