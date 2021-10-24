#pragma once
#include <cflw工具_循环.h>
#include "数学包含.h"
#include "图形包含.h"
#include "图形资源.h"
#include "图形管线接口.h"
namespace 东方山寨 {
class C图形引擎;
using tp模型 = const class C模型*;
//定义
struct VS_3D {
	数学::S向量4 m坐标0;
	数学::S向量2 m纹理;
};
class C场景循环 : public 工具::循环::I循环<C场景循环> {
public:
	static constexpr float c近位置 = -20;
	static constexpr float c远位置 = 100;
	C场景循环(float 移动, float 间隔, float 近 = c近位置, float 远 = c远位置);
	void f循环控制_自增();
	bool f循环控制_i继续() const;
	float f循环控制_解引用();
	float m位置, m间隔, m远, m长;
};
class C画三维 : public I图形管线 {
public:
	static constexpr size_t c顶点缓冲数量 = 1000;
	static constexpr size_t c索引缓冲数量 = 2000;
	C画三维(C图形引擎 &, 三维::C三维 &);
	~C画三维() = default;
	void f准备() override;
	void f刷新() override;
	void f更新常量缓冲();
	void fs世界矩阵(const 数学::S矩阵4 &);
	void fs视图矩阵(const 数学::S矩阵4 &);
	void fs物体矩阵(const 数学::S矩阵4 &);
	void fs相机(const 数学::S相机 &);
	void fs雾颜色(const 数学::S颜色 &);
	void fs雾范围(float 开始, float 范围);
	void fs纹理(const S纹理 &);
	void f画模型(const C模型 &);
	void f画平面(int x, int y);
public:
	三维::C渲染控制 *m渲染控制;
	struct S常量v {
		数学::S矩阵4 m世界 = 数学::S矩阵4::c单位, m视图 = 数学::S矩阵4::c单位, m投影 = 数学::S矩阵4::c单位;
	} m常量v;
	struct S常量p {
		数学::S向量3 m眼睛位置 = 数学::S向量3::c零;
		int32_t x0;	//填充
		数学::S颜色 m雾颜色 = 数学::S颜色(0.0f, 0.0f, 0.0f, 1);
		float m雾开始 = 0, m雾范围 = 1000;
	} m常量p;
	数学::S矩阵4 m物体矩阵;
	三维::tp图形管线 m图形管线;
	三维::C自动缓冲 m缓冲;
	三维::tp纹理资源视图 m纹理;
	工具::C空间<VS_3D> m顶点空间;
	三维::tp缓冲 m常量缓冲v, m常量缓冲p;
	三维::tp采样器 m采样器;
	bool m更新v = false, m更新p = false;
};
}