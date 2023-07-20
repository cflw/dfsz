#include <cflw视窗.h>
#include "程序设置.h"
import 东方山寨.文本管理;
namespace 视窗 = cflw::视窗;
namespace 东方山寨 {
const std::pair<std::wstring, std::wstring> ca玩家名称[] = {
	{L"en-US", L"Player"},
	{L"zh-CN", L"玩家"},
};
S程序设置 S程序设置::fc系统() {
	S程序设置 v;
	const std::wstring v用户语言 = 视窗::fg用户语言();
	v.m文本语言 = v.m界面语言 = v用户语言;
	using t迭代器 = const std::pair<std::wstring, std::wstring> *;
	const auto f取语言 = [](t迭代器 a)->std::wstring_view {
		return a->first;
	};
	const t迭代器 v找语言 = f找语言<t迭代器>(std::begin(ca玩家名称), std::end(ca玩家名称), f取语言, v用户语言);
	v.m玩家名称 = v找语言->second;
	return v;
}
}	//namespace 东方山寨