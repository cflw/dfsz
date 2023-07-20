#pragma once
#include <string>
#include "基础_属性数组.h"
namespace 东方山寨 {
namespace 计算 {
std::wstring f文本语言前缀(const std::wstring &a名称, const std::wstring &a语言);
}	//namespace 计算
class C取文本 {
public:
	C取文本(const C属性数组<std::wstring> &数组, const std::wstring &名称);
	std::wstring operator ()(const std::wstring &) const;	//使用模板取文本,格式"{名称}"
	const std::wstring &operator [](const std::wstring &) const;	//使用名称取文本
	const std::wstring &operator [](int) const;	//使用标识取文本
	std::wstring f计算名称(const std::wstring &) const;
	const C属性数组<std::wstring> *ma文本;
	std::wstring m名称;	//数组名称
};
}	//namespace 东方山寨