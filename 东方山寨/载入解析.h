#pragma once
#include "载入基础.h"
#include "图形资源工厂.h"
namespace 东方山寨::载入 {
//==============================================================================
// 结构
//==============================================================================
class C解析助手 {
public:
	static t向量2 f获取向量2(const t属性树 &a节点);
	static t向量2 f获取向量3(const t属性树 &a节点);
	static t向量2 f获取纹理坐标(const t属性树 &a节点);
	static t向量2 f获取尺寸(const t属性树 &a节点);
	static std::wstring f获取路径(const S载入参数 &a载入参数, const t属性树 &a节点);
};
//==============================================================================
// 引用
//==============================================================================
class C解析引用 {
public:
	C解析引用(int a引用, bool a存在 = true);
	template<typename t>
	static void f解析赋值(t &a, const C解析引用 &a全局引用, const t可选属性树 &a树);
	template<typename t>
	static void f解析名称赋值(t &a, const t可选属性树 &a树);
	operator bool() const;
	std::wstring f解析名称标识(const t属性树 &a树) const;
	C解析引用 f解析数字标识(const t属性树 &a树) const;
	bool fi存在() const;
	int fg值() const;
private:
	int m引用;	//全局标识
	bool m存在;	//?
};
template<typename t>
void C解析引用::f解析赋值(t &a, const C解析引用 &a全局引用, const t可选属性树 &a树) {
	if (a树) {
		if (const std::wstring v名称 = a全局引用.f解析名称标识(*a树); !v名称.empty()) {
			a = v名称;
		} else if (const auto &v引用 = a全局引用.f解析数字标识(*a树)) {
			a = v引用.fg值();
		} else {
			a = 0;
		}
	} else {
		a = 0;
	}
}
template<typename t>
void C解析引用::f解析名称赋值(t &a, const t可选属性树 &a树) {
	if (a树) {
		if (const auto &v名称标识 = a树->get_optional<std::wstring>(L"名称")) {
			a = *v名称标识;
		} else {
			a = 0;
		}
	} else {
		a = 0;
	}
}
//==============================================================================
// 纹理
//==============================================================================
struct S解析纹理 {
	operator bool() const;
	const t向量2 &fg尺寸() const;
	const std::wstring &fg路径() const;
	const S纹理 *m纹理 = nullptr;
	std::wstring m路径;	//全路径
};
class C解析纹理 {
public:
	C解析纹理(const S载入参数 &);
	S解析纹理 f解析纹理(int 标识, const t属性树 &) const;
	S解析纹理 f解析纹理(int 标识, const t可选属性树 &) const;
	const S载入参数 &m载入参数;
	const C纹理工厂 &m纹理工厂;
};
}	//namespace 东方山寨