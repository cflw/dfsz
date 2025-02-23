module;
#include <cassert>
#include <string>
#include <map>
#include <pugixml.hpp>	//pugixml
#include "标识.h"
export module 东方山寨.载入.xml;
import cflw.文件.文本;
import 东方山寨.文件系统;
export namespace 东方山寨::xml {
using t路径 = std::filesystem::path;
using t文档 = pugi::xml_document;
using t结果 = pugi::xml_parse_result;
using t节点 = pugi::xml_node;
using t属性 = pugi::xml_attribute;
struct S载入参数 {
	const t节点 &m根;	//根节点
	const t路径 &m路径;	//xml文件路径
};
class C读取 {
public:
	static bool f读取0(t文档 &, const t路径 &);	//不计算路径
	static bool f读取(t文档 &, const t路径 &);
	static bool f读取(t文档 &, const S载入参数 &, const t路径 &, t路径 &);
};
class C载入 {
public:
	typedef void(*tf载入数据)(const S载入参数 &);
	static void f汇总(const S载入参数 &);
	static void f子弹(const S载入参数 &);
	static void f图形(const S载入参数 &);
	static void f动画(const S载入参数 &);
	static void f自机(const S载入参数 &);
	static void f敌机(const S载入参数 &);
	static void f子机(const S载入参数 &);
	static void f玩家子弹(const S载入参数 &);
	static void f纹理(const S载入参数 &);
	static void f模型(const S载入参数 &);
	static void f音效(const S载入参数 &);
	static void f音乐(const S载入参数 &);
	static void f文本(const S载入参数 &);
	static void f立绘(const S载入参数 &);
};
namespace 解析 {	//解析具体节点
template<typename t>
void f引用赋值(t &a输出, const int a全局引用, const t节点 &a节点) {
	const std::wstring_view v方法 = a节点.attribute(L"方法").as_string();
	if (v方法 == L"名称") {
		const std::wstring v名称 = a节点.text().as_string();
		a输出 = v名称;
	} else if (v方法 == L"标识") {
		const bool v绝对 = a节点.attribute(L"绝对").as_bool();
		const int v标识 = a节点.text().as_int();
		if (v绝对) {
			a输出 = v标识;
		} else {
			a输出 = 计算::f标识(a全局引用, v标识, 0);
		}
	}
}
std::wstring f路径(const S载入参数 &, const t节点 &);
}	//namespace 解析
}	//namespace 东方山寨::xml
module: private;
namespace 东方山寨::xml {
//==============================================================================
// 读取
//==============================================================================
bool C读取::f读取0(t文档 &a文档, const t路径 &a路径) {
	std::wstring v文本 = cflw::文件::文本::f读取文件<char8_t, wchar_t>(a路径);
	if (v文本.empty()) {
		return false;
	}
	t结果 v结果 = a文档.load_string(v文本.c_str());
	if (!v结果) {
		return false;
	}
	return true;
}
bool C读取::f读取(t文档 &a文档, const t路径 &a路径) {
	const t路径 v路径 = 文件系统::f计算路径(a路径, L"");
	return f读取0(a文档, v路径);
}
bool C读取::f读取(t文档 &a文档, const S载入参数 &a参数, const t路径 &a路径, t路径 &a输出路径) {
	a输出路径 = 文件系统::f计算路径(a路径, a参数.m路径);
	return f读取0(a文档, a输出路径);
}
//==============================================================================
// 载入
//==============================================================================
void C载入::f汇总(const S载入参数 &a参数) {
	static const std::map<std::wstring, tf载入数据> v载入函数{
		{L"载入列表0", f汇总},
		{L"图形", f图形},
		{L"动画", f动画},
		{L"敌人子弹", f子弹},
		{L"敌人飞机", f敌机},
		{L"玩家飞机", f自机},
		{L"玩家子机", f子机},
		{L"玩家子弹", f玩家子弹},
		{L"纹理", f纹理},
		{L"模型", f模型},
		{L"音效", f音效},
		{L"音乐", f音乐},
		{L"文本", f文本},
		{L"立绘", f立绘},
	};
	const t节点 &v数据 = a参数.m根.child(L"数据");
	for (const t节点 &v文件 : v数据.children(L"文件")) {
		const std::wstring_view &v文件名 = v文件.child_value();
		t文档 v文档;
		t路径 v路径;
		const bool v读取结果 = C读取::f读取(v文档, a参数, v文件名, v路径);
		if (!v读取结果) {
			throw;
		}
		const t节点 &v根 = v文档.child(L"根");
		const std::wstring &v类型 = v根.child(L"头部").attribute(L"类型").as_string();
		if (v类型.empty()) {
			throw;
		}
		v载入函数.at(v类型)(S载入参数{v根, v路径});
	}
}
//==============================================================================
// 解析
//==============================================================================
namespace 解析 {
std::wstring f路径(const S载入参数 &a参数, const t节点 &a路径节点) {
	const std::wstring_view &v路径 = a路径节点.child_value();
	assert(!v路径.empty());	//必需有值
	return 文件系统::f计算路径(v路径, a参数.m路径).native();
}
}	//namespace 解析
}	//namespace 东方山寨::xml