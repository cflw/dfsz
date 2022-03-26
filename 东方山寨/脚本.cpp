#include "脚本.h"
namespace 东方山寨 {
t向量2 fg自机坐标() {
	return C游戏::g内容.fg自机().m坐标;
}
t向量2 fg自机速度(float a秒) {
	return C游戏::g内容.fg玩家().m轨迹.fg平均速度(a秒);
}
std::shared_ptr<C敌机> f王入场(E敌机 a敌机, const t向量2 &a开始, const t向量2 &a结束) {
	auto v敌机工厂 = C游戏::fg内容().f工厂_敌机();
	v敌机工厂.m参数.fs坐标(a开始);
	v敌机工厂.m参数.fs移动到_时间(a结束, 1);
	v敌机工厂.m参数.m样式 = (int)a敌机;
	auto v敌机 = v敌机工厂.f产生王();
	图形模板::f分血条(*v敌机);
	auto &v王战 = C游戏::fg内容().fg王战控制();
	v王战.fs王(v敌机);
	return v敌机;
}
}	//namespace 东方山寨