﻿#include "游戏常量.h"
#include "判定处理_敌机与玩家子弹.h"
#include "敌机基础.h"
#include "玩家子弹基础.h"
namespace 东方山寨 {
//==============================================================================
// 子弹与玩家子弹判定
//==============================================================================
void C敌机与玩家子弹判定::f绑定敌机(C敌机 &a敌机) {
	m敌机 = &a敌机;
}
void C敌机与玩家子弹判定::f绑定玩家子弹(C玩家子弹 &a子弹) {
	m子弹 = &a子弹;
}
void C敌机与玩家子弹判定::f绑定游戏速度(float a游戏速度) {
	m游戏速度 = a游戏速度;
}
void C敌机与玩家子弹判定::f计算判定() {
	m敌机->f接口_玩家子弹判定(*this);
}
bool C敌机与玩家子弹判定::f敌机_提交判定(const t圆形 &a圆) {
	m敌机判定 = a圆;
	return m子弹->f接口_敌机判定(*this);
}
bool C敌机与玩家子弹判定::f玩家子弹_提交判定(const tf判定 &af) {
	const bool v结果 = af(m敌机判定);
	if (v结果) {
		if (!m敌机->fi无敌() && m子弹->m标志[C玩家子弹::e伤害]) {
			const float v伤害 = m子弹->f属性_g伤害();
			if (m子弹->f属性_i秒伤()) {
				const float v伤害1 = v伤害 * m游戏速度;
				m敌机->f中弹(v伤害1);
				m造成伤害 += v伤害1;
			} else {
				m敌机->f中弹(v伤害);
				m造成伤害 += v伤害;
			}
		}
	}
	return v结果;
}
bool C敌机与玩家子弹判定::f玩家子弹_提交判定(const t圆形 &a圆0) {
	return f玩家子弹_提交判定([&a圆0](const t圆形 &a圆1)->bool {
		return 数学::f圆形相交判定(a圆0, a圆1);
	});
}
bool C敌机与玩家子弹判定::f玩家子弹_提交判定(const t旋转矩形 &a矩形) {
	return f玩家子弹_提交判定([&a矩形](const t圆形 &a圆形)->bool {
		return 数学::f圆形旋转矩形相交判定(a圆形, a矩形);
	});
}
float C敌机与玩家子弹判定::f结算_g造成伤害() const {
	return m造成伤害;
}
}	//namespace 东方山寨