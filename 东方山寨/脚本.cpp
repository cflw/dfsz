#include "脚本.h"
import 东方山寨.玩家炸弹发射;
namespace 东方山寨 {
namespace 脚本 {
//==============================================================================
// 资源
//==============================================================================
tp敌机属性 fg敌机样式(const std::wstring &a名称) {
	const auto &va敌机属性 = C游戏::fg资源().fg敌机属性();
	return va敌机属性[a名称];
}
tp模型 fg模型(const std::wstring &a名称) {
	static auto &va模型 = C游戏::fg图形().fg模型();
	return va模型[a名称];
}
tp纹理 fg纹理(const std::wstring &a名称) {
	static auto &va纹理 = C游戏::fg图形().fg纹理();
	return va纹理[a名称];
}
tp静态立绘 fg静态立绘(const std::wstring &a名称) {
	static auto &va静态立绘 = C游戏::fg资源().fg静态立绘();
	return va静态立绘.ma属性[a名称];
}
//==============================================================================
// 内容
//==============================================================================
std::function<float()> F随机数(unsigned long long a推进) {
	return C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<float>(0, 1), a推进);
}
void f全屏清弹(const t向量2 &a坐标, float a半径, bool a道具) {
	return C游戏::fg内容().fg炸弹发射管理().f全屏清弹(a坐标, a半径, a道具);
}
float fg动态难度() {
	const auto &v难度 = C游戏::fg内容().fg难度();
	return v难度.fg动态难度();
}
t向量2 fg自机坐标() {
	return C游戏::g内容.fg自机().m坐标;
}
t向量2 fg自机速度(float a秒) {
	return C游戏::g内容.fg玩家().m轨迹.fg平均速度(a秒);
}
std::shared_ptr<C敌机> f王入场(E敌机 a敌机, const t向量2 &a开始, const t向量2 &a结束) {
	const auto &v敌机工厂 = C游戏::fg内容().f工厂_敌机();
	t敌机参数 v敌机参数;
	v敌机参数.fs坐标(a开始);
	v敌机参数.fs移动到_时间(a结束, 1);
	v敌机参数.m样式 = (int)a敌机;
	auto v敌机 = v敌机工厂.f产生王(v敌机参数);
	图形模板::f分血条(*v敌机);
	auto &v王战 = C游戏::fg内容().fg王战控制();
	v王战.fs王(v敌机);
	return v敌机;
}
void f掉落道具(const t道具组 &a道具组, const t向量2 &a坐标, const t向量2 &a速度) {
	const auto &v工厂 = C游戏::fg内容().f工厂_道具();
	t道具参数 v参数;
	v参数.m坐标 = a坐标;
	v参数.m速度 = a速度;
	v工厂.f产生道具(v参数, a道具组);
}
}	//namespace 脚本
}	//namespace 东方山寨