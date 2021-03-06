﻿#include "游戏.h"
#include "关卡效果.h"
#include "图形工厂.h"
#include "图形_抬显.h"
namespace 东方山寨 {
//=============================================================================
// 效果
//=============================================================================
void C关卡效果::f显示标题(const S关卡标题 &a关卡标题) {
	auto v图形工厂 = C游戏::fg资源().f工厂_图形();
	v图形工厂.m参数.m寿命 = 5;
	v图形工厂.m参数.m图层 = (int)E图层::e抬显;
	v图形工厂.f产生图形<C关卡标题>(a关卡标题);
}
std::function<void()> C关卡效果::F显示标题(const S关卡标题 &a关卡标题) {
	return [a关卡标题]() {
		f显示标题(a关卡标题);
	};
}

}