module;
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <string>
#include <filesystem>
#include <cflw时间.h>
#include <cflw工具_运算.h>
#include "游戏设置.h"
#include "玩家.h"
export module 东方山寨.录像_文件;
import cflw.文件.二进制;
import 东方山寨.录像_结构;
namespace 二进制 = cflw::文件::二进制;
namespace 时间 = cflw::时间;
namespace 工具 = cflw::工具;
using namespace std::string_literals;
export namespace 东方山寨 {
enum class E录像读写结果 {
	e成功,
	e文件不存在,
	e写入失败,
	e版本不匹配,
	e校验失败,
};
class C录像文件 {
public:
	static E录像读写结果 f打开(const std::filesystem::path &a文件路径, std::shared_ptr<C录像> &a返回, bool a全读取 = true) {
		二进制::C读 v文件;
		if (!v文件.f打开(a文件路径.native())) {
			return E录像读写结果::e文件不存在;
		}
		std::shared_ptr<C录像> v录像 = std::make_shared<C录像>();
		//录像信息
		v录像->m录像信息.m录像版本 = v文件.f读值<int>(0);
		if (v录像->m录像信息.m录像版本 != c录像版本) {
			return E录像读写结果::e版本不匹配;	//也有可能是读不到数据
		}
		v录像->m录像信息.m游戏版本 = v文件.f读值<int>();
		v录像->m录像信息.m录像标题 = v文件.f读动态数组<std::wstring>(工具::F小于值<size_t>(32));
		v录像->m录像信息.m玩家名称 = v文件.f读动态数组<std::wstring>(工具::F小于值<size_t>(32));
		v录像->m录像信息.m开始时间 = v文件.f读值<时间::t时间点>();
		v录像->m录像信息.m结束时间 = v文件.f读值<时间::t时间点>();
		v录像->m录像信息.m关卡数量 = v文件.f读值<size_t>();
		if (v录像->m录像信息.m关卡数量 > 6) {
			return E录像读写结果::e校验失败;	//关卡太多
		}
		v录像->m录像信息.m游戏设置 = v文件.f读值<S游戏设置>();
		//关卡信息
		for (size_t i = 0; i != v录像->m录像信息.m关卡数量; ++i) {
			v录像->ma关卡信息.emplace_back(v文件.f读值<S关卡信息>());
		}
		if (a全读取) {
			//帧数据
			for (size_t i = 0; i != v录像->m录像信息.m关卡数量; ++i) {
				const int v关卡 = v文件.f读值<int>();
				const size_t &v帧数 = v录像->ma关卡信息[i].m帧数;
				std::vector<S录像帧> v数据 = v文件.f读动态数组<std::vector<S录像帧>>(工具::F等于值(v帧数));
				v录像->ma帧数据.emplace(std::pair<int, std::vector<S录像帧>>{v关卡, std::move(v数据)});
			}
		}
		//结束
		v录像->m文件路径 = a文件路径;
		a返回 = std::move(v录像);
		return E录像读写结果::e成功;
	}
	static E录像读写结果 f保存(const std::filesystem::path &a文件路径, C录像 &a录像) {
		//校验数据
		if (a录像.m录像信息.m关卡数量 != a录像.ma关卡信息.size()) {
			return E录像读写结果::e校验失败;
		}
		for (const auto &v关卡信息 : a录像.ma关卡信息) {
			if (a录像.ma帧数据.at(v关卡信息.m关卡).size() != v关卡信息.m帧数) {
				return E录像读写结果::e校验失败;
			}
		}
		//打开文件
		二进制::C写 v文件;
		if (!v文件.f打开(a文件路径.native())) {
			return E录像读写结果::e写入失败;
		}
		//录像信息
		const 时间::t时间点 v现在 = 时间::fg现在();
		v文件.f写值<int>(a录像.m录像信息.m录像版本);
		v文件.f写值<int>(a录像.m录像信息.m游戏版本);
		const std::wstring &v录像标题 = !a录像.m录像信息.m录像标题.empty() ? a录像.m录像信息.m录像标题 : (L"自动录像"s + std::format(c紧凑时间格式, 时间::f本地时间(v现在)));
		v文件.f写动态数组<std::wstring>(v录像标题);
		v文件.f写动态数组<std::wstring>(a录像.m录像信息.m玩家名称);
		v文件.f写值<时间::t时间点>(a录像.m录像信息.m开始时间);
		const 时间::t时间点 v结束时间 = (a录像.m录像信息.m结束时间 != a录像.m录像信息.m开始时间) ? a录像.m录像信息.m结束时间 : v现在;
		v文件.f写值<时间::t时间点>(v结束时间);
		const size_t v关卡数量 = a录像.ma关卡信息.size();
		v文件.f写值<size_t>(v关卡数量);
		v文件.f写值<S游戏设置>(a录像.m录像信息.m游戏设置);
		//关卡信息
		for (size_t i = 0; i != v关卡数量; ++i) {
			v文件.f写值<S关卡信息>(a录像.ma关卡信息.at(i));
		}
		//帧数据
		for (size_t i = 0; i != v关卡数量; ++i) {
			const int v关卡 = a录像.ma关卡信息.at(i).m关卡;
			v文件.f写值<int>(v关卡);
			v文件.f写动态数组<std::vector<S录像帧>>(a录像.ma帧数据.at(v关卡));
		}
		//结束
		a录像.m文件路径 = a文件路径;
		return E录像读写结果::e成功;
	}
};
}	//namespace 东方山寨