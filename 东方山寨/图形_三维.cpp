#include "图形_三维.h"
#include "游戏.h"
#include "程序.h"
#include "图形引擎.h"
namespace 东方山寨 {
//=============================================================================
// 模型
//=============================================================================
C模型::C模型(const S三维顶点 *a顶点, size_t a顶点数, const uint16_t *a索引, size_t a索引数):
	m顶点(new S三维顶点[a顶点数]), m索引(new uint16_t[a索引数]), m顶点数(a顶点数), m索引数(a索引数) {
	memcpy(m顶点, a顶点, sizeof(S三维顶点) * a顶点数);
	memcpy(m索引, a索引, sizeof(uint16_t) * a索引数);
}
C模型::C模型(C模型 &&a):
	m顶点(a.m顶点), m索引(a.m索引), m顶点数(a.m顶点数), m索引数(a.m索引数) {
	assert(a.m顶点);
	assert(a.m索引);
	a.m顶点 = nullptr;
	a.m索引 = nullptr;
}
C模型::~C模型() {
	delete[] m顶点;
	delete[] m索引;
}
C模型 &C模型::operator =(C模型 &&a) {
	assert(a.m顶点);
	assert(a.m索引);
	m顶点 = a.m顶点;
	m索引 = a.m索引;
	m顶点数 = a.m顶点数;
	m索引数 = a.m索引数;
	a.m顶点 = nullptr;
	a.m索引 = nullptr;
	return *this;
}
//=============================================================================
// 场景循环
//=============================================================================
C场景循环::C场景循环(float a移动, float a间隔, float a近, float a远) :
	m间隔(a间隔), m远(a远), m长(a远 - a近), m位置(数学::f求余<float>(a移动, a间隔)) {
}
void C场景循环::f循环控制_自增() {
	m位置 += m间隔;
}
bool C场景循环::f循环控制_i继续() const {
	return m位置 < m长;
}
float C场景循环::f循环控制_解引用() {
	return m远 - m位置;
}
//=============================================================================
// 画三维
//=============================================================================
C画三维::C画三维(C图形引擎 &a引擎, 三维::C三维 &a三维):
	m缓冲(a三维), m渲染控制(&a三维.fg渲染控制()) {
	m缓冲.m顶点缓冲.f初始化(sizeof(VS_3D), c顶点缓冲数量);
	m缓冲.m索引缓冲.f初始化(sizeof(uint16_t), c索引缓冲数量);
	m缓冲.mf刷新回调 = [this]() {
		f自动准备();
		f更新常量缓冲();
		m渲染控制->fs纹理(0, m纹理.Get());
	};
	三维::C顶点格式 v顶点格式;
	v顶点格式.f添加(三维::C顶点格式::e位置, 4);
	v顶点格式.f添加(三维::C顶点格式::e纹理, 2);
	三维::S图形管线参数 v图形管线;
	v图形管线.fs输入布局(v顶点格式);
	着色器::tp着色器 vs, ps;
	auto v着色器工厂 = a引擎.fg着色器工厂();
	v着色器工厂.f读取着色器(vs, C程序::f计算路径(L"~/shader/vs_stage0.cso").c_str());
	v着色器工厂.f读取着色器(ps, C程序::f计算路径(L"~/shader/ps_stage0.cso").c_str());
	v图形管线.fs顶点着色器(着色器::fc跨度(vs));
	v图形管线.fs像素着色器(着色器::fc跨度(ps));
	三维::C渲染状态 &v渲染状态 = a三维.fg渲染状态();
	v图形管线.fs光栅化(v渲染状态.m光栅化.m默认.Get());
	v图形管线.fs混合(v渲染状态.m混合.m开启透明.Get());
	v图形管线.fs深度模板(v渲染状态.m深度模板.m正常深度r.Get());
	a三维.f创建图形管线(m图形管线, v图形管线);
	m采样器 = v渲染状态.m采样器.m纹理.Get();
	//常量缓冲v
	const t向量2 v窗口大小 = a三维.fg窗口大小();
	数学::S投影 v投影{v窗口大小.x, v窗口大小.y, 数学::c半π<float>, 0.0001f, 10000};
	m常量v.m投影 = v投影.ft矩阵4r();
	三维::C缓冲工厂 &v缓冲工厂 = a三维.fg缓冲工厂();
	v缓冲工厂.f创建缓冲(m常量缓冲v, &m常量v, sizeof(m常量v), 三维::E缓冲::e常量);
	//常量缓冲p
	v缓冲工厂.f创建缓冲(m常量缓冲p, &m常量p, sizeof(m常量p), 三维::E缓冲::e常量);
}
void C画三维::f准备() {
	m渲染控制->fs图形管线(*m图形管线);
	m渲染控制->fs常量缓冲v(0, m常量缓冲v.Get());
	m渲染控制->fs常量缓冲p(0, m常量缓冲p.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->fs采样器(0, m采样器.Get());
}
void C画三维::f刷新() {
	m缓冲.f刷新();
}
void C画三维::f更新常量缓冲() {
	if (m更新v) {
		m渲染控制->f更新资源(m常量缓冲v.Get(), &m常量v);
		m更新v = false;
	}
	if (m更新p) {
		m渲染控制->f更新资源(m常量缓冲p.Get(), &m常量p);
		m更新p = false;
	}
}
void C画三维::fs世界矩阵(const 数学::S矩阵4 &a) {
	f刷新();
	m常量v.m世界 = a;
	m更新v = true;
}
void C画三维::fs视图矩阵(const 数学::S矩阵4 &a) {
	f刷新();
	m常量v.m视图 = a;
	m更新v = true;
}
void C画三维::fs物体矩阵(const 数学::S矩阵4 &a) {
	m物体矩阵 = a;
}
void C画三维::fs相机(const 数学::S相机 &a) {
	f刷新();
	m常量v.m视图 = a.ft矩阵4r();
	m更新v = true;
	m常量p.m眼睛位置 = a.m坐标;
	m更新p = true;
}
void C画三维::fs雾颜色(const 数学::S颜色 &a) {
	f刷新();
	m常量p.m雾颜色 = a;
	m更新p = true;
}
void C画三维::fs雾范围(float a开始, float a范围) {
	f刷新();
	m常量p.m雾开始 = a开始;
	m常量p.m雾范围 = a范围;
	m更新p = true;
}
void C画三维::fs纹理(tp纹理 a纹理) {
	if (m纹理 != a纹理) {
		m缓冲.f刷新();
		m纹理 = a纹理;
	}
}
void C画三维::f画模型(const C模型 &a) {
	assert(&a);
	VS_3D *vp顶点 = m顶点空间.f分配(4);
	size_t v顶点数量 = a.m顶点数;
	for (size_t i = 0; i != v顶点数量; ++i) {
		const S三维顶点 &v输入 = a.m顶点[i];
		VS_3D &v输出 = vp顶点[i];
		v输出.m坐标0 = v输入.m坐标.ft向量4(1) * m物体矩阵;
		v输出.m纹理 = v输入.m纹理;
	}
	m缓冲.f复制(vp顶点, v顶点数量 * sizeof(VS_3D), a.m索引, a.m索引数 * sizeof(uint16_t));
}
void C画三维::f画平面(int x, int y) {
	const uint16_t c平面索引[] = {
		0, 1, 2,
		1, 3, 2
	};
	VS_3D *vp顶点 = m顶点空间.f分配(4);
	const float v半x = (float)x / 2;
	const float v半y = (float)y / 2;
	const auto f赋值 = [&](int i, float px, float py, float u, float v) {
		VS_3D &v输出 = vp顶点[i];
		const 数学::S向量2 v坐标(px, py);
		v输出.m坐标0 = v坐标.ft向量4(0, 1) * m物体矩阵;
		v输出.m纹理.x = u;
		v输出.m纹理.y = v;
	};
	f赋值(0, -v半x, v半y, 0, 0);
	f赋值(1, v半x, v半y, 1, 0);
	f赋值(2, -v半x, -v半y, 0, 1);
	f赋值(3, v半x, -v半y, 1, 1);
	m缓冲.f复制(vp顶点, 4 * sizeof(VS_3D), c平面索引, sizeof(c平面索引));
}
}	//namespace 东方山寨