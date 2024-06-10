#include "游戏常量.h"
#include "图形工厂.h"
#include "图形_图片.h"
#include "游戏.h"
#include "计算.h"
#include "标识.h"
#include "敌机基础.h"
#include "预设图形.h"
namespace 东方山寨::图形模板 {
void f敌机死亡爆炸0(const t向量2 &a坐标, const t向量2 &a速度, float a缩放, const t颜色 &) {
	class C死亡圈 : public C二维图片图形 {
	public:
		C死亡圈(float a旋转, const t向量2 &a缩放) {
			m旋转 = a旋转;
			m缩放 = t向量2::c零;
			m放大速度 = a缩放 * 8;
		}
		void f事件_执行() override {
			m缩放 += m放大速度 * m游戏速度->fg渲染秒();
		}
		t向量2 m放大速度;
	};
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	auto v随机数 = C游戏::fg资源().f工厂_随机数引擎(0x68c3);
	auto v圆形分布 = 数学::C圆形分布(t圆形::fc坐标半径(t向量2::c零, 32));
	auto v圆周分布 = 数学::c圆周分布r<float>;
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m坐标 = a坐标;
	v参数.m速度 = a速度 * 0.5f;
	v参数.m寿命 = 0.25f * a缩放;
	v参数.m顶点 = 计算::f标识((int)E图形::e效果0, 0, 0);
	v参数.m纹理 = (int)E图形::e效果0;
	v参数.m图层 = (int)E图层::e敌机;
	v图形工厂.f产生图形<C死亡圈>(v参数, 0, t向量2{a缩放, a缩放});
	v图形工厂.f产生图形<C死亡圈>(v参数, v圆周分布(v随机数), t向量2{0.5f * a缩放, 1.5f * a缩放});
	for (int i = 0; i != 3; ++i) {	//白色线条圈
		v参数.m坐标 = a坐标 + v圆形分布(v随机数);
		v图形工厂.f产生图形<图形::C圆形>(v参数, 0, 100);
	}
}
void f敌机死亡小爆炸(const C敌机 &a敌机) {
	f敌机死亡爆炸0(a敌机.m坐标, a敌机.m速度, 1, t颜色::c红);
}
void f敌机死亡大爆炸(const C敌机 &a敌机) {
	f敌机死亡爆炸0(a敌机.m坐标, a敌机.m速度, 3, t颜色::c红);
}
}	//namespace 东方山寨::图形模板