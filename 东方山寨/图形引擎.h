#pragma once
#include <map>
#include <vector>
#include <cflw视窗.h>
#include "图形包含.h"
#include "数学包含.h"
#include "基础_对象数组.h"
#include "基础_属性数组.h"
#include "基础_缓冲数组.h"
#include "基础_扩展数组.h"
#include "游戏常量.h"
#include "图形资源.h"
#include "图形管线接口.h"
namespace 东方山寨 {
//接口
class I图形;
class I图形缓冲;
class I图形管线;
//资源
struct S顶点矩形;
struct S纹理;
struct S三维顶点;
class C模型;
//工厂
class C纹理工厂;
class C顶点矩形工厂;
class C模型工厂;
//管理
class C图形管理;
class C背景管理;
//绘制
class C画图片;
class C画三维;
class C画玩家成绩;
using t画图片 = class C画图片;
class C图形层;
class C图形工厂;
class C画边框;
//图形管线
constexpr int c图形管线标识 = 1109021423;	//0x421A52EF
enum class E图形管线 {
	e图片 = c图形管线标识,
	e子弹正常,
	e子弹高光,
	e子弹线条,
	e三维场景,
	e静态立绘,
};
//==============================================================================
// 图形引擎
//==============================================================================
class C图形引擎 {
public:
	C图形引擎();
	~C图形引擎();
	void f初始化(HWND, float 缩放);	//顺序:三维->二维->其它
	void f初始化_s渲染间隔(const int &);
	void f初始化_三维(HWND);
	void f初始化_二维(float 缩放);
	void f初始化_其它();
	void f销毁();
	void f渲染开始();
	void f渲染结束();
	//重要对像
	三维::C三维 &fg三维() const;
	二维::C二维 &fg二维() const;
	二维::C文本工厂 &fg文本工厂();
	二维::tp渲染目标 fg二维渲染目标() const;
	二维::C坐标转换 &fg二维坐标计算() const;
	//函数
	void fs图形管线(I图形管线 *);
	void fs图形资源窗口大小();	//窗口大小改变之后调用
	//资源&工厂
	C属性数组<S纹理> &fg纹理();
	C纹理工厂 &fg纹理工厂();
	C属性数组<S顶点矩形> &fg顶点矩形();
	C顶点矩形工厂 &fg顶点工厂();
	C属性数组<C模型> &fg模型();
	C模型工厂 &fg模型工厂();
	ID3D11Buffer *fg二维常量缓冲();
	着色器::C着色器工厂 &fg着色器工厂();
	C图形管理 &fg图形管理();
	C对象数组<I图形> &fg图形数组();
	C缓冲数组<I图形缓冲> &fg图形缓冲数组();
	C图形工厂 f工厂_图形();
	std::shared_ptr<C图形工厂> f工厂_图形p();
	C背景管理 &fg背景管理();
	C扩展数组<I图形管线> &fg图形管线数组();
	template<typename t图形管线> t图形管线 *fg图形管线(E图形管线) const;
	//画预设图形
	void f画边框();
	void f画十字(const t向量2 &, const float &半径 = 16);
	void f画调试信息(const std::wstring &);
	//画对象
	std::shared_ptr<二维::C画图形> fc画图形();
	二维::C画图形 &fg画图形();
	std::shared_ptr<二维::C画文本> fc画文本();
	二维::C画文本 &fg画文本();
	std::unique_ptr<C画图片> fc画图片();
	C画图片 &fg画图片();
	C画三维 &fg画三维();
	C画玩家成绩 &fg画玩家成绩();
	C画边框 &fg画边框();
	//属性
	float fg渲染秒() const;	//游戏速度无关
	float fg渲染帧() const;
public:
	//管理
	std::unique_ptr<三维::C三维> m三维;
	std::unique_ptr<二维::C二维> m二维;
	二维::C文本工厂 m文本;
	三维::tp缓冲 m二维常量缓冲;	//二维
	I图形管线 *m图形管线 = nullptr;	//当前设置的图形管线
	float m缩放 = 1;
	float m比例 = 4.f / 3.f;
	const int *m渲染间隔 = nullptr;
	//资源
	C属性数组<S纹理> ma纹理;
	std::unique_ptr<C纹理工厂> m纹理工厂;
	C属性数组<S顶点矩形> ma顶点矩形;
	std::unique_ptr<C顶点矩形工厂> m顶点工厂;
	C属性数组<C模型> ma模型;
	std::unique_ptr<C模型工厂> m模型工厂;
	std::unique_ptr<着色器::C着色器工厂> m着色器工厂;
	std::unique_ptr<C图形管理> m图形管理;
	std::unique_ptr<C背景管理> m背景管理;
	C扩展数组<I图形管线> ma图形管线;
	//绘制
	std::shared_ptr<二维::C画图形> m画图形;
	std::shared_ptr<二维::C画图形> m画十字;
	std::shared_ptr<二维::C画文本> m画文本;
	std::shared_ptr<二维::C画文本> m画调试文本;
	std::unique_ptr<C画图片> m画图片;
	std::unique_ptr<C画三维> m画三维;
	std::unique_ptr<C画玩家成绩> m画玩家成绩;
	std::unique_ptr<C画边框> m画边框;
};
template<typename t图形管线>
t图形管线 *C图形引擎::fg图形管线(E图形管线 a) const {
	return ma图形管线.fg扩展<t图形管线>((int)a);
}
}	//namespace 东方山寨