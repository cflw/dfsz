#pragma once
#include <string>
namespace 东方山寨 {
inline const std::wstring c玩家名称 = L"玩家";
inline const std::wstring c语言 = L"zh-cn";
struct S程序设置 {
	std::wstring m玩家名称 = c玩家名称;
	std::wstring m文本语言 = c语言;
	std::wstring m界面语言 = c语言;
};
}	//namespace 东方山寨