﻿export module 东方山寨.对话基础;
export import "基础.h";
export import "基础_对象工厂.h";
export namespace 东方山寨 {
class I图形建造机;
enum class E立绘状态 {
	e聚焦,
	e消失,
};
enum class E对话方向 {
	e从左向右,	//false
	e从右向左,	//true
};
enum class E立绘表情 {
	e无,
	e正常,
	e高兴,
	e伤心,
	e愤怒,
	c最大值,
};
//图形
class I对话立绘;
//功能
class C对话控制;
class C对话脚本;
using tf对话事件 = std::function<void(C对话控制 &)>;
using ta对话事件 = std::vector<tf对话事件>;
using tp对话脚本 = std::shared_ptr<const ta对话事件>;
struct S对话参数_对话 {
	std::wstring m文本;
	E对话方向 m方向 = E对话方向::e从左向右;
};
struct S对话参数_显示立绘 {
	std::shared_ptr<const I图形建造机> m立绘工厂 = nullptr;
	int m标识 = 0;
	E对话方向 m方向 = E对话方向::e从左向右;
};
struct S对话参数_立绘状态 {
	int m标识 = 0;
	E立绘状态 m状态 = E立绘状态::e聚焦;
};
struct S对话参数_立绘表情 {
	int m标识 = 0;
	E立绘表情 m表情 = E立绘表情::e无;
};
constexpr bool ft对话方向(E对话方向 a方向) {
	switch (a方向) {
	case E对话方向::e从左向右:
		return false;
	case E对话方向::e从右向左:
		return true;
	}
	return false;
}
constexpr E对话方向 ft对话方向(bool a方向) {
	switch (a方向) {
	case false:
		return E对话方向::e从左向右;
	case true:
		return E对话方向::e从右向左;
	}
	return E对话方向::e从左向右;
}
}	//namespace 东方山寨