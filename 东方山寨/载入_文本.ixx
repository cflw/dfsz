module;
#include "载入.h"
#include "标识.h"
#include "取文本.h"
module 东方山寨.载入.文本;
import cflw.字符串;
import 东方山寨.文本管理;
namespace 字符串 = cflw::字符串;
namespace 东方山寨::载入 {
void C载入::f文本(const S载入参数 &a) {
	const int v全局标识 = 计算::fc随机标识();
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	const std::wstring v语言 = a.m树.get<std::wstring>(L"全局.语言");
	const std::wstring v显示语言 = a.m树.get<std::wstring>(L"全局.显示语言");
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va文本 = C文本管理::fg实例().f新文本数组(v全局名称, v语言, v显示语言);
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(计算::f文本语言前缀(v全局名称, v语言), v全局标识);
	int v主标识 = -1;
	for (const auto &[v名称0, v树0] : va数据) {
		const std::wstring &v文本 = v树0.get_value<std::wstring>();
		if (字符串::fi整数(v名称0)) {
			va文本.f添加(_wtoi(v名称0.data()), v文本);
		} else {
			const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识, true);
			va文本.f添加(v名称标识1, v文本);
		}
	}
}
}	//namespace 东方山寨