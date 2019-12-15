#include "游戏常量.h"
#include "子弹基础.h"
#include "游戏.h"
#include "图形引擎.h"
#include "计算.h"
#include "子弹图形缓冲.h"
namespace 东方山寨 {
//==============================================================================
// 子弹
//==============================================================================
void C子弹::f对象_使用() {
	this->f接口_初始化();
	m标志[e使用] = true;
	m标志[e动作] = true;
	m计数指针->f加计数();
	//v显示编号 = v子弹显示编号.f新编号();
}
void C子弹::f对象_销毁() {
	assert(m标志[e使用]);	//禁止重复销毁
	this->f接口_销毁();
	m图形缓冲->f对象_销毁();
	m标志.reset();
	m计数指针->f减计数();
}
bool C子弹::f对象_i使用() const {
	return m标志[e使用];
}
void C子弹::f基础_计算运动() {
	计算::f基本运动计算(m坐标, m速度, m游戏速度->fg秒());
}
float C子弹::f基础_计算方向() {
	if (!m速度.fi零()) {
		m方向 = m速度.fg方向r();
	}
	return m方向;
}
bool C子弹::f基础_擦弹() {
	if (m擦弹间隔 <= 0) {
		m擦弹间隔 = 1;
		return true;
	}
	return false;
}
t向量2 C子弹::f基础_到点方位(const t向量2 &a坐标) const {
	return m坐标.f到点方位r(a坐标, m方向);
}
bool C子弹::f基础_i不透明判定(float a阀值) const {
	return (m颜色[0].a <= a阀值) && (m颜色[1].a <= a阀值);
}
void C子弹::f接口_初始化() {
}
void C子弹::f接口_参数初始化(const S子弹参数 &a) {
	m坐标 = a.m坐标;
	m速度 = a.m速度;
	m颜色[0] = a.m颜色[0];
	m颜色[1] = a.m颜色[1];
	m方向 = a.m速度.fg方向r();
	m缩放 = a.m缩放;
}
void C子弹::f接口_计算() {
	f基础_计算运动();
}
void C子弹::f接口_更新() {
}
void C子弹::f接口_销毁() {
}
void C子弹::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (a判定.f子弹_提交判定(t圆形{m坐标, c判定半径})) {
		a判定.f子弹_判定有效();
		if (a判定.f子弹_i碰撞()) {
			f对象_销毁();
		}
	}
}
bool C子弹::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	if (a判定.f子弹_提交判定(m坐标, c判定半径)) {
		a判定.f子弹_产生道具(m坐标, m速度);
		m标志[e停止炸弹判定] = true;
		f对象_销毁();
		return true;
	}
	return false;
}
bool C子弹::f接口_i在窗口外() {
	return C边界::c窗口.f外边判断(m坐标, 0);
}
bool C子弹::f接口_i可显示() const {
	return true;
}
bool C子弹::f接口_i停止炸弹判定() const {
	return m标志[e停止炸弹判定];
}
//初始化
void C子弹::f初始化_样式(int a) {
	auto &va子弹属性 = C游戏::g资源.fg子弹属性();
	m子弹属性 = va子弹属性.fg指针(a);
}
void C子弹::f初始化_绘制(int) {

}
//动作
void C子弹::f动作_空() {
	m标志[C子弹::e动作] = false;
}
void C子弹::f动作_取消产生() {
	m标志[C子弹::e取消产生] = true;
}
void C子弹::f动作_消失(bool) {
	m标志.reset();
}
void C子弹::f动作_旋转(float a度) {
	m速度.fs旋转d(a度 * m游戏速度->fg秒());
}
bool C子弹::f动作_限速(float a小, float a大, float a变化, float a时间) {
	assert(a小 <= a大);
	const float v过秒 = m游戏速度->fg秒();
	const float v变化 = a变化 * a时间 * v过秒;
	float v大小 = m速度.fg大小();
	const auto f速度变化 = [&](float a目标)->bool {
		if (a变化 > 0) {
			v大小 = 数学::f线性渐变<float>(v大小, a目标, v变化);
			m速度.fs大小(v大小);
			return v大小 == a目标;
		} else {
			m速度.fs大小(a目标);
			return true;
		}
	};
	if (v大小 <= a小) {
		if (f速度变化(a小)) {
			return true;
		}
	} else if (v大小 >= a大) {
		if (f速度变化(a大)) {
			return true;
		}
	}
	return false;
}
void C子弹::f动作_加速度(float a加数, float a时间) {
	const float v过秒 = m游戏速度->fg秒();
	m速度 = m速度.fg归一() * (m速度.fg大小() + a加数 * a时间 * v过秒);
}
void C子弹::f动作_加速度(const t向量2 &a加速度, float a时间) {
	const float v过秒 = m游戏速度->fg秒();
	m速度 += a加速度 * a时间 * v过秒;
}
void C子弹::f动作_乘速度(float a乘数, float a时间) {
	const float v过秒 = m游戏速度->fg秒();
	const float v变化量 = pow(a乘数, 1.f / a时间 * v过秒);
	m速度 *= v变化量;
}
int C子弹::f动作_屏幕反弹(int a方向, int a次数, const std::function<bool(int)> &af判断) {
	int v次数 = 0;
	if (v次数 >= a次数) {
		return v次数;
	}
	const auto f = [&](int a方向1, float &a坐标, float &a速度, const bool &a正, const float &a屏幕范围) {
		const bool v超出坐标 = a正 ? (a坐标 > a屏幕范围) : (a坐标 < -a屏幕范围);
		if ((a方向 & a方向1) && v超出坐标 && (af判断 ? af判断(a方向1) : true)) {
			a坐标 = -a坐标 + (a正 ? 2 : -2) * a屏幕范围;
			a速度 = -a速度;
			++v次数;
		}
	};
	f(e左, m坐标.x, m速度.x, false, c框架范围x);
	f(e右, m坐标.x, m速度.x, true, c框架范围x);
	if (v次数 >= a次数) {
		return v次数;
	}
	f(e下, m坐标.y, m速度.y, false, c框架范围y);
	f(e上, m坐标.y, m速度.y, true, c框架范围y);
	return v次数;
}
void C子弹::f动作_透明(float a目标, float a变化速度) {
	const float v过秒 = m游戏速度->fg秒();
	const float v变化速度 = a变化速度 * v过秒;
	m颜色[0].a = 数学::f线性渐变<float>(m颜色[0].a, a目标, v变化速度);
	m颜色[1].a = 数学::f线性渐变<float>(m颜色[1].a, a目标, v变化速度);
}
//==============================================================================
// 子弹属性
//==============================================================================
float S子弹属性::f判定计算(float a原始, float a修正, float a倍数) {
	return a原始 * a倍数 - a修正 * sqrt(a倍数);
}
float S子弹属性::fg判定x(float x) const {
	return f判定计算(m判定.x, m判定修正.x, x);
}
float S子弹属性::fg判定y(float y) const {
	if (fi圆形()) {
		return fg判定x(y);
	} else {
		return f判定计算(m判定.y, m判定修正.y, y);
	}
}
t向量2 S子弹属性::fg判定(const t向量2 &a向量) const {
	return {fg判定x(a向量.x), fg判定y(a向量.y)};
}
float S子弹属性::fg显示x(float x) const {
	return m顶点->fg宽() * x * 0.5f;
}
float S子弹属性::fg显示y(float y) const {
	return m顶点->fg高() * y * 0.5f;
}
t向量2 S子弹属性::fg显示(const t向量2 &a向量) const {
	return{fg显示x(a向量.x), fg显示y(a向量.y)};
}
bool S子弹属性::fi圆形() const {
	return m判定.y <= 0;
}
bool S子弹属性::fi矩形() const {
	return m判定.y > 0;
}
//--------------------------------------------------------------------------------
// 子弹出现
//--------------------------------------------------------------------------------
S子弹出现::S子弹出现(S子弹出现 &a前, S子弹出现 &a后, float a插值) : 
	m帧{数学::f插值<float>(a前.m帧, a后.m帧, a插值)} {
}
void S子弹出现::f初始化() {
	m帧 = 0;
}
void S子弹出现::f计算() {
	m帧 = 数学::f线性渐变<float>(m帧, 1, c速度);
}
bool S子弹出现::fi正在出现() const {
	return m帧 < 1;
}
bool S子弹出现::fi出现完() const {
	return m帧 >= 1;
}
//--------------------------------------------------------------------------------
// 子弹消失
//--------------------------------------------------------------------------------
S子弹消失::S子弹消失(S子弹消失 &a前, S子弹消失 &a后, float a插值) :
	m帧{数学::f插值<float>(a前.m帧, a后.m帧, a插值)},
	m目标{数学::f插值<float>(a前.m目标, a后.m目标, a插值)},
	m速度{数学::f插值<float>(a前.m速度, a后.m速度, a插值)} {
}
void S子弹消失::f初始化(float a初始值) {
	m帧 = a初始值;
	m目标 = a初始值;
	m速度 = 0;
}
void S子弹消失::f计算() {
	if (m帧 < m目标) {
		m帧 += m速度;
	}
}
void S子弹消失::f消失(float a目标) {
	m目标 = a目标;
	fs消失速度(a目标);
}
void S子弹消失::f增加消失(float a目标) {
	m目标 += a目标;
	fs消失速度(a目标);
}
void S子弹消失::fs消失速度(float a差) {
	if (a差 > 1) {
		m速度 = c速度 * (a差 + 1.f) / 2.f;
	} else {
		m速度 = c速度 * a差;
	}
}
bool S子弹消失::fi消失() const {
	return m目标 > 0;
}
bool S子弹消失::fi全消失() const {
	return m目标 >= 1;
}
bool S子弹消失::fi存在() const {
	return m帧 <= 0;
}
bool S子弹消失::fi半存在() const {
	return (m目标 < 1) && fi还没消失();
}
bool S子弹消失::fi正在消失() const {
	return m帧 > 0;
}
bool S子弹消失::fi已经消失() const {
	return m帧 >= 1;
}
bool S子弹消失::fi还没消失() const {
	return m帧 < 1;
}

}