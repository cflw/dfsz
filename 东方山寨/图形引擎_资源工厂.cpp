#include "图形引擎_资源工厂.h"
#include "图形_三维.h"
#include "游戏.h"
#include "标识.h"
namespace 东方山寨 {
namespace 视窗 = cflw::视窗;
//=============================================================================
// 纹理工厂
//=============================================================================
C纹理工厂::~C纹理工厂() {
}
void C纹理工厂::f初始化(三维::C三维 &a三维, C属性数组<tp纹理> &aa纹理) {
	m工厂 = &a三维.fg纹理工厂();
	ma纹理 = &aa纹理;
}
tp纹理 C纹理工厂::f创建纹理(int a标识, const std::wstring &a文件) const {
	if (ma纹理->fi不存在(a标识)) {
		tp纹理 v纹理;
		HRESULT hr = m工厂->f从文件创建纹理(v纹理, a文件.c_str());
		if (FAILED(hr)) {
			__debugbreak();
			return nullptr;
		}
		ma纹理->f添加(a标识, v纹理);
		return v纹理;
	} else {
		return ma纹理->fg数据(a标识);
	}
}
tp纹理 C纹理工厂::f创建纹理(int a标识, const 纹理::I纹理 &a纹理) {
	if (ma纹理->fi不存在(a标识)) {
		try {
			三维::tp纹理2 v纹理2;
			HRESULT hr = m工厂->f从纹理对象创建纹理2(v纹理2, a纹理);
			视窗::f失败则抛出(hr);
			tp纹理 v纹理;
			hr = m工厂->f创建纹理资源视图(v纹理, v纹理2, a纹理.fg格式());
			视窗::f失败则抛出(hr);
			ma纹理->f添加(a标识, v纹理);
			return v纹理;
		} catch (HRESULT hr) {
			return nullptr;
		}
	} else {
		return ma纹理->fg数据(a标识);
	}
}
//=============================================================================
// 顶点工厂
//=============================================================================
C顶点工厂::C循环::C循环(C顶点工厂 &a工厂, int a列, int a行) :
	m参数(&a工厂.m参数), 
	m行(a行), m列(a列), i(0), j(0), 
	m参数备份(a工厂.m参数) {
}
void C顶点工厂::C循环::f循环控制_自增() {
	++i;
	if (i >= m列) {
		i -= m列;
		++j;
	}
	*m参数 = m参数备份;
}
bool C顶点工厂::C循环::f循环控制_i继续() {
	return j < m行;
}
int C顶点工厂::C循环::fg计数() const {
	return i + j * m列;
}
void C顶点工厂::C循环::f变换_平移(const t向量2 &a向量) {
	t向量2 &v映射点 = m参数->m映射点;
	v映射点.x += a向量.x * i;
	v映射点.y += a向量.y * j;
}
//参数
void C顶点工厂::S参数::fs顶点半尺寸(const t向量2 &a半尺寸) {
	m半尺寸 = a半尺寸;
}
void C顶点工厂::S参数::fs顶点尺寸(const t向量2 &a尺寸) {
	m半尺寸 = a尺寸 * 0.5f;
}
void C顶点工厂::S参数::fs纹理尺寸(const t向量2 &a尺寸) {
	m纹理尺寸 = a尺寸;
}
void C顶点工厂::S参数::fs映射点_中心(const t向量2 &a点) {
	m映射点 = a点;
	m映射点标记 = e中心;
}
void C顶点工厂::S参数::fs映射点_左上(const t向量2 &a点) {
	m映射点 = a点;
	m映射点标记 = e左上;
}
void C顶点工厂::S参数::fs映射尺寸偏移(float a偏移) {
	m映射尺寸偏移 = a偏移;
}
void C顶点工厂::S参数::fs顶点中心偏移(const t向量2 &a偏移) {
	m中心偏移 = a偏移;
	m标志[e中心偏移] = true;
}
void C顶点工厂::S参数::fs顶点缩放(const t向量2 &a) {
	m缩放 = a;
	m标志[e缩放] = true;
}
void C顶点工厂::S参数::fs顶点尺寸偏移(float a) {
	m顶点尺寸偏移 = a;
	m标志[e尺寸偏移] = true;
}
void C顶点工厂::S参数::f转换映射点() {
	switch (m映射点标记) {
	case e已转换:
		break;
	case e中心:
		m映射点标记 = e已转换;
		break;
	case e左上:
		m映射点 += m半尺寸;
		m映射点标记 = e已转换;
		break;
	}
}
void C顶点工厂::S参数::f计算_顶点半尺寸(float *a) const {
	a[0] = -m半尺寸.x;
	a[1] = m半尺寸.y;
	a[2] = m半尺寸.x;
	a[3] = -m半尺寸.y;
}
void C顶点工厂::S参数::f计算_纹理坐标(float *a) const {
	a[0] = (m映射点.x - m半尺寸.x - m映射尺寸偏移) / m纹理尺寸.x;
	a[1] = (m映射点.y - m半尺寸.y - m映射尺寸偏移) / m纹理尺寸.y;
	a[2] = (m映射点.x + m半尺寸.x + m映射尺寸偏移) / m纹理尺寸.x;
	a[3] = (m映射点.y + m半尺寸.y + m映射尺寸偏移) / m纹理尺寸.y;
}
void C顶点工厂::S参数::f计算_顶点尺寸偏移(float *a) const {
	a[0] -= m顶点尺寸偏移;
	a[1] += m顶点尺寸偏移;
	a[2] += m顶点尺寸偏移;
	a[3] -= m顶点尺寸偏移;
}
void C顶点工厂::S参数::f计算_顶点缩放(float *a) const {
	a[0] *= m缩放.x;
	a[1] *= m缩放.y;
	a[2] *= m缩放.x;
	a[3] *= m缩放.y;
}
void C顶点工厂::S参数::f计算_顶点中心偏移(float *a) const {
	a[0] += m中心偏移.x;
	a[1] += m中心偏移.y;
	a[2] += m中心偏移.x;
	a[3] += m中心偏移.y;
}
//顶点工厂
void C顶点工厂::f初始化(C属性数组<S顶点矩形> &a) {
	ma顶点矩形 = &a;
}
void C顶点工厂::f创建矩形(int a标识) {
	assert(ma顶点矩形->fi不存在(a标识));
	m参数.f转换映射点();
	S顶点矩形 v矩形;
	m参数.f计算_顶点半尺寸(v矩形.m坐标);
	m参数.f计算_纹理坐标(v矩形.m纹理);
	if (m参数.m标志[e尺寸偏移]) {
		m参数.f计算_顶点尺寸偏移(v矩形.m坐标);
	}
	if (m参数.m标志[e缩放]) {
		m参数.f计算_顶点缩放(v矩形.m坐标);
	}
	if (m参数.m标志[e中心偏移]) {
		m参数.f计算_顶点中心偏移(v矩形.m坐标);
	}
	ma顶点矩形->f添加(a标识, v矩形);
	m参数.m标志.reset();
}
void C顶点工厂::f复制矩形(int p新, int p旧) {
	ma顶点矩形->f引用(p新, p旧);
}
C顶点工厂::C循环 C顶点工厂::f循环(int a列, int a行) {
	m参数.f转换映射点();
	return C循环(*this, a列, a行);
}
void C顶点工厂::f自动化_完整纹理(int a标识, const t向量2 &a纹理尺寸) {
	m参数.fs顶点半尺寸(a纹理尺寸 / 2);
	m参数.fs纹理尺寸(a纹理尺寸);
	m参数.fs映射点_左上(t向量2());
	f创建矩形(a标识);
}
void C顶点工厂::f自动化_完整切割(int a标识, const t向量2 &a纹理尺寸, const t向量2 &a顶点尺寸) {
	const int v列 = (int)(a纹理尺寸.x / a顶点尺寸.x);
	const int v行 = (int)(a纹理尺寸.y / a顶点尺寸.y);
	m参数.fs顶点半尺寸(a顶点尺寸 / 2);
	m参数.fs纹理尺寸(a纹理尺寸);
	m参数.fs映射点_左上(t向量2());
	for (auto &v循环 : f循环(v列, v行)) {
		v循环.f变换_平移(a顶点尺寸);
		f创建矩形(计算::f标识(a标识, 0, v循环.fg计数()));
	}
}
void C顶点工厂::f自动化_完整切割(int a标识, const t向量2 &a纹理尺寸, int a列, int a行) {
	const t向量2 v顶点尺寸{a纹理尺寸.x / (float)a列, a纹理尺寸.y / (float)a行};
	m参数.fs顶点半尺寸(v顶点尺寸 / 2);
	m参数.fs纹理尺寸(a纹理尺寸);
	m参数.fs映射点_左上(t向量2());
	for (auto &v循环 : f循环(a列, a行)) {
		v循环.f变换_平移(v顶点尺寸);
		f创建矩形(计算::f标识(a标识, 0, v循环.fg计数()));
	}
}
//=============================================================================
// 模型工厂
//=============================================================================
void C模型工厂::S参数::fs顶点(const S三维顶点 *a指针, size_t a数量) {
	m顶点 = a指针;
	m顶点数 = a数量;
}
void C模型工厂::S参数::fs索引(const uint16_t *a指针, size_t a数量) {
	m索引 = a指针;
	m索引数 = a数量;
}
void C模型工厂::f初始化(C属性数组<C模型> &a) {
	ma模型 = &a;
}
void C模型工厂::f创建模型(int a标识) {
	ma模型->f构造(a标识, m参数.m顶点, m参数.m顶点数, m参数.m索引, m参数.m索引数);
}
}	//namespace 东方山寨