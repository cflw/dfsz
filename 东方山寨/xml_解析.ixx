module;
#include <string>
#include <tuple>
#include <boost/rational.hpp>
#include <pugixml.hpp>	//pugixml
#include <cflw时间.h>
#include "数学包含.h"
#include "游戏设置.h"
#include "玩家成绩.h"
export module 东方山寨.xml.解析;
export import cflw.字符串.数字;
import 东方山寨.录像_结构;
namespace 时间 = cflw::时间;
namespace 字符串 = cflw::字符串;
namespace 东方山寨 {
struct S游戏设置;
struct S录像信息;
struct S录像关卡信息;
struct S玩家成绩;
}	//namespace 东方山寨
export namespace 东方山寨::xml {
using t文档 = pugi::xml_document;
using t结果 = pugi::xml_parse_result;
using t节点 = pugi::xml_node;
using t属性 = pugi::xml_attribute;
namespace 解析 {
template<typename t0, typename t1>
std::tuple<t0, t1> f二元组(const t节点 &a节点, const std::tuple<t0, t1> &a默认值 = {}) {	//分割带逗号的数据
	static_assert(std::is_arithmetic_v<t0> && std::is_arithmetic_v<t1>);
	if (a节点.empty()) {
		return a默认值;
	}
	const std::wstring_view v文本 = a节点.child_value();
	const size_t v逗号位置 = v文本.find(L',');
	if (v逗号位置 == std::wstring_view::npos) {
		return std::make_tuple<t0, t1>(
			字符串::f到数字<t0>(v文本),
			+std::get<1>(a默认值)
		);
	} else {
		const std::wstring_view v文本0 = v文本.substr(0, v逗号位置);
		const std::wstring_view v文本1 = v文本.substr(v逗号位置 + 1);
		return std::make_tuple<t0, t1>(
			字符串::f到数字<t0>(v文本0),
			字符串::f到数字<t1>(v文本1)
		);
	}
}
template<typename t0, typename t1, typename t2>
std::tuple<t0, t1, t2> f三元组(const t节点 &a节点, const std::tuple<t0, t1, t2> &a默认值 = {}) {
	static_assert(std::is_arithmetic_v<t0> && std::is_arithmetic_v<t1> && std::is_arithmetic_v<t2>);
	if (a节点.empty()) {
		return a默认值;
	}
	const std::wstring_view v文本 = a节点.child_value();
	const size_t v逗号位置0 = v文本.find(L",");
	if (v逗号位置0 == std::wstring_view::npos) {	//无逗号
		return std::make_tuple<t0, t1, t2>(
			字符串::f到数字<t0>(v文本),
			+std::get<1>(a默认值),
			+std::get<2>(a默认值)
		);
	} else {
		const std::wstring_view v文本0 = v文本.substr(0, v逗号位置0);
		const size_t v逗号位置1 = v文本.find(L",", v逗号位置0 + 1);
		if (v逗号位置1 == std::wstring_view::npos) {	//1个逗号
			const std::wstring_view v文本1 = v文本.substr(v逗号位置0 + 1);
			return std::make_tuple<t0, t1, t2>(
				字符串::f到数字<t0>(v文本0),
				字符串::f到数字<t1>(v文本1),
				+std::get<2>(a默认值)
			);
		} else {	//2个逗号
			const std::wstring_view v文本1 = v文本.substr(v逗号位置0 + 1, v逗号位置1 - v逗号位置0 - 1);
			const std::wstring_view v文本2 = v文本.substr(v逗号位置1 + 1);
			return std::make_tuple<t0, t1, t2>(
				字符串::f到数字<t0>(v文本0),
				字符串::f到数字<t1>(v文本1),
				字符串::f到数字<t2>(v文本2)
			);
		}
	}
}
t向量2 f向量2(const t节点 &, const t向量2 &默认值 = t向量2::c零);
t向量3 f向量3(const t节点 &, const t向量3 &默认值 = t向量3::c零);
时间::t本地时间 f时间(const t节点 &);
boost::rational<int> f分数(const t节点 &);
S游戏设置 f游戏设置(const t节点 &);
S录像信息 f录像信息(const t节点 &);
S录像关卡信息 f录像关卡信息(const t节点 &);
S玩家成绩 f玩家成绩(const t节点 &);
}	//namespace 解析
}	//namespace 东方山寨::xml
module: private;
namespace 东方山寨::xml {
namespace 解析 {
t向量2 f向量2(const t节点 &a向量节点, const t向量2 &a默认值) {
	const auto &[x, y] = f二元组<float, float>(a向量节点, {a默认值.x, a默认值.y});
	return t向量2{x, y};
}
t向量3 f向量3(const t节点 &a向量节点, const t向量3 &a默认值) {
	const auto &[x, y, z] = f三元组<float, float, float>(a向量节点, {a默认值.x, a默认值.y, a默认值.z});
	return t向量3{x, y, z};
}
时间::t本地时间 f时间(const t节点 &a时间节点) {
	const time_t v时间值 = a时间节点.text().as_llong();
	return 时间::f本地时间(v时间值);
}
boost::rational<int> f分数(const t节点 &a节点) {
	if (a节点.empty()) {
		return {0, 1};
	}
	const std::wstring_view v文本 = a节点.text().as_string();
	const size_t v斜杠位置 = v文本.find(L'/');
	if (v斜杠位置 == std::wstring_view::npos) {
		const int v分子 = 字符串::f到数字<int>(v文本);
		return {v分子, 1};
	} else {
		const int v分子 = 字符串::f到数字<int>(v文本.substr(0, v斜杠位置));
		const int v分母 = 字符串::f到数字<int>(v文本.substr(v斜杠位置+1));
		return {v分子, v分母};
	}
}
S游戏设置 f游戏设置(const t节点 &a节点) {
	东方山寨::S游戏设置 v;
	v.m自机标识 = a节点.child(L"自机标识").text().as_int();
	v.m子机标识 = a节点.child(L"子机标识").text().as_int();
	v.m炸弹标识 = a节点.child(L"炸弹标识").text().as_int();
	v.m残机 = a节点.child(L"残机").text().as_int();
	v.m炸弹 = a节点.child(L"炸弹").text().as_int();
	v.m火力 = a节点.child(L"火力").text().as_int();
	v.m最大点 = a节点.child(L"最大点").text().as_int();
	v.m基础难度 = a节点.child(L"基础难度").text().as_int();
	v.m增加难度 = a节点.child(L"增加难度").text().as_int();
	v.m关卡 = a节点.child(L"关卡").text().as_int();
	v.m关卡组 = a节点.child(L"关卡组").text().as_int();
	v.m游戏模式 = (东方山寨::E游戏模式)a节点.child(L"游戏模式").text().as_int();
	return v;

}
S录像信息 f录像信息(const t节点 &a节点) {
	东方山寨::S录像信息 v;
	v.m录像版本 = a节点.child(L"录像版本").text().as_int();
	v.m游戏版本 = a节点.child(L"游戏版本").text().as_int();
	v.m录像标题 = a节点.child(L"录像标题").text().as_string();
	v.m玩家名称 = a节点.child(L"玩家名称").text().as_string();
	v.m开始时间 = f时间(a节点.child(L"开始时间"));
	v.m结束时间 = f时间(a节点.child(L"结束时间"));
	v.m关卡数量 = a节点.child(L"关卡数量").text().as_ullong();
	v.m游戏设置 = f游戏设置(a节点.child(L"游戏设置"));
	return v;
}
S录像关卡信息 f录像关卡信息(const t节点 &a节点) {
	东方山寨::S录像关卡信息 v;
	v.m关卡 = a节点.attribute(L"关卡").as_int();
	v.m帧数 = a节点.child(L"帧数").text().as_ullong();
	v.m开始时间 = f时间(a节点.child(L"开始时间"));
	v.m结束时间 = f时间(a节点.child(L"结束时间"));
	v.m随机数种子 = a节点.child(L"随机数种子").text().as_uint();
	v.m自机坐标 = f向量2(a节点.child(L"自机坐标"));
	v.m开始成绩 = f玩家成绩(a节点.child(L"开始成绩"));
	v.m结束成绩 = f玩家成绩(a节点.child(L"结束成绩"));
	return v;
}
S玩家成绩 f玩家成绩(const t节点 &a节点) {
	东方山寨::S玩家成绩 v;
	v.m得分 = a节点.child(L"得分").text().as_llong();
	v.m残机 = f分数(a节点.child(L"残机"));
	v.m炸弹 = f分数(a节点.child(L"炸弹"));
	v.m火力 = f分数(a节点.child(L"火力"));
	v.m最大点 = a节点.child(L"最大点").text().as_int();
	v.m擦弹 = a节点.child(L"擦弹").text().as_int();
	v.m吸收.m值 = a节点.child(L"吸收").text().as_float();
	return v;
}
}	//namespace 解析
}	//namespace 东方山寨::xml