module;
#include <cassert>
#include <filesystem>
#include <cflw视窗.h>
export module 东方山寨.文件系统;
using namespace std::filesystem;
namespace 视窗 = cflw::视窗;
export namespace 东方山寨::文件系统 {
const path &fg资产目录();
const path &fg临时目录();
const path &fg用户目录();
path f计算路径(const path &a目标路径, const path &a当前文件 = L"");
}	//namespace 东方山寨::文件系统
module: private;
namespace 东方山寨::文件系统 {
const path &fg资产目录() {	//当前目录/assets
	static const path v资产目录 = current_path() / L"assets";
	assert(exists(v资产目录));
	return v资产目录;
}
const path &fg临时目录() {	//%temp%\dfsz
	static const path v临时目录 = []()->path {
		path v路径 = 视窗::fg环境变量(L"temp");
		v路径 /= L"dfsz";
		if (!exists(v路径)) {
			create_directories(v路径);
		}
		return v路径;
	}();
	return v临时目录;
}
const path &fg用户目录() {	//%appdata%\dfsz
	static const path v用户目录 = []()->path {
		path v路径 = 视窗::fg环境变量(L"appdata");
		v路径 /= L"dfsz";
		if (!exists(v路径)) {
			create_directories(v路径);
		}
		return v路径;
	}();
	return v用户目录;
}
path f计算路径(const path &a目标路径, const path &a当前文件) {
	const path v数据路径 = path(a目标路径).make_preferred();
	const std::wstring v数据字符串 = v数据路径.native();
	if (const size_t v位置 = v数据字符串.find(std::wstring(L"~") + path::preferred_separator); v位置 == 0) {	//使用资产目录
		return (fg资产目录() / v数据字符串.substr(2)).lexically_normal();
	} else if (a当前文件.empty()) {	//使用程序目录
		return (current_path() / v数据路径).lexically_normal();
	} else {	//使用当前文件目录
		const path v当前目录 = a当前文件.parent_path();
		return (v当前目录 / v数据路径).lexically_normal();
	}
}
}	//namespace 东方山寨::文件系统