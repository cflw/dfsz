#include "子弹_普通子弹.h"
#include "子弹图形接口.h"
#include "子弹图形缓冲.h"
namespace 东方山寨 {
//核心
void C普通子弹::f接口_初始化() {
	m出现.f初始化();
	m消失.f初始化();
}
void C普通子弹::f接口_计算() {
	//运动
	f基础_计算运动();
	f基础_计算方向();
	//渐变&消失
	m出现.f计算();
	if (m消失.fi消失()) {
		m消失.f计算();
		if (m消失.fi已经消失()) {
			f对象_销毁();
			return;
		}
	}
}
void C普通子弹::f接口_更新() {
	C子弹顶点::C点 v顶点(this);
	v顶点.m中心.m出现 = m出现.m帧;
	v顶点.m中心.m消失 = m消失.m帧;
	m图形缓冲->m绘制->f生成点(m图形缓冲->m图形数据, v顶点);
}
void C普通子弹::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (m出现.fi正在出现()) {
		return;
	}
	if (m消失.fi正在消失()) {
		return;
	}
	if (m子弹属性->fi圆形()) {
		const t圆形 v圆1{m坐标, m子弹属性->fg判定x(m缩放.x)};
		a判定.f子弹_提交判定(v圆1);
	} else {
		t旋转矩形 v矩形{m坐标, m子弹属性->fg判定(m缩放), m方向};
		a判定.f子弹_提交判定(v矩形);
	}
	a判定.f子弹_判定有效();
	if (a判定.f子弹_i碰撞()) {
		m消失.f消失();
	}
}
bool C普通子弹::f接口_i在窗口外() {
	const float v半径 = m子弹属性->fg显示x(m缩放.x);
	return 边框::C矩形::c窗口.f判断(m坐标, v半径);
}
bool C普通子弹::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	const float v半径 = m子弹属性->fg判定x(m缩放.x);
	if (a判定.f子弹_提交判定(m坐标, v半径)) {
		a判定.f子弹_产生道具(m坐标, m速度);
		f动作_消失(true);
		m标志[e停止炸弹判定] = true;
		return true;
	}
	return false;
}
//动作
void C普通子弹::f动作_消失(bool a动画) {
	if (a动画) {
		m消失.f消失();
	} else {
		f对象_销毁();
	}
}
}	//namespace 东方山寨