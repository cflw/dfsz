#include "取文本.h"
#include "游戏.h"
namespace 东方山寨 {
namespace 计算 {
std::wstring f文本语言前缀(const std::wstring &a名称, const std::wstring &a语言) {
	return a名称 + L"." + a语言;
}
}	//namespace 计算
const std::wstring c空文本 = L"(空)";
C取文本::C取文本(const C属性数组<std::wstring> &a数组, const std::wstring &a名称):
	ma文本(&a数组), m名称(a名称 + L".") {
}
const std::wstring &C取文本::operator [](const std::wstring &a名称) const {
	const std::wstring v名称 = f计算名称(a名称);
	const auto &va名称标识 = C游戏::fg资源().fg名称标识();
	if (auto v找 = va名称标识.find(v名称); v找 != va名称标识.end()) {
		return ma文本->fg数据(v找->second);
	} else {
		return c空文本;
	}
}
std::wstring C取文本::f计算名称(const std::wstring &a名称) const {
	return m名称 + a名称;
}

}	//namespace 东方山寨