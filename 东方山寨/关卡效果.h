#pragma once
#include "关卡.h"
namespace 东方山寨 {
//=============================================================================
// 结构
//=============================================================================
struct S关卡标题 {
	std::wstring m标题;
	std::wstring m场景;
};
//=============================================================================
// 效果
//=============================================================================
class C关卡效果 {
public:
	static void f显示标题(const S关卡标题 &);
	static std::function<void()> F显示标题(const S关卡标题 &);
};
}