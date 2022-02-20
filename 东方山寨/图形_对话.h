#pragma once
#include "游戏常量.h"
#include "边框常量.h"
#include "图形包含.h"
#include "数学包含.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "对话基础.h"
namespace 东方山寨 {
//每句话都是一个对话框对象
class C对话框 : public I图形 {
public:
	static constexpr float c渐变速度 = 4;
	static constexpr float c边框 = 12;
	static constexpr float c开始位置x = c边框范围x - 32;
	static constexpr float c开始位置y = -96;	//顶部
	static constexpr float c对话框透明度 = 0.8f;
	static constexpr float c字号 = 二维::ca中文字号[二维::E中文字号::e三号];
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp画图形 m画图形;
		二维::tp画文本 m画文本;
		二维::tp文本布局 m文本布局;
		二维::tp路径几何 m三角形;
		t圆角矩形 m方框矩形;
		t向量2 m文本坐标;	//中心坐标
	};
	using t图形缓冲 = C图形缓冲;
	C对话框(const S对话参数_对话 &);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
private:
	t向量2 m实际尺寸;
	t向量2 m显示尺寸;
	S对话参数_对话 m参数;
	float m出现 = 0;
};
}	//namespace 东方山寨