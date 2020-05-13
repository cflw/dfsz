#pragma once
#include "遮罩基础.h"
#include "数学基础.h"
namespace 东方山寨::遮罩 {
class C圆形 : public I遮罩形状 {
public:
	C圆形(const t圆形 &);
	bool f判定_点(const t向量2 &) const override;
	t圆形 m圆形;
};
class C旋转矩形 : public I遮罩形状 {
public:
	C旋转矩形(const t旋转矩形 &);
	bool f判定_点(const t向量2 &) const override;
	t旋转矩形 m旋转矩形;
};
class C左 : public I遮罩形状 {
public:
	C左(float);
	bool f判定_点(const t向量2 &) const override;
	float x;
};
class C右 : public I遮罩形状 {
public:
	C右(float);
	bool f判定_点(const t向量2 &) const override;
	float x;
};
class C上 : public I遮罩形状 {
public:
	C上(float);
	bool f判定_点(const t向量2 &) const override;
	float y;
};
class C下 : public I遮罩形状 {
public:
	C下(float);
	bool f判定_点(const t向量2 &) const override;
	float y;
};
}	//namespace 东方山寨::遮罩