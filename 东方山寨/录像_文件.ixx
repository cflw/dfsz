module;
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <string>
#include <cflw时间.h>
#include "游戏设置.h"
#include "玩家.h"
export module 东方山寨.录像_文件;
import cflw.文件.二进制;
import 东方山寨.录像_结构;
namespace 二进制 = cflw::文件::二进制;
namespace 时间 = cflw::时间;
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
	static int f打开(const std::wstring &a文件名, std::unique_ptr<C录像> &a返回) {
		二进制::C读 v文件;
		if (v文件.f打开(a文件名)) {
			return (int)E录像读写结果::e文件不存在;
		}
		std::unique_ptr<C录像> v录像 = std::make_unique<C录像>();
		//录像信息
		v录像->m录像信息.m录像版本 = v文件.f读值<int>();
		if (v录像->m录像信息.m录像版本 != c录像版本) {
			return (int)E录像读写结果::e版本不匹配;
		}
		v录像->m录像信息.m游戏版本 = v文件.f读值<int>();
		v录像->m录像信息.m玩家名称 = v文件.f读动态数组<std::wstring>();
		v录像->m录像信息.m开始时间 = v文件.f读值<时间::t时间点>();
		v录像->m录像信息.m结束时间 = v文件.f读值<时间::t时间点>();
		v录像->m录像信息.m关卡数量 = v文件.f读值<size_t>();
		//关卡信息
		for (size_t i = 0; i != v录像->m录像信息.m关卡数量; ++i) {
			S关卡信息 &v关卡信息 = v录像->m关卡信息.emplace_back();
			v关卡信息 = v文件.f读值<S关卡信息>();
		}
		//关卡数据
		for (size_t i = 0; i != v录像->m录像信息.m关卡数量; ++i) {
			const int v关卡 = v文件.f读值<int>();
			std::vector<S录像帧> v数据 = v文件.f读动态数组<std::vector<S录像帧>>();
			v录像->m关卡数据.emplace(std::pair<int, std::vector<S录像帧>>{v关卡, std::move(v数据)});
		}
		//结束
		a返回 = std::move(v录像);
		return (int)E录像读写结果::e成功;
	}
	static int f保存(const std::wstring &a文件名, const C录像 &a录像) {
		//校验数据
		if (a录像.m录像信息.m关卡数量 != a录像.m关卡信息.size()) {
			return (int)E录像读写结果::e校验失败;
		}
		for (const auto &v关卡信息 : a录像.m关卡信息) {
			if (a录像.m关卡数据.at(v关卡信息.m关卡).size() != v关卡信息.m帧数) {
				return (int)E录像读写结果::e校验失败;
			}
		}
		//打开文件
		二进制::C写 v文件;
		if (!v文件.f打开(a文件名)) {
			return (int)E录像读写结果::e写入失败;
		}
		//录像信息
		v文件.f写值(a录像.m录像信息.m录像版本);
		v文件.f写值(a录像.m录像信息.m游戏版本);
		v文件.f写动态数组(a录像.m录像信息.m玩家名称);
		v文件.f写值(a录像.m录像信息.m开始时间);
		v文件.f写值(a录像.m录像信息.m结束时间);
		v文件.f写值(a录像.m录像信息.m关卡数量);
		v文件.f写值(a录像.m录像信息.m游戏设置);
		//关卡信息
		for (size_t i = 0; i != a录像.m录像信息.m关卡数量; ++i) {
			v文件.f写值(a录像.m关卡信息.at(i));
		}
		//关卡数据
		for (size_t i = 0; i != a录像.m录像信息.m关卡数量; ++i) {
			const int v关卡 = a录像.m关卡信息.at(i).m关卡;
			v文件.f写值(v关卡);
			v文件.f写动态数组(a录像.m关卡数据.at(v关卡));
		}
		//结束
		return (int)E录像读写结果::e成功;
	}
};
}	//namespace 东方山寨