#pragma once
#include <string>
#include <filesystem>
#include <boost/property_tree/ptree.hpp>
namespace 东方山寨 {
class C程序设置 {
public:
	static const std::wstring c程序设置文件名;
	static const std::wstring c游戏设置文件名;
	static const std::filesystem::path c设置文件目录;
	static const std::filesystem::path c程序设置文件路径;
	static const std::filesystem::path c游戏设置文件路径;
	static C程序设置 &fg这();
	void f初始设置();	//在 f打开设置 失败后调用
	bool f打开设置();
	bool f保存设置();
	const std::wstring &fg文本语言() const;
	const std::wstring &fg界面语言() const;
public:
	bool f打开程序设置();
	bool f打开游戏设置();
	bool f保存程序设置();
	bool f保存游戏设置();
	bool mi保存程序设置 = true, mi保存游戏设置 = true;	//保存指示,不修改不保存
	boost::property_tree::wptree m程序设置树, m游戏设置树;
	std::wstring m玩家名称;
	std::wstring m文本语言;
	std::wstring m界面语言;
};
}