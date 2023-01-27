module;
#include <string>
#include <memory>
#include <chrono>
#include <format>
#include <filesystem>
#include <cflw时间.h>
#include "程序.h"
#include "游戏.h"
#include "程序设置.h"
#include "游戏设置.h"
export module 东方山寨.游戏录像管理;
import cflw.工具.单例;
import 东方山寨.录像_结构;
export import 东方山寨.录像_功能;
import 东方山寨.录像_文件;
import 东方山寨.设置管理;
import 东方山寨.文件系统;
namespace 时间 = cflw::时间;
namespace 工具 = cflw::工具;
using namespace std::string_literals;
export namespace 东方山寨 {
inline const std::filesystem::path c录像目录 = 文件系统::fg用户目录();
//==============================================================================
// 游戏录像管理
//==============================================================================
class C游戏录像管理 : public 工具::C弱单例<C游戏录像管理> {	//管理录像文件和正在录制的录像
public:
	//函数
	C游戏录像管理() = default;
	C录像机 &f新建录像() {	//在进入游戏前调用
		m录像.f新建录像(C设置管理::fg实例().fg程序设置(), C设置管理::fg实例().fg游戏设置());
		return m录像;
	}
	void f保存录像() {	//保存当前录制的录像
		m录像.f结束录像();
		const auto v路径 = c录像目录 / f自动录像文件名();
		C录像文件::f保存(v路径, *m录像.m录像);
	}
	static std::wstring f自动录像文件名() {
		return std::format(c紧凑时间格式, 时间::f本地秒(时间::fg本地现在())) + L".zip"s;
	}
	std::shared_ptr<C录像> f打开录像(const std::filesystem::path &a文件名, bool a完整 = true, bool a缓存 = true) {	//读取录像,返回录像
		if (a缓存) {
			if (auto v找 = ma缓存.find(a文件名.native()); v找 != ma缓存.end()) {	//查找缓存
				if (auto &[v路径, vp录像] = *v找; vp录像->fi完整数据() || !a完整) {	//录像完整 或 不需要完整数据
					return vp录像;
				} else {	//需要完整读取
					if (C录像文件::f打开(v路径, vp录像, a完整) == E录像读写结果::e成功) {
						return vp录像;
					} else {
						return nullptr;
					}
				}
			}
		}
		//计算路径
		const auto v路径 = a文件名.is_absolute() ? a文件名 : (c录像目录 / a文件名);
		//打开录像
		std::shared_ptr<C录像> v录像;
		if (C录像文件::f打开(v路径, v录像, a完整) == E录像读写结果::e成功) {
			ma缓存.emplace(a文件名, v录像);
		}
		return v录像;
	}
	E录像读写结果 f完整打开录像(std::shared_ptr<C录像> &ap录像) {	//重新载入录像
		return C录像文件::f打开(ap录像->m文件路径, ap录像, true);
	}
	C回放机 &f回放录像(const std::shared_ptr<C录像> &a录像) {
		m回放.m录像 = a录像;
		return m回放;
	}
	//录像摘要
	void f增量刷新() {
		//扫描录像目录
		//对比文件差异.只记录新增,减少的要全量刷新
		//打开录像
	}
	void f全量刷新() {
		//清空录像列表,扫描录像目录,打开录像
		ma摘要.clear();
		std::vector<std::filesystem::directory_entry> va文件;
		int i = 0;
		for (const auto &v目录条目 : std::filesystem::directory_iterator(c录像目录)) {
			const auto &v文件名 = v目录条目.path();
			if (v文件名.extension() == L".zip") {
				const auto vp录像 = f打开录像(v文件名, false);
				if (vp录像) {
					ma摘要.emplace(++i, vp录像);
				}
			}
		}
	}
	//变量
	C录像机 m录像;	//正在录制的录像
	C回放机 m回放;	//正在回放的录像
	std::map<std::wstring, std::shared_ptr<C录像>> ma缓存;	//录像缓存,文件名和读取的录像
	bool m读取中 = false;
	std::thread m线程_刷新列表;
	std::map<int, std::shared_ptr<C录像>> ma摘要;	//扫描录像目录得到的录像列表,键是文件名顺序
};
}	//namespace 东方山寨