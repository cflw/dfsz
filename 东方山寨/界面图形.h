#pragma once
#include "基础.h"
#include "图形基础.h"
#include "动画.h"
namespace 东方山寨 {
class C背景;
namespace 界面图形 {
class C标题人物;
class C云;
}	//namespace 界面图形
class C界面图形控制 {
public:
	static constexpr int c云数 = 200;
	enum E标志 {
		e云,
	};
	enum E图层 {
		e无 = 0,
		e背景 = 1,	//=东方山寨::E图层::e背景
		e后云,
		e人,
		e前云,
		e星,
	};
	C界面图形控制();
	~C界面图形控制();
	void f计算();
	void f关闭图形();	//进入游戏后需要关闭
	void f背景(bool);
	void f标题人物(bool);
	void f云(bool);
	t标志 m标志;
	std::shared_ptr<界面图形::C标题人物> m标题人物;
	std::shared_ptr<界面图形::C云> ma云[c云数];
	std::shared_ptr<C背景> m背景;
	float m云透明度 = 0;
};
}	//namespace 东方山寨