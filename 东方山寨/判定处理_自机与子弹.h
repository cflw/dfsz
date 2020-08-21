#pragma once
#include "数学包含.h"
namespace 东方山寨 {
class C自机;
class C自机与子弹判定 {
public:
	enum E判定结果 {
		e无相交 = 0,
		e擦弹 = 0x1,
		e碰撞 = 0x2,
	};
	void f绑定自机(C自机 *);
	void f计算判定();
	int f子弹_提交判定(const t圆形 &);
	int f子弹_提交判定(const t旋转矩形 &);
	void f子弹_判定有效();	//在子弹调用
	bool f子弹_i碰撞() const;
	bool f子弹_i擦弹() const;
	const t向量2 &fg自机坐标() const;
private:
	void f碰撞成立处理();
	void f擦弹成立处理();
	C自机 *m自机;
	t圆形 m碰撞点, m擦弹点;
	int m擦弹数;
	int m判定结果;
};

}