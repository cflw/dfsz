#include "子弹_直线激光.h"
#include "子弹图形接口.h"
#include "子弹图形缓冲.h"
namespace 东方山寨 {
void C直线激光::f接口_初始化() {
	assert(m初始化_长宽.x >= 1);
	m目标 = m初始化_长宽;
	if (m目标.y < 1) {
		m目标.y = 1;
	}
	m出现.f初始化();
	const int v数量 = (int)m初始化_长宽.x;
	ma节点.resize(v数量);
	for (auto &v节点 : ma节点) {
		v节点.v消失.f初始化();
	}
}
void C直线激光::f接口_参数初始化(const S子弹参数 &a) {
	C子弹::f接口_参数初始化(a);
	f初始化_长宽(a.m长宽.x, a.m长宽.y);
}
void C直线激光::f接口_计算() {
	//渐变&消失
	m出现.f计算();
	bool vi全部消失 = true;
	for (auto &v节点 : ma节点) {
		v节点.v消失.f计算();
		if (v节点.v消失.fi还没消失()) {
			vi全部消失 = false;
		}
	}
	if (vi全部消失) {
		f对象_销毁();
		return;
	}
	//移动&长度
	t向量2 v移动速度 = m速度 * m游戏速度->fg秒();
	float &v目标长度 = m目标.x;
	float &v实际长度 = m缩放.x;
	if (v实际长度 < v目标长度) {
		const float v缩放速度 =  v移动速度.fg大小() / m子弹属性->m判定.x * 0.5f;	//缩放速度跟移动速度成正比, 这里要除以完整长度
		if (v目标长度 - v实际长度 > v缩放速度) {
			v实际长度 += v缩放速度;
		} else {
			v实际长度 = v目标长度;
		}
		v移动速度 *= 0.5f;
	}
	m坐标 += v移动速度;
	f基础_计算方向();
	//宽度
	const float v目标宽度 = m目标.y;
	float &v实际宽度 = m缩放.y;
	if (v实际宽度 != v目标宽度) {
		v实际宽度 = 数学::f线性渐变<float>(v实际宽度, v目标宽度, 0.05f);
	}
}
void C直线激光::f接口_更新() {
	const int v数量 = ma节点.size();
	C子弹顶点::C直线::ta顶点 va原始顶点((unsigned)v数量);
	const float v半数量 = (float)(v数量 - 1) / 2.f;
	for (int i = 0; i != v数量; ++i) {
		auto &v原始顶点 = va原始顶点[i];
		auto &v节点 = ma节点[i];
		v原始顶点.m位置 = (float)i / (float)(v数量 - 1);
		v原始顶点.m消失 = v节点.v消失.m帧;
	}
	C子弹顶点::C直线 v子弹顶点{this, v数量};
	v子弹顶点.m中心.m出现 = m出现.m帧;
	m图形缓冲->m绘制->f生成直线(m图形缓冲->m图形数据, v子弹顶点, va原始顶点);
}
void C直线激光::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (m出现.fi正在出现()) {
		return;
	}
	const t旋转矩形 v判定{m坐标, m子弹属性->fg判定(m缩放), m方向};
	if (a判定.f子弹_提交判定(v判定)) {
		auto &v节点 = f扩展_取坐标最近节点(a判定.fg自机坐标());
		if (!v节点.v消失.fi已经消失()) {
			a判定.f子弹_判定有效();
			if (a判定.f子弹_i碰撞()) {
				v节点.v消失.f消失(2);
			}
		}
	}
}
bool C直线激光::f接口_i在窗口外() {
	const float v半径 = m子弹属性->fg显示x();
	bool v = C矩形边界::c窗口.f外边判断(f扩展_取显示端点(1), v半径);
	v &= C矩形边界::c窗口.f外边判断(f扩展_取显示端点(-1), v半径);
	return v;
}
bool C直线激光::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	const float v长半径 = m子弹属性->fg判定x(m缩放.x);
	if (a判定.f子弹_提交判定(m坐标, v长半径)) {
		bool v真 = false;
		const float v短半径 = m子弹属性->fg判定x();
		const int v数量 = ma节点.size();
		for (int i = 0; i != v数量; ++i) {
			S节点 &v节点 = f扩展_取节点(i);
			if (v节点.v消失.fi全消失()) {
				continue;
			}
			const t向量2 v节点坐标 = f扩展_取节点坐标(i);
			if (a判定.f子弹_提交判定(v节点坐标, v短半径)) {
				a判定.f子弹_产生道具(v节点坐标, m速度);
				v节点.v消失.f消失(2);
				v真 = true;
			}
		}
		return v真;
	} else {
		return false;
	}
}
//初始化
void C直线激光::f初始化_长宽(float x, float y) {
	m初始化_长宽.x = x;
	m初始化_长宽.y = y;
}
//动作
void C直线激光::f动作_消失(bool a动画) {
	if (a动画) {
		for (auto &v节点 : ma节点) {
			v节点.v消失.f消失(1);
		}
	} else {
		f对象_销毁();
	}
}
//扩展
t向量2 C直线激光::f扩展_取固定端点(float a位置, float a半长) {
	return m坐标 + t向量2::fc方向r(a半长 * a位置, m方向);
}
t向量2 C直线激光::f扩展_取显示端点(float a位置) {
	return f扩展_取固定端点(a位置, m子弹属性->fg显示x(m缩放.x));
}
t向量2 C直线激光::f扩展_取判定端点(float a位置) {
	return f扩展_取固定端点(a位置, m子弹属性->fg判定x(m缩放.x));
}
t向量2 C直线激光::f扩展_取节点坐标(int a序号) {
	const int v数量 = ma节点.size();
	const float v半 = (float)(v数量 - 1) / 2;
	return f扩展_取显示端点((a序号 - v半) / v半);
}
C直线激光::S节点 &C直线激光::f扩展_取节点(int a序号) {
	return ma节点[a序号];
}
C直线激光::S节点 &C直线激光::f扩展_取坐标最近节点(const t向量2 &a坐标) {
	const int v数量 = ma节点.size();
	const float v方位x = m坐标.f到点方位r(a坐标, m方向).x;
	const float v判定x = m子弹属性->fg显示x(m缩放.x);	//使用显示长度,这样取的点才能和看到的一样
	const float v位置 = 数学::C范围变换计算<float>::f变换计算({-v判定x, v判定x}, {0, (float)(v数量 - 1)}, v方位x);
	const int v序号 = (int)数学::f四舍五入<float>(v位置);	//位置的四舍五入
	const int v最后序号 = 数学::f夹取<int>(v序号, 0, v数量 - 1);
	return ma节点[v最后序号];
}
}	//namespace 东方山寨