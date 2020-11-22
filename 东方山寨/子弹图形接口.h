#pragma once
#include <concepts>
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
	enum E顶点标志 {
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
class I子弹图形数据;
using tp子弹图形数据 = std::unique_ptr<I子弹图形数据>;
template<typename t> concept T子弹图形数据 = std::derived_from<t, I子弹图形数据>;
class I子弹图形数据 {
public:
	virtual ~I子弹图形数据() = default;
};
template<T子弹图形数据 t子弹图形数据> t子弹图形数据 *f创建子弹图形数据(tp子弹图形数据 &a数据) {
	if (a数据 == nullptr || dynamic_cast<t子弹图形数据*>(a数据.get()) == nullptr) {
		a数据 = std::make_unique<t子弹图形数据>();
	}
	return static_cast<t子弹图形数据 *>(a数据.get());
}
class I画子弹 : public I图形管线 {
public:
	virtual void f生成点(tp子弹图形数据 &, const C子弹顶点::C点 &) = 0;
	virtual void f生成直线(tp子弹图形数据 &, const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) = 0;
	virtual void f生成曲线(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual void f生成连续点(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) = 0;
	virtual void f生成网格(tp子弹图形数据 &, const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) = 0;
	virtual void f绘制图形数据(const tp子弹图形数据 &) = 0;
};
}