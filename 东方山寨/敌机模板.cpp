#include "敌机模板.h"
#include "敌机扩展.h"
#include "敌机制造机.h"
#include "图形工厂.h"
#include "图形_抬显.h"
#include "游戏.h"
namespace 东方山寨::敌机模板 {
std::shared_ptr<C敌机> f护盾(C敌机 &a敌机, int a生命值, const t颜色 &a颜色) {
	auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
	v敌机工厂.m参数.m坐标 = a敌机.m坐标;
	v敌机工厂.m参数.m生命值 = a生命值;
	v敌机工厂.m参数.m样式 = &C敌机扩展生命::c属性;
	auto vp敌机 = v敌机工厂.f产生敌机<C敌机扩展生命>(a敌机);
	图形模板::f分血条(*vp敌机, t颜色::c蓝);
	return vp敌机;
}
}	//namespace 东方山寨::敌机模板