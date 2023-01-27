#pragma once
#include <string>
namespace 东方山寨 {
inline const std::wstring c玩家名称 = L"玩家";
inline const std::wstring c语言 = L"zh-CN";
struct S程序设置 {
	std::wstring m玩家名称;
	std::wstring m文本语言;
	std::wstring m界面语言;
	S程序设置() = default;	//空白设置
	static S程序设置 fc系统();	//从系统设置中读取
};
}	//namespace 东方山寨