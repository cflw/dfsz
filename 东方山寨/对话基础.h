#pragma once
#include "基础.h"
#include "基础_对象工厂.h"
namespace 东方山寨 {
enum class E立绘状态 {
	e聚焦,
	e消失,
};
//图形
class I对话立绘;
//功能
class C对话控制;
class C对话脚本;
class I对话事件;
using ta对话事件 = std::vector<std::unique_ptr<I对话事件>>;
using tp对话脚本 = std::shared_ptr<const ta对话事件>;
struct S对话参数_对话 {
	std::wstring m文本;
	bool m方向;
};
struct S对话参数_显示立绘 {
	const I工厂<I对话立绘> *m立绘工厂;
	int m标识;
	bool m方向;
};
struct S对话参数_立绘状态 {
	int m标识;
	E立绘状态 m状态;
};
}