module;
#include "基础_属性数组.h"
#include "游戏.h"
#include "图形工厂.h"
#include "图层.h"
export module 东方山寨.图形_符卡立绘模板;
import 东方山寨.图形_符卡立绘;
export namespace 东方山寨::图形模板 {
void f符卡立绘(const std::wstring &a名称, C符卡立绘::tf显示参数 af显示参数, float a寿命 = C符卡立绘::c显示时间);
}	//namespace 东方山寨::图形模板
module : private;
namespace 东方山寨::图形模板 {
void f符卡立绘(const std::wstring &a名称, C符卡立绘::tf显示参数 af显示参数, float a寿命) {
	const auto &v图形工厂 = C游戏::fg图形().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m图层 = (int)E图层::e立绘;
	v参数.m纹理 = C游戏::fg图形().fg纹理()[a名称];
	v参数.m顶点 = C游戏::fg图形().fg顶点矩形()[a名称];
	v图形工厂.f产生图形<C符卡立绘>(v参数, af显示参数, a寿命);
}
}	//namespace 东方山寨::图形模板