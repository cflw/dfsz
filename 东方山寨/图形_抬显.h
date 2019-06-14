#pragma once
#include "图形包含.h"
#include "图形基础.h"
#include "游戏常量.h"
namespace 东方山寨 {
class C敌机;
struct S关卡标题;
//=============================================================================
// 标题
//=============================================================================
class C关卡标题 : public I粒子 {
public:
	static constexpr float c大字号 = 二维::ca中文字号[二维::e初号];
	static constexpr float c小字号 = 二维::ca中文字号[二维::e五号];
	C关卡标题(const S关卡标题 &);
	void f接口_计算() override;
	void f接口_显示() const override;
public:
	二维::tp文本布局 m布局;
};

//=============================================================================
// 血条
//=============================================================================
class C总血条 : public I图形 {
public:
	static constexpr float c变化速度 = 0.5f; 
	static constexpr float c线宽 = 4;
	static constexpr float c间隔 = 2;	//每段之间留一点空白
	static constexpr float c左 = -c边框范围x;
	static constexpr float c右 = c边框范围x + c间隔;
	static constexpr float c总长度 = 2 * c边框范围x + c间隔;
	C总血条(int);
	void f接口_更新() override;
	void f接口_显示() const override;
	bool f接口_i可销毁() const override;
	void f减一();
private:
	二维::tp渲染目标 m渲染目标;
	二维::tp纯色画笔 m画笔;
	int m总数, m当前;
	float m显示, m实际;	//百分比
};
class C分血条 : public I图形 {	//圆形血条
public:
	static constexpr float c变化速度 = 2.f;
	static constexpr float c半径 = 64;
	static constexpr float c线宽 = 4;
	static constexpr float c外圈 = c半径 + c线宽 / 2 + 2;
	static constexpr float c内圈 = c半径 - c线宽 / 2 - 2;
	static const 数学::S颜色 c颜色;
	C分血条(const C敌机 &);
	void f接口_计算() override;
	void f接口_更新() override;
	void f接口_显示() const override;
	bool f接口_i可销毁() const override;
private:
	二维::tp渲染目标 m渲染目标;
	二维::tp纯色画笔 m画笔;
	二维::tp路径几何 m几何;
	二维::t椭圆 m外圈, m内圈;
	t向量2 m坐标;
	float m显示, m实际;	//百分比
	const C敌机 *m敌机;	//跟踪的对象
	bool mi更新 = false;
};
//=============================================================================
// 弹幕时间
//=============================================================================
class C弹幕时间 : public I图形 {
public:
	static constexpr float c字号 = 二维::ca中文字号[二维::e一号];
	static constexpr float c小数字号 = c字号 * 0.6f;
	static constexpr float c透明度 = 0.5f;
	static constexpr float c透明度速度 = c透明度 * 2;
	static const t颜色 c正常颜色, c急促颜色0, c急促颜色1;
	C弹幕时间(const float &);
	void f接口_更新() override;
	void f接口_显示() const override;
	void f动作_重置颜色();
private:
	二维::tp渲染目标 m渲染目标;
	二维::tp纯色画笔 m画笔;
	二维::tp文本布局 m布局;
	二维::tp文本格式 m格式;
	const float &m实际;
	float m显示, m透明度 = 1;
};

}