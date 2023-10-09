module;
#include "关卡.h"
#include "游戏.h"
#include "图形工厂.h"
#include "图形_抬显.h"
export module 东方山寨.关卡效果;
export import 东方山寨.图形_关卡标题;
export namespace 东方山寨 {
class C关卡效果 {
public:
	static void f显示标题(const S关卡标题 &);
	static std::function<void()> F显示标题(const S关卡标题 &);
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void C关卡效果::f显示标题(const S关卡标题 &a关卡标题) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m寿命 = 5;
	v参数.m图层 = (int)E图层::e抬显;
	v图形工厂.f产生图形<C关卡标题>(v参数, a关卡标题);
}
std::function<void()> C关卡效果::F显示标题(const S关卡标题 &a关卡标题) {
	return [a关卡标题]() {
		f显示标题(a关卡标题);
		};
}
}	//namespace 东方山寨