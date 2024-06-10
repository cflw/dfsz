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
#include "序列化.h"
export module 东方山寨.录像_文件;
import cflw.文件.zip;
import 东方山寨.录像_结构;
namespace zip = cflw::文件::zip;
namespace json = cflw::文件::json;
namespace 时间 = cflw::时间;
namespace 工具 = cflw::工具;
using namespace std::string_literals;
export namespace 东方山寨 {
inline const std::string c录像文件名 = "replay.json";
enum class E录像读写结果 {
	e成功,
	e未知错误,
	e文件不存在,
	e写入失败,
	e版本不匹配,
	e校验失败,
};
class C录像文件 {
public:
	static E录像读写结果 f打开(const std::filesystem::path &a文件路径, std::shared_ptr<C录像> &a返回, bool a全读取 = true);
	static E录像读写结果 f保存(const std::filesystem::path &a文件路径, C录像 &a录像);
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
E录像读写结果 C录像文件::f打开(const std::filesystem::path &a文件路径, std::shared_ptr<C录像> &a返回, bool a全读取) {
	zip::C提取 v文件;
	if (!v文件.f打开(a文件路径.native())) {
		return E录像读写结果::e文件不存在;
	}
	std::shared_ptr<C录像> v录像 = std::make_shared<C录像>();
	std::u8string v数据;
	v文件.f提取到容器(c录像文件名, v数据);
	const json::t树 v树 = json::f解析数据(v数据);
	//录像信息
	v录像->m录像信息 = json::f解析<S录像信息>(v树.get_child(L"录像信息"));
	if (v录像->m录像信息.m录像版本 != c录像版本) {
		return E录像读写结果::e版本不匹配;	//也有可能是读不到数据
	}
	if (v录像->m录像信息.m关卡数量 > 6) {
		return E录像读写结果::e校验失败;	//关卡太多
	}
	//关卡信息
	for (const auto &[v名称0_, v节点0] : v树.get_child(L"关卡信息")) {
		v录像->ma关卡信息.emplace_back(json::f解析<S录像关卡信息>(v节点0));
	}
	if (a全读取) {
		//帧数据
		for (const S录像关卡信息 &v关卡信息 : v录像->ma关卡信息) {
			const int v关卡 = v关卡信息.m关卡;
			std::vector<S录像帧> v数据;
			v文件.f提取到容器(std::to_string(v关卡), v数据);
			v录像->ma帧数据.emplace(std::pair<int, std::vector<S录像帧>>{v关卡, std::move(v数据)});
		}
	}
	//结束
	v录像->m文件路径 = a文件路径;
	a返回 = std::move(v录像);
	return E录像读写结果::e成功;
}
E录像读写结果 C录像文件::f保存(const std::filesystem::path &a文件路径, C录像 &a录像) {
	//校验数据
	const size_t &v关卡数量 = a录像.m录像信息.m关卡数量;
	if (v关卡数量 != a录像.ma关卡信息.size()) {
		return E录像读写结果::e校验失败;
	}
	for (const auto &v关卡信息 : a录像.ma关卡信息) {
		if (a录像.ma帧数据.at(v关卡信息.m关卡).size() != v关卡信息.m帧数) {
			return E录像读写结果::e校验失败;
		}
	}
	//打开文件
	zip::C归档 v归档;
	if (!v归档.f打开(a文件路径.native())) {
		return E录像读写结果::e写入失败;
	}
	//全局信息
	json::t树 v树;
	const 时间::t时间点 v现在 = 时间::fg现在();
	const time_t v时间戳 = 时间::f时间戳(v现在);
	v树.put<std::wstring>(L"全局.名称", L"录像");
	v树.put<std::wstring>(L"全局.类型", L"游戏录像0");
	v树.put<time_t>(L"全局.标识", v时间戳 & 0x1fffffff);	//随便设一个
	//录像信息
	v树.put_child(L"录像信息", json::f序列化<S录像信息>(a录像.m录像信息));
	//关卡信息
	json::t树 v关卡树组;
	for (size_t i = 0; i != v关卡数量; ++i) {
		v关卡树组.push_back({ L"", json::f序列化<S录像关卡信息>(a录像.ma关卡信息[i]) });
	}
	v树.put_child(L"关卡信息", v关卡树组);
	const auto v数据 = json::f生成数据(v树);
	v归档.f归档从容器(c录像文件名, v数据);
	//帧数据
	for (size_t i = 0; i != v关卡数量; ++i) {
		const int v关卡 = a录像.ma关卡信息.at(i).m关卡;
		v归档.f归档从容器(std::to_string(v关卡), a录像.ma帧数据.at(v关卡));
	}
	//结束
	a录像.m文件路径 = a文件路径;
	return E录像读写结果::e成功;
}
}	//namespace 东方山寨