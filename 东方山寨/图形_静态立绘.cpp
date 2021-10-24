﻿#include <ranges>
#include "图形_静态立绘.h"
#include "程序.h"
#include "游戏.h"
#include "图形工厂.h"
namespace 东方山寨 {
//==============================================================================
// 静态立绘图形管线
//==============================================================================
std::unique_ptr<C静态立绘管线> C静态立绘管线::g这;
C静态立绘管线::C静态立绘管线(C图形引擎 &a引擎, 三维::C三维 &a三维):
	C画图片管线(a引擎, a三维) {
	三维::S深度模板参数 v深度模板参数 = m渲染状态->m深度模板参数.m模板比较;
	v深度模板参数.fs深度部分(m渲染状态->m深度模板参数.m总是覆盖);
	v深度模板参数.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	v深度模板参数.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	v深度模板参数.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER;
	a三维.fg设备()->CreateDepthStencilState(&v深度模板参数, &m深度模板);
}
C静态立绘管线::~C静态立绘管线() {
}
C静态立绘管线 &C静态立绘管线::fg这() {
	if (g这 == nullptr) {
		g这 = std::make_unique<C静态立绘管线>(C程序::fg图形(), C程序::fg图形().fg三维());
	}
	return *g这;
}
void C静态立绘管线::f准备() {
	m渲染控制->fs顶点着色器(m顶点着色器.Get());
	m渲染控制->fs像素着色器(m像素着色器.Get());
	m渲染控制->fs输入布局(m输入布局.Get());
	m渲染控制->fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制->fs采样器(0, m渲染状态->m采样器.m纹理.Get());
	m渲染控制->fs光栅化(m渲染状态->m光栅化.m显示隐藏面.Get());
	m渲染控制->fs混合(m渲染状态->m混合.m开启透明.Get());
	//m渲染控制->fs深度模板(m渲染状态->m深度模板.m总是覆盖.Get());
	m渲染控制->fs深度模板(m深度模板.Get());
	m渲染控制->fs模板参考值(0x01);
	m渲染控制->fs常量缓冲(0, m常量缓冲.Get());
}
void C静态立绘管线::f刷新() {
	m缓冲.f刷新();
}
//==============================================================================
// 静态立绘图形缓冲
//==============================================================================
void C静态对话立绘::C图形缓冲::f显示() const {
	for (const S静态立绘组件 *v组件 : ma组件 | std::views::reverse) {
		f画组件(*v组件);
	}
}
void C静态对话立绘::C图形缓冲::f画组件(const S静态立绘组件 &a组件) const {
	//复制自 C画图片::f画图片,以后重构
	//顶点
	VS_IMAGE v顶点[4];
	const S顶点矩形 &v矩形 = *a组件.m矩形;
	auto f赋顶点 = [&](VS_IMAGE &a顶点, int x, int y) {
		//坐标
		数学::S向量4 v{0, 0, 0, 1};
		v.x += v矩形.m坐标[x];
		v.y += v矩形.m坐标[y];
		a顶点.m坐标.x = v.x + m坐标.x;
		a顶点.m坐标.y = v.y + m坐标.y;
		//纹理
		a顶点.m纹理.x = v矩形.m纹理[x];
		a顶点.m纹理.y = v矩形.m纹理[y];
		//透明度
		a顶点.m透明度 = m透明度;
	};
	f赋顶点(v顶点[0], 0, 1);	//左上
	f赋顶点(v顶点[1], 2, 1);	//右上
	f赋顶点(v顶点[2], 0, 3);	//左下
	f赋顶点(v顶点[3], 2, 3);	//右下
	//索引
	static const WORD v索引[] = {
		0, 1, 2,
		1, 3, 2
	};
	//复制
	const S纹理 &v纹理 = *a组件.m纹理;
	m图形管线->f自动准备();
	m图形管线->fs纹理(v纹理.m纹理);
	m图形管线->f绘制(v顶点, v索引);
}
//==============================================================================
// 静态立绘图形对象
//==============================================================================
C静态对话立绘::C静态对话立绘(const S静态立绘属性 &a属性):
	m属性(&a属性) {
}
void C静态对话立绘::f接口_初始化(const S图形参数 &a参数) {
	C图形缓冲 *const v缓冲 = (C图形缓冲 *)m图形缓冲;
	v缓冲->m图形管线 = &C静态立绘管线::fg这();
}
void C静态对话立绘::f接口_更新() {
	const float v渲染秒 = C游戏::fg图形().fg渲染秒();
	C图形缓冲 *const v缓冲 = (C图形缓冲 *)m图形缓冲;
	const S静态立绘属性::S表情映射 &v表情映射 = m属性->ma表情映射.at(m表情);
	const size_t v数量 = std::size(v表情映射.ma组件);
	for (size_t i = 0; i != v数量; ++i) {
		v缓冲->ma组件[i] = v表情映射.ma组件[i].m指针;
	}
	v缓冲->m透明度 = 数学::f线性渐变<float>(v缓冲->m透明度, 0.5f, v渲染秒);
}
void C静态对话立绘::f接口_改变表情(E立绘表情 a表情) {
	m表情 = a表情;
}
//==============================================================================
// 静态立绘图形建造机
//==============================================================================
C静态立绘建造机::C静态立绘建造机(const S静态立绘属性 &a属性):
	m属性(&a属性) {
}
void C静态立绘建造机::f接口_建造图形(t过程 &a过程) const {
	a过程.f建造图形<C静态对话立绘>(*m属性);
}
//==============================================================================
// 静态立绘资源管理
//==============================================================================
C静态立绘管理::C静态立绘管理() {
}
C静态立绘管理::~C静态立绘管理() {
}
void C静态立绘管理::f编译(const C属性数组<S纹理> &aa纹理, const C属性数组<S顶点矩形> &aa矩形) {
	for (auto &v组件 : ma组件.ma数据) {
		aa纹理.f编译(v组件.m纹理);
		aa矩形.f编译(v组件.m矩形);
	}
	for (auto &v属性 : ma属性.ma数据) {
		for (auto &[_, v表情] : v属性.ma表情映射) {
			for (auto &v组件 : v表情.ma组件) {
				ma组件.f编译(v组件);
			}
		}
	}
}
}	//namespace 东方山寨