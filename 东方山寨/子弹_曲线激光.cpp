#include "子弹_曲线激光.h"
#include "计算.h"
#include "子弹图形接口.h"
#include "子弹图形缓冲.h"
namespace 东方山寨 {
//==============================================================================
// 扩展-曲线激光
//==============================================================================
//曲线激光节点
void C曲线激光::S节点::f更新(const t向量2 &a坐标, const t向量2 &a速度, float a方向, const t颜色 &a颜色) {
	m原坐标 = m坐标 = a坐标;
	m速度 = a速度;
	m方向 = a方向;
	m颜色 = a颜色;
}
//接口
void C曲线激光::f接口_初始化() {
	m计算计时 = 0;
	int i = 0;
	for (auto &v节点 : ma节点) {
		v节点.m序号 = (i++);
		v节点.f更新(m坐标, t向量2(), m方向, m颜色[0]);
		v节点.mi道具 = true;
		v节点.m消失.f初始化();
	}
}
void C曲线激光::f接口_参数初始化(const S子弹参数 &a) {
	C子弹::f接口_参数初始化(a);
	//长
	const float v像素长 = a.m长宽.x > 0 ? a.m长宽.x : c默认长度;
	const float v倍数长 = c节点基数 * v像素长 / m速度.fg大小();
	assert(v倍数长 >= 2);
	const size_t v数量 = (size_t)std::round(v倍数长);
	ma节点.resize(v数量);
	//宽
	f初始化_宽度到缩放(a.m长宽.y);
	//其他
	m出现.f初始化(a.m出现);
}
void C曲线激光::f接口_计算() {
	//渐变&消失
	m出现.f计算();
	bool v全部消失 = true;
	for (auto &v节点 : ma节点) {
		v节点.m消失.f计算();
		if (v节点.m消失.fi还没消失()) {
			v全部消失 = false;
		}
	}
	if (v全部消失) {
		f对象_销毁();
		return;
	}
	//移动
	f基础_计算运动();
	f基础_计算方向();
	m计算计时 += m游戏速度->fg速度();
	if (m计算计时 >= c节点计算周期) {
		m计算计时 -= c节点计算周期;
		for (int i = (int)ma节点.size() - 1; i != 0; --i) {
			auto &v这 = f扩展_取节点(i);
			auto &v前 = f扩展_取节点(i - 1);
			v这.f更新(v前.m原坐标, v前.m速度, v前.m方向, v前.m颜色);
		}
		f扩展_更新头节点();
	} else {
		for (auto &v节点 : ma节点) {
			计算::f基本运动计算(v节点.m坐标, v节点.m速度, m游戏速度->fg秒());
		}
	}
}
void C曲线激光::f接口_更新() {
	const int v数量 = (int)ma节点.size();
	C子弹顶点::C曲线::ta顶点 va原始顶点{(unsigned)v数量};
	for (int i = 0; i != v数量; ++i) {
		auto &v节点 = f扩展_取节点(i);
		auto &v原始顶点 = va原始顶点[i];
		v原始顶点.m位置 = (float)i / (float)(v数量 - 1);
		v原始顶点.m坐标 = v节点.m坐标;
		v原始顶点.m出现 = m出现.m帧;
		v原始顶点.m消失 = v节点.m消失.m帧;
		v原始顶点.m颜色[0] = &v节点.m颜色;
	}
	C子弹顶点::C曲线 v子弹顶点{this, v数量};
	v子弹顶点.m中心.m出现 = m出现.m帧;
	m图形缓冲->m绘制->f生成曲线(m图形缓冲->m图形数据, v子弹顶点, va原始顶点);
}
void C曲线激光::f接口_自机判定(C自机与子弹判定 &a判定) {
	for (auto &v节点 : ma节点) {
		if (v节点.m消失.fi正在消失()) {
			continue;
		}
		const t圆形 v节点判定{v节点.m坐标, m子弹属性->fg判定y(m缩放.y)};
		if (a判定.f子弹_提交判定(v节点判定)) {
			a判定.f子弹_判定有效();
			if (a判定.f子弹_i碰撞()) {
				f扩展_节点消失(v节点.m序号);
			}
		}
	}
}
bool C曲线激光::f接口_i在窗口外() {
	for (auto &v节点 : ma节点) {
		if (!边框::C矩形::c窗口.f判断(v节点.m坐标, m子弹属性->fg显示y())) {
			return false;
		}
	}
	return true;
}
bool C曲线激光::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	auto f产生道具 = [&](int a节点) {
		auto &v节点 = f扩展_取节点(a节点);
		if (v节点.mi道具) {
			v节点.mi道具 = false;
			a判定.f子弹_产生道具(v节点.m坐标, v节点.m速度);
		}
	};
	const float v半径 = m子弹属性->fg判定x();
	bool v真 = false;
	for (auto &v节点 : ma节点) {
		if (v节点.m消失.fi全消失()) {
			continue;
		}
		if (a判定.f子弹_提交判定(v节点.m坐标, v半径)) {
			f扩展_节点消失(v节点.m序号);
			for (auto &v节点 : fe范围(v节点.m序号 - 1, v节点.m序号 + 2)) {
				if (v节点.mi道具) {
					v节点.mi道具 = false;
					a判定.f子弹_产生道具(v节点.m坐标, v节点.m速度);
				}
			}
			v真 = true;
		}
	}
	return v真;
}
//动作
void C曲线激光::f动作_消失(bool a动画) {
	if (a动画) {
		for (auto &v节点 : ma节点) {
			v节点.m消失.f消失();
		}
	} else {
		f对象_销毁();
	}
}
//扩展
C曲线激光::S节点 &C曲线激光::f扩展_取节点(int a序号) {
	if (a序号 <= 0) {
		return f扩展_取头节点();
	} else if (a序号 >= (int)ma节点.size()) {
		return f扩展_取尾节点();
	} else {
		return ma节点[a序号];
	}
}
const C曲线激光::S节点 &C曲线激光::f扩展_取节点(int a序号) const {
	if (a序号 <= 0) {
		return ma节点.front();
	} else if (a序号 >= (int)ma节点.size()) {
		return ma节点.back();
	} else {
		return ma节点[a序号];
	}
}
C曲线激光::S节点 &C曲线激光::f扩展_取头节点() {
	return ma节点.front();
}
C曲线激光::S节点 &C曲线激光::f扩展_取尾节点() {
	return ma节点.back();
}
void C曲线激光::f扩展_更新头节点() {
	auto &v头 = f扩展_取头节点();
	v头.f更新(m坐标, m速度, m方向, m颜色[0]);
}
void C曲线激光::f扩展_节点消失(int a序号) {
	auto &v = f扩展_取节点(a序号);
	v.m消失.f消失(2);
	for (auto &v节点 : fe周围(a序号)) {
		if (v节点.m消失.fi正在消失()) {
			v节点.m消失.f消失();
		} else {
			v节点.m消失.f消失(0.1f);
		}
	}
	f扩展_节点消失检查();
}
void C曲线激光::f扩展_节点消失检查() {
	bool v全部消失 = true;
	for (auto &v节点 : ma节点) {
		if (v节点.m消失.fi存在()) {
			v全部消失 = false;
			break;
		}
	}
	if (v全部消失) {
		for (auto &v节点 : ma节点) {
			v节点.m消失.f消失();
		}
	}
}
std::vector<C曲线激光::S节点> &C曲线激光::fe节点() {
	return ma节点;
}
循环::C零散<std::vector<C曲线激光::S节点>> C曲线激光::fe周围(int a序号) {
	if (a序号 <= 0) {
		return {ma节点, {a序号 + 1}};
	} else if (a序号 >= (int)ma节点.size() - 1) {
		return {ma节点, {a序号 - 1}};
	} else {
		return {ma节点, {a序号 - 1, a序号 + 1}};
	}
}
循环::C范围<std::vector<C曲线激光::S节点>> C曲线激光::fe范围(int a开始, int a结束) {
	return {ma节点, a开始, a结束};
}
std::experimental::generator<C曲线激光::S节点> C曲线激光::fe节点插值(int a数量) {
	assert(a数量 > 0);
	const float v节点上限 = (float)(ma节点.size() - 1);
	const float v循环上限 = (float)(a数量 - 1);
	for (int i = 0; i != a数量; ++i) {
		const float v序号 = (float)i * v节点上限 / v循环上限;
		const float v序号下 = std::floor(v序号);
		const int j = (int)v序号;
		if (v序号 == v序号下) {
			co_yield ma节点[j];
		} else {
			const float v插值 = v序号 - v序号下;
			co_yield 数学::f插值(ma节点[j], ma节点[j + 1], v插值);
		}
	}
}
}	//namespace 东方山寨
namespace cflw::数学 {
template<> 东方山寨::C曲线激光::S节点 f插值<东方山寨::C曲线激光::S节点>(const 东方山寨::C曲线激光::S节点 &a前, const 东方山寨::C曲线激光::S节点 &a后, float a插值) {
	东方山寨::C曲线激光::S节点 v节点;
	v节点.m序号 = (a前.m序号 + a后.m序号) / 2;
	v节点.m原坐标 = 数学::f插值(a前.m原坐标, a后.m原坐标, a插值);
	v节点.m坐标 = 数学::f插值(a前.m坐标, a后.m坐标, a插值);
	v节点.m速度 = 数学::f插值(a前.m速度, a后.m速度, a插值);
	v节点.m方向 = 数学::c弧度计算<float>.f插值(a前.m方向, a后.m方向, a插值);
	v节点.m颜色 = 数学::f插值(a前.m颜色, a后.m颜色, a插值);
	return v节点;
}
}	//namespace cflw::数学