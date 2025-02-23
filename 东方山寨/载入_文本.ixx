module;
#include "载入.h"
#include "标识.h"
#include "取文本.h"
export module 东方山寨.载入.文本;
import cflw.字符串;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import 东方山寨.文本管理;
namespace 字符串 = cflw::字符串;
namespace 东方山寨::xml {
void C载入::f文本(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = 计算::fc随机标识();
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	const std::wstring v语言 = v头部节点.child(L"语言").text().as_string();
	const std::wstring v显示语言 = v头部节点.child(L"显示语言").text().as_string();
	auto &va文本 = C文本管理::fg实例().f新文本数组(v全局名称, v语言, v显示语言);
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(计算::f文本语言前缀(v全局名称, v语言), v全局标识);
	int v主标识 = -1;
	for (const t节点 &v文本节点 : a参数.m根.child(L"数据").children(L"文本")) {
		const std::wstring v名称0 = v文本节点.attribute(L"名称").as_string();
		const std::wstring v文本 = v文本节点.text().as_string();
		if (字符串::fi整数(v名称0)) {
			va文本.f添加(_wtoi(v名称0.data()), v文本);
		} else {
			const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识, true);
			va文本.f添加(v名称标识1, v文本);
		}
	}
}
}	//namespace 东方山寨