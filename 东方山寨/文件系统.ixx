module;
#include <cassert>
#include <filesystem>
#include <cflw视窗.h>
export module 东方山寨.文件系统;
using namespace std::filesystem;
namespace 视窗 = cflw::视窗;
export namespace 东方山寨::文件系统 {
const path &fg数据目录() {
	static const path v数据目录 = []()->path {
		const path v当前目录 = current_path();
		const path v上级目录 = v当前目录.parent_path();
		if (const path v目录名 = v上级目录.filename(); v目录名 == L"~") {
			return v上级目录;
		}
		return v当前目录 / L"~";
	}();
	assert(exists(v数据目录));
	return v数据目录;
}
const path &fg临时目录() {	//%temp%\cflw
	static const path v临时目录 = []()->path {
		path v路径 = 视窗::fg环境变量(L"temp");
		v路径 /= L"cflw";
		if (!exists(v路径)) {
			create_directories(v路径);
		}
		return v路径;
	}();
	return v临时目录;
}
const path &fg用户目录() {	//%appdata%\cflw
	static const path v用户目录 = []()->path {
		path v路径 = 视窗::fg环境变量(L"appdata");
		v路径 /= L"cflw";
		if (!exists(v路径)) {
			create_directories(v路径);
		}
		return v路径;
	}();
	return v用户目录;
}
path f计算路径(const path &a目标路径, const path &a当前文件 = L"") {
	const path v数据路径 = path(a目标路径).make_preferred();
	const std::wstring v数据字符串 = v数据路径.native();
	if (a当前文件.empty()) {
		return (current_path() / v数据路径).lexically_normal();
	} else if (const size_t v位置 = v数据字符串.find(std::wstring(L"~") + path::preferred_separator); v位置 == 0) {
		return (fg数据目录() / v数据字符串.substr(2)).lexically_normal();
	} else {
		const path v当前目录 = a当前文件.parent_path();
		return (v当前目录 / v数据路径).lexically_normal();
	}
}
}	//namespace 东方山寨::文件系统