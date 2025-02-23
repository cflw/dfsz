module;
#include <cassert>
#include <string>
#include <filesystem>
#include <cflw视窗.h>
#include "程序设置.h"
#include "游戏设置.h"
#include "输入.h"
export module 东方山寨.设置管理;
export import cflw.工具.单例;
namespace 视窗 = cflw::视窗;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
class C设置管理 : public 工具::C弱单例<C设置管理> {
public:
	static const std::wstring c程序设置文件名;
	static const std::wstring c游戏设置文件名;
	static const std::filesystem::path c设置文件目录;
	static const std::filesystem::path c程序设置文件路径;
	static const std::filesystem::path c游戏设置文件路径;
	C设置管理() = default;
	~C设置管理() {
	}
	//static bool f写设置文件(const std::filesystem::path &a路径, const t属性树 &a树) {
	//	t属性文件 v文件;
	//	if (v文件.f打开(a路径, std::ios::out)) {
	//		v文件.f写入(a树);
	//		return true;
	//	}
	//	return false;
	//}
	//void f初始设置() {	//在 f打开设置 失败后调用
	//	const auto f设置默认语言 = [&, v默认语言 = 视窗::C语言区域::fg语言名称()](std::wstring &a语言) {
	//		if (a语言.empty()) {
	//			a语言 = v默认语言;
	//			mi保存程序设置 = true;
	//		}
	//	};
	//	f设置默认语言(m程序设置.m文本语言);
	//	f设置默认语言(m程序设置.m界面语言);
	//}
	//bool f打开设置() {
	//	const bool v打开程序设置 = f打开程序设置();
	//	const bool v打开游戏设置 = f打开游戏设置();
	//	return v打开程序设置 && v打开游戏设置;
	//}
	//bool f打开程序设置() {
	//	t属性文件 v文件;
	//	if (v文件.f打开(c程序设置文件路径)) {
	//		v文件.f读取(m程序设置树);
	//		if (auto vp数据 = m程序设置树.get_child_optional(L"数据")) {
	//			m程序设置.m文本语言 = vp数据->get<std::wstring>(L"语言.文本语言", L"");
	//			m程序设置.m界面语言 = vp数据->get<std::wstring>(L"语言.界面语言", L"");
	//		}
	//		//结束
	//		mi保存程序设置 = false;
	//		return true;
	//	}
	//	return false;
	//}
	//bool f打开游戏设置() {
	//	t属性文件 v文件;
	//	if (v文件.f打开(c游戏设置文件路径)) {
	//		v文件.f读取(m游戏设置树);
	//		if (auto vp数据 = m游戏设置树.get_child_optional(L"数据")) {

	//		}
	//		//结束
	//		mi保存游戏设置 = false;
	//		return true;
	//	}
	//	return false;
	//}
	//bool f保存设置() {
	//	const bool v保存程序设置 = f保存程序设置();
	//	const bool v保存游戏设置 = f保存游戏设置();
	//	return v保存程序设置 && v保存游戏设置;
	//}
	//bool f保存程序设置() {
	//	if (!mi保存程序设置) {
	//		return true;
	//	}
	//	if (m程序设置树.empty()) {
	//		t属性树 v全局, v数据;
	//		v全局.add(L"名称", L"程序设置");
	//		v全局.add(L"类型", L"程序设置");
	//		m程序设置树.add_child(L"全局", v全局);
	//		v数据.add(L"玩家名称", L"");
	//		v数据.add_child(L"语言", {});
	//		v数据.add_child(L"图形", {});
	//		v数据.add_child(L"声音", {});
	//		m程序设置树.add_child(L"数据", v数据);
	//	}
	//	t属性树 &v数据 = m程序设置树.get_child(L"数据");
	//	v数据.put(L"玩家名称", m程序设置.m玩家名称);
	//	t属性树 &v语言 = v数据.get_child(L"语言");
	//	v语言.put(L"文本语言", m程序设置.m文本语言);
	//	v语言.put(L"界面语言", m程序设置.m界面语言);
	//	t属性树 &v图形 = v数据.get_child(L"图形");
	//	//保存文件
	//	const bool v保存结果 = f写设置文件(c程序设置文件路径, m程序设置树);
	//	mi保存程序设置 = !v保存结果;
	//	return v保存结果;
	//}
	//bool f保存游戏设置() {
	//	if (!mi保存游戏设置) {
	//		return true;
	//	}
	//	if (m游戏设置树.empty()) {
	//		t属性树 v全局, v数据;
	//		v全局.add(L"名称", L"stg0");
	//		v全局.add(L"类型", L"程序设置");
	//		m游戏设置树.add_child(L"全局", v全局);
	//		v数据.add_child(L"手柄", {});
	//		m游戏设置树.add_child(L"数据", v数据);
	//	}
	//	t属性树 &v数据 = m游戏设置树.get_child(L"数据");
	//	t属性树 &v手柄 = v数据.get_child(L"手柄");
	//	v手柄.put<int>(L"射击", (int)ca手柄映射.at(E按键::e射击));
	//	v手柄.put<int>(L"炸弹", (int)ca手柄映射.at(E按键::e炸弹));
	//	v手柄.put<int>(L"低速", (int)ca手柄映射.at(E按键::e低速));
	//	//v手柄.put<int>(L"释放", (int)ca手柄映射.at(E按键::e释放));
	//	//保存文件
	//	const bool v保存结果 = f写设置文件(c游戏设置文件路径, m游戏设置树);
	//	mi保存程序设置 = !v保存结果;
	//	return v保存结果;
	//}
	S程序设置 &fg程序设置() {
		if (m载入程序设置) {
			m程序设置 = S程序设置::fc系统();
			m载入程序设置 = false;
		}
		return g这->m程序设置;
	}
	S游戏设置 &fg游戏设置() {
		if (m载入游戏设置) {
			m游戏设置 = S游戏设置::fc默认();
			m载入游戏设置 = false;
		}
		return g这->m游戏设置;
	}
private:
	bool m载入程序设置 = true, m载入游戏设置 = true;	//载入指示,true=需要载入
	bool m保存程序设置 = true, m保存游戏设置 = true;	//保存指示,true=需要保存
	//boost::property_tree::wptree m程序设置树, m游戏设置树;	//boost1.79中实例化wptree会报链接错误，以后改用boost/json库
	S程序设置 m程序设置;
	S游戏设置 m游戏设置;
};
//常量
const std::wstring C设置管理::c程序设置文件名 = std::wstring(L"setting0-") + 视窗::C环境::fg计算机名称() + L".json";
const std::wstring C设置管理::c游戏设置文件名 = L"stg0.json";
//const std::filesystem::path C程序设置::c设置文件目录 = L"%UserProfile%/AppData/Roaming/cflw/public";	//应用数据目录
const std::filesystem::path C设置管理::c设置文件目录 = 视窗::C环境::fg工作目录();	//当前目录
const std::filesystem::path C设置管理::c程序设置文件路径 = c设置文件目录 / c程序设置文件名;
const std::filesystem::path C设置管理::c游戏设置文件路径 = c设置文件目录 / c游戏设置文件名;
}	//namespace 东方山寨