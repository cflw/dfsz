#pragma once
#include "游戏常量.h"
#include "边框常量.h"
#include "基础.h"
#include "图形包含.h"
#include "数学包含.h"
#include "图形基础.h"
#include "对话基础.h"
namespace 东方山寨 {
enum class E立绘表情 {
	e无
};
class C对话框 : public I图形 {
public:
	static constexpr float c透明度速度 = c帧秒<float> / 0.25f;
	static constexpr float c边框 = 16;
	static constexpr float c开始位置x = c边框范围x - 32;
	static constexpr float c开始位置y = -96;	//顶部
	static constexpr float c对话框透明度 = 0.8f;
	C对话框(const S对话参数_对话 &);
	void f接口_计算() override;
	void f接口_更新() override;
	void f兼容显示() const;
	bool f接口_i可销毁() const override;
private:
	二维::tp画图形 m画图形;
	二维::tp画文本 m画文本;
	二维::tp文本布局 m文本布局;
	二维::tp文本效果 m文本效果;
	float m透明度 = 0;	//同时表示渐变进度
	float m边框实际宽 = 0;
	float m边框实际高 = 0;
	float m边框显示宽 = 0;
	bool m方向;	//0左到右,1右到左
};
class I对话立绘 : public I图形 {
public:
	enum E初始化标志 {
		e方向,
	};
	enum E标志 {
		e焦点 = I图形::E标志::e自定义,
	};
	static constexpr float c开始位置x = c边框范围x - 32;
	static constexpr float c开始位置y = -32;	//中心
	static constexpr float c动画速度 = 4;	//0.25秒完成
	void f接口_计算() override;
	void f兼容显示() const;	//默认画个白色矩形
	bool f接口_i可销毁() const override;
	void f接口_初始化(const S图形参数 &) override;
	virtual void f接口_改变表情(E立绘表情);
	void f动作_表情(E立绘表情);	//调用f接口_改变表情
	void f动作_聚焦();
	void f动作_失焦();
protected:
	数学::S向量2 m坐标;	//立绘位置
	float m出现;
	float m焦点;	//如果说话者是当前立绘,为1
	bool m方向;
};
}