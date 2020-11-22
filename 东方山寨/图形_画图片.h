#pragma once
#include "图形包含.h"
#include "数学包含.h"
#include "基础.h"
namespace 东方山寨 {
class C图形引擎;
struct S顶点矩形;
//==============================================================================
// 画图片
//==============================================================================
class C画图片 : public I图形管线 {
public:
	static const unsigned int c顶点缓存数量 = 1000;
	static const unsigned int c索引缓存数量 = c顶点缓存数量 * 2;
	C画图片(C图形引擎 &, 三维::C三维 &);
	~C画图片();
	void f准备() override;
	void f刷新() override;
	void fs坐标(const t向量2 &);
	void fs透明度(float);
	void fs纹理(三维::tp纹理);
	void f变换_重置();
	void f变换_旋转(const t向量3 &xyz);
	void f变换_旋转(float z);
	void f变换_翻转(float x, float y);
	void f变换_缩放(float x, float y);
	void f画图片(const S顶点矩形 &);
public:
	//绘制资源
	三维::C渲染控制 &m渲染控制;
	三维::C渲染状态 &m渲染状态;
	t自动缓冲 m缓存;
	三维::tp顶点着色器 m顶点着色器;
	三维::tp像素着色器 m像素着色器;
	三维::tp输入布局 m输入布局;
	//绘制变量
	t向量2 m坐标;
	t矩阵4 m矩阵;
	float m透明度;
	三维::tp纹理 m纹理;
	三维::tp缓冲 m常量缓冲;
};
}	//namespace 东方山寨