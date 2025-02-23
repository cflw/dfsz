﻿export module 东方山寨.载入.玩家子弹发射;
import 东方山寨.载入.内部;
import "游戏.h";
import "玩家子弹发射基础.h";
import "玩家子弹发射_发散.h";
import "玩家子弹发射扩展.h";
import "玩家炸弹扩展.h";
namespace 东方山寨::载入 {
void C内部载入::f玩家子弹发射() {
	struct S内置发射属性 {
		std::wstring m名称;
		E玩家发射 m标识;
		I工厂<C玩家子弹发射器> *m发射对象;
	};
	const S内置发射属性 v玩家发射表[] = {
		{L"玩家发射.测试", E玩家发射::e测试子弹, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C自机基础>()},
		{L"玩家发射.自机", E玩家发射::e自机基础, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C自机基础>()},
		{L"玩家发射.灵梦诱导", E玩家发射::e灵梦诱导, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C灵梦诱导>()},
		{L"玩家发射.灵梦集中", E玩家发射::e灵梦集中, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C灵梦集中>()},
		{L"玩家发射.魔理沙贯穿", E玩家发射::e魔理沙贯穿, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C魔理沙贯穿>()},
		{L"玩家发射.魔理沙范围", E玩家发射::e魔理沙范围, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C魔理沙范围>()},
		{L"玩家发射.全屏清弹", E玩家发射::e全屏清弹, new C简单工厂<C玩家子弹发射器, C玩家炸弹简单发射器<玩家炸弹::C全屏清弹>>()},
		{L"玩家发射.测试炸弹", E玩家发射::e测试炸弹, new C简单工厂<C玩家子弹发射器, C玩家炸弹简单发射器<玩家炸弹::C风神录>>()},
	};
	auto &va玩家发射 = C游戏::g资源.fg玩家发射();
	for (auto &v : v玩家发射表) {
		C全局名称标识::f创建(v.m名称, (int)v.m标识);
		va玩家发射.f添加((int)v.m标识, v.m发射对象);
	}
}
}	//namespace 东方山寨::载入