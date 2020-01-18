#include "玩家子弹扩展_贯穿.h"
#include "敌机基础.h"
#include "玩家子弹图形模板.h"
#include "玩家子弹图形_贯穿.h"
namespace 东方山寨::玩家子弹 {
//==============================================================================
// 贯穿激光
//==============================================================================
void C贯穿::f接口_初始化图形(C缓冲数组<I图形缓冲> &aa图形缓冲) {
	if (m子弹属性->m纹理) {
		m图形 = std::make_unique<C贯穿激光图形_图片>(*this, aa图形缓冲);
	} else {
		m图形 = std::make_unique<C贯穿激光图形_线条>(*this, aa图形缓冲);
	}
}
void C贯穿::f接口_计算() {
	const float v过秒 = m游戏速度->fg秒();
	//消失
	m消失 += c消失速度 * v过秒;
	if (m消失 < 0) {
		m消失 = 0;
	} else if (m消失 >= 1) {
		f对象_销毁();
		return;
	}
	//运动
	m长度 = 数学::f线性渐变<float>(m长度, c长度上限, m速度.fg大小() * v过秒);
	//其它
	f基础_计算时间();
	f基础_计算方向();
}
void C贯穿::f接口_敌机判定(C敌机与玩家子弹判定 &a判定) {
	if (m消失 >= 0.5f) {	//消失的子弹不参与判定
		return;
	}
	const bool v结果 = a判定.f玩家子弹_提交判定(t旋转矩形::fc线段(m坐标, fg末端(), 4));
	if (v结果) {
		f接口_命中敌机(*a判定.m敌机);
	}
}
void C贯穿::f接口_命中敌机(const C敌机 &a敌机) {
	if (m消失时间点 <= m出现 - c消失间隔 || m消失时间点 >= m出现) {
		m消失时间点 = m出现;
		//计算消失位置
		const float v敌机判定半径 = a敌机.fg判定半径();
		const t向量2 v敌机方位 = m坐标.f到点方位r(a敌机.m坐标, m方向);
		const float v水平距离差 = [&]()->float {
			const float v垂直距离 = abs(v敌机方位.y);
			if (v垂直距离 == 0) {
				return v敌机判定半径;
			} else {
				if (v垂直距离 >= v敌机判定半径) {
					return 0;
				} else {
					return 数学::f反勾股<float>(v敌机判定半径, v垂直距离);
				}
			}
		}();
		const t向量2 v速度 = t向量2::fc方向r(200, m方向);
		图形模板::f玩家子弹消失(m坐标 + t向量2::fc方向r(v敌机方位.x - v水平距离差, m方向), v速度, *m子弹属性);
	}
}
float C贯穿::fg透明度() const {
	const float v消失透明度 = (1 - m消失) * c透明度;
	const float v出现透明度 = f基础_g出现透明度();
	const float v透明度 = std::min<float>(v出现透明度, v消失透明度);
	return v透明度;
}
t向量2 C贯穿::fg末端() const {
	return m坐标 + t向量2::fc方向r(m长度, m速度.fg方向r());
}
void C贯穿::f持续() {
	m消失 -= c消失速度 * m游戏速度->fg秒() * 2;
}
}	//namespace 东方山寨::玩家子弹