#include <cflw视窗.h>
#include "游戏常量.h"
#include "图形引擎.h"
#include "图形引擎_资源工厂.h"
#include "图形_三维.h"
#include "图形_玩家成绩.h"
#include "图形管理.h"
#include "游戏.h"
#include "计算.h"
#include "玩家.h"
#include "程序.h"
namespace 东方山寨 {
namespace 视窗 = cflw::视窗;
//=============================================================================
// 图形引擎
//=============================================================================
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
C属性数组<tp纹理> &C图形引擎::fg纹理() {
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
		const float c缓存数据[4] = {c屏幕范围x, c屏幕范围y, c边框范围x, c边框范围y};
		auto &v缓冲工厂 = m三维->fg缓冲工厂();
		v缓冲工厂.f创建缓冲(m二维常量缓冲, c缓存数据, 16, 三维::e常量);
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
C图形工厂 C图形引擎::f工厂_图形() {
	return m图形管理->f工厂_图形();
}
std::shared_ptr<C图形工厂> C图形引擎::f工厂_图形p() {
	return m图形管理->f工厂_图形p();
}
void C图形引擎::f画边框() {
	if (m画边框 == nullptr) {
		m画边框 = fc画图形();
		m画边框->fs颜色(t颜色(1, 1, 1, 0.5f));
	}
	m画边框->f填充矩形(t矩形::fc左上右下(c边框范围x, c外边框范围y, c外边框范围x, -c外边框范围y));	//右
	m画边框->f填充矩形(t矩形::fc左上右下(-c外边框范围x, c外边框范围y, -c边框范围x, -c外边框范围y));	//左
	m画边框->f填充矩形(t矩形::fc左上右下(c边框范围x, c外边框范围y, -c边框范围x, c边框范围y));	//上
	m画边框->f填充矩形(t矩形::fc左上右下(c边框范围x, -c边框范围y, -c边框范围x, -c外边框范围y));	//下
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
C画图片 &C图形引擎::fg画图片() {
	if (m画图片 == nullptr) {
		m画图片 = std::make_unique<C画图片>(*this, *m三维);
	}
	return *m画图片;
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
C画背景 &C图形引擎::fg画背景() {
	if (m画背景 == nullptr) {
		m画背景 = std::make_unique<C画背景>(fg画图片());
	}
	return *m画背景;
}
float C图形引擎::fg渲染秒() const {
	return (float)c帧秒 * fg渲染帧();
}
float C图形引擎::fg渲染帧() const {
	return (float)*m渲染间隔;
}
//=============================================================================
// 图形管线
//=============================================================================
void I图形管线::f自动准备() {
	auto &v图形 = C游戏::fg图形();
	v图形.fs图形管线(this);
}
//=============================================================================
// 二维顶点,一个纹理的其中一个片段
//=============================================================================
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
C画图片::C画图片(C图形引擎 &a引擎, 三维::C三维 &a三维) : m渲染控制{a三维.fg渲染控制()}, m渲染状态{a三维.fg渲染状态()}, m缓存{a三维} {
	三维::C顶点格式 v顶点格式;
	v顶点格式.f添加(三维::C顶点格式::e位置, 2);
	v顶点格式.f添加(三维::C顶点格式::e纹理, 2);
	v顶点格式.f添加("ALPHA", 1);
	auto &v着色器工厂 = a引擎.fg着色器工厂();
	着色器::tp着色器 vs, ps;
	v着色器工厂.f读取着色器(vs, C程序::f计算路径(L"~/shader/vs_image0.cso").c_str());
	v着色器工厂.f读取着色器(ps, C程序::f计算路径(L"~/shader/ps_image0.cso").c_str());
	const auto v顶点跨度 = 着色器::fc跨度(vs);
	a三维.f创建顶点着色器(m顶点着色器, v顶点跨度);
	a三维.f创建输入布局(m输入布局, v顶点跨度, v顶点格式);
	a三维.f创建像素着色器(m像素着色器, 着色器::fc跨度(ps));
	m缓存.m顶点缓冲.f初始化(sizeof(S顶点顶点), c顶点缓存数量);
	m缓存.m索引缓冲.f初始化(sizeof(WORD), c索引缓存数量);
	m缓存.mf刷新回调 = [this]() {
		f自动准备();
	};
	m常量缓冲 = a引擎.fg二维常量缓冲();
}
C画图片::~C画图片() {
}
void C画图片::f准备() {
	m渲染控制.fs顶点着色器(m顶点着色器.Get());
	m渲染控制.fs像素着色器(m像素着色器.Get());
	m渲染控制.fs输入布局(m输入布局.Get());
	m渲染控制.fs图元拓扑(三维::E图元拓扑::e列表三角形);
	m渲染控制.fs采样器(0, m渲染状态.m采样器.m纹理.Get());
	m渲染控制.fs光栅化(m渲染状态.m光栅化.m显示隐藏面.Get());
	m渲染控制.fs混合(m渲染状态.m混合.m开启透明.Get());
	m渲染控制.fs深度模板(m渲染状态.m深度模板.m总是覆盖.Get());
	m渲染控制.fs常量缓冲(0, m常量缓冲.Get());
}
void C画图片::f刷新() {
	m缓存.f刷新();
}
void C画图片::fs坐标(const t向量2 &a坐标) {
	m坐标 = a坐标;
}
void C画图片::fs透明度(float a透明度) {
	m透明度 = a透明度;
}
void C画图片::fs纹理(tp纹理 a纹理) {
	if (m纹理 != a纹理) {
		f刷新();
		m纹理 = a纹理;
	}
}
void C画图片::f变换_重置() {
	m矩阵 = 数学::S矩阵4::fc单位();
}
void C画图片::f变换_旋转(const t向量3 &a旋转) {
	if (a旋转.z != 0) {
		m矩阵 *= 数学::S矩阵4::fc绕z旋转(a旋转.z);
	}
	if (a旋转.x != 0) {
		m矩阵 *= 数学::S矩阵4::fc绕x旋转(a旋转.y);
	}
	if (a旋转.y != 0) {
		m矩阵 *= 数学::S矩阵4::fc绕y旋转(a旋转.y);
	}
}
void C画图片::f变换_旋转(float a旋转) {
	m矩阵 *= 数学::S矩阵4::fc绕z旋转(a旋转);
}
void C画图片::f变换_翻转(float x, float y) {
	if (x != 0) {
		m矩阵 *= 数学::S矩阵4::fc绕x旋转(y);
	}
	if (y != 0) {
		m矩阵 *= 数学::S矩阵4::fc绕y旋转(y);
	}
}
void C画图片::f变换_缩放(float x, float y) {
	m矩阵 *= 数学::S矩阵4::fc缩放(x, y, 1);
}
void C画图片::f画图片(const S顶点矩形 &a矩形) {
	f自动准备();
	//顶点
	S顶点顶点 v顶点[4];
	auto f赋顶点 = [&](S顶点顶点 &a顶点, int x, int y) {
		//坐标
		数学::S向量4 v{0, 0, 0, 1};
		v.x += a矩形.m坐标[x];
		v.y += a矩形.m坐标[y];
		v = v * m矩阵;
		a顶点.m坐标.x = v.x + m坐标.x;
		a顶点.m坐标.y = v.y + m坐标.y;
		//纹理
		a顶点.m纹理.x = a矩形.m纹理[x];
		a顶点.m纹理.y = a矩形.m纹理[y];
		//透明度
		a顶点.m透明度 = m透明度;
	};
	f赋顶点(v顶点[0], 0, 1);	//左上
	f赋顶点(v顶点[1], 2, 1);	//右上
	f赋顶点(v顶点[2], 0, 3);	//左下
	f赋顶点(v顶点[3], 2, 3);	//右下
	//索引
	WORD v索引[] = {
		0, 1, 2,
		1, 3, 2
	};
	//复制
	m渲染控制.fs纹理(0, m纹理.Get());
	m缓存.f复制(v顶点, sizeof(v顶点), v索引, sizeof(v索引));
}
//画背景
C画背景::C画背景(C画图片 &a画图片):
	m画图片(&a画图片) {
}
void C画背景::f计算() {
	for (auto &v背景 : ma背景) {
		v背景.m透明度 += c帧秒;
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
}	//namespace 东方山寨