#pragma once
#include "子弹图形接口.h"
namespace 东方山寨 {
class C子弹;
class C图形引擎;
class C画子弹_线条 : public I画子弹 {	//只画判定点
public:	//图形数据
	class C图形数据_点;
	class C图形数据_直线;
	class C图形数据_曲线;
	class C图形数据_连续点;
	class C图形数据_网格;
public:
	C画子弹_线条(二维::C二维 &);
	virtual ~C画子弹_线条() = default;
	void f准备() override;
	void f刷新() override;
	//生成
	void f生成点(tp子弹图形数据 &, const C子弹顶点::C点 &) override;
	void f生成直线(tp子弹图形数据 &, const C子弹顶点::C直线 &, const C子弹顶点::C直线::ta顶点 &) override;
	void f生成曲线(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) override;
	void f生成连续点(tp子弹图形数据 &, const C子弹顶点::C曲线 &, const C子弹顶点::C曲线::ta顶点 &) override;
	void f生成网格(tp子弹图形数据 &, const C子弹顶点::C网格 &, const C子弹顶点::C网格::ta顶点 &) override;
	//绘制
	void f绘制图形数据(const tp子弹图形数据 &) override;
	void f绘制点(const C图形数据_点 &);
	void f绘制直线(const C图形数据_直线 &);
	void f绘制曲线(const C图形数据_曲线 &);
	void f绘制连续点(const C图形数据_连续点 &);
	void f绘制网格(const C图形数据_网格 &);
	//辅助
	static float f计算透明度(float 出现, float 消失);
private:
	std::shared_ptr<二维::C画图形> m画图;
};
}	//namespace 东方山寨