#pragma once
#include "图形包含.h"
#include "数学包含.h"
#include "图形引擎.h"
#include "边框常量.h"
namespace 东方山寨 {
class C画图片;
class C画背景 {
public:
	struct S背景 {
		tp纹理 m纹理;
		t向量2 m纹理尺寸;
		S顶点矩形 m顶点矩形;
		float m透明度 = 0;
	};
	C画背景(C画图片 &);
	void f计算();
	void f显示() const;
	void fs屏幕尺寸(float, float);
	void fs透明度(float);
	void f切换背景(tp纹理, const t向量2 &尺寸);
	S顶点矩形 f计算顶点矩形(const t向量2 &纹理尺寸);
	const S背景 &fg当前背景() const;
public:
	C画图片 *m画图片;
	t向量2 m屏幕尺寸 = {c标准尺寸x, c标准尺寸y};
	std::deque<S背景> ma背景;
	float m透明度 = 1;
};

}