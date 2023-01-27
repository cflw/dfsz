#include <cflw视窗.h>
#include "程序设置.h"
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
	const auto vf找 = [&](const std::pair<std::wstring, std::wstring> &a)->bool {
		return a.first == v用户语言;
	};
	if (const auto v找 = std::find_if(std::begin(ca玩家名称), std::end(ca玩家名称), vf找); v找 != std::end(ca玩家名称)) {
		v.m玩家名称 = v找->second;
	} else {
		v.m玩家名称 = ca玩家名称[0].second;
	}
	return v;
}
}	//namespace 东方山寨