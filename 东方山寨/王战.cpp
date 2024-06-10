#include "游戏常量.h"
#include "王战.h"
#include "游戏.h"
#include "玩家.h"
#include "图形工厂.h"
#include "关卡.h"
#include "敌机基础.h"
#include "图形_抬显.h"
#include "音频引擎.h"
namespace 东方山寨 {
constexpr float c最大时间 = 10000;
//==============================================================================
// 总控制
//==============================================================================
void C王战控制::f初始化_环境(C关卡控制 &a) {
	m关卡控制 = &a;
}
void C王战控制::f新事件_(const std::shared_ptr<I王战事件> &a) {
	assert(a != nullptr);
	mi结束 = false;
	m击破 = nullptr;
	a->m王战 = this;
	a->m关卡 = m关卡控制;
	m事件 = a.get();
	std::unique_ptr<C关卡事件状态> v新 = std::make_unique<C关卡事件状态>(a);
	v新->m开始时间 = -1;
	m关卡控制->f添加事件(std::move(v新));
}
void C王战控制::f计算() {
	if (m事件 && m事件->m状态->m标志[(int)E关卡事件状态::e初始化]) {	//初始化了才能计算
		//生命值
		for (auto &v : ma王) {
			if (v->fi死亡() && mi结束 == false) {
				mi结束 = true;
				m事件->f事件_王被击破(*v);
				f事件结束();
			}
		}
		//时间
		m时间控制.f计算();
		if (m时间控制.fi时间到() && mi结束 == false) {
			mi结束 = true;
			m事件->f事件_时间到();
			f事件结束();
		}
	}
}
void C王战控制::f王战_开始(int a事件数) {
	fg王战标志() = true;
	assert(m总血条 == nullptr);
	m时间控制.fs时间(c最大时间, c最大时间);
	if (a事件数 > 1) {
		m总血条 = 图形模板::f总血条(a事件数 - 1);
	}
	m弹幕时间 = 图形模板::f弹幕时间(m时间控制);
}
void C王战控制::f王战_结束() {
	fg王战标志() = false;
	if (m总血条) {
		m总血条->f动作_结束();
		m总血条 = nullptr;
	}
	m弹幕时间->f动作_结束();
	m弹幕时间 = nullptr;
	ma王.clear();
}
void C王战控制::fs弹幕时间(float a时间, float a冻结) {
	m时间控制.fs时间(a时间, a冻结);
	m弹幕时间->f动作_重置颜色();
}
void C王战控制::f发动符卡(const std::wstring &a名称, int a分数, bool ai时间符) {
	m符卡控制.f开始(a名称, a分数, ai时间符);
	m符卡文本 = 图形模板::f符卡文本(m符卡控制);
}
void C王战控制::f事件结束() {
	if (m符卡控制.fi发动()) {
		m符卡控制.f结束();
		m符卡文本->f动作_结束();
		m符卡文本 = nullptr;
	}
	m时间控制.f冻结(c最大时间);
	m事件->f动作_结束();
	m事件 = nullptr;
}
void C王战控制::f总血条减一() {
	m总血条->f减一();
}
//属性
t标志::reference C王战控制::fg王战标志() {
	return m关卡控制->m标志[C关卡控制::E标志::e王战];
}
bool C王战控制::fi王战() const {
	return m关卡控制->m标志[C关卡控制::E标志::e王战];
}
void C王战控制::fs王(C敌机 *a王) {
	assert(a王->m标志[C敌机::E标志::e王]);
	ma王.push_back(a王);
}
void C王战控制::fs王(const std::shared_ptr<C敌机> &a王) {
	fs王(a王.get());
}
C敌机 *C王战控制::fg王(int i) const {
	return ma王.at(i);
}
C敌机 *C王战控制::fg击破的王() {
	if (m击破) {
		return m击破;
	}
	//寻找对象
	for (auto &v : ma王) {
		if (v->fi死亡()) {
			m击破 = v;
			return m击破;
		}
	}
	return nullptr;
}
//==============================================================================
// 时间控制
//==============================================================================
void C王战时间控制::f计算() {
	if (m冻结 > 0) {
		m冻结 -= c帧秒<float>;
	} else {
		m倒计时 -= c帧秒<float>;
		const float v地板 = floor(m倒计时);
		if (m地板 != v地板) {
			m地板 = v地板;
			auto &v音频 = C游戏::fg音频();
			auto &v播放控制 = v音频.fg播放控制();
			if (m地板 < c王战倒计时1) {
				static const tp声音 v倒计时1 = v音频.fg声音()[L"声音.音效.倒计时1"];
				v播放控制.f播放音效l(*v倒计时1);
			} else if (m地板 < c王战倒计时0) {
				static const tp声音 v倒计时0 = v音频.fg声音()[L"声音.音效.倒计时0"];
				v播放控制.f播放音效l(*v倒计时0);
			}
		}
		if (m倒计时 < 0) {
			m倒计时 = 0;
		}
	}
}
bool C王战时间控制::fi时间到() const {
	return m倒计时 <= 0;
}
void C王战时间控制::fs时间(float a秒, float a冻结) {
	m总时间 = a秒;
	m倒计时 = a秒;
	f冻结(a冻结);
}
void C王战时间控制::f冻结(float a冻结) {
	m冻结 = a冻结;
}
float C王战时间控制::fg倒计时() const {
	return m倒计时;
}
float C王战时间控制::fg正计时() const {
	return m总时间 - m倒计时;
}
float C王战时间控制::fg倒计时百分比() const {
	return m倒计时 / m总时间;
}
float C王战时间控制::fg显示倒计时() const {
	return m倒计时 > 0 ? m倒计时 : 0;
}
//==============================================================================
// 符卡控制
//==============================================================================
C符卡控制::C符卡控制(const C王战时间控制 &a时间控制):
	m时间(&a时间控制) {
}
void C符卡控制::f开始(const std::wstring &a名称, int a分数, bool ai时间符) {
	m名称 = a名称;
	m分数 = a分数;
	m标志[e发动] = true;
	m标志[e时间符] = ai时间符;
}
void C符卡控制::f结束() {
	m标志[e发动] = false;
	const int v分数 = fg当前分数();
	auto &v玩家 = C游戏::fg内容().fg玩家();
	//std::lock_guard<std::mutex> v锁(v玩家.m成绩锁);	//应该不需要锁
	v玩家.m成绩.m得分 += v分数;
}
void C符卡控制::f分数减半() {
	m除数 *= 2;
}
int C符卡控制::fg当前分数() const {
	if (m标志[e时间符]) {
		return static_cast<int>(m分数 / m除数);
	} else {
		const float v插值 = 数学::f插值<float>(0.5f, 1, m时间->fg倒计时百分比());
		return static_cast<int>(m分数 * v插值 / m除数);
	}
}
const std::wstring &C符卡控制::fg名称() const {
	return m名称;
}
bool C符卡控制::fi发动() const {
	return m标志[e发动];
}
bool C符卡控制::fi时间符() const {
	return m标志[e时间符];
}
//==============================================================================
// 王战事件
//==============================================================================
const t向量2 &I王战事件::f事件_g坐标() const {
	return m王战->fg王()->m坐标;
}
void I王战事件::f事件_王被击破(C敌机 &) {
}
void I王战事件::f事件_时间到() {
}
void I王战事件::f事件_王战阶段结束() {
}
}	//namespace 东方山寨