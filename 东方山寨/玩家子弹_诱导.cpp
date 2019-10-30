#include "玩家子弹_诱导.h"
#include "敌机基础.h"
namespace 东方山寨 {
namespace 玩家子弹 {
const float C诱导::c初始生命 = 2;
void C诱导::f接口_初始化() {
	v状态组.f新建(1, [this](S状态 &a, int i) {
		//v子弹扩展.v编号 = i;
		a.v目标 = nullptr;
		a.v生命 = c初始生命;
		a.f对象_使用();
	});
}
void C诱导::f接口_销毁() {
	auto &v扩展状态 = f扩展_状态();
	v扩展状态.f对象_销毁();
}
void C诱导::f接口_计算() {
	auto &v扩展状态 = f扩展_状态();
	if (v扩展状态.v生命 > 0) {
		v扩展状态.v生命 -= m游戏速度->fg秒();
	} else {
		if (v扩展状态.v目标) {
			if (!v扩展状态.v目标->f对象_w使用()) {
				v扩展状态.v目标 = f扩展_寻找目标();
			}
		} else {
			v扩展状态.v目标 = f扩展_寻找目标();
		}
		if (v扩展状态.v目标) {
			const float v目标方向 = 0;
			const float v子弹方向 = m速度.fg方向r();
			m速度.fs方向(数学::C角度计算<float>::c弧度.f旋转渐变(v子弹方向, v目标方向, 1));
		}
	}
	f基础_计算运动();
}
C诱导::S状态 &C诱导::f扩展_状态() {
	return v状态组[0/*v子弹扩展.v编号*/];
}
C敌机 *C诱导::f扩展_寻找目标() {
	C敌机 *v目标敌机 = nullptr;
	float v目标分数 = 999999;
	for (auto &v当前敌机 : va敌机->f循环_使用()) {
		if (v当前敌机.f对象_w使用()) {
			const float v方向0 = m坐标.f到点方向r(v当前敌机.m坐标);
			const float v方向1 = 数学::C角度计算<float>::c弧度.f夹角(v方向0, m速度.fg方向r());
			const float v距离 = m坐标.f到点距离(v当前敌机.m坐标);
			const float v分数 = v距离 * v方向1 * v方向1;
			if (v分数 < v目标分数) {
				v目标敌机 = &v当前敌机;
				v目标分数 = v分数;
			}
		}
	}
	return v目标敌机;
}

}
}