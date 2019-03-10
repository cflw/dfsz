#pragma once
#include "数学包含.h"
#include "图形包含.h"
#include "基础.h"
namespace 东方山寨 {
class C子弹;
//==============================================================================
// 子弹顶点
//==============================================================================
class C子弹顶点 {
public:
	enum E顶点标记 {
		e坐标,	//为true时使用v点的成员变量,为false时使用v中心的成员变量
		e位置,	//[0,1],如果为false每个点的位置平均分配
		e出现,
		e颜色,	//还没实现
		e环,	//只在连续点使用,头点与尾点将连接起来
	};
	//顶点类型
	class C点 {
	public:
		struct S中心 {
			float m出现;
			float m消失;
		};
		const C子弹 *m子弹;
		S中心 m中心;
		C点(const C子弹 *);
	};
	class C直线 {
	public:
		struct S顶点 {
			float m位置;
			float m消失;
		};
		struct S中心 {
			t向量2 m坐标;
			float m出现;
		};
		typedef S顶点 t顶点;
		typedef std::vector<S顶点> ta顶点;
		const C子弹 *m子弹;
		t标志 m标志;
		S中心 m中心;
		int m数量;
		C直线(const C子弹 *, int);
	};
	class C曲线 {
	public:
		struct S顶点 {
			t向量2 m坐标;
			float m位置;
			float m出现;
			float m消失;
			const t颜色 *m颜色[2];
		};
		struct S中心 {
			float m出现;
		};
		typedef S顶点 t顶点;
		typedef std::vector<S顶点> ta顶点;
		const C子弹 *m子弹;
		t标志 m标志;
		S中心 m中心;
		int m数量;
		C曲线(const C子弹 *, int);
	};
	class C网格 {
	public:
		struct S顶点 {
			t向量2 m坐标;
			float m消失;
			const t颜色 *m颜色[2];
		};
		struct S平均点 {
			t向量2 m坐标;
			float m出现;
			const t颜色 *m颜色[2];
		};
		struct S中心 {
			float m出现;
		};
		typedef S顶点 t顶点;
		typedef S平均点 t平均点;
		typedef std::vector<S顶点> ta顶点;
		const C子弹 *m子弹;
		t标志 m标志;
		S中心 m中心;
		int m宽, m高;
		C网格(const C子弹 *, int, int);
	};
};
//==============================================================================
// 画子弹接口
//==============================================================================
class I子弹图形数据 {
};
using tp子弹图形数据 = std::shared_ptr<I子弹图形数据>;
class I画子弹 : public I图形管线 {
public:
	virtual void f绘制点(const C子弹顶点::C点 &) = 0;
	virtual void f绘制直线(const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) = 0;
	virtual void f绘制曲线(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual void f绘制连续点(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual void f绘制网格(const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) = 0;
	virtual tp子弹图形数据 f生成点(const C子弹顶点::C点 &) = 0;
	virtual tp子弹图形数据 f生成直线(const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) = 0;
	virtual tp子弹图形数据 f生成曲线(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual tp子弹图形数据 f生成连续点(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual tp子弹图形数据 f生成网格(const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) = 0;
	virtual void f绘制图形数据(const tp子弹图形数据 &) = 0;
};
}