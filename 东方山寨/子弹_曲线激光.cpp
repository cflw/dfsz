#include "子弹_曲线激光.h"
#include "计算.h"
#include "子弹图形接口.h"
#include "子弹图形缓冲.h"
namespace 东方山寨 {
//==============================================================================
// 扩展-曲线激光
//==============================================================================
//曲线激光节点
void C曲线激光::S节点::f更新(const t向量2 &p坐标, const t向量2 &p速度, float p方向, const t颜色 &p颜色) {
	m原坐标 = m坐标 = p坐标;
	m速度 = p速度;
	m方向 = p方向;
	m颜色 = p颜色;
}
//接口
void C曲线激光::f接口_初始化() {
	const int v数量 = (int)m初始化_长度;
	assert(v数量 > 1);
	m出现.f初始化();
	m计算计时 = 0;
	m计算周期 = 1 / m初始化_精度;
	ma节点.resize(v数量);
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
	f初始化_长宽(a.m长宽.x, a.m长宽.y);
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
	if (m计算计时 >= m计算周期) {
		m计算计时 -= m计算周期;
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
		if (!C边界::c窗口.f外边判断(v节点.m坐标, m子弹属性->fg显示y())) {
			return false;
		}
	}
	return true;
}
bool C曲线激光::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	auto f产生道具 = [&](int p节点) {
		auto &v节点 = f扩展_取节点(p节点);
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
			for (auto &v节点 : f循环_范围(v节点.m序号 - 1, v节点.m序号 + 2)) {
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
//初始化
void C曲线激光::f初始化_长宽(float a长, float a宽) {
	m初始化_长度 = (a长 > 1) ? a长 : c默认长度;
	m初始化_宽度 = (a宽 > 0) ? a宽 : 1;
}
void C曲线激光::f初始化_精度(float a精) {
	m初始化_精度 = a精;
}
//动作
void C曲线激光::f动作_消失(bool p) {
	if (p) {
		for (auto &v节点 : ma节点) {
			v节点.m消失.f消失(1);
		}
	} else {
		f对象_销毁();
	}
}
//扩展
C曲线激光::S节点 &C曲线激光::f扩展_取节点(int p) {
	if (p <= 0) {
		return f扩展_取头节点();
	} else if (p >= (int)ma节点.size()) {
		return f扩展_取尾节点();
	} else {
		return ma节点[p];
	}
}
const C曲线激光::S节点 &C曲线激光::f扩展_取节点(int p) const {
	if (p <= 0) {
		return ma节点.front();
	} else if (p >= (int)ma节点.size()) {
		return ma节点.back();
	} else {
		return ma节点[p];
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
void C曲线激光::f扩展_节点消失(int p) {
	auto &v = f扩展_取节点(p);
	v.m消失.f消失(2);
	for (auto &v节点 : f循环_周围(p)) {
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
std::vector<C曲线激光::S节点> &C曲线激光::f循环_全部() {
	return ma节点;
}
循环::C零散<std::vector<C曲线激光::S节点>> C曲线激光::f循环_周围(int p) {
	if (p <= 0) {
		return {ma节点, {p + 1}};
	} else if (p >= (int)ma节点.size() - 1) {
		return {ma节点, {p - 1}};
	} else {
		return {ma节点, {p - 1, p + 1}};
	}
}
循环::C范围<std::vector<C曲线激光::S节点>> C曲线激光::f循环_范围(int p0, int p1) {
	return {ma节点, p0, p1};
}
}