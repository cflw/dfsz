#pragma once
#include "数学包含.h"
#include "图形资源.h"
#include "边框常量.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "基础_数组指针.h"
namespace 东方山寨 {
struct S图形参数;
class C画图片;
class C背景管理;
//==============================================================================
// 普通的背景
//==============================================================================
class C背景 : public I图形 {
public:
	enum E标志 {
		e消失 = I图形::E标志::e自定义,
	};
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		const S纹理 *m纹理 = nullptr;
		const S顶点矩形 *m顶点矩形 = nullptr;
		float m透明度 = 0;
	};
	C背景(const C背景管理 &);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
	void f动作_结束();
private:
	const C背景管理 *m背景管理 = nullptr;
	float m最大透明度 = 1;
	float m出现 = 0;
	float m消失 = 0;
};
//==============================================================================
// 背景管理
//==============================================================================
class C背景管理 {
public:
	void fs屏幕尺寸(float, float);
public:
	C画图片 *m画图片 = nullptr;
	t向量2 m屏幕尺寸;
	S顶点矩形 m顶点矩形;
};
//图形模板
namespace 图形模板 {
std::shared_ptr<C背景> f全屏静态背景(const S纹理 &);
std::shared_ptr<C背景> f符卡展开背景(const S纹理 &, const t向量2 &展开坐标);
std::shared_ptr<C背景> f符卡淡入背景(const S纹理 &);
}	//namespace 图形模板
}	//namespace 东方山寨