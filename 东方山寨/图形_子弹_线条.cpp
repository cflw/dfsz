#include "图形_子弹_线条.h"
#include "子弹基础.h"
#include "图形引擎.h"
#include "图形_子弹_工具.h"
namespace 东方山寨 {
//==============================================================================
// 线条
//==============================================================================
C画子弹_线条::C画子弹_线条(二维::C二维 &a二维) : m画图(a二维.fc画图形()) {

}
void C画子弹_线条::f准备() {

}
void C画子弹_线条::f刷新() {

}
void C画子弹_线条::f绘制点(const C子弹顶点::C点 &a点) {
	const C子弹 *const v子弹 = a点.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	t颜色 v颜色 = v子弹->m颜色[0];
	v颜色.a = f计算透明度(a点.m中心.m出现, a点.m中心.m消失);
	m画图->fs颜色(v颜色);
	const t向量2 v判定 = v子弹属性->fg判定(v子弹->m缩放);
	const float &v子弹方向 = v子弹->m方向;
	const t向量2 &v子弹坐标 = v子弹->m坐标;
	if (v判定.x == v判定.y) {
		m画图->f绘制圆形(t圆形(v子弹坐标, v判定.x));
	} else {
		m画图->f绘制旋转矩形(t旋转矩形(v子弹坐标, v判定, v子弹方向));
	}
}
void C画子弹_线条::f绘制直线(const C子弹顶点::C直线 &a直线信息, const C子弹顶点::C直线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a直线信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float vy = v子弹属性->fg显示y(v子弹->m缩放.y);
	auto f坐标 = [v子弹方向 = v子弹->m方向, v子弹坐标 = v子弹->m坐标](float px, float py)->t向量2 {
		return t向量2(px, py).f旋转r(v子弹方向) + v子弹坐标;
	};
	const float &v子弹方向 = v子弹->m方向;
	const t向量2 &v子弹坐标 = v子弹->m坐标;
	const t向量2 v左上 = t向量2(-vx, vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v左下 = t向量2(-vx, -vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v右上 = t向量2(vx, vy).f旋转r(v子弹方向) + v子弹坐标;
	const t向量2 v右下 = t向量2(vx, -vy).f旋转r(v子弹方向) + v子弹坐标;
	//画边
	t颜色 v颜色 = v子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	m画图->f绘制线条(t线段(v左上, v左下));
	m画图->f绘制线条(t线段(v左上, v右上));
	m画图->f绘制线条(t线段(v右上, v右下));
	m画图->f绘制线条(t线段(v左下, v右下));
	//画节点
	const int v数量 = (int)a数组.size();
	数学::C范围变换计算<float> f范围变换{{0, (float)(v数量 - 1)}, {-vx, vx}};
	for (int i = 0; i != v数量; i++) {
		v颜色.a = f计算透明度(a直线信息.m中心.m出现, a数组[i].m消失);
		m画图->fs颜色(v颜色);
		m画图->f绘制圆形(t圆形(f坐标(f范围变换(i), 0), vy));
	}
}
void C画子弹_线条::f绘制曲线(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a顶点信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float v半径 = v子弹属性->fg显示y(v子弹->m缩放.y);
	画子弹工具::F曲线方向 f方向{v子弹->m方向};
	for (auto &v : 循环::C前后<const C子弹顶点::C曲线::ta顶点>{a数组}) {
		const float v方向 = f方向(v.m这->m坐标, v.m后->m坐标);
		const t向量2 v移动 = t向量2::fc方向r(v半径, v方向 + 数学::c半π<float>);
		m画图->f绘制线条(t线段(v.m这->m坐标 + v移动, v.m这->m坐标 - v移动));
		if (!v.fw前()) {
			m画图->f绘制线条(t线段(v.m前->m坐标 + v移动, v.m这->m坐标 + v移动));
			m画图->f绘制线条(t线段(v.m前->m坐标 - v移动, v.m这->m坐标 - v移动));
		}
	}
}
void C画子弹_线条::f绘制连续点(const C子弹顶点::C曲线 &a顶点信息, const C子弹顶点::C曲线::ta顶点 &a数组) {
	const C子弹 *const v子弹 = a顶点信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const float vx = v子弹属性->fg显示x(v子弹->m缩放.x);
	const float v半径 = v子弹属性->fg显示y(v子弹->m缩放.y);
	t颜色 v颜色 = a顶点信息.m子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	auto f画两点之间的线 = [&](const t向量2 &p0, const t向量2 &p1) {
		const float v方向 = p0.f到点方向r(p1);
		const t向量2 v移动 = t向量2::fc方向r(v半径, v方向 + 数学::c半π<float>);
		m画图->f绘制线条(t线段(p0 + v移动, p1 + v移动));
		m画图->f绘制线条(t线段(p0 - v移动, p1 - v移动));
	};
	for (auto &v : 循环::C前后<const C子弹顶点::C曲线::ta顶点>{a数组}) {
		const t向量2 &v这坐标 = v.m这->m坐标;
		m画图->f绘制圆形(t圆形(v这坐标, v半径));
		if (!v.fw前()) {
			f画两点之间的线(v.m前->m坐标, v这坐标);
		}
	}
	if (a顶点信息.m标志[C子弹顶点::e环]) {
		f画两点之间的线(a数组.back().m坐标, a数组.front().m坐标);
	}
}
void C画子弹_线条::f绘制网格(const C子弹顶点::C网格 &p网络信息, const C子弹顶点::C网格::ta顶点 &a数组) {
	const C子弹 *const v子弹 = p网络信息.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const t向量2 v显示 = v子弹属性->fg显示(v子弹->m缩放);
	const float v宽数 = (float)p网络信息.m宽;
	const float v高数 = (float)p网络信息.m高;
	const float v半宽 = v显示.x / (float)p网络信息.m宽;
	const float v半高 = v显示.y / (float)p网络信息.m高;
	const float v半径 = (v半宽 + v半高) / 2;
	const float v全宽 = v半宽 * 2;
	const float v全高 = v半高 * 2;
	//画线
	const t向量2 &m坐标 = v子弹->m坐标;
	const float &v方向 = v子弹->m方向;
	t颜色 v颜色 = p网络信息.m子弹->m颜色[0];
	m画图->fs颜色(v颜色);
	m画图->f绘制旋转矩形(t旋转矩形(m坐标, v显示, v方向));
	//画圆
	数学::C二维序号计算<int> f序号{p网络信息.m宽};
	for (int y = 0; y != p网络信息.m高; ++y) {
		const float v位置y = t位置计算::f右到中(y, v高数 - 1) * v全高;
		for (int x = 0; x != p网络信息.m宽; ++x) {
			const float v位置x = t位置计算::f右到中(x, v宽数 - 1) * v全宽;
			v颜色.a = f计算透明度(p网络信息.m中心.m出现, a数组[f序号(y, x)].m消失);
			m画图->fs颜色(v颜色);
			m画图->f绘制圆形(t圆形(t向量2{v位置x, v位置y}.f旋转r(v方向) + m坐标, v半径));
		}
	}
}
void C画子弹_线条::f生成点(tp子弹图形数据 &a数据, const C子弹顶点::C点 &) {
}
void C画子弹_线条::f生成直线(tp子弹图形数据 &a数据, const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) {
}
void C画子弹_线条::f生成曲线(tp子弹图形数据 &a数据, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) {
}
void C画子弹_线条::f生成连续点(tp子弹图形数据 &a数据, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) {
}
void C画子弹_线条::f生成网格(tp子弹图形数据 &a数据, const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) {
}
void C画子弹_线条::f绘制图形数据(const tp子弹图形数据 &) {
}
float C画子弹_线条::f计算透明度(float a出现, float a消失) {
	return a出现 * (1 - a消失);
}
}