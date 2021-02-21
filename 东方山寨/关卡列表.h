#pragma once
#include <vector>
#include <string>
namespace 东方山寨 {
class C关卡;
static const std::wstring c关卡前缀 = L"东方月亮船";
static const std::wstring ca关卡[] = {
	L"测试关卡",
	c关卡前缀 + L"1",
	c关卡前缀 + L"2",
	c关卡前缀 + L"3",
	c关卡前缀 + L"4",
	c关卡前缀 + L"5",
	c关卡前缀 + L"6",
	c关卡前缀 + L"ex",
	c关卡前缀 + L"ex2",
};
enum class E关卡 {	//枚举值的顺序要和数组顺序一样
	e测试,
	e一,
	e二,
	e三,
	e四,
	e五,
	e六,
	e附加,
	e附加2,
};
class C关卡列表 {	//用来获取当前游戏的关卡列表
public:
	static std::vector<C关卡*> &fg列表();	//传统模式的关卡列表
	static C关卡 &fg关卡(E关卡);
};
}	//namespace 东方山寨