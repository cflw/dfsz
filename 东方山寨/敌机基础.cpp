#include "游戏常量.h"
#include "游戏.h"
#include "敌机基础.h"
#include "图形引擎.h"
#include "边框形状.h"
import 东方山寨.计算;
import 东方山寨.敌机图形;
namespace 东方山寨 {
//==============================================================================
// 敌机类
//==============================================================================
C敌机::C敌机() {
}
C敌机::~C敌机() {
}
void C敌机::f对象_使用() {
	this->f接口_初始化();
	m标志[e使用] = true;
	m计数指针->f加计数();
}
void C敌机::f对象_销毁() {
	assert(m标志[e使用]);	//禁止重复销毁
	this->f事件_销毁();
	m标志.reset();
	m计数指针->f减计数();
	m图形->fg图形缓冲().f对象_销毁();
}
bool C敌机::f对象_i使用() const {
	return m标志[e使用];
}
void C敌机::f接口_初始化() {
}
void C敌机::f接口_计算() {
	const float v帧秒 = m游戏速度->fg秒();
	const float v目标透明度 = m标志[e消失] ? 0 : 1;
	m透明度 = 数学::f线性渐变<float>(m透明度, v目标透明度, 2 * v帧秒);
	if (m透明度 == 0) {
		f对象_销毁();
		return;
	}
	m无敌时间 -= v帧秒;
	f计算运动(v帧秒);
	m图形->f计算();
}
void C敌机::f接口_更新() {
	m图形->f更新();
}
bool C敌机::f接口_玩家子弹判定(C敌机与玩家子弹判定 &a判定) {
	return a判定.f敌机_提交判定(fg判定点());
}
void C敌机::f接口_击破() {
}
const t向量2 &C敌机::f事件_g坐标() const {
	return m坐标;
}
//取值
bool C敌机::fi在窗口外() const {
	return 边框::C矩形::c窗口.f判断(m坐标, 32);
}
bool C敌机::fi死亡() const {
	return m生命值.m当前 <= 0;
}
bool C敌机::fi王() const {
	return m标志[e王];
}
bool C敌机::fi无敌() const {
	return m无敌时间 > 0 || m标志[e无敌];
}
const S图片动画属性 &C敌机::fg图片动画属性() const {
	return *m敌机属性;
}
float C敌机::fg判定半径() const {
	return m敌机属性 ? m敌机属性->m判定半径 : c判定半径;
}
t圆形 C敌机::fg判定点() const {
	return {m坐标, fg判定半径()};
}
float C敌机::fg透明度() const {
	return m透明度;
}
bool C敌机::fi消失中() const {
	return m标志[e消失];
}
void C敌机::f中弹(float a伤害) {
	//无敌时不会计算伤害
	m生命值.m当前 -= a伤害;
}
//初始化
void C敌机::fs生命值(float a生命值) {
	m生命值.f重置(a生命值);
}
void C敌机::fs无敌时间(float a无敌时间) {
	m无敌时间 = a无敌时间;
}
//动作
void C敌机::f动作_结束() {
	m标志[e无动作] = true;
}
void C敌机::f动作_死亡() {
	this->f事件_击破();
	this->f对象_销毁();
}
void C敌机::f动作_消失(bool a动画) {
	if (a动画) {
		m标志[e消失] = true;
	} else {
		f对象_销毁();
	}
}
}	//namespace 东方山寨