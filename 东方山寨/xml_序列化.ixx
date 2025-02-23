module;
#include <string>
#include <format>
#include <tuple>
#include <boost/rational.hpp>
#include <pugixml.hpp>	//pugixml
#include <cflw时间.h>
#include "数学包含.h"
#include "程序常量.h"
#include "游戏设置.h"
#include "玩家成绩.h"
export module 东方山寨.xml.序列化;
import 东方山寨.录像_结构;
namespace 时间 = cflw::时间;
namespace 东方山寨 {
struct S游戏设置;
struct S录像信息;
struct S录像关卡信息;
struct S玩家成绩;
}	//namespace 东方山寨
export namespace 东方山寨::xml {
using t路径 = std::filesystem::path;
using t文档 = pugi::xml_document;
using t结果 = pugi::xml_parse_result;
using t节点 = pugi::xml_node;
using t属性 = pugi::xml_attribute;
namespace 序列化 {
template<typename t0, typename t1>
std::wstring f二元组(const t0 &a, const t1 &b) {
	return std::format(L"{},{}", a, b);
}
template<typename t0, typename t1, typename t2>
std::wstring f三元组(const t0 &a, const t1 &b, const t2 &c) {
	return std::format(L"{},{},{}", a, b, c);
}
std::wstring f向量2(const t向量2 &);
std::wstring f向量3(const t向量3 &);
std::wstring f分数(const boost::rational<int> &);
void f游戏设置(t节点 &, const S游戏设置 &);
void f录像信息(t节点 &, const S录像信息 &);
void f录像关卡信息(t节点 &, const S录像关卡信息 &);
void f玩家成绩(t节点 &, const S玩家成绩 &);
}	//namespace 序列化
}	//namespace 东方山寨::xml
module: private;
namespace 东方山寨::xml {
namespace 序列化 {
std::wstring f向量2(const t向量2 &a) {
	return std::format(L"{},{}", a.x, a.y);
}
std::wstring f向量3(const t向量3 &a) {
	return std::format(L"{},{}", a.x, a.y, a.z);
}
std::wstring f分数(const boost::rational<int> &a) {
	if (a.denominator() == 1) {
		return std::to_wstring(a.numerator());
	} else {
		return std::format(L"{}/{}", a.numerator(), a.denominator());
	}
}
void f游戏设置(t节点 &a节点, const S游戏设置 &a) {
	a节点.append_child(L"自机标识").text() = a.m自机标识;
	a节点.append_child(L"子机标识").text() = a.m子机标识;
	a节点.append_child(L"炸弹标识").text() = a.m炸弹标识;
	a节点.append_child(L"残机").text() = a.m残机;
	a节点.append_child(L"炸弹").text() = a.m炸弹;
	a节点.append_child(L"火力").text() = a.m火力;
	a节点.append_child(L"最大点").text() = a.m最大点;
	a节点.append_child(L"基础难度").text() = a.m基础难度;
	a节点.append_child(L"增加难度").text() = a.m增加难度;
	a节点.append_child(L"关卡").text() = a.m关卡;
	a节点.append_child(L"关卡组").text() = a.m关卡组;
	a节点.append_child(L"游戏模式").text() = (int)a.m游戏模式;
}
void f录像信息(t节点 &a节点, const S录像信息 &a) {
	const 时间::t本地时间 v现在 = 时间::fg本地现在();
	a节点.append_child(L"录像版本").text() = a.m录像版本;
	a节点.append_child(L"游戏版本").text() = a.m游戏版本;
	const std::wstring v默认录像标题 = std::wstring(L"自动录像") + std::format(东方山寨::c紧凑时间格式, 时间::f本地秒(v现在));
	const std::wstring &v录像标题 = !a.m录像标题.empty() ? a.m录像标题 : v默认录像标题;
	a节点.append_child(L"录像标题").text() = v录像标题.c_str();
	a节点.append_child(L"玩家名称").text() = a.m玩家名称.c_str();
	a节点.append_child(L"开始时间").text() = 时间::f时间戳(a.m开始时间);
	a节点.append_child(L"结束时间").text() = 时间::f时间戳(a.m结束时间);
	a节点.append_child(L"关卡数量").text() = a.m关卡数量;
	t节点 v游戏设置节点 = a节点.append_child(L"游戏设置");
	f游戏设置(v游戏设置节点, a.m游戏设置);
}
void f录像关卡信息(t节点 &a节点, const S录像关卡信息 &a) {
	a节点.append_attribute(L"关卡") = a.m关卡;
	a节点.append_child(L"帧数").text() = a.m帧数;
	a节点.append_child(L"开始时间").text() = 时间::f时间戳(a.m开始时间);
	a节点.append_child(L"结束时间").text() = 时间::f时间戳(a.m结束时间);
	a节点.append_child(L"随机数种子").text() = a.m随机数种子;
	a节点.append_child(L"自机坐标").text() = f向量2(a.m自机坐标).c_str();
	t节点 v开始成绩节点 = a节点.append_child(L"开始成绩");
	f玩家成绩(v开始成绩节点, a.m开始成绩);
	t节点 v结束成绩节点 = a节点.append_child(L"结束成绩");
	f玩家成绩(v结束成绩节点, a.m结束成绩);
}
void f玩家成绩(t节点 &a节点, const S玩家成绩 &a) {
	a节点.append_child(L"得分").text() = a.m得分;
	a节点.append_child(L"残机").text() = f分数(a.m残机).c_str();
	a节点.append_child(L"炸弹").text() = f分数(a.m炸弹).c_str();
	a节点.append_child(L"火力").text() = f分数(a.m火力).c_str();
	a节点.append_child(L"最大点").text() = a.m最大点;
	a节点.append_child(L"擦弹").text() = a.m擦弹;
	a节点.append_child(L"吸收").text() = a.m吸收.m值;
}
}	//namespace 序列化
}	//namespace 东方山寨::xml