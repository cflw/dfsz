﻿#include "标识.h"
#include "判定处理_子弹与玩家炸弹.h"
#include "道具制造机.h"
#include "玩家炸弹基础.h"
#include "子弹基础.h"
namespace 东方山寨 {
//==============================================================================
// 子弹与玩家炸弹判定
//==============================================================================
void C子弹与玩家炸弹判定::f绑定道具(C道具制造机 *a) {
	m道具制造机 = a;
	m道具制造机->m参数.fs属性((int)E道具::e微最大点);
}
void C子弹与玩家炸弹判定::f绑定子弹(C子弹 *a子弹) {
	m子弹 = a子弹;
}
void C子弹与玩家炸弹判定::f绑定炸弹(C玩家炸弹 *a炸弹) {
	m炸弹 = a炸弹;
	m玩家 = m炸弹->m玩家;
	m道具制造机->m参数.m跟随玩家 = m玩家;
}
void C子弹与玩家炸弹判定::f计算判定() {
	m炸弹->f接口_子弹判定(*this);
}
bool C子弹与玩家炸弹判定::fi产生道具() const {
	return m炸弹->f接口_i产生道具();
}
bool C子弹与玩家炸弹判定::f炸弹_提交判定(tf判定 af) {
	mf判定 = af;
	return m子弹->f接口_炸弹判定(*this);
}
bool C子弹与玩家炸弹判定::f炸弹_提交判定(const t圆形 &a圆) {
	return f炸弹_提交判定([&a圆](const t向量2 &a坐标, float a半径)->bool {
		return 数学::f圆形相交判定(a圆.m坐标, a圆.m半径, a坐标, a半径);
	});
}
bool C子弹与玩家炸弹判定::f子弹_提交判定(const t向量2 &a坐标, float a半径) const {
	return mf判定(a坐标, a半径);
}
void C子弹与玩家炸弹判定::f子弹_产生道具(const t向量2 &a坐标, const t向量2 &a速度) const {
	if (fi产生道具()) {
		m道具制造机->m参数.m坐标 = a坐标;
		m道具制造机->m参数.m速度 = a速度;
		m道具制造机->f产生道具();
	}
}

}	//namespace 东方山寨