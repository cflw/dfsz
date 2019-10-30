#pragma once
#include <string>
#include "基础_数组.h"
namespace 东方山寨 {
namespace 计算 {
std::wstring f文本语言前缀(const std::wstring &a名称, const std::wstring &a语言);
}
class C取文本 {
public:
	C取文本(const C属性数组<std::wstring> &数组, const std::wstring &名称);
	const std::wstring &operator [](const std::wstring &) const;
	std::wstring f计算名称(const std::wstring &) const;
	const C属性数组<std::wstring> *ma文本;
	std::wstring m名称;
};
}