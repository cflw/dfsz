#pragma once
#include "基础.h"
#include "图形基础.h"
#include "动画.h"
namespace 东方山寨 {
namespace 界面图形 {
class C标题人物;
}	//namespace 界面图形
class C界面图形控制 {
public:
	enum E标志 {

	};
	C界面图形控制();
	~C界面图形控制();
	void f计算();
	void f背景(bool);
	void f标题人物(bool);
	t标志 m标志;
	std::shared_ptr<界面图形::C标题人物> m标题人物;
};
}	//namespace 东方山寨