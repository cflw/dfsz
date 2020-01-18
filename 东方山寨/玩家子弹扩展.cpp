#include "玩家子弹扩展.h"
#include "敌机基础.h"
#include "游戏.h"
#include "玩家子弹图形模板.h"
#include "图形_画图片.h"
namespace 东方山寨::玩家子弹 {
//==============================================================================
// 诱导
//==============================================================================
C诱导::C诱导():
	ma敌机{&C游戏::g内容.fg敌机数组()} {
}
void C诱导::f接口_计算() {
	if (m生命 > 0) {
		std::shared_ptr<C敌机> v目标 = m目标.lock();
		//寻找目标
		if (v目标 && !v目标->f对象_i使用()) {	//原来有目标但是现在没了
			v目标 = f寻找目标();
		} else {	//没目标
			v目标 = f寻找目标();
		}
		//确定目标
		if (v目标) {
			const float v目标方向 = m坐标.f到点方向r(v目标->m坐标);
			const float v子弹方向 = m速度.fg方向r();
			m速度.fs方向(数学::C角度计算<float>::c弧度.f旋转渐变(v子弹方向, v目标方向, c角速度));
		}
		//其它
		m目标 = v目标;
		m生命 -= m游戏速度->fg秒();
	}
	f基础_计算运动();
	f基础_计算方向();
	f基础_计算时间();
}
std::shared_ptr<C敌机> C诱导::f寻找目标() {
	std::shared_ptr<C敌机> v目标敌机 = nullptr;
	float v目标分数 = 999999;
	ma敌机->fe使用p([&](std::shared_ptr<C敌机> a当前敌机) {
		const C敌机 &v当前敌机 = *a当前敌机;
		const float v方向0 = m坐标.f到点方向r(v当前敌机.m坐标);
		const float v方向1 = 数学::C角度计算<float>::c弧度.f夹角(v方向0, m速度.fg方向r());
		const float v距离 = m坐标.f到点距离(v当前敌机.m坐标);
		const float v分数 = v距离 * v方向1 * v方向1;
		if (v分数 < v目标分数) {
			v目标敌机 = a当前敌机;
			v目标分数 = v分数;
		}
	});
	return v目标敌机;
}
}	//namespace 东方山寨::玩家子弹