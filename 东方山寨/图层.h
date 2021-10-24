#pragma once
#include <atomic>
namespace 东方山寨 {
enum class E图层 {
	e无 = 0,	//未指定图层,使用图层0会触发断言
	e背景 = 1,
	e场景 = 5,
	e前景 = 10,
	e敌机 = 20,
	e玩家 = 30,
	e玩家子弹 = 35,
	e道具 = 40,
	e图形 = 50,
	e子弹 = 60,
	e立绘 = 70,
	e对话 = 75,
	e抬显 = 80,
	e顶层 = 100,
};
namespace 计算 {
//获得一个递增的显示编号.允许数据竞争,反正图形显示顺序错乱不影响游戏
inline int fg显示编号() {
	static int v显示编号 = 0;
	return v显示编号++;
}
}	//namespace 计算
}	//namespace 东方山寨