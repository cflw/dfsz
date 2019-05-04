#pragma once
#include "图形引擎.h"
namespace 东方山寨 {
//=============================================================================
// 纹理工厂
//=============================================================================
class C纹理工厂 {
public:
	~C纹理工厂();
	void f初始化(三维::C三维&, C属性数组<tp纹理>&);
	tp纹理 f创建纹理(int, const std::wstring &) const;	//如果纹理不存在,则从文件中读取
	tp纹理 f创建纹理(int, const 纹理::I纹理 &);
private:
	三维::C纹理工厂 *m工厂;
	C属性数组<tp纹理> *ma纹理;
};
//=============================================================================
// 平面顶点工厂,从纹理裁出一块矩形
//=============================================================================
class C顶点工厂 {
public:
	enum E创建标志 {
		e尺寸偏移,
		e缩放,
		e中心偏移,
	};
	enum E映射点 {
		e已转换,
		e中心,
		e左上
	};
	struct S参数 {
		t标志 m标志;
		E映射点 m映射点标记 = e已转换;
		t向量2 m半尺寸;
		t向量2 m纹理尺寸;
		t向量2 m映射点;	//窗口坐标
		t向量2 m中心偏移;	//直角坐标
		t向量2 m缩放;
		float m映射尺寸偏移 = 0;
		float m顶点尺寸偏移 = 0;
		void fs顶点半尺寸(const t向量2 &);
		void fs顶点尺寸(const t向量2 &);
		void fs纹理尺寸(const t向量2 &);
		void fs映射点_中心(const t向量2 &);	//把顶点矩形的点对齐到纹理映射中
		void fs映射点_左上(const t向量2 &);
		void fs映射尺寸偏移(float);
		void fs顶点中心偏移(const t向量2 &);
		void fs顶点缩放(const t向量2 &);
		void fs顶点尺寸偏移(float);
		void f转换映射点();
		//创建顶点时的计算,这顺序表示计算时的调用顺序
		void f计算_顶点半尺寸(float*) const;
		void f计算_纹理坐标(float*) const;
		void f计算_顶点尺寸偏移(float*) const;
		void f计算_顶点缩放(float*) const;
		void f计算_顶点中心偏移(float*) const;
	};
	class C循环 : public 循环::I循环<C循环> {
	public:
		C循环(C顶点工厂 &, int, int);
		void f循环控制_自增();
		bool f循环控制_i继续();
		int fg计数() const;
		void f变换_平移(const t向量2 &);	//窗口坐标
	private:
		S参数 *m参数, m参数备份;
		int m行, m列, i, j;
	};
	void f初始化(C属性数组<S顶点矩形>&);
	static S顶点矩形 f创建矩形(const S参数 &);
	void f创建矩形(int 标识);
	void f复制矩形(int 新, int 旧);
	C循环 f循环(int, int);
	void f自动化_完整纹理(int 标识, const t向量2 &纹理尺寸);
	void f自动化_完整切割(int 标识, const t向量2 &纹理尺寸, const t向量2 &顶点尺寸);
	void f自动化_完整切割(int 标识, const t向量2 &纹理尺寸, int, int);
public:
	S参数 m参数;
private:
	C属性数组<S顶点矩形> *ma顶点矩形;
};
//=============================================================================
// 模型工厂
//=============================================================================
class C模型工厂 {
public:
	struct S参数 {
		const S三维顶点 *m顶点 = nullptr;
		const uint16_t *m索引 = nullptr;
		size_t m顶点数, m索引数;
		void fs顶点(const S三维顶点 *, size_t);
		void fs索引(const uint16_t *, size_t);
	} m参数;
	void f初始化(C属性数组<C模型>&);
	void f创建模型(int 标识);
private:
	C属性数组<C模型> *ma模型;
};
}	//namespace 东方山寨