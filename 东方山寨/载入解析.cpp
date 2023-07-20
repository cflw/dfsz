#include "载入解析.h"
#include "游戏.h"
#include "标识.h"
import 东方山寨.文件系统;
namespace 东方山寨::载入 {
//==============================================================================
// 常见结构
//==============================================================================
t向量2 C解析助手::f获取向量2(const t属性树 &a节点) {
	const float x = a节点.get<float>(L"x", 0);
	const float y = a节点.get<float>(L"y", 0);
	return t向量2{x, y};
}
t向量2 C解析助手::f获取向量3(const t属性树 &a节点) {
	const float x = a节点.get<float>(L"x", 0);
	const float y = a节点.get<float>(L"y", 0);
	const float z = a节点.get<float>(L"z", 0);
	return t向量2{x, y};
}
t向量2 C解析助手::f获取纹理坐标(const t属性树 &a节点) {
	const float x = a节点.get<float>(L"u", 0);
	const float y = a节点.get<float>(L"v", 0);
	return t向量2{x, y};
}
t向量2 C解析助手::f获取尺寸(const t属性树 &a节点) {
	const float x = a节点.get<float>(L"宽", 0);
	const float y = a节点.get<float>(L"高", 0);
	return t向量2{x, y};
}
std::wstring C解析助手::f获取路径(const S载入参数 &a载入参数, const t属性树 &a节点) {
	if (const auto &v路径节点 = a节点.get_optional<std::wstring>(L"路径")) {
		return 文件系统::f计算路径(*v路径节点, a载入参数.m路径).native();
	}
	return L"";
}
//==============================================================================
// 引用
//==============================================================================
C解析引用::C解析引用(int a引用, bool a存在):
	m引用(a引用),
	m存在(a存在) {
}
C解析引用::operator bool() const {
	return fi存在();
}
std::wstring C解析引用::f解析名称标识(const t属性树 &a树) const {
	if (const auto &v名称标识 = a树.get_optional<std::wstring>(L"名称")) {
		return *v名称标识;
	} else {
		return L"";
	}
}
C解析引用 C解析引用::f解析数字标识(const t属性树 &a树) const {
	bool v存在 = false;
	int v引用 = 0;
	int v子引用 = 0;
	if (const auto &v引用节点 = a树.get_optional<int>(L"标识")) {
		v引用 = *v引用节点;
		v存在 = true;
	}
	if (const auto &v子引用节点 = a树.get_optional<int>(L"子标识")) {
		v子引用 = *v子引用节点;
		v存在 = true;
	}
	if (a树.get<bool>(L"绝对", false)) {
		return {计算::f标识(v引用, 0, v子引用), v存在};
	} else {
		return {计算::f标识(m引用, v引用, v子引用), v存在};
	}
}
bool C解析引用::fi存在() const {
	return m存在;
}
int C解析引用::fg值() const {
	return m引用;
}
}	//namespace 东方山寨