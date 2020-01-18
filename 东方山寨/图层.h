#pragma once
#include <atomic>
namespace 东方山寨 {
enum class E图层 {
	e无 = 0,	//未初始化
	e底层 = 10,
	e敌机 = 20,
	e玩家 = 30,
	e玩家子弹 = 31,
	e道具 = 40,
	e图形 = 50,
	e子弹 = 60,
	e抬显 = 80,
	e顶层 = 100,
};
namespace 计算 {
//获得一个递增的显示编号
inline int fg显示编号() {
	static int v显示编号 = 0;
	return v显示编号++;
}
}	//namespace 计算
}	//namespace 东方山寨