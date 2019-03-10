#pragma once
#include <string>
#include <memory>
#include <vector>
namespace 东方山寨 {
class C名称标识 {
public:
	static int f解析名称(const std::wstring &名称);
	static void f复制名称标识(const std::wstring &入, const std::wstring &出);
	C名称标识(const std::wstring &名称, int 标识 = 0);
	C名称标识(const std::wstring &名称, int 标识, C名称标识 const*);
	C名称标识(const C名称标识 &) = delete;
	C名称标识(C名称标识 &&);
	~C名称标识();
	void fs名称(const std::wstring &名称);
	C名称标识 f创建层(const std::wstring &名称, int 标识 = 0) const;
	int fg标识() const;
	int fg计算标识() const;
	int fg主标识() const;
	int fg子标识() const;
private:
	void f创建名称标识() const;
	std::wstring m名称;
	std::shared_ptr<std::vector<int>> m标识;
	int m层 = 0;
	bool mi可创建;
};
}