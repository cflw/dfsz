#pragma once
#include "子弹图形接口.h"
namespace 东方山寨 {
class C子弹;
struct S子弹属性;
class C图形引擎;
//设备无关的子弹顶点,在"I画子弹::f绘制"中转换成显示用的顶点
class C画子弹_顶点 : public I画子弹 {
private:
	class C图形数据;
	struct S顶点;
	class C顶点赋值;
	using t顶点 = S顶点;
	using t索引 = WORD;
	using tf顶点 = std::function<t顶点*(int)>;
	using tf索引 = std::function<t索引*(int)>;
	static constexpr unsigned int c顶点缓存数量 = 8000;
	static constexpr unsigned int c索引缓存数量 = c顶点缓存数量 * 2;
	static constexpr float c左 = 0, c上 = 0, c右 = 1, c下 = 1, c中 = 0.5f;
public:	//函数
	C画子弹_顶点(C图形引擎 &, 三维::C三维 &, bool 高光);
	virtual ~C画子弹_顶点() = default;
	void f准备() override;
	void f刷新() override;
	void f生成点(tp子弹图形数据 &, const C子弹顶点::C点 &) override;
	void f生成直线(tp子弹图形数据 &, const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) override;
	void f生成曲线(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) override;
	void f生成连续点(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) override;
	void f生成网格(tp子弹图形数据 &, const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) override;
	void f绘制图形数据(const tp子弹图形数据 &) override;
private:	//内部画子弹函数
	void f画子弹(const S子弹属性 &, const void *a顶点指针, size_t a顶点大小, const void *a索引指针, size_t a索引大小);
	//索引
	static void f自动索引_长条(int, const tf索引 &);
	static void f自动索引_网格(int, int, const tf索引 &);
	static int f计算索引数量(int 宽, int 高 = 1);
	//总生成
	static void f生成点0(const C子弹顶点::C点 &, const tf顶点 &, const tf索引 &);
	static void f生成直线0(const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &, const tf顶点 &, const tf索引 &);
	static void f生成曲线0(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &, const tf顶点 &, const tf索引 &);
	static void f生成连续点0(const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &, const tf顶点 &, const tf索引 &);
	static void f生成网格0(const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &, const tf顶点 &, const tf索引 &);
	//分配函数
	三维::C渲染控制 *m渲染控制 = nullptr;
	三维::tp图形管线 m图形管线;
	三维::tp纹理 m纹理;
	t自动缓冲 m缓冲;
	三维::tp采样器 m采样器;
	三维::tp缓冲 m常量缓冲;
};
}//命名空间结束