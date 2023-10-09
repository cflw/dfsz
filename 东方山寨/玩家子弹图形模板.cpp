#include "玩家子弹基础.h"
#include "图形_图片.h"
#include "游戏.h"
#include "图形工厂.h"
namespace 东方山寨::图形模板 {
constexpr float c玩家子弹消失时间 = 0.2f;
class C玩家子弹消失 : public C二维图片图形 {
public:
	C玩家子弹消失(const S玩家子弹属性 &a子弹属性):
		m子弹属性(&a子弹属性) {
	}
	void f接口_初始化(const S图形参数 &a参数) override {
		C二维图片图形::f接口_初始化(a参数);
		m旋转 = m速度.fg方向r();
	}
	float f接口_g透明度() const override {
		return fg反生命百分比() * C玩家子弹::c透明度;
	}
	int f接口_g顶点序号() const override {
		return (int)(fg生命百分比() * m子弹属性->m消失帧数);
	}
	const S玩家子弹属性 *m子弹属性 = nullptr;
};
void f玩家子弹消失(const t向量2 &a坐标, const t向量2 &a速度, const S玩家子弹属性 &a属性) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m坐标 = a坐标;
	v参数.m速度 = a速度;
	v参数.m寿命 = c玩家子弹消失时间;
	v参数.m顶点 = a属性.m消失顶点;
	v参数.m纹理 = a属性.m消失纹理;
	v参数.m图层 = (int)E图层::e玩家子弹;
	v图形工厂.f产生图形<C玩家子弹消失>(v参数, a属性);
}
void f玩家子弹消失(const C玩家子弹 &a玩家子弹) {
	f玩家子弹消失(a玩家子弹.m坐标, a玩家子弹.m速度 * 0.2f, *a玩家子弹.m子弹属性);
}
}	//namespace 东方山寨::图形模板