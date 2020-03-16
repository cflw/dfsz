#include "图形_背景.h"
#include "图形_画图片.h"
#include "图形引擎_资源工厂.h"
namespace 东方山寨 {
//==============================================================================
// 画背景
//==============================================================================
C画背景::C画背景(C画图片 &a画图片) :
	m画图片(&a画图片) {
}
void C画背景::f计算() {
	for (auto &v背景 : ma背景) {
		v背景.m透明度 += c帧秒<float>;
		if (v背景.m透明度 > m透明度) {
			v背景.m透明度 = m透明度;
		}
	}
	if (ma背景.size() >= 2 && ma背景[1].m透明度 >= 1) {
		ma背景.pop_front();
	}
}
void C画背景::f显示() const {
	m画图片->fs坐标(t向量2::c零);
	for (const auto &v背景 : ma背景) {
		m画图片->fs纹理(v背景.m纹理);
		m画图片->fs透明度(v背景.m透明度);
		m画图片->f画图片(v背景.m顶点矩形);
	}
}
void C画背景::fs屏幕尺寸(float x, float y) {
	m屏幕尺寸.x = x;
	m屏幕尺寸.y = y;
}
void C画背景::fs透明度(float a) {
	m透明度 = a;
}
void C画背景::f切换背景(tp纹理 a纹理, const t向量2 &a纹理尺寸) {
	S背景 v背景;
	v背景.m纹理 = a纹理;
	v背景.m纹理尺寸 = a纹理尺寸;
	v背景.m顶点矩形 = f计算顶点矩形(a纹理尺寸);
	ma背景.push_back(v背景);
}
S顶点矩形 C画背景::f计算顶点矩形(const t向量2 &a纹理尺寸) {
	C顶点工厂::S参数 v顶点参数;
	v顶点参数.fs顶点尺寸(m屏幕尺寸);
	//纹理
	const float v屏幕比 = m屏幕尺寸.fg横纵比();
	const float v纹理比 = a纹理尺寸.fg横纵比();
	if (v屏幕比 == v纹理比) {
		v顶点参数.fs纹理尺寸(m屏幕尺寸);
	} else if (v屏幕比 > v纹理比) {
		const float v纹理缩放 = m屏幕尺寸.x / a纹理尺寸.x;
		v顶点参数.fs纹理尺寸(a纹理尺寸 * v纹理缩放);
	} else {	//v屏幕比 < v纹理比
		const float v纹理缩放 = m屏幕尺寸.y / a纹理尺寸.y;
		v顶点参数.fs纹理尺寸(a纹理尺寸 * v纹理缩放);
	}
	v顶点参数.fs映射点_左上(t向量2::c零);
	v顶点参数.f转换映射点();
	return C顶点工厂::f创建矩形(v顶点参数);
}
const C画背景::S背景 &C画背景::fg当前背景() const {
	return ma背景.back();
}
}