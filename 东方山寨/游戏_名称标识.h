#pragma once
#include <string>
#include <vector>
#include <map>
namespace 东方山寨 {
class C名称标识;
class S名称标识层;
class C名称标识组;
//==============================================================================
// 基础
//==============================================================================
class C名称标识 {	//一个名称标识层的引用,利用生命周期控制标识层次
public:
	C名称标识(C名称标识组 &, const S名称标识层 &);
	C名称标识(const C名称标识 &) = delete;
	C名称标识(C名称标识 &&);
	~C名称标识();
	operator int() const;
	C名称标识 f创建层(const std::wstring &名称, int 标识) const;
	const std::wstring &fg当前名称() const;
	const std::wstring &fg计算名称() const;
	int fg当前标识() const;
	int fg计算标识() const;
	C名称标识组 *m标识组 = nullptr;
	const S名称标识层 *m标识层 = nullptr;
};
class S名称标识层 {	//保存信息
public:
	S名称标识层();
	operator int() const;
	void f重置0(const std::wstring &名称, int 标识);	//第0层
	void f重置1(const S名称标识层 &, const std::wstring &名称, int 标识);	//第1~层
	void f清空();
	std::wstring m当前名称, m计算名称;
	int m当前标识 = -1, m计算标识 = 0;
	bool mi可创建 = false;
};
//==============================================================================
// 组
//==============================================================================
class C名称标识组 {
public:
	static constexpr int c层数 = 4;	//上限
	C名称标识组();
	S名称标识层 &operator [](int 层);
	C名称标识 f创建层(const std::wstring &, int 标识);
	void f弹出层();
	int fg当前层号() const;
	int fg当前层数() const;
	int fg计算标识() const;	//重新计算到当前层的总的标识
	int fg层标识(int 层) const;
	S名称标识层 ma标识[c层数];
	int m当前层数 = 0;
};
//==============================================================================
// 全局名称标识
//==============================================================================
class C全局名称标识 {
public:
	static std::map<std::wstring, int> &fg映射();
	static int f解析(const std::wstring &名称);
	static void f复制(const std::wstring &入, const std::wstring &出);
	static void f创建(const std::wstring &名称, int 标识);
	static std::wstring f连接名称(const std::wstring &, const std::wstring &);
};
}	//namespace 东方山寨