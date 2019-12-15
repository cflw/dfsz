#pragma once
#include "图形基础.h"
#include "图形缓冲.h"
namespace 东方山寨::图形 {
class C圆形 : public I粒子 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		t向量2 m坐标;
		t颜色 m颜色;
		float m半径;
	};
	C圆形() = default;
	C圆形(float, float);
	void f接口_计算() override;
	void f接口_更新() override;
	float fg当前半径() const;
public:
	float m开始半径 = 0;
	float m结束半径 = 100;
};
}