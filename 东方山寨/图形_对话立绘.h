#pragma once
#include "边框常量.h"
#include "基础.h"
#include "图形包含.h"
#include "图形建造机.h"
#include "对话基础.h"
namespace 东方山寨 {
//==============================================================================
// 对话立绘
//==============================================================================
enum class E立绘表情 {
	e无,
	e正常,
	c最大值,
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
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	bool f接口_i可销毁() const override;
	virtual void f接口_改变表情(E立绘表情);
	void f动作_表情(E立绘表情);	//调用f接口_改变表情
	void f动作_聚焦();
	void f动作_失焦();
protected:
	t向量2 m坐标;	//立绘位置
	float m出现 = 0;
	float m焦点 = 0;	//如果说话者是当前立绘,为1
	E对话方向 m方向 = E对话方向::e从左向右;	//同对话框
};
//方框,用来测试
class C对话立绘_空 : public I对话立绘 {
public:
	class C图形缓冲 : public I图形缓冲 {	//画个白色矩形
	public:
		void f显示() const override;
		二维::tp画图形 m画图形;
		t矩形 m矩形;
	};
	void f接口_初始化(const S图形参数 &) override;
	void f接口_更新() override;
};
using C空白立绘建造机 = C图形建造机<C对话立绘_空, C对话立绘_空::C图形缓冲>;
}	//namespace 东方山寨