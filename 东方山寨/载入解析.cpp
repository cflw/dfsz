﻿#include "载入解析.h"
#include "程序.h"
#include "游戏.h"
#include "标识.h"
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
		return C程序::f计算路径(*v路径节点, a载入参数.m路径).native();
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

//==============================================================================
// 纹理
//==============================================================================
S解析纹理::operator bool() const {
	return m纹理;
}
const t向量2 &S解析纹理::fg尺寸() const {
	return m纹理->m尺寸;
}
const std::wstring &S解析纹理::fg路径() const {
	return m路径;
}
//解析纹理
C解析纹理::C解析纹理(const S载入参数 &a):
	m载入参数(a),
	m纹理工厂(C游戏::fg资源().fg纹理工厂()) {
}
S解析纹理 C解析纹理::f解析纹理(int a标识, const t属性树 &a树) const {
	S解析纹理 v返回;
	v返回.m路径 = C解析助手::f获取路径(m载入参数, a树);
	if (!v返回.m路径.empty()) {
		v返回.m纹理 = m纹理工厂.f创建纹理(a标识, v返回.m路径);
	}
	return v返回;
}
S解析纹理 C解析纹理::f解析纹理(int a标识, const t可选属性树 &a树) const {
	if (a树) {
		return f解析纹理(a标识, *a树);
	} else {
		return {};
	}
}
}	//namespace 东方山寨