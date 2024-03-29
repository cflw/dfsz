﻿#include "场景.h"
namespace 东方山寨 {
//=============================================================================
// 场景接口
//=============================================================================
void I场景::f接口_初始化() {}
void I场景::f接口_计算() {}
void I场景::f接口_更新() {}
void I场景::f接口_显示(C画三维 &) const {}
//=============================================================================
// 场景控制
//=============================================================================
void C场景控制::f初始化_图形(C画三维 &a) {
	m画三维 = &a;
}
void C场景控制::f设置场景(std::shared_ptr<I场景> a) {
	m新场景 = a;
}
void C场景控制::f计算() {
	if (m新场景) {
		m场景 = std::move(m新场景);
		m场景->f接口_初始化();
	}
	if (m场景) {
		m场景->f接口_计算();
	}
}
void C场景控制::f更新() {
	if (m场景) {
		m场景->f接口_更新();
	}
}
void C场景控制::f显示() const {
	if (m场景) {
		m场景->f接口_显示(*m画三维);
	}
}
}	//namespace 东方山寨