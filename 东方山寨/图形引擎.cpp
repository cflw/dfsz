#include <cflw视窗.h>
#include "游戏常量.h"
#include "边框常量.h"
#include "图形引擎.h"
#include "图形资源.h"
#include "图形资源工厂.h"
#include "图形_三维.h"
#include "图形_玩家成绩.h"
#include "图形_画图片.h"
#include "图形_画边框.h"
#include "图形_背景.h"
#include "图形管理.h"
#include "游戏.h"
#include "计算.h"
#include "玩家.h"
#include "程序.h"
namespace 东方山寨 {
namespace 视窗 = cflw::视窗;
//==============================================================================
// 图形引擎
//==============================================================================
C图形引擎::C图形引擎() {
}
C图形引擎::~C图形引擎() {
	if (m三维) {
		f销毁();
	}
}
void C图形引擎::f销毁() {
	//资源
	ma纹理.f清空();
	ma顶点矩形.f清空();
	ma模型.f清空();
	m图形管理.reset();
	//画图
	m画图片.reset();
	m画图形.reset();
	m画边框.reset();
	m画十字.reset();
	m画文本.reset();
	m画调试文本.reset();
	m画三维.reset();
	//工厂
	m纹理工厂.reset();
	m顶点工厂.reset();
	m模型工厂.reset();
	//图形核心
	m二维常量缓冲.Reset();
	m二维.reset();
	m三维.reset();
}
void C图形引擎::f初始化(HWND a窗口, float a缩放) {
	f初始化_三维(a窗口);
	f初始化_二维(a缩放);
	f初始化_其它();
}
void C图形引擎::f初始化_s渲染间隔(const int &a) {
	m渲染间隔 = &a;
}
void C图形引擎::f初始化_三维(HWND a窗口) {
	if (m三维 == nullptr) {
		m三维 = std::make_unique<三维::C三维>();
	}
	m三维->f初始化窗口(a窗口);
	m三维->f初始化设备();
	m三维->f初始化交换链();
	m三维->f初始化渲染目标视图();
	m三维->f初始化深度模板视图();
	m三维->fs视口();
}
void C图形引擎::f初始化_二维(float a缩放) {
	m缩放 = a缩放;
	if (m二维 == nullptr) {
		m二维 = std::make_unique<二维::C二维>();
		m二维->f初始化_工厂();
		m二维->f初始化_设备(m三维->fg基础设备().Get());
		m文本.f初始化();
	}
	m二维->f初始化_单个位图(m三维->fg交换链().Get(), m缩放);
}
void C图形引擎::f初始化_其它() {
	m图形管理 = std::make_unique<C图形管理>();
}
void C图形引擎::f渲染开始() {
	三维::C渲染控制 &v渲染控制 = m三维->fg渲染控制();
	二维::C渲染控制 &v渲染控制2 = m二维->fg渲染控制();
	v渲染控制.f清屏();
	v渲染控制2.f开始();
}
void C图形引擎::f渲染结束() {
	三维::C渲染控制 &v渲染控制 = m三维->fg渲染控制();
	二维::C渲染控制 &v渲染控制2 = m二维->fg渲染控制();
	v渲染控制2.f结束();
	v渲染控制.f显示();
}
//
void C图形引擎::fs图形管线(I图形管线 *a图形管线) {
	if (m图形管线 != a图形管线) {
		if (m图形管线) {
			m图形管线->f刷新();
		}
		if (a图形管线) {
			a图形管线->f准备();
		}
		m图形管线 = a图形管线;
	}
}
void C图形引擎::fs图形资源窗口大小() {
	const auto &[v标准宽, v标准高] = C程序::fg标准窗口大小();
	if (const float v比例 = v标准宽 / v标准高; v比例 == m比例) {
		return;
	} else {
		m比例 = v比例;
	}
	if (m二维常量缓冲) {
		const float c缓冲数据[4] = {
			v标准宽 * 0.5f, v标准高 * 0.5f,
			c框架范围x, c框架范围y
		};
		m三维->fg渲染控制().f更新资源(m二维常量缓冲.Get(), c缓冲数据);
	}
	if (m背景管理) {
		m背景管理->fs屏幕尺寸(v标准宽, v标准高);
	}
	if (m画边框) {
		m画边框->fs标准尺寸(v标准宽, v标准高);
	}
}
三维::C三维 &C图形引擎::fg三维() const {
	return *m三维;
}
二维::C二维 &C图形引擎::fg二维() const {
	return *m二维;
}
二维::C文本工厂 &C图形引擎::fg文本工厂() {
	return m文本;
}
二维::tp渲染目标 C图形引擎::fg二维渲染目标() const {
	return m二维->fg渲染目标();
}
二维::C坐标转换 &C图形引擎::fg二维坐标计算() const {
	return m二维->fg坐标计算();
}
C属性数组<S纹理> &C图形引擎::fg纹理() {
	return ma纹理;
}
C纹理工厂 &C图形引擎::fg纹理工厂() {
	if (m纹理工厂 == nullptr) {
		m纹理工厂 = std::make_unique<C纹理工厂>();
		m纹理工厂->f初始化(*m三维, ma纹理);
	}
	return *m纹理工厂;
}
C属性数组<S顶点矩形> &C图形引擎::fg顶点矩形() {
	return ma顶点矩形;
}
C顶点工厂 &C图形引擎::fg顶点工厂() {
	if (m顶点工厂 == nullptr) {
		m顶点工厂 = std::make_unique<C顶点工厂>();
		m顶点工厂->f初始化(ma顶点矩形);
	} else {
		m顶点工厂->m参数.f重置();
	}
	return *m顶点工厂;
}
C属性数组<C模型> &C图形引擎::fg模型() {
	return ma模型;
}
C模型工厂 &C图形引擎::fg模型工厂() {
	if (m模型工厂 == nullptr) {
		m模型工厂 = std::make_unique<C模型工厂>();
		m模型工厂->f初始化(ma模型);
	}
	return *m模型工厂;
}
ID3D11Buffer *C图形引擎::fg二维常量缓冲() {
	if (m二维常量缓冲 == nullptr) {
		const auto &[v标准宽, v标准高] = C程序::fg标准窗口大小();
		m比例 = v标准宽 / v标准高;
		const float c缓冲数据[4] = {
			v标准宽 * 0.5f, v标准高 * 0.5f,
			c框架范围x, c框架范围y
		};
		auto &v缓冲工厂 = m三维->fg缓冲工厂();
		v缓冲工厂.f创建缓冲(m二维常量缓冲, c缓冲数据, sizeof(c缓冲数据), 三维::e常量);
	}
	return m二维常量缓冲.Get();
}
着色器::C着色器工厂 &C图形引擎::fg着色器工厂() {
	if (m着色器工厂 == nullptr) {
		m着色器工厂 = std::make_unique<着色器::C着色器工厂>();
		m着色器工厂->f初始化();
	}
	return *m着色器工厂;
}
C图形管理 &C图形引擎::fg图形管理() {
	return *m图形管理;
}
C对象数组<I图形> &C图形引擎::fg图形数组() {
	return m图形管理->fg图形数组();
}
C缓冲数组<I图形缓冲> &C图形引擎::fg图形缓冲数组() {
	return m图形管理->fg图形缓冲数组();
}
C图形工厂 C图形引擎::f工厂_图形() {
	return m图形管理->f工厂_图形();
}
std::shared_ptr<C图形工厂> C图形引擎::f工厂_图形p() {
	return m图形管理->f工厂_图形p();
}
void C图形引擎::f画边框() {
	C画边框 &v画边框 = fg画边框();
	v画边框.f画框架();
}
C背景管理 &C图形引擎::fg背景管理() {
	if (m背景管理 == nullptr) {
		m背景管理 = std::make_unique<C背景管理>();
		const auto &[v标准宽, v标准高] = C程序::fg标准窗口大小();
		m背景管理->fs屏幕尺寸(v标准宽, v标准高);
	}
	return *m背景管理;
}
void C图形引擎::f画十字(const 数学::S向量2 &a坐标, const float &a半径) {
	if (m画十字 == nullptr) {
		m画十字 = fc画图形();
		m画十字->fs线条宽度(1);
		m画十字->fs颜色(t颜色(1, 1, 1, 1));
	}
	m画十字->f绘制线条(t线段(a坐标 + 数学::S向量2{a半径, 0}, a坐标 + 数学::S向量2{-a半径, 0}));
	m画十字->f绘制线条(t线段(a坐标 + 数学::S向量2{0, a半径}, a坐标 + 数学::S向量2{0, -a半径}));
}
void C图形引擎::f画调试信息(const std::wstring &a文本) {
	if (m画调试文本 == nullptr) {
		auto &v文本 = fg文本工厂();
		m画调试文本 = m二维->fc画文本();
		m画调试文本->m矩形 = m二维->fg坐标计算().f矩形_窗口();
		二维::S文本格式参数 v格式;
		v格式.fs字号(二维::ca中文字号[二维::e小四号]);
		v格式.fs水平对齐(二维::E文本水平对齐::e左);
		v格式.fs垂直对齐(二维::E文本垂直对齐::e上);
		m画调试文本->m格式 = v文本.fc文本格式(v格式);
	}
	m画调试文本->f绘制文本(a文本);
}
std::shared_ptr<二维::C画图形> C图形引擎::fc画图形() {
	return m二维->fc画图形();
}
二维::C画图形 &C图形引擎::fg画图形() {
	if (m画图形 == nullptr) {
		m画图形 = fc画图形();
	}
	return *m画图形;
}
std::unique_ptr<C画图片> C图形引擎::fc画图片() {
	return std::make_unique<C画图片>(fg画图片管线());
}
C画图片 &C图形引擎::fg画图片() {
	if (m画图片 == nullptr) {
		m画图片 = fc画图片();
	}
	return *m画图片;
}
C画图片管线 &C图形引擎::fg画图片管线() {	//废弃
	if (m画图片管线 == nullptr) {
		m画图片管线 = std::make_unique<C画图片管线>(*this, *m三维);
	}
	return *m画图片管线;
}
std::shared_ptr<二维::C画文本> C图形引擎::fc画文本() {
	return m二维->fc画文本();
}
二维::C画文本 &C图形引擎::fg画文本() {
	if (m画文本 == nullptr) {
		m画文本 = fc画文本();
	}
	return *m画文本;
}
C画三维 &C图形引擎::fg画三维() {
	if (m画三维 == nullptr) {
		m画三维 = std::make_unique<C画三维>(*this, *m三维);
	}
	return *m画三维;
}
C画玩家成绩 &C图形引擎::fg画玩家成绩() {
	if (m画玩家成绩 == nullptr) {
		m画玩家成绩 = std::make_unique<C画玩家成绩>(*m二维);
	}
	return *m画玩家成绩;
}
C画边框 &C图形引擎::fg画边框() {
	if (m画边框 == nullptr) {
		m画边框 = std::make_unique<C画边框>(*this, fg二维());
		const auto &[v标准宽, v标准高] = C程序::fg标准窗口大小();
		m画边框->fs标准尺寸(v标准宽, v标准高);
	}
	return *m画边框;
}
float C图形引擎::fg渲染秒() const {
	return c帧秒<float> * fg渲染帧();
}
float C图形引擎::fg渲染帧() const {
	return (float)*m渲染间隔;
}
//==============================================================================
// 图形管线
//==============================================================================
void I图形管线::f自动准备() {
	auto &v图形 = C游戏::fg图形();
	v图形.fs图形管线(this);
}
}	//namespace 东方山寨