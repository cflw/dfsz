#include "游戏常量.h"
#include "王战.h"
#include "游戏.h"
#include "图形工厂.h"
#include "关卡.h"
#include "敌机基础.h"
#include "图形_抬显.h"
#include "音频引擎.h"
namespace 东方山寨 {
void C王战控制::f初始化_环境(C关卡控制 &a) {
	m关卡控制 = &a;
}
std::shared_ptr<C关卡事件状态> C王战控制::f新事件_(const std::shared_ptr<C王战事件> &a) {
	mi结束 = false;
	m击破 = nullptr;
	a->m王战 = this;
	a->m关卡 = m关卡控制;
	m事件 = a.get();
	std::shared_ptr<C关卡事件状态> v新 = std::make_shared<C关卡事件状态>(a);
	m关卡控制->f添加事件(v新);
	v新->m开始时间 = -1;
	return v新;
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
		if (m冻结 > 0) {
			m冻结 -= c帧秒<float>;
		} else {
			m时间 -= c帧秒<float>;
			const float v地板 = floor(m时间);
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
			if (m时间 <= 0 && mi结束 == false) {
				mi结束 = true;
				m时间 = 0;
				m事件->f事件_时间到();
				f事件结束();
			}
		}
	}
}
void C王战控制::f王战开始(int a数量) {
	fg王战标志() = true;
	assert(m总血条 == nullptr);
	m总血条 = 图形模板::f总血条(a数量 - 1);
	m弹幕时间 = 图形模板::f弹幕时间(m时间);
	m时间 = 10000;
	m冻结 = 10000;
}
void C王战控制::f王战结束() {
	fg王战标志() = false;
	m总血条->f动作_结束();
	m总血条 = nullptr;
	m弹幕时间->f动作_结束();
	m弹幕时间 = nullptr;
	ma王.clear();
}
void C王战控制::f符卡开始(const std::wstring &a名称, int a分数) {

}
void C王战控制::f符卡结束() {

}
void C王战控制::f事件结束() {
	f时间冻结(10000);
	m事件->f动作_结束();
	m事件 = nullptr;
}
void C王战控制::fs时间(float a秒, float a冻结) {
	m时间 = a秒;
	f时间冻结(a冻结);
	m弹幕时间->f动作_重置颜色();
}
void C王战控制::f时间冻结(float a冻结) {
	m冻结 = a冻结;
}
void C王战控制::f总血条减一() {
	m总血条->f减一();
}
t标志::reference C王战控制::fg王战标志() {
	return m关卡控制->m标志[C关卡控制::E标志::e王战];
}
bool C王战控制::fg王战标志() const {
	return m关卡控制->m标志[C关卡控制::E标志::e王战];
}
void C王战控制::fs王(C敌机 *p) {
	assert(p->m标志[C敌机::E标志::e王]);
	ma王.push_back(p);
}
void C王战控制::fs王(std::shared_ptr<C敌机> p) {
	fs王(p.get());
}
C敌机 *C王战控制::fg王(int i) const {
	return ma王[i];
}
C敌机 *C王战控制::fg击破() {
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
}	//namespace 东方山寨