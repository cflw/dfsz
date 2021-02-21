#include <cflw工具_循环.h>
#include "图形_子弹_线条.h"
#include "子弹基础.h"
#include "图形引擎.h"
#include "图形_子弹_工具.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
//==============================================================================
// 图形数据
//==============================================================================
class C画子弹_线条::C图形数据_点 : public I子弹图形数据 {
public:
	t向量2 m坐标;
	t向量2 m判定;
	t颜色 m颜色;
	float m方向;
};
class C画子弹_线条::C图形数据_直线 : public I子弹图形数据 {
public:
	struct S节点 {
		float m位置;
		float m透明度;
	};
public:
	t旋转矩形 m矩形;
	t颜色 m颜色;
	std::vector<S节点> ma节点;
};
class C画子弹_线条::C图形数据_曲线 : public I子弹图形数据 {
public:
	struct S节点 {
		t颜色 m颜色;	//含透明
		t向量2 m坐标;
	};
public:
	float m半径;
	float m方向;
	std::vector<S节点> ma节点;
};
class C画子弹_线条::C图形数据_连续点 : public I子弹图形数据 {
public:
	struct S节点 {
		t颜色 m颜色;	//含透明
		t向量2 m坐标;
	};
public:
	float m半径;
	bool mi环;
	std::vector<S节点> ma节点;
};
class C画子弹_线条::C图形数据_网格 : public I子弹图形数据 {
public:
	struct S节点 {
		float m透明度;
	};
public:
	t向量2 m坐标;
	t向量2 m判定;
	t向量2 m节点尺寸;
	t颜色 m颜色;
	int m宽数;
	int m高数;
	float m方向;
	float m节点半径;
	std::vector<S节点> ma节点;
};
//==============================================================================
// 线条
//==============================================================================
C画子弹_线条::C画子弹_线条(二维::C二维 &a二维) : m画图(a二维.fc画图形()) {

}
void C画子弹_线条::f准备() {
}
void C画子弹_线条::f刷新() {
}
//生成
void C画子弹_线条::f生成点(tp子弹图形数据 &a数据, const C子弹顶点::C点 &a点) {
	const auto v数据 = f创建子弹图形数据<C图形数据_点>(a数据);
	const C子弹 *const v子弹 = a点.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	v数据->m坐标 = v子弹->m坐标;
	v数据->m判定 = v子弹属性->fg判定(v子弹->m缩放);
	v数据->m颜色 = v子弹->m颜色[0];
	v数据->m颜色.a = f计算透明度(a点.m中心.m出现, a点.m中心.m消失);
	v数据->m方向 = v子弹->m方向;
}
void C画子弹_线条::f生成直线(tp子弹图形数据 &a数据, const C子弹顶点::C直线 &a直线, const C子弹顶点::C直线::ta顶点 &a顶点) {
	const auto v数据 = f创建子弹图形数据<C图形数据_直线>(a数据);
	const C子弹 *const v子弹 = a直线.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	v数据->m矩形 = t旋转矩形::fc坐标半尺寸(a直线.m中心.m坐标, v子弹属性->fg判定(v子弹->m缩放), v子弹->m方向);
	v数据->m颜色 = v子弹->m颜色[0];
	const size_t n = a顶点.size();
	v数据->ma节点.resize(n);
	for (size_t i = 0; i != n; ++i) {
		auto &v顶点 = a顶点[i];
		auto &v节点 = v数据->ma节点[i];
		v节点.m位置 = v顶点.m位置;
		v节点.m透明度 = f计算透明度(a直线.m中心.m出现, v顶点.m消失);
	}
}
void C画子弹_线条::f生成曲线(tp子弹图形数据 &a数据, const C子弹顶点::C曲线 &a曲线, const C子弹顶点::C曲线::ta顶点 &a顶点) {
	const auto v数据 = f创建子弹图形数据<C图形数据_曲线>(a数据);
	const C子弹 *const v子弹 = a曲线.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	v数据->m半径 = v子弹属性->fg判定y(v子弹->m缩放.y);
	const size_t n = a顶点.size();
	v数据->ma节点.resize(n);
	for (size_t i = 0; i != n; ++i) {
		auto &v顶点 = a顶点[i];
		auto &v节点 = v数据->ma节点[i];
		v节点.m坐标 = v顶点.m坐标;
		v节点.m颜色 = *v顶点.m颜色[0];
		v节点.m颜色.a = f计算透明度(a曲线.m中心.m出现, v顶点.m消失);
	}
}
void C画子弹_线条::f生成连续点(tp子弹图形数据 &a数据, const C子弹顶点::C曲线 &a曲线, const C子弹顶点::C曲线::ta顶点 &a顶点) {
	const auto v数据 = f创建子弹图形数据<C图形数据_连续点>(a数据);
	const C子弹 *const v子弹 = a曲线.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	v数据->m半径 = v子弹属性->fg判定x(v子弹->m缩放.x);
	const size_t n = a顶点.size();
	v数据->ma节点.resize(n);
	for (size_t i = 0; i != n; ++i) {
		auto &v顶点 = a顶点[i];
		auto &v节点 = v数据->ma节点[i];
		v节点.m坐标 = v顶点.m坐标;
		v节点.m颜色 = *v顶点.m颜色[0];
		v节点.m颜色.a = f计算透明度(a曲线.m中心.m出现, v顶点.m消失);
	}
	v数据->mi环 = a曲线.m标志[C子弹顶点::e环];
}
void C画子弹_线条::f生成网格(tp子弹图形数据 &a数据, const C子弹顶点::C网格 &a网格, const C子弹顶点::C网格::ta顶点 &a顶点) {
	const auto v数据 = f创建子弹图形数据<C图形数据_网格>(a数据);
	const C子弹 *const v子弹 = a网格.m子弹;
	const S子弹属性 *v子弹属性 = v子弹->m子弹属性;
	const t向量2 v显示 = v子弹属性->fg显示(v子弹->m缩放);
	const float v宽数 = (float)a网格.m宽;
	const float v高数 = (float)a网格.m高;
	const float v半宽 = v显示.x / v宽数;
	const float v半高 = v显示.y / v高数;
	//填充数据
	v数据->m坐标 = v子弹->m坐标;
	v数据->m判定 = v子弹属性->fg判定(v子弹->m缩放);
	v数据->m节点尺寸 = {v半宽 * 2, v半高 * 2};
	v数据->m方向 = v子弹->m方向;
	v数据->m颜色 = v子弹->m颜色[0];
	v数据->m节点半径 = (v半宽 + v半高) / 2;
	v数据->m宽数 = a网格.m宽;
	v数据->m高数 = a网格.m高;
	const size_t n = a顶点.size();
	v数据->ma节点.resize(n);
	for (size_t i = 0; i != n; ++i) {
		auto &v顶点 = a顶点[i];
		auto &v节点 = v数据->ma节点[i];
		v节点.m透明度 = f计算透明度(a网格.m中心.m出现, v顶点.m消失);
	}
}
//绘制
void C画子弹_线条::f绘制图形数据(const tp子弹图形数据 &a数据) {
	I子弹图形数据 *const v数据 = a数据.get();
	if (const auto v点 = dynamic_cast<C图形数据_点 *>(v数据)) {
		f绘制点(*v点);
	} else if (const auto v直线 = dynamic_cast<C图形数据_直线 *>(v数据)) {
		f绘制直线(*v直线);
	} else if (const auto v曲线 = dynamic_cast<C图形数据_曲线 *>(v数据)) {
		f绘制曲线(*v曲线);
	} else if (const auto v连续点 = dynamic_cast<C图形数据_连续点 *>(v数据)) {
		f绘制连续点(*v连续点);
	} else if (const auto v网格 = dynamic_cast<C图形数据_网格 *>(v数据)) {
		f绘制网格(*v网格);
	}
}
void C画子弹_线条::f绘制点(const C图形数据_点 &a图形数据) {
	m画图->fs颜色(a图形数据.m颜色);
	if (a图形数据.m坐标.fi分量相等()) {
		m画图->f绘制圆形(t圆形(a图形数据.m坐标, a图形数据.m判定.x));
	} else {
		m画图->f绘制旋转矩形(t旋转矩形(a图形数据.m坐标, a图形数据.m判定, a图形数据.m方向));
	}
}
void C画子弹_线条::f绘制直线(const C图形数据_直线 &a图形数据) {
	const t向量2 v左上 = a图形数据.m矩形.fg点(-1, 1);
	const t向量2 v左下 = a图形数据.m矩形.fg点(-1, -1);
	const t向量2 v右上 = a图形数据.m矩形.fg点(1, 1);
	const t向量2 v右下 = a图形数据.m矩形.fg点(1, -1);
	//画边
	t颜色 v颜色 = a图形数据.m颜色;
	m画图->fs颜色(v颜色);
	m画图->f绘制线条(t线段(v左上, v左下));
	m画图->f绘制线条(t线段(v左上, v右上));
	m画图->f绘制线条(t线段(v右上, v右下));
	m画图->f绘制线条(t线段(v左下, v右下));
	//画节点
	const int v数量 = (int)a图形数据.ma节点.size();
	const t向量2 v头节点 = a图形数据.m矩形.fg点(1, 0);
	const t向量2 v尾节点 = a图形数据.m矩形.fg点(-1, 0);
	for (auto &v节点 : a图形数据.ma节点) {
		v颜色.a = v节点.m透明度;
		m画图->fs颜色(v颜色);
		const t向量2 v坐标 = 数学::f插值<t向量2>(v尾节点, v头节点, v节点.m位置);
		m画图->f绘制圆形(t圆形(v坐标, a图形数据.m矩形.m半尺寸.y));
	}
}
void C画子弹_线条::f绘制曲线(const C图形数据_曲线 &a图形数据) {
	画子弹工具::F曲线方向 f方向{a图形数据.m方向};
	for (auto &v前后节点 : 循环::C前后{a图形数据.ma节点}) {
		const float v方向 = f方向(v前后节点.m这->m坐标, v前后节点.m后->m坐标);
		const t向量2 v移动 = t向量2::fc方向r(a图形数据.m半径, v方向 + 数学::c半π<float>);
		m画图->fs颜色(v前后节点.m这->m颜色);
		m画图->f绘制线条(t线段(v前后节点.m这->m坐标 + v移动, v前后节点.m这->m坐标 - v移动));
		if (!v前后节点.fi前()) {
			m画图->f绘制线条(t线段(v前后节点.m前->m坐标 + v移动, v前后节点.m这->m坐标 + v移动));
			m画图->f绘制线条(t线段(v前后节点.m前->m坐标 - v移动, v前后节点.m这->m坐标 - v移动));
		}
	}
}
void C画子弹_线条::f绘制连续点(const C图形数据_连续点 &a图形数据) {
	auto f画两点之间的线 = [&](const t向量2 &p0, const t向量2 &p1) {
		const float v方向 = p0.f到点方向r(p1);
		const t向量2 v移动 = t向量2::fc方向r(a图形数据.m半径, v方向 + 数学::c半π<float>);
		m画图->f绘制线条(t线段(p0 + v移动, p1 + v移动));
		m画图->f绘制线条(t线段(p0 - v移动, p1 - v移动));
	};
	for (auto &v前后节点 : 循环::C前后{a图形数据.ma节点}) {
		const auto &v前 = *v前后节点.m前;
		const auto &v这 = *v前后节点.m这;
		m画图->fs颜色(v这.m颜色);
		m画图->f绘制圆形(t圆形(v这.m坐标, a图形数据.m半径));
		if (!v前后节点.fi前()) {
			m画图->fs颜色(数学::f平均(v这.m颜色, v前.m颜色));
			f画两点之间的线(v前后节点.m前->m坐标, v这.m坐标);
		}
	}
	if (a图形数据.mi环) {
		const auto &v前 = a图形数据.ma节点.back();
		const auto &v这 = a图形数据.ma节点.front();
		m画图->fs颜色(数学::f平均(v这.m颜色, v前.m颜色));
		f画两点之间的线(v前.m坐标, v这.m坐标);
	}
}
void C画子弹_线条::f绘制网格(const C图形数据_网格 &a图形数据) {
	t颜色 v颜色 = a图形数据.m颜色;
	m画图->fs颜色(v颜色);
	m画图->f绘制旋转矩形(t旋转矩形(a图形数据.m坐标, a图形数据.m判定, a图形数据.m方向));
	//画圆
	数学::C二维序号计算<int> f序号{a图形数据.m宽数};
	for (int y = 0; y != a图形数据.m高数; ++y) {
		const float v位置y = -(y - (a图形数据.m高数 - 1) * 0.5f) * a图形数据.m节点尺寸.y;
		for (int x = 0; x != a图形数据.m宽数; ++x) {
			const float v位置x = (x - (a图形数据.m宽数 - 1) * 0.5f) * a图形数据.m节点尺寸.x;
			const auto &v节点 = a图形数据.ma节点[f序号(y, x)];
			v颜色.a = v节点.m透明度;
			m画图->fs颜色(v颜色);
			m画图->f绘制圆形(t圆形(t向量2{v位置x, v位置y}.f旋转r(a图形数据.m方向) + a图形数据.m坐标, a图形数据.m节点半径));
		}
	}
}
float C画子弹_线条::f计算透明度(float a出现, float a消失) {
	return a出现 * (1 - a消失);
}
}	//namespace 东方山寨