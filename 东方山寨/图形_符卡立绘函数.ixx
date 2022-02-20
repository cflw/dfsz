module;
#include "数学包含.h"
#include "动画接口.h"
export module 东方山寨.图形_符卡立绘函数;
export import 东方山寨.图形_符卡立绘;
export namespace 东方山寨 {
//==============================================================================
// 符卡立绘函数,给出时间[0, 1],计算相关值
//==============================================================================
namespace 符卡立绘 {
constexpr float c短距离 = 50;
constexpr float c长距离 = 100;
inline const t向量2 c左下 = t向量2::fc方向r(c长距离, 数学::cπ<float> * 1.25f);
C符卡立绘::tf显示参数 F单向变速(const t向量2 &a方向) {
	return [=](float t)->S动画缓冲 {
		S动画缓冲 v;
		if (t < 0.25f) {
			const t向量2 v点0 = -a方向 * 2;
			const t向量2 v点1 = -a方向 * 0.5f;
			const float t0 = t * 4;
			v.m坐标 = 数学::f插值<t向量2>(v点0, v点1, t0);
			v.m透明度 = 数学::f插值<float>(0, C符卡立绘::c最大透明度, t0);
		} else if (t < 0.75f) {
			const t向量2 v点0 = -a方向 * 0.5f;
			const t向量2 v点1 = a方向 * 0.5f;
			const float t0 = (t - 0.25f) * 2;
			v.m坐标 = 数学::f插值<t向量2>(v点0, v点1, t0);
			v.m透明度 = C符卡立绘::c最大透明度;
		} else {
			const t向量2 v点0 = a方向 * 0.5f;
			const t向量2 v点1 = a方向 * 2;
			const float t0 = (t - 0.75f) * 4;
			v.m坐标 = 数学::f插值<t向量2>(v点0, v点1, t0);
			v.m透明度 = 数学::f插值<float>(C符卡立绘::c最大透明度, 0, t0);
		}
		return v;
	};
}
}	//namespace 符卡立绘
}	//namespace 东方山寨