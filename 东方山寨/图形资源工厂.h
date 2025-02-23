#pragma once
#include <cflw工具_循环.h>
#include "基础.h"
#include "图形资源.h"
#include "基础_属性数组.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
//==============================================================================
// 纹理工厂
//==============================================================================
class C纹理工厂 {
public:
	~C纹理工厂();
	void f初始化(三维::C三维 &, C属性数组<S纹理> &);
	//创建纹理,成功返回纹理指针,失败返回nullptr
	//↓返回的指针只能临时使用,禁止保存
	const S纹理 *f创建纹理(int, const std::wstring_view &) const;	//如果纹理不存在,则从文件中读取
	const S纹理 *f创建纹理(int, const 纹理::I纹理 &) const;
private:
	三维::C纹理工厂 *m纹理工厂 = nullptr;
	C属性数组<S纹理> *ma纹理 = nullptr;
};
//==============================================================================
// 平面顶点工厂,从纹理裁出一块矩形
//==============================================================================
class C顶点矩形工厂 {
public:
	enum E创建标志 {
		e矩形尺寸缩放,
		e相对原点缩放,
		e矩形坐标偏移,
		e自定义矩形尺寸,	//矩形尺寸 ?= 裁剪尺寸
	};
	struct S参数;
	class C循环;
	struct S参数 {
		t标志 m标志;
		t向量2 m裁剪尺寸 = t向量2::c零;
		t向量2 m纹理尺寸 = t向量2::c零;
		t向量2 m裁剪坐标 = t向量2::c零;	//窗口坐标
		t向量2 m矩形坐标 = t向量2::c零;	//直角坐标
		t向量2 m矩形尺寸 = t向量2::c零;
		t向量2 m矩形尺寸缩放 = t向量2::c一;
		t向量2 m相对原点缩放 = t向量2::c一;
		float m裁剪尺寸偏移 = -0.5f;
		void f重置();
		C循环 f循环(int, int);
		void fs裁剪半尺寸(const t向量2 &);
		void fs裁剪尺寸(const t向量2 &);
		void fs纹理尺寸(const t向量2 &);
		void fs裁剪坐标(const t向量2 &);
		void fs裁剪尺寸偏移(float = 0.5f);
		void fs矩形坐标(const t向量2 &);
		void fs矩形半尺寸(const t向量2 &);
		void fs矩形尺寸(const t向量2 &);
		void fs矩形尺寸缩放(const t向量2 &);	//相对矩形中心缩放
		void fs相对原点缩放(const t向量2 &);	//相对坐标原点缩放
		//创建顶点时的计算,这顺序表示计算时的调用顺序
		void f计算_顶点坐标_裁剪(float *) const;	//=矩形尺寸
		void f计算_顶点坐标_矩形(float *) const;	//=裁剪尺寸
		void f计算_纹理坐标(float *) const;
		void f计算_矩形尺寸缩放(float *) const;
		void f计算_矩形坐标偏移(float *) const;
		void f计算_矩形坐标缩放(float *) const;
	};
	class C循环 : public 循环::I循环<C循环> {
	public:
		C循环(S参数 &, int, int);
		void f循环控制_自增();
		bool f循环控制_i继续();
		int fg计数() const;
		void f变换_平移(const t向量2 &);	//窗口坐标
	private:
		S参数 *m参数 = nullptr, m参数备份;
		int m行, m列, i, j;
	};
	void f初始化(C属性数组<S顶点矩形> &);
	static S顶点矩形 fc顶点矩形(const S参数 &);
	void f创建矩形(int 标识, const S参数 &) const;
	void f复制矩形(int 新, int 旧) const;
	void f创建矩形_完整纹理(int 标识, const t向量2 &纹理尺寸, float 缩放 = 1) const;
	void f创建矩形_完整切割(int 标识, const t向量2 &纹理尺寸, const t向量2 &顶点尺寸) const;
	void f创建矩形_完整切割(int 标识, const t向量2 &纹理尺寸, int, int) const;
private:
	C属性数组<S顶点矩形> *ma顶点矩形 = nullptr;
};
using t顶点矩形参数 = C顶点矩形工厂::S参数;
//==============================================================================
// 模型工厂
//==============================================================================
class C模型工厂 {
public:
	struct S参数 {
		const S三维顶点 *m顶点 = nullptr;
		const uint16_t *m索引 = nullptr;
		size_t m顶点数 = 0, m索引数 = 0;
		void fs顶点(const S三维顶点 *, size_t);
		void fs索引(const uint16_t *, size_t);
	} m参数;
	void f初始化(C属性数组<C模型>&);
	void f创建模型(int 标识);
private:
	C属性数组<C模型> *ma模型 = nullptr;
};
}	//namespace 东方山寨