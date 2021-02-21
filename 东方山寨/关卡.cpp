﻿#include "关卡.h"
#include "关卡列表.h"
#include "游戏.h"
#include "玩家.h"
#include "难度.h"
#include "场景.h"
#include "对话.h"
#include "图形_三维.h"
namespace 东方山寨 {
//==============================================================================
// 关卡事件状态
//==============================================================================
C关卡事件状态::C关卡事件状态(const std::shared_ptr<C关卡事件> &a事件):
	m事件(a事件) {
	a事件->m状态 = this;
}
C关卡事件 &C关卡事件状态::fg事件() const {
	return *m事件;
}
bool C关卡事件状态::fi存在() const {
	return !m标志[(int)E关卡事件状态::e结束];
}
bool C关卡事件状态::fi结束() const {
	return m标志[(int)E关卡事件状态::e结束];
}
void C关卡事件状态::f结束() {
	m标志[(int)E关卡事件状态::e结束] = true;
}
//==============================================================================
// 关卡控制
//==============================================================================
void C关卡控制::f初始化_环境(C场景控制 &a场景, C对话控制 &a对话) {
	m场景 = &a场景;
	m对话 = &a对话;
}
void C关卡控制::f初始化_在游戏开始(C关卡 *const *aa关卡, size_t a数量) {
	ma关卡 = aa关卡;
	m关卡数量 = a数量;
}
void C关卡控制::f初始化关卡(C关卡 &a关卡) {
	f结束关卡();
	m经过时间 = 0;
	a关卡.m关卡 = this;
	a关卡.f事件_初始化();
	m关卡 = &a关卡;
}
void C关卡控制::f结束关卡() {
	if (m关卡) {
		m关卡->f事件_结束();
		m关卡 = nullptr;
	}
	ma事件.clear();
	ma新事件.clear();
}
void C关卡控制::f切换关卡(C关卡 &a关卡, float a时间) {
	if (a时间 > 0) {
		C关卡脚本 v脚本 = fc脚本();
		v脚本.f等待(a时间);
		v脚本.f事件<C切换关卡事件>(a关卡);
		C玩家 &v玩家 = C游戏::g内容.fg玩家();
		v玩家.f发射_抑制发射子弹(a时间);
		v玩家.f发射_抑制发射炸弹(a时间);
	} else {
		C游戏::fg内容().f游戏_进入关卡(a关卡);
	}
}
C关卡脚本 C关卡控制::fc脚本() {
	return C关卡脚本(this);
}
void C关卡控制::f计算() {
	const float v秒 = C游戏::fg内容().fg游戏速度().fg秒();
	m经过时间 += v秒;
	bool vi删除 = false;
	m关卡->f事件_执行();
	f合并事件();
	for (auto &v事件状态 : ma事件) {
		C关卡事件 &v事件 = v事件状态->fg事件();
		bool vi可执行 = false;
		if (m经过时间 >= v事件状态->m开始时间) {
			auto v初始化标志 = v事件状态->m标志[(int)E关卡事件状态::e初始化];
			if (v初始化标志 == false) {
				v事件.f事件_初始化();
				v初始化标志 = true;
			}
			if (v事件状态->m等待 > 0) {
				v事件状态->m等待 -= v秒;
			} else {
				vi可执行 = true;
			}
		}
		if (vi可执行) {
			if (!v事件状态->fi结束()) {
				v事件.f事件_执行();
			}
			if (v事件状态->fi结束()) {	//执行后状态可能有变,所以重新取值
				v事件.f事件_结束();
				v事件状态.reset();
				vi删除 = true;
			}
		}
	}
	//删除
	if (vi删除) {
		auto f删除 = [](const std::shared_ptr<C关卡事件状态> &a)->bool {
			return a == nullptr;
		};
		ma事件.erase(std::remove_if(ma事件.begin(), ma事件.end(), f删除), ma事件.end());
	}
}
void C关卡控制::f合并事件() {
	if (!ma新事件.empty()) {
		ma事件.insert(ma事件.end(), ma新事件.begin(), ma新事件.end());
		ma新事件.clear();
	}
}
void C关卡控制::f添加事件(std::shared_ptr<C关卡事件状态> a) {
	ma新事件.push_back(a);
}
void C关卡控制::f设置场景(std::shared_ptr<I场景> a) {
	m场景->f设置场景(a);
}
void C关卡控制::f动作_开始对话(tp对话脚本 a) {
	m对话->f开始(a);
	m标志[E标志::e对话] = true;
}
std::shared_ptr<C关卡事件状态> C关卡控制::fg事件(int a) {
	f合并事件();
	return ma事件.at(a);
}
void C关卡控制::f动作_增加难度() {
	auto &v难度 = C游戏::fg内容().fg难度();
	auto &v玩家 = C游戏::fg内容().fg玩家();
	v难度.f增加难度_最大点(v玩家.m成绩.m最大点);
}
void C关卡控制::f动作_增加难度(const boost::rational<int> &a) {
	auto &v难度 = C游戏::fg内容().fg难度();
	v难度.f增加难度(a);
}
void C关卡控制::f动作_结束关卡(float a时间) {
	//计算下一关卡
	++m当前关卡序号;
	assert(m当前关卡序号 <= m关卡数量);	//如果>说明重复执行了
	if (m当前关卡序号 < m关卡数量) {
		C关卡 *const v下一关卡 = ma关卡[m当前关卡序号];
		f切换关卡(*v下一关卡, a时间);
	} else {	//没有下一关卡了,结束游戏
		const auto f结束游戏 = []() {
			C游戏::fg内容().f游戏_结束游戏();
		};
		if (a时间 > 0) {
			C关卡脚本 v脚本 = fc脚本();
			v脚本.f等待(a时间);
			v脚本.f事件<C关卡效果事件>(f结束游戏);
			C玩家 &v玩家 = C游戏::g内容.fg玩家();
			v玩家.f发射_抑制发射子弹(a时间);
			v玩家.f发射_抑制发射炸弹(a时间);
		} else {
			f结束游戏();
		}
	}
}
float C关卡控制::fg经过时间() const {
	return m经过时间;
}
//==============================================================================
// 关卡脚本
//==============================================================================
C关卡脚本::C关卡脚本(C关卡控制 *a控制) :
	m关卡控制(a控制), m经过时间(a控制->m经过时间){
}
std::shared_ptr<C关卡事件状态> C关卡脚本::f新事件_(const std::shared_ptr<C关卡事件> &a) {
	std::shared_ptr<C关卡事件状态> v新 = std::make_shared<C关卡事件状态>(a);
	a->m状态 = v新.get();
	a->m关卡 = m关卡控制;
	m关卡控制->f添加事件(v新);
	v新->m开始时间 = m开始时间 + m经过时间;
	return v新;
}
std::shared_ptr<C关卡事件状态> C关卡脚本::operator ()(const std::function<void()> &af) {
	return f新事件_(std::make_shared<C关卡效果事件>(af));
}
std::shared_ptr<C关卡事件状态> C关卡脚本::f事件(const std::function<void()> &af) {
	return f新事件_(std::make_shared<C关卡效果事件>(af));
}
std::shared_ptr<C关卡事件状态> C关卡脚本::f对话(tp对话脚本 a) {
	class C关卡对话事件 : public C关卡事件 {
	public:
		C关卡对话事件(tp对话脚本 a) {
			m对话脚本 = a;
		}
		void f事件_执行() override {
			m关卡->f动作_开始对话(m对话脚本);
			f动作_结束();
		}
		tp对话脚本 m对话脚本;
	};
	return f新事件_(std::make_shared<C关卡对话事件>(a));
}
void C关卡脚本::f时间点(float a时间) {
	m开始时间 = a时间;
}
void C关卡脚本::f等待(float a时间) {
	m开始时间 += a时间;
}
//==============================================================================
// 关卡接口
//==============================================================================
void C关卡::f注册关卡(const std::wstring &a名称) {
	C关卡管理::fg关卡组()[a名称] = this;
}
void C关卡事件::f动作_暂停(float a) {
	m状态->m等待 = a;
}
void C关卡事件::f动作_结束() {
	m状态->f结束();
}
float C关卡事件::fg暂停时间() const {
	return m状态->m等待;
}
//==============================================================================
// 关卡管理
//==============================================================================
ta关卡 &C关卡管理::fg关卡组() {
	static ta关卡 va关卡;
	return va关卡;
}
C关卡 &C关卡管理::fg关卡(const std::wstring &a名称) {
	return *fg关卡组().at(a名称);
}
//==============================================================================
// 效果
//==============================================================================
C关卡效果事件::C关卡效果事件(const std::function<void()> &af) :
	mf{af} {
}
void C关卡效果事件::f事件_执行() {
	mf();
	f动作_结束();
}
C关卡场景事件::C关卡场景事件(const std::shared_ptr<I场景> &a):
	m场景(std::shared_ptr<I场景>(a)){
}
void C关卡场景事件::f事件_执行() {
	m关卡->f设置场景(m场景);
	f动作_结束();
}
C切换关卡事件::C切换关卡事件(C关卡 &a关卡):
	m关卡(&a关卡) {
}
void C切换关卡事件::f事件_执行() {
	C游戏::fg内容().f游戏_进入关卡(*m关卡);
}
}	//namespace 东方山寨