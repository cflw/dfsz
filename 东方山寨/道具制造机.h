#pragma once
#include "基础.h"
#include "基础_对象数组.h"
#include "基础_属性数组.h"
#include "道具.h"
namespace 东方山寨 {
//==============================================================================
// 道具制造机
//==============================================================================
using t道具组 = std::map<E道具, t道具数量>;
using tp道具组 = std::shared_ptr<t道具组>;
class C道具制造机 {
public:
	struct S参数 {
		t向量2 m坐标, m速度;
		C玩家 *m跟随玩家 = nullptr;
		t属性指针<S道具属性> m道具属性;
		void fs属性(int);
	};
	class C实现 {
	public:
		C对象数组<C道具> *ma道具 = nullptr;
		C缓冲数组<I图形缓冲> *ma图形缓冲 = nullptr;
		const C属性数组<S道具属性> *ma道具属性 = nullptr;
		const C游戏速度 *m游戏速度 = nullptr;
		void f初始化_环境(const C游戏速度 &);
		void f初始化_数组(C对象数组<C道具> &, C缓冲数组<I图形缓冲> &);
		void f初始化_资源(const C属性数组<S道具属性> &);
		void f产生道具(S参数 &);
		bool fi有空(const t道具数量 = 1);
	};
	C道具制造机(C实现 &);
	void f产生道具();
	void f产生道具(t道具数量);
	void f产生道具(const t道具组 &);
	S参数 m参数;
private:
	C实现 *m实现 = nullptr;
};
}	//namespace 东方山寨
