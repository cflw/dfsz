#include "图形资源.h"
#include "图形资源工厂.h"
namespace 东方山寨 {
//==============================================================================
// 二维顶点,一个纹理的其中一个片段
//==============================================================================
//构造
S顶点矩形 S顶点矩形::fc纹理切片(const t向量2 &a纹理尺寸, float a左, float a上, float a右, float a下) {
	S顶点矩形 v;
	const float v半尺寸x = 数学::f半距离(a左, a右);
	const float v半尺寸y = 数学::f半距离(a下, a上);
	v.m坐标[0] = -v半尺寸x;
	v.m坐标[1] = v半尺寸y;
	v.m坐标[2] = v半尺寸x;
	v.m坐标[3] = -v半尺寸y;
	v.m纹理[0] = a左 / a纹理尺寸.x;
	v.m纹理[1] = a上 / a纹理尺寸.y;
	v.m纹理[2] = a右 / a纹理尺寸.x;
	v.m纹理[3] = a下 / a纹理尺寸.y;
	return v;
}
S顶点矩形 S顶点矩形::fc填充背景(const t向量2 &a屏幕尺寸, const t向量2 &a纹理尺寸) {
	C顶点矩形工厂::S参数 v顶点参数;
	v顶点参数.fs裁剪尺寸(a屏幕尺寸);
	//纹理
	const float v屏幕比 = a屏幕尺寸.fg横纵比();
	const float v纹理比 = a纹理尺寸.fg横纵比();
	if (v屏幕比 == v纹理比) {
		v顶点参数.fs纹理尺寸(a屏幕尺寸);
	} else if (v屏幕比 > v纹理比) {
		const float v纹理缩放 = a屏幕尺寸.x / a纹理尺寸.x;
		v顶点参数.fs纹理尺寸(a纹理尺寸 * v纹理缩放);
	} else {	//v屏幕比 < v纹理比
		const float v纹理缩放 = a屏幕尺寸.y / a纹理尺寸.y;
		v顶点参数.fs纹理尺寸(a纹理尺寸 * v纹理缩放);
	}
	v顶点参数.fs裁剪坐标(t向量2::c零);
	return C顶点矩形工厂::fc顶点矩形(v顶点参数);
}
S顶点矩形 S顶点矩形::fc适应背景(const t向量2 &a屏幕尺寸, const t向量2 &a纹理尺寸) {
	//未实现
	return fc拉伸背景(a屏幕尺寸, a纹理尺寸);
}
S顶点矩形 S顶点矩形::fc拉伸背景(const t向量2 &a屏幕尺寸, const t向量2 &a纹理尺寸) {
	S顶点矩形 v;
	const float v屏幕半尺寸x = a屏幕尺寸.x * 0.5f;
	const float v屏幕半尺寸y = a屏幕尺寸.y * 0.5f;
	v.m坐标[0] = -v屏幕半尺寸x;
	v.m坐标[1] = v屏幕半尺寸y;
	v.m坐标[2] = v屏幕半尺寸x;
	v.m坐标[3] = -v屏幕半尺寸y;
	v.m纹理[0] = 0;
	v.m纹理[1] = 0;
	v.m纹理[2] = 1;
	v.m纹理[3] = 1;
	return v;
}
S顶点矩形 S顶点矩形::fc平铺背景(const t向量2 &a屏幕尺寸, const t向量2 &a纹理尺寸, float a纹理缩放) {
	S顶点矩形 v;
	const float v屏幕半尺寸x = a屏幕尺寸.x * 0.5f;
	const float v屏幕半尺寸y = a屏幕尺寸.y * 0.5f;
	v.m坐标[0] = -v屏幕半尺寸x;
	v.m坐标[1] = v屏幕半尺寸y;
	v.m坐标[2] = v屏幕半尺寸x;
	v.m坐标[3] = -v屏幕半尺寸y;
	const float v纹理倍数x = a屏幕尺寸.x / a纹理尺寸.x / a纹理缩放;
	const float v纹理倍数y = a屏幕尺寸.y / a纹理尺寸.y / a纹理缩放;
	v.m纹理[0] = 0;
	v.m纹理[1] = 0;
	v.m纹理[2] = v纹理倍数x;
	v.m纹理[3] = v纹理倍数y;
	return v;
}
S顶点矩形 S顶点矩形::fc居中背景(const t向量2 &a屏幕尺寸, const t向量2 &a纹理尺寸, float a纹理缩放) {
	S顶点矩形 v;
	const float v纹理半尺寸x = a纹理尺寸.x * 0.5f;
	const float v纹理半尺寸y = a纹理尺寸.y * 0.5f;
	v.m坐标[0] = -v纹理半尺寸x;
	v.m坐标[1] = v纹理半尺寸y;
	v.m坐标[2] = v纹理半尺寸x;
	v.m坐标[3] = -v纹理半尺寸y;
	const float v纹理倍数x = a屏幕尺寸.x / a纹理尺寸.x / a纹理缩放;
	const float v纹理倍数y = a屏幕尺寸.y / a纹理尺寸.y / a纹理缩放;
	const float v纹理半倍数x = v纹理倍数x * 0.5f;
	const float v纹理半倍数y = v纹理倍数y * 0.5f;
	v.m纹理[0] = -v纹理半倍数x + 0.5f;
	v.m纹理[1] = -v纹理半倍数y + 0.5f;
	v.m纹理[2] = v纹理半倍数x + 0.5f;
	v.m纹理[3] = v纹理半倍数y + 0.5f;
	return v;
}
//属性
float S顶点矩形::fg坐标x(float a插值) const {
	return 数学::f插值<float>(m坐标[e左], m坐标[e右], a插值);
}
float S顶点矩形::fg坐标y(float a插值) const {
	return 数学::f插值<float>(m坐标[e上], m坐标[e下], a插值);
}
float S顶点矩形::fg纹理x(float a插值) const {
	return 数学::f插值<float>(m纹理[e左], m纹理[e右], a插值);
}
float S顶点矩形::fg纹理y(float a插值) const {
	return 数学::f插值<float>(m纹理[e上], m纹理[e下], a插值);
}
float S顶点矩形::fg宽() const {
	return m坐标[e右] - m坐标[e左];
}
float S顶点矩形::fg高() const {
	return m坐标[e上] - m坐标[e下];
}
//==============================================================================
// 模型
//==============================================================================
C模型::C模型(const S三维顶点 *a顶点, size_t a顶点数, const uint16_t *a索引, size_t a索引数) :
	m顶点(new S三维顶点[a顶点数]), 
	m索引(new uint16_t[a索引数]), 
	m顶点数(a顶点数), 
	m索引数(a索引数) {
	memcpy(m顶点, a顶点, sizeof(S三维顶点) * a顶点数);
	memcpy(m索引, a索引, sizeof(uint16_t) * a索引数);
}
C模型::C模型(C模型 &&a) :
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
}	//namespace 东方山寨