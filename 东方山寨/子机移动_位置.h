﻿#pragma once
#include "子机移动接口.h"
#include "基础.h"
#include "基础_对象工厂.h"
namespace 东方山寨 {
namespace 子机移动 {
//位置
class C位置 : public I子机移动 {
public:
	static const int c数量 = 10;	//1+2+3+4=10	属性容纳的坐标个数
	enum E属性 {
		e测试,
	};
	struct S属性 {
		t向量2 m正常[c数量];
		t向量2 m低速[c数量];
		S属性(const t向量2 *);
		const t向量2 *fg正常(int 序号) const;
		const t向量2 *fg低速(int 序号) const;
	};
	class C取属性 {
	public:
		C取属性(const S属性 &, int);
		const t向量2 &fg正常(int) const;
		const t向量2 &fg低速(int) const;
		t向量2 fg插值(int, float) const;
	private:
		int m数量;
		int m序号;
		const t向量2 *m正常;
		const t向量2 *m低速;
	};
	class C工厂 : public I自动工厂<I子机移动, C位置, C工厂> {
	public:
		C工厂(const std::initializer_list<t向量2> &);
		C工厂(const std::shared_ptr<S属性> &);
		std::tuple<const std::shared_ptr<S属性> &> f工厂_g构造实参() const;
		std::shared_ptr<S属性> m属性;
	};
	static int f计算序号(int);	//跟据火力计算数组开始序号
	C位置(const std::shared_ptr<S属性> &);
	void f接口_计算() override;
	void f接口_复位(int) override;
	C取属性 f取属性() const;
private:
	std::shared_ptr<S属性> m属性;
};
//命名空间结束
}	//namespace 子机移动

}