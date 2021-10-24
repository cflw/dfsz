#pragma once
#include "基础_数组指针.h"
#include "图形包含.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "图形管线接口.h"
#include "图形引擎.h"
#include "对话基础.h"
#include "图形_对话立绘.h"
#include "图形_画图片.h"
namespace 东方山寨 {
constexpr size_t c最大立绘图层数 = 2;
//==============================================================================
// 静态立绘类
//==============================================================================
class C静态立绘管线;
struct S静态立绘组件;
//立绘对象
struct S静态立绘属性;
class C静态对话立绘 : public I对话立绘 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:	//部分代码可以和 C画图片 复用,以后重构
		void f显示() const override;
		void f画组件(const S静态立绘组件 &) const;
		C静态立绘管线 *m图形管线 = nullptr;
		const S静态立绘组件 *ma组件[c最大立绘图层数];
		t向量2 m坐标;
		float m透明度 = 0;
	};
	C静态对话立绘(const S静态立绘属性 &);
	void f接口_初始化(const S图形参数 &);
	void f接口_更新() override;
	void f接口_改变表情(E立绘表情) override;
public:
	const S静态立绘属性 *m属性 = nullptr;
	E立绘表情 m表情 = E立绘表情::e无;
};
struct S静态立绘组件 {
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m矩形;	//载入时计算，表示组件的位置
	t向量2 m偏移;	//载入时保存,表示组件偏移位置
};
struct S静态立绘属性 {
	struct S表情映射 {
		t属性指针<S静态立绘组件> ma组件[c最大立绘图层数];	//设置成某个表情时, 每一个图层对应的纹理
	};
	using ta表情映射 = std::map<E立绘表情, S表情映射>;
	ta表情映射 ma表情映射;
};
class C静态立绘建造机 : public C图形建造机<C静态对话立绘, C静态对话立绘::C图形缓冲> {
public:
	C静态立绘建造机() = default;
	C静态立绘建造机(const S静态立绘属性 &);
	void f接口_建造图形(t过程 &) const override;
	const S静态立绘属性 *m属性 = nullptr;
};
//管理资源
class C静态立绘管理 {
public:
	C静态立绘管理();
	~C静态立绘管理();
	void f编译(const C属性数组<S纹理> &, const C属性数组<S顶点矩形> &);
	C属性数组<S静态立绘组件> ma组件;
	C属性数组<S静态立绘属性> ma属性;
};
//==============================================================================
// 静态立绘管线
//==============================================================================
//支持星莲船之后的正作的立绘
struct VS_CHARACTER1 {
	t向量2 m位置;
	t向量2 m纹理[c最大立绘图层数];
	float m透明度 = 0;
	//float x0;	//不使用
};
//在构造函数中初始化使得派生类难以重写整个初始化过程。以后改掉。
class C静态立绘管线 : public C画图片管线 {
public:
	static std::unique_ptr<C静态立绘管线> g这;	//临时单例
	C静态立绘管线(C图形引擎 &, 三维::C三维 &);
	~C静态立绘管线();
	static C静态立绘管线 &fg这();	//临时实现.以后改成一个管理类统一管理所有图形管线
	void f准备() override;
	void f刷新() override;
private:
	三维::tp深度模板 m深度模板;
};
}	//namespace 东方山寨