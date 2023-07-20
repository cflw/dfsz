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
std::wstring C取文本::operator ()(const std::wstring &a模板) const {
	assert(!a模板.empty());
	const size_t v模板长度 = a模板.size();
	std::wstring v返回;
	v返回.reserve(v模板长度 * 2);
	size_t v右位置 = 0;
	size_t v左位置 = a模板.find(L'{');
	while (v左位置 != std::wstring::npos) {
		if (v右位置 != 0) {
			v返回 += a模板.substr(v右位置, v左位置 - v右位置 - 1);	//拼接上次右括号到这次左括号之间的字符串
		}
		v右位置 = a模板.find(L'}', v左位置);
		if (v右位置 == std::wstring::npos) {	//没有闭合
			v返回 += a模板.substr(v左位置);
			return v返回;
		}
		const std::wstring v名称 = a模板.substr(v左位置 + 1, v右位置 - v左位置 - 1);
		v返回 += operator [](v名称);
		//下一循环
		++v右位置;
		if (v右位置 >= v模板长度) {	//到达末尾
			return v返回;
		}
		v左位置 = a模板.find(L'{', v右位置);
	}
	v返回 += a模板.substr(v右位置);
	return v返回;
}
const std::wstring &C取文本::operator [](const std::wstring &a名称) const {
	assert(!a名称.empty());
	const std::wstring v名称 = f计算名称(a名称);
	const auto &va名称标识 = C游戏::fg资源().fg名称标识();
	if (auto v找 = va名称标识.find(v名称); v找 != va名称标识.end()) {
		return ma文本->fg数据(v找->second);
	} else {
		return a名称;	//找不到,返回名称
	}
}
const std::wstring &C取文本::operator [](int a标识) const {
	assert(a标识 != 0);
	return ma文本->fg数据(a标识);
}
std::wstring C取文本::f计算名称(const std::wstring &a名称) const {
	return m名称 + a名称;
}
}	//namespace 东方山寨