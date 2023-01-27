#include <string>
#include <cflw时间.h>
#include <cflw数学_向量.h>
#include "程序常量.h"
#include "游戏设置.h"
#include "序列化.h"
#include "玩家成绩.h"
import 东方山寨.录像_结构;
namespace 时间 = cflw::时间;
using namespace std::string_literals;
namespace 东方山寨 {
}	//namespace 东方山寨
namespace cflw::文件::json {
//数学类型
t树 f序列化_向量2(const cflw::数学::S向量2 &a) {
	t树 v;
	v.put<float>(L"x", a.x);
	v.put<float>(L"y", a.y);
	return v;
}
cflw::数学::S向量2 f解析_向量2(const t树 &a) {
	const float x = a.get<float>(L"x", 0);
	const float y = a.get<float>(L"x", 0);
	return {x, y};
}
t树 f序列化_分数(const boost::rational<int> &a) {
	t树 v;
	v.put<int>(L"n", a.numerator());
	v.put<int>(L"d", a.denominator());
	return v;
}
boost::rational<int> f解析_分数(const t树 &a) {
	const int n = a.get<int>(L"n", 0);
	const int d = a.get<int>(L"d", 1);
	return {n, d};
}
//游戏设置
template<> t树 f序列化(const 东方山寨::S游戏设置& a) {
	t树 v;
	v.put<int>(L"自机标识", a.m自机标识);
	v.put<int>(L"子机标识", a.m子机标识);
	v.put<int>(L"炸弹标识", a.m炸弹标识);
	v.put<int>(L"残机", a.m残机);
	v.put<int>(L"炸弹", a.m炸弹);
	v.put<int>(L"火力", a.m火力);
	v.put<int>(L"最大点", a.m最大点);
	v.put<int>(L"基础难度", a.m基础难度);
	v.put<int>(L"增加难度", a.m增加难度);
	v.put<int>(L"关卡", a.m关卡);
	v.put<int>(L"关卡组", a.m关卡组);
	v.put<int>(L"游戏模式", (int)a.m游戏模式);
	return v;
}
template<> 东方山寨::S游戏设置 f解析(const t树& a) {
	东方山寨::S游戏设置 v;
	v.m自机标识 = a.get<int>(L"自机标识", 0);
	v.m子机标识 = a.get<int>(L"子机标识", 0);
	v.m炸弹标识 = a.get<int>(L"炸弹标识", 0);
	v.m残机 = a.get<int>(L"残机", 0);
	v.m炸弹 = a.get<int>(L"炸弹", 0);
	v.m火力 = a.get<int>(L"火力", 0);
	v.m最大点 = a.get<int>(L"最大点", 0);
	v.m基础难度 = a.get<int>(L"基础难度", 0);
	v.m增加难度 = a.get<int>(L"增加难度", 0);
	v.m关卡 = a.get<int>(L"关卡", 0);
	v.m关卡组 = a.get<int>(L"关卡组", 0);
	v.m游戏模式 = (东方山寨::E游戏模式)a.get<int>(L"游戏模式", 0);
	return v;
}
//录像信息
template<> t树 f序列化(const 东方山寨::S录像信息 &a) {
	t树 v;
	const 时间::t本地时间 v现在 = 时间::fg本地现在();
	v.put<int>(L"录像版本", a.m录像版本);
	v.put<int>(L"游戏版本", a.m游戏版本);
	const std::wstring &v录像标题 = !a.m录像标题.empty() ? a.m录像标题 : (L"自动录像"s + std::format(东方山寨::c紧凑时间格式, 时间::f本地秒(v现在)));
	v.put<std::wstring>(L"录像标题", v录像标题);
	v.put<std::wstring>(L"玩家名称", a.m玩家名称);
	v.put<time_t>(L"开始时间", 时间::f时间戳(a.m开始时间));
	v.put<time_t>(L"结束时间", 时间::f时间戳(a.m结束时间));
	v.put<size_t>(L"关卡数量", a.m关卡数量);
	v.put_child(L"游戏设置", f序列化<东方山寨::S游戏设置>(a.m游戏设置));
	return v;
}
template<> 东方山寨::S录像信息 f解析(const t树 &a) {
	东方山寨::S录像信息 v;
	v.m录像版本 = a.get<int>(L"录像版本", 0);
	v.m游戏版本 = a.get<int>(L"游戏版本", 0);
	v.m录像标题 = a.get<std::wstring>(L"录像标题", L"");
	v.m玩家名称 = a.get<std::wstring>(L"玩家名称", L"");
	v.m开始时间 = 时间::f本地时间(a.get<time_t>(L"开始时间", 0));
	v.m结束时间 = 时间::f本地时间(a.get<time_t>(L"结束时间", 0));
	v.m关卡数量 = a.get<size_t>(L"关卡数量", 0);
	v.m游戏设置 = f解析<东方山寨::S游戏设置>(a.get_child(L"游戏设置"));
	return v;
}
//关卡信息
template<> t树 f序列化(const 东方山寨::S录像关卡信息 &a) {
	t树 v;
	v.put<int>(L"关卡", a.m关卡);
	v.put<size_t>(L"帧数", a.m帧数);
	v.put<time_t>(L"开始时间", 时间::f时间戳(a.m开始时间));
	v.put<time_t>(L"结束时间", 时间::f时间戳(a.m结束时间));
	v.put<unsigned int>(L"随机数种子", a.m随机数种子);
	v.put_child(L"自机坐标", f序列化_向量2(a.m自机坐标));
	v.put_child(L"开始成绩", f序列化<东方山寨::S玩家成绩>(a.m开始成绩));
	v.put_child(L"结束成绩", f序列化<东方山寨::S玩家成绩>(a.m结束成绩));
	return v;
}
template<> 东方山寨::S录像关卡信息 f解析(const t树 &a) {
	东方山寨::S录像关卡信息 v;
	v.m关卡 = a.get<int>(L"关卡", 0);
	v.m帧数 = a.get<size_t>(L"帧数", 0);
	v.m开始时间 = 时间::f本地时间(a.get<time_t>(L"开始时间", 0));
	v.m结束时间 = 时间::f本地时间(a.get<time_t>(L"结束时间", 0));
	v.m随机数种子 = a.get<unsigned int>(L"随机数种子", 0);
	v.m自机坐标 = f解析_向量2(a.get_child(L"自机坐标"));
	v.m开始成绩 = f解析<东方山寨::S玩家成绩>(a.get_child(L"开始成绩"));
	v.m结束成绩 = f解析<东方山寨::S玩家成绩>(a.get_child(L"结束成绩"));
	return v;
}
//玩家成绩
template<> t树 f序列化(const 东方山寨::S玩家成绩 &a) {
	t树 v;
	v.put<long long>(L"得分", a.m得分);
	v.put_child(L"残机", f序列化_分数(a.m残机));
	v.put_child(L"炸弹", f序列化_分数(a.m炸弹));
	v.put_child(L"火力", f序列化_分数(a.m火力));
	v.put<int>(L"最大点", a.m最大点);
	v.put<int>(L"擦弹", a.m擦弹);
	v.put<float>(L"吸收", a.m吸收.m值);
	return v;
}
template<> 东方山寨::S玩家成绩 f解析(const t树 &a) {
	东方山寨::S玩家成绩 v;
	v.m得分 = a.get<long long>(L"得分", 0);
	if (const auto v残机 = a.get_child_optional(L"残机")) {
		v.m残机 = f解析_分数(*v残机);
	}
	if (const auto v炸弹 = a.get_child_optional(L"炸弹")) {
		v.m炸弹 = f解析_分数(*v炸弹);
	}
	if (const auto v火力 = a.get_child_optional(L"火力")) {
		v.m火力 = f解析_分数(*v火力);
	}
	v.m最大点 = a.get<int>(L"最大点", 0);
	v.m擦弹 = a.get<int>(L"擦弹", 0);
	v.m吸收.m值 = a.get<float>(L"吸收", 0);
	return v;
}
}	//namespace cflw::文件::json