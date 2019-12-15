#include <math.h>
#include "游戏常量.h"
#include "计算.h"
#include "游戏.h"
namespace 东方山寨 {
namespace 计算 {
float f插值(const std::pair<float, float> &a数值, float a插值) {
	return 数学::f插值<float>(a数值.first, a数值.second, a插值);
}
bool f计时(float &a计时, float p) {
	a计时 += (float)c帧秒;
	if (a计时 > p) {
		a计时 = 0;
		return true;
	} else {
		return false;
	}
}
float f加变化(float a变化, float a时间) {
	return a变化 * a时间 * (float)c帧秒;
}
float f乘变化(float a变化, float a时间) {
	return pow(a变化, 1 / a时间 / (float)c计算频率);
}
float f距离透明度(float a原透明, float a距离) {
	const float c最低透明度 = 0.2f;
	float v目标透明 = a距离 / 128.f;
	if (v目标透明 < c最低透明度) {
		v目标透明 = c最低透明度;
	} else if (v目标透明 > 1) {
		v目标透明 = 1;
	}
	return 数学::f倍数渐变(a原透明, v目标透明, 0.1f, 0.f, 1.f / 120.f);
}
void f基本运动计算(t向量2 &a坐标, const t向量2 &a速度, float a时间) {
	a坐标 += a速度 * a时间;
}
float f到目标时间(const t向量2 &a原, const t向量2 &a目标, float a速度) {
	const float v距离 = a目标.f到点距离(a原);
	const float v帧 = v距离 / a速度;
	return v帧 * (float)c帧秒;
}
t向量2 f到目标速度(const t向量2 &a原, const t向量2 &a目标, float a时间) {
	if (a时间 <= c帧秒) {
		return a目标 - a原;
	} else {
		return (a目标 - a原) / a时间;
	}
}
int fc随机标识() {
	static int v = 0;
	v -= 10000;
	return v;
}
float f预判自机狙(const t向量2 &a目标坐标, const t向量2 &a目标速度, const t向量2 &a发射坐标, float a发射速度) {
	//已知问题1：目标坐标与目标速度同向时b>0，t为负。解决方法：b总是取负绝对值
	//已知问题2：目标坐标与目标速度近似垂直时b≈0，t出现浮动。未解决
	const t向量2 v目标坐标 = a目标坐标 - a发射坐标;
	const float a0 = a目标速度.f平方() - std::pow(a发射速度, 2);
	const float b0 = -abs(v目标坐标.f点乘(a目标速度)) * 2;
	const float c0 = v目标坐标.f平方();
	const float d0 = b0 * b0 - 4 * a0 * c0;
	const float v根号 = (d0 > 0) ? std::sqrt(d0) : 0;
	const float t = (-b0 - v根号) / (2 * a0);
	//if (t < 0) {
	//	return v目标坐标.fg方向r();
	//}
	const t向量2 v命中坐标 = v目标坐标 + a目标速度 * t;
	return v命中坐标.fg方向r();
}
}}	//命名空间结束
