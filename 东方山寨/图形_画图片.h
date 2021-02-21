#pragma once
#include "图形包含.h"
#include "数学包含.h"
#include "基础.h"
namespace 东方山寨 {
class C图形引擎;
struct S纹理;
struct S顶点矩形;
//==============================================================================
// 画图片管线
//==============================================================================
//顶点格式
struct VS_IMAGE {
	t向量2 m坐标;
	t向量2 m纹理;
	float m透明度 = 0;
};
//画图片管线,只能由 C画图片 调用
class C画图片管线 : public I图形管线 {
public:
	static const unsigned int c顶点缓存数量 = 1000;
	static const unsigned int c索引缓存数量 = c顶点缓存数量 * 2;
	C画图片管线(C图形引擎 &, 三维::C三维 &);
	~C画图片管线();
	void f准备() override;
	void f刷新() override;
	void f绘制(const VS_IMAGE *顶点, const WORD *索引);
	void fs纹理(const 三维::tp纹理资源视图 &);
private:
	三维::C渲染控制 &m渲染控制;
	三维::C渲染状态 &m渲染状态;
	三维::C自动缓冲 m缓冲;
	三维::tp顶点着色器 m顶点着色器;
	三维::tp像素着色器 m像素着色器;
	三维::tp输入布局 m输入布局;
	三维::tp纹理资源视图 m纹理;
	三维::tp缓冲 m常量缓冲;
};
//==============================================================================
// 画图片
//==============================================================================
class C画图片 {
public:
	C画图片(C画图片管线 &);
	void fs坐标(const t向量2 &);
	void fs透明度(float);
	void fs纹理(const S纹理 &);
	void f变换_重置();
	void f变换_旋转(const t向量3 &xyz);
	void f变换_旋转(float z);
	void f变换_翻转(float x, float y);
	void f变换_缩放(float x, float y);
	void f画图片(const S顶点矩形 &);
private:
	C画图片管线 *m图形管线 = nullptr;
	const S纹理 *m纹理 = nullptr;
	t向量2 m坐标;
	t矩阵4 m矩阵;
	float m透明度 = 0;
};
}	//namespace 东方山寨