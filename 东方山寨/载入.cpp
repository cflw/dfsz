#include <tuple>
#include <boost/property_tree/json_parser.hpp>
#include <cflw文件_json.h>
#include "载入基础.h"
#include "载入解析.h"
//基础
#include "程序常量.h"
#include "游戏常量.h"
#include "载入.h"
#include "程序.h"
#include "计算.h"
#include "游戏.h"
#include "标识.h"
#include "取文本.h"
//图形
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "图形_三维.h"
#include "动画接口.h"
#include "动画.h"
#include "图形_子弹_线条.h"
#include "图形_子弹_顶点.h"
#include "道具动画.h"
#include "图形_静态立绘.h"
//其它
#include "道具.h"
#include "子弹基础.h"
#include "音频引擎.h"
//玩家
#include "玩家.h"
#include "自机.h"
#include "子机移动_位置.h"
#include "玩家子弹基础.h"
#include "玩家子弹发射基础.h"
#include "玩家子弹发射_发散.h"
#include "玩家子弹发射扩展.h"
#include "玩家炸弹扩展.h"
//敌机
#include "敌机基础.h"
import 东方山寨.文件系统;
namespace 东方山寨::载入 {
//==============================================================================
// 读json
//==============================================================================
class C读json文件 {
public:
	static bool f读取(boost::property_tree::wptree &a输出树, const std::filesystem::path &a路径) {
		t属性文件 v文件;
		const std::filesystem::path v路径 = 文件系统::f计算路径(a路径, L"");
		if (v文件.f打开(v路径.c_str())) {
			v文件.f读取(a输出树);
			return true;
		} else {
			return false;
		}
	}
	static bool f读取(boost::property_tree::wptree &a输出树, const S载入参数 &a参数, const std::filesystem::path &a路径, std::filesystem::path &a输出路径) {
		t属性文件 v文件;
		const std::filesystem::path v路径 = 文件系统::f计算路径(a路径, a参数.m路径);
		if (v文件.f打开(v路径.c_str())) {
			v文件.f读取(a输出树);
			a输出路径 = v路径;
			return true;
		} else {
			__debugbreak();
			return false;
		}
	}
};
//==============================================================================
// 解析数据
//==============================================================================
//子机移动
class C解析子机移动json {
public:
	typedef std::unique_ptr<I工厂<I子机移动>> t返回值;
	typedef std::unique_ptr<I工厂<I子机移动>> (*tf解析)(int, const boost::property_tree::wptree &);
	static std::unique_ptr<I工厂<I子机移动>> f汇总(int a类型, int a子机数, const boost::property_tree::wptree &a树) {
		static const std::map<int, tf解析> v解析函数{
			{0, f位置}
		};
		return v解析函数.at(a类型)(a子机数, a树);
	}
	static std::unique_ptr<I工厂<I子机移动>> f位置(int a子机数, const boost::property_tree::wptree &a树) {
		const int v数量 = (1 + a子机数) * a子机数 / 2;//=1+2+..+子机数
		const int v总数量 = v数量 * 2;
		std::vector<t向量2> v数组;
		//int i1 = 0;
		for (auto &v1 : a树) {
			const auto &v节点1 = v1.second;
			const float x = v节点1.get<float>(L"x", 0);
			const float y = v节点1.get<float>(L"y", 0);
			v数组.emplace_back(x, y);
			assert(v数组.size() <= v总数量);
		}
		auto va属性 = std::make_shared<子机移动::C位置::S属性>(v数组.data());
		return std::make_unique<子机移动::C位置::C工厂>(va属性);
	}
};
//==============================================================================
// 载入数据
//==============================================================================
void C载入::f汇总(const S载入参数 &a) {
	static const std::map<std::wstring, tf载入数据> v载入函数{
		{L"载入列表0", f汇总},
		{L"图形", f图形},
		{L"动画", f动画},
		{L"敌人子弹", f子弹},
		{L"敌人飞机", f敌机},
		{L"玩家飞机", f自机},
		{L"玩家子飞机", f子机},
		{L"玩家子飞机.位置", f子机位置},
		//{L"玩家发射", f玩家发射},
		{L"玩家子弹", f玩家子弹},
		{L"纹理列表0", f纹理列表0},
		{L"模型列表0", f模型列表0},
		{L"声音列表0", f声音列表0},
		{L"声音列表1", f声音列表1},
		{L"文本", f文本},
		{L"立绘列表1", f立绘列表1},
	};
	const boost::property_tree::wptree &v数据 = a.m树.get_child(L"数据");
	for (const auto &v0 : v数据) {
		const std::wstring &v文件名 = v0.second.get_value<std::wstring>();
		boost::property_tree::wptree v树;
		std::filesystem::path v路径;
		C读json文件::f读取(v树, a, v文件名, v路径);
		const std::wstring v类型 = v树.get<std::wstring>(L"全局.类型", L"");
		if (v类型.empty()) {
			throw;
		}
		v载入函数.at(v类型)(S载入参数{v树, v路径});
	}
}
void C载入::f图形(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring &v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	auto &v纹理工厂 = C游戏::g资源.fg纹理工厂();
	auto &v顶点工厂 = C游戏::g资源.fg顶点工厂();
	int v主标识 = -1;
	for (const auto &[v名称0_, v节点0] : a.m树.get_child(L"数据")) {
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring &v图形名称 = v节点0.get<std::wstring>(L"名称", std::wstring(L"图形") + std::to_wstring(v主标识));
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v图形名称, v主标识);
		//纹理
		const t属性树 &v纹理节点 = v节点0.get_child(L"纹理");
		if (const std::wstring v纹理路径 = C解析助手::f获取路径(a, v纹理节点); !v纹理路径.empty()) {
			v纹理工厂.f创建纹理(v名称标识1, v纹理路径);
		}
		const t向量2 v纹理尺寸 = C解析助手::f获取尺寸(v纹理节点.get_child(L"尺寸"));
		v顶点工厂.m参数.fs纹理尺寸(v纹理尺寸);
		//顶点
		int v顶点矩形标识 = 0;
		for (const auto &[v名称1_, v节点1] : v节点0.get_child(L"顶点")) {
			const std::wstring v顶点名称 = v节点1.get<std::wstring>(L"名称", std::wstring(L"顶点") + std::to_wstring(v顶点矩形标识));
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v顶点名称, v顶点矩形标识);
			++v顶点矩形标识;
			const float x = v节点1.get<float>(L"x", 0);
			const float y = v节点1.get<float>(L"y", 0);
			const float v宽 = v节点1.get<float>(L"宽", v纹理尺寸.x - x);
			const float v高 = v节点1.get<float>(L"高", v纹理尺寸.y - y);
			const int v行数 = v节点1.get<int>(L"行数", 1);
			const int v列数 = v节点1.get<int>(L"列数", 1);
			const float v偏移x = v节点1.get<float>(L"偏移x", 0);
			const float v偏移y = v节点1.get<float>(L"偏移y", 0);
			const float v分宽 = v宽 / (float)v列数;
			const float v分高 = v高 / (float)v行数;
			//创建矩形
			const t向量2 v顶点尺寸{v分宽, v分高};
			v顶点工厂.m参数.fs裁剪坐标({x, y});
			v顶点工厂.m参数.fs裁剪尺寸(v顶点尺寸);
			v顶点工厂.m参数.fs矩形坐标({v偏移x, v偏移y});
			int v切片标识 = 0;
			for (auto &v循环 : v顶点工厂.f循环(v列数, v行数)) {
				const C名称标识 v名称标识3 = v名称标识2.f创建层(std::to_wstring(v切片标识), v切片标识);
				++v切片标识;
				v循环.f变换_平移(v顶点尺寸);
				const int v计算切片标识 = v名称标识3;
				v顶点工厂.f创建矩形(v计算切片标识);
			}
		}
	}
}
void C载入::f动画(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const boost::property_tree::wptree &va数据 = a.m树.get_child(L"数据");
	auto &va动画 = C游戏::g资源.fg动画();
	int v主标识 = -1;
	for (const auto &v0 : va数据) {
		const auto &v节点0 = v0.second;
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring v动画名称 = v节点0.get<std::wstring>(L"名称", L"");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v动画名称, v主标识);
		C角色动画::S属性 v属性;
		const float v变化速度 = v节点0.get<float>(L"变化速度", 8);
		const float v循环速度 = v节点0.get<float>(L"循环速度", 8);
		auto f读组 = [&](C角色动画::S属性::S动画方向 &a结构, const boost::property_tree::wptree &a数据) {
			a结构.m序号 = a数据.get<int>(L"开始", 0);
			a结构.m循环 = a数据.get<int>(L"循环", 0);
			a结构.m帧数 = a数据.get<int>(L"帧数", 0);
			a结构.m变化速度 = a数据.get<float>(L"变化速度", v变化速度) / c计算频率<float>;
			a结构.m循环速度 = a数据.get<float>(L"循环速度", v循环速度) / c计算频率<float>;
			a结构.m境像 = a数据.get<bool>(L"镜像", false);
		};
		f读组(v属性.m正常, v节点0.get_child(L"正常动画"));
		f读组(v属性.m左移, v节点0.get_child(L"左移动画"));
		f读组(v属性.m右移, v节点0.get_child(L"右移动画"));
		va动画.f添加(v名称标识1, new C角色动画::C工厂(std::make_shared<C角色动画::S属性>(v属性)));
	}
}
void C载入::f子弹(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	assert(c子弹标识 == v全局标识);
	const boost::property_tree::wptree &va数据 = a.m树.get_child(L"数据");
	auto &v纹理工厂 = C游戏::g资源.fg纹理工厂();
	auto &v顶点工厂 = C游戏::g资源.fg顶点工厂();
	auto &va子弹属性 = C游戏::g资源.fg子弹属性();
	int v主标识 = -1;
	for (const auto &v0 : va数据) {
		const auto &v子弹节点 = v0.second;
		v主标识 = v子弹节点.get<int>(L"标识", v主标识 + 1);
		const std::wstring v子弹名称 = v子弹节点.get<std::wstring>(L"名称", L"");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v子弹名称, v主标识);
		const int v子弹标识 = v名称标识1;
		//纹理
		const t属性树 &v纹理节点 = v子弹节点.get_child(L"纹理");
		const std::wstring v纹理路径 = C解析助手::f获取路径(a, v纹理节点);
		v纹理工厂.f创建纹理(v子弹标识, v纹理路径);
		//顶点
		const t向量2 v纹理尺寸 = C解析助手::f获取尺寸(v纹理节点.get_child(L"尺寸"));
		v顶点工厂.f自动化_完整纹理(v子弹标识, v纹理尺寸);
		//属性
		S子弹属性 &v属性 = va子弹属性.f取空(v子弹标识);
		const int v判定类型 = v子弹节点.get<int>(L"判定.类型");
		switch (v判定类型) {
			case 0: {	//圆形
				const float v纹理尺寸d = (v纹理尺寸.x + v纹理尺寸.y) / 2;
				const float v判定r = v子弹节点.get<float>(L"判定.判定r", v纹理尺寸d / 2);
				const float v修正r = v子弹节点.get<float>(L"判定.修正r", v纹理尺寸d / 4);
				v属性.m判定 = t向量2{v判定r, 0};
				v属性.m判定修正 = t向量2{v修正r, v修正r};
				break;
			}
			case 1: {	//矩形
				const float v判定x = v子弹节点.get<float>(L"判定.判定x", v纹理尺寸.x / 2);
				const float v判定y = v子弹节点.get<float>(L"判定.判定y", v纹理尺寸.y / 2);
				const float v修正x = v子弹节点.get<float>(L"判定.修正x", v纹理尺寸.x / 4);
				const float v修正y = v子弹节点.get<float>(L"判定.修正y", v纹理尺寸.y / 4);
				v属性.m判定 = t向量2{v判定x, v判定y};
				v属性.m判定修正 = t向量2{v修正x, v修正y};
				break;
			}
			default:
				break;
		}
		v属性.m纹理 = v子弹标识;
		v属性.m顶点 = v子弹标识;
		v属性.m动画帧数 = 1;
		//va子弹属性.f添加(v子弹标识, v属性);
	}
}
void C载入::f敌机(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const int v全局动画引用 = a.m树.get<int>(L"全局.动画.引用.标识", 0);
	const int v全局顶点引用 = a.m树.get<int>(L"全局.顶点.引用.标识", 0);
	auto &va敌机属性 = C游戏::g资源.fg敌机属性();
	auto &v纹理工厂 = C游戏::g资源.fg纹理工厂();
	const auto &va数据 = a.m树.get_child(L"数据");
	int v主标识 = -1;
	for (const auto &v0 : va数据) {
		const auto &v节点0 = v0.second;
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring v敌机名称 = v节点0.get<std::wstring>(L"名称", L""); 
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v敌机名称, v主标识);
		const int v敌机标识 = v名称标识1;
		auto &v属性 = va敌机属性.f取空(v敌机标识);
		v属性.m判定半径 = v节点0.get<float>(L"判定半径", 16);
		const auto &v纹理路径 = v节点0.get_optional<std::wstring>(L"纹理.路径");
		if (v纹理路径) {
			v纹理工厂.f创建纹理(v敌机标识, 文件系统::f计算路径(*v纹理路径, a.m路径).native());
			v属性.m纹理 = v敌机标识;
		} else {
			v属性.m纹理 = nullptr;
		}
		C解析引用::f解析赋值(v属性.m动画, v全局动画引用, v节点0.get_child_optional(L"动画.引用"));
		C解析引用::f解析赋值(v属性.m顶点, v全局顶点引用, v节点0.get_child_optional(L"顶点.引用"));
	}
}
void C载入::f自机(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const int v全局发射引用 = a.m树.get<int>(L"全局.发射.引用.标识", 0);
	const int v全局动画引用 = a.m树.get<int>(L"全局.动画.引用.标识", 0);
	const int v全局顶点引用 = a.m树.get<int>(L"全局.顶点.引用.标识", 0);
	const C解析引用 v全局子弹引用 = {a.m树.get<int>(L"全局.子弹.引用.标识", 0)};
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &v纹理工厂 = C游戏::g资源.fg纹理工厂();
	auto &va自机属性 = C游戏::g资源.fg自机属性();
	int v主标识 = -1;
	for (const auto &v0 : va数据) {
		const auto &v节点0 = v0.second;
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring v自机名称 = v节点0.get<std::wstring>(L"名称", L"");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v自机名称, v主标识);
		const int v自机标识 = v名称标识1;
		auto &v属性 = va自机属性.f取空(v自机标识);
		//纹理
		const auto &v纹理路径 = v节点0.get_optional<std::wstring>(L"纹理.路径");
		if (v纹理路径) {
			v纹理工厂.f创建纹理(v自机标识, 文件系统::f计算路径(*v纹理路径, a.m路径).native());
			v属性.m纹理 = v自机标识;
		} else {
			v属性.m纹理 = nullptr;
		}
		//属性
		v属性.m判定半径 = v节点0.get<float>(L"判定半径", C自机::c判定半径);
		v属性.m擦弹半径 = v节点0.get<float>(L"擦弹半径", C自机::c擦弹半径);
		v属性.m道具半径 = v节点0.get<float>(L"道具半径", C自机::c道具半径);
		v属性.m移动速度 = v节点0.get<float>(L"移动速度", C自机::c移动速度);
		C解析引用::f解析赋值(v属性.m动画, v全局动画引用, v节点0.get_child_optional(L"动画.引用"));
		C解析引用::f解析赋值(v属性.m顶点, v全局顶点引用, v节点0.get_child_optional(L"顶点.引用"));
		C解析引用::f解析赋值(v属性.m发射子弹, v全局发射引用, v节点0.get_child_optional(L"发射.引用"));
		C解析引用::f解析赋值(v属性.m子弹属性, v全局子弹引用, v节点0.get_child_optional(L"子弹.引用"));
	}
}
void C载入::f子机(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	assert(c子机标识 == v全局标识);
	const C解析引用 v全局纹理引用 = {a.m树.get<int>(L"全局.纹理.引用.标识", 0)};
	const C解析引用 v全局顶点引用 = {a.m树.get<int>(L"全局.顶点.引用.标识", 0)};
	const C解析引用 v全局移动引用 = {a.m树.get<int>(L"全局.移动.引用.标识", 0)};
	const C解析引用 v全局发射引用 = {a.m树.get<int>(L"全局.发射.引用.标识", 0)};
	const C解析引用 v全局子弹引用 = {a.m树.get<int>(L"全局.子弹.引用.标识", 0)};
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va子机 = C游戏::g资源.fg子机属性();
	auto &va子机移动 = C游戏::g资源.fg子机移动();
	int v主标识 = -1;
	for (const auto &v0 : va数据) {
		const auto &v节点0 = v0.second;
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring v子机名称 = v节点0.get<std::wstring>(L"名称", L"");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v子机名称, v主标识);
		const int v子机标识 = v名称标识1;
		auto &v子机属性 = va子机.f取空(v子机标识);
		const int v类型 = v节点0.get<int>(L"类型", 0);
		//子机数
		const int v子机数 = v节点0.get<int>(L"子机数", 0);
		v子机属性.m数量上限 = v子机数;

		C解析引用::f解析赋值(v子机属性.m纹理, v全局纹理引用, v节点0.get_child_optional(L"纹理.引用"));
		C解析引用::f解析赋值(v子机属性.m顶点, v全局顶点引用, v节点0.get_child_optional(L"顶点.引用"));
		C解析引用::f解析赋值(v子机属性.m发射, v全局发射引用, v节点0.get_child_optional(L"发射.引用"));
		C解析引用::f解析赋值(v子机属性.m子弹属性, v全局子弹引用, v节点0.get_child_optional(L"子弹.引用"));
		//移动
		if (const auto &v子机移动节点 = v节点0.get_child_optional(L"移动")) {
			if (const auto &v子机移动引用节点 = v子机移动节点->get_child_optional(L"引用")) {
				C解析引用::f解析赋值(v子机属性.m移动, v全局移动引用, v子机移动引用节点);
			} else if (const auto &v子机移动类型 = v子机移动节点->get_optional<int>(L"类型")) {
				v子机属性.m移动 = v子机标识;
				va子机移动.f添加(v子机标识, C解析子机移动json::f汇总(*v子机移动类型, v子机数, v子机移动节点->get_child(L"值")).release());
			} else {
				v子机属性.m移动 = v全局移动引用.fg值();
			}
		} else {
			v子机属性.m移动 = v全局移动引用.fg值();
		}
	}
}
void C载入::f子机位置(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	assert(c子机移动标识 == v全局标识);
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va子机移动 = C游戏::g资源.fg子机移动();
	for (const auto &v0 : va数据) {
		const auto &v节点0 = v0.second;
		const int v主标识 = v节点0.get<int>(L"标识");
		const int v子机移动标识 = 计算::f标识(v全局标识, v主标识, 0);
		const int v类型 = v节点0.get<int>(L"类型", 0);
		const int v子机数 = v节点0.get<int>(L"子机数", 0);
		const auto &va值 = v节点0.get_child(L"值");
		va子机移动.f添加(v子机移动标识, C解析子机移动json::f汇总(v类型, v子机数, va值).release());
	}
}
void C载入::f玩家子弹(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const C解析引用 v全局顶点引用 = {a.m树.get<int>(L"全局.顶点.引用.标识", 0)};
	const C解析引用 v全局纹理引用 = {a.m树.get<int>(L"全局.纹理.引用.标识", 0)};
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va玩家子弹属性 = C游戏::fg资源().fg玩家子弹属性();
	int v主标识 = -1;
	for (const auto &[v名称0_, v节点0] : va数据) {
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring v玩家子弹名称 = v节点0.get<std::wstring>(L"名称", L"");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v玩家子弹名称, v主标识);
		const int v玩家子弹标识 = v名称标识1;
		auto &v玩家子弹属性 = va玩家子弹属性.f取空(v玩家子弹标识);
		//图形
		C解析引用::f解析赋值(v玩家子弹属性.m纹理, v全局纹理引用, v节点0.get_child_optional(L"纹理.引用"));
		C解析引用::f解析赋值(v玩家子弹属性.m顶点, v全局顶点引用, v节点0.get_child_optional(L"顶点.引用"));
		if (auto v消失纹理 = v节点0.get_child_optional(L"消失纹理.引用")) {
			C解析引用::f解析赋值(v玩家子弹属性.m消失纹理, v全局纹理引用, v消失纹理);
		} else {
			v玩家子弹属性.m消失纹理 = v玩家子弹属性.m纹理;
		}
		if (auto v消失顶点 = v节点0.get_child_optional(L"消失顶点.引用")) {
			C解析引用::f解析赋值(v玩家子弹属性.m消失顶点, v全局顶点引用, v消失顶点);
		} else {
			v玩家子弹属性.m消失顶点 = v玩家子弹属性.m顶点;
		}
		v玩家子弹属性.m动画帧数 = v节点0.get<int>(L"动画帧数", 0);
		v玩家子弹属性.m消失帧数 = v节点0.get<int>(L"消失帧数", 0);
		v玩家子弹属性.m伤害 = v节点0.get<int>(L"伤害", 10);
		//判定
		if (const auto &v判定节点 = v节点0.get_child_optional(L"判定")) {
			const int v类型 = v判定节点->get<int>(L"类型", 0);
			switch (v类型) {
			case 0:	//圆形
				v玩家子弹属性.m判定.x = v判定节点->get<float>(L"判定r", 4);
				break;
			case 1:	//矩形
				v玩家子弹属性.m判定.x = v判定节点->get<float>(L"判定x", 4);
				v玩家子弹属性.m判定.y = v判定节点->get<float>(L"判定y", 4);
				break;
			default:
				v玩家子弹属性.m判定.x = 4;
				break;
			}
		}
	}
}
void C载入::f玩家发射(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	assert(c玩家发射标识 == v全局标识);
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va玩家发射 = C游戏::g资源.fg玩家发射();
	int v主标识 = -1;
	for (const auto &[v名称0, v树0] : va数据) {
		v主标识 = v树0.get<int>(L"标识", v主标识 + 1);
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, v主标识);
		const int v射击类型 = v树0.get<int>(L"类型");
		switch (v射击类型) {
			case 1:
			{	//发散
				const int v数量 = v树0.get<int>(L"数量");
				const int v发散0 = v树0.get<int>(L"发散0");
				const int v发散1 = v树0.get<int>(L"发散1");
				const int v并列0 = v树0.get<int>(L"并列0");
				const int v并列1 = v树0.get<int>(L"并列1");
				const auto v射击属性 = 玩家子弹发射::C发散::S属性::fc总(v数量, v发散0, v发散1, v并列0, v并列1);
				va玩家发射.f构造<玩家子弹发射::C发散::C工厂>(v名称标识1, v射击属性);
				break;
			}
			default:
				break;
		}
	}

}
void C载入::f纹理列表0(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"纹理.") + a.m树.get<std::wstring>(L"全局.名称");
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &v纹理工厂 = C游戏::fg资源().fg纹理工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const auto &[v名称0, v树0] : va数据) {
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识);
		v纹理工厂.f创建纹理(v名称标识1, 文件系统::f计算路径(v树0.get_value<std::wstring>(), a.m路径));
	}
}
void C载入::f模型列表0(const S载入参数 &a) {
	const std::wstring c模型名称 = L"模型";
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"模型.") + a.m树.get<std::wstring>(L"全局.名称");
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &v模型工厂 = C游戏::fg图形().fg模型工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const auto &[v名称0_, v树0] : va数据) {
		const std::wstring &v名称0 = v树0.get<std::wstring>(L"名称", c模型名称 + std::to_wstring(++v主标识));
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, v主标识);
		std::vector<S三维顶点> va顶点;
		for (const auto &[v名称1_, v树1] : v树0.get_child(L"顶点")) {
			S三维顶点 v顶点;
			v顶点.m坐标.x = v树1.get<float>(L"坐标.x", 0);
			v顶点.m坐标.y = v树1.get<float>(L"坐标.y", 0);
			v顶点.m坐标.z = v树1.get<float>(L"坐标.z", 0);
			v顶点.m纹理.x = v树1.get<float>(L"纹理.u", 0);
			v顶点.m纹理.y = v树1.get<float>(L"纹理.v", 0);
			va顶点.push_back(v顶点);
		}
		std::vector<三维::t索引> va索引;
		for (const auto &[v名称1_, v树1] : v树0.get_child(L"索引")) {
			const 三维::t索引 v索引 = v树1.get_value<三维::t索引>(0);
			va索引.push_back(v索引);
		}
		v模型工厂.m参数.fs顶点(va顶点.data(), va顶点.size());
		v模型工厂.m参数.fs索引(va索引.data(), va索引.size());
		v模型工厂.f创建模型(v名称标识1);
	}
}
void C载入::f声音列表0(const S载入参数 &a) {
	//音效
	const std::wstring c模型名称 = L"模型";
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"声音.") + a.m树.get<std::wstring>(L"全局.名称");
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &v声音工厂 = C游戏::fg音频().fg声音工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const auto &[v名称0, v树0] : va数据) {
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识);
		v声音工厂.f创建声音(v名称标识1, 文件系统::f计算路径(v树0.get_value<std::wstring>(), a.m路径));
	}
}
void C载入::f声音列表1(const S载入参数 &) {
	//音乐
}
void C载入::f文本(const S载入参数 &a) {
	const int v全局标识 = 计算::fc随机标识();
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	const std::wstring v语言 = a.m树.get<std::wstring>(L"全局.语言");
	const auto &va数据 = a.m树.get_child(L"数据");
	auto &va文本 = C游戏::fg资源().f新文本数组(v全局名称, v语言);
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const auto &[v名称0, v树0] : va数据) {
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识);
		va文本.f添加(v名称标识1, v树0.get_value<std::wstring>());
	}
}
//==============================================================================
// 内部载入
//==============================================================================
void C内部载入::f道具() {
	auto &va道具属性 = C游戏::fg资源().fg道具属性();
	struct S道具属性0 {
		E道具 m标识;
		tf道具效果 m效果函数;
		int m效果值;
		float m判定半径;
		float m最大透明;
		int m图形标识1;	//纹理
		int m图形标识2;	//顶点
	} v道具属性表[] = {
		//序号				效果					值 半径 透明	图形标识
		{E道具::e残机,		道具效果::f残机_十分之一,	10, 8, 1,		0, 1},
		{E道具::e残机碎片,	道具效果::f残机_十分之一,	3, 8, 1	,		0, 0},
		{E道具::e炸弹,		道具效果::f炸弹_十分之一,	10, 8, 1,		0, 3},
		{E道具::e炸弹碎片,	道具效果::f炸弹_十分之一,	3, 8, 1,		0, 2},
		{E道具::e火力,		道具效果::f火力_百分之一,	1, 4, 1,		1, 0},
		{E道具::e得点,		道具效果::f得分_最大点,		1, 4, 1,		1, 1},
		{E道具::e最大点,	道具效果::f最大点,			1000, 4, 1,		1, 2},
		{E道具::e微最大点,	道具效果::f最大点,			10, 4, 0.2f,	1, 3},
	};
	for (auto &v : v道具属性表) {
		S道具属性 &v属性 = va道具属性.f取空((int)v.m标识);
		v属性.mf效果 = v.m效果函数;
		v属性.m值 = v.m效果值;
		v属性.m判定半径 = v.m判定半径;
		v属性.m最大透明度 = v.m最大透明;
		const int v道具图形标识 = 计算::f标识(c道具标识, v.m图形标识1);
		v属性.m纹理 = v道具图形标识;
		v属性.m顶点 = 计算::f标识(v道具图形标识, 0, 0, v.m图形标识2);
		v属性.m动画 = (int)E动画::e道具;
	}
}
void C内部载入::f图形管线() {
	auto &v图形 = C游戏::fg图形();
	auto &va图形管线 = v图形.fg图形管线数组();
	va图形管线.f构造<C画图片管线>((int)E图形管线::e图片, v图形, *v图形.m三维);
	va图形管线.f构造<C画子弹_顶点>((int)E图形管线::e子弹正常, v图形, *v图形.m三维, false);
	va图形管线.f构造<C画子弹_顶点>((int)E图形管线::e子弹高光, v图形, *v图形.m三维, true);
	va图形管线.f构造<C画子弹_线条>((int)E图形管线::e子弹线条, *v图形.m二维);
	va图形管线.f构造<C画三维管线>((int)E图形管线::e三维场景, v图形, *v图形.m三维);
	va图形管线.f构造<C静态立绘管线>((int)E图形管线::e静态立绘, v图形, *v图形.m三维);
}
void C内部载入::f子机() {
	auto &va子机属性 = C游戏::g资源.fg子机属性();
	struct {
		E子机 v名称;
		int v数量;
		E玩家发射 v发射;
		E子机移动 v移动;
	} v子机属性表[] = {
		//序号			数量	发射						移动
		{E子机::e测试, 4, E玩家发射::e灵梦诱导, E子机移动::e位置},
	};
	for (auto &v : v子机属性表) {
		S子机属性 v属性;
		v属性.m数量上限 = v.v数量;
		v属性.m发射 = (int)v.v发射;
		v属性.m移动 = (int)v.v移动;
		va子机属性.f添加((int)v.v名称, v属性);
	}
}
void C内部载入::f玩家子弹() {
	typedef std::tuple<E玩家子弹, t向量2> t;
	t v玩家子弹属性表[] = {
		//名称					判定
		t{E玩家子弹::e测试子弹, {4, 4}}
	};
	auto &va玩家子弹属性 = C游戏::g资源.fg玩家子弹属性();
	for (auto &v : v玩家子弹属性表) {
		S玩家子弹属性 &v属性 = va玩家子弹属性.f取空((int)std::get<0>(v));
		v属性.m判定 = std::get<1>(v);
		v属性.m纹理 = nullptr;
		v属性.m帧半尺寸 = {};
		v属性.m动画帧数 = 0;
	}
}
void C内部载入::f玩家子弹发射() {
	struct S内置发射属性 {
		std::wstring m名称;
		E玩家发射 m标识;
		I工厂<C玩家子弹发射器> *m发射对象;
	};
	const S内置发射属性 v玩家发射表[] = {
		{L"玩家发射.测试", E玩家发射::e测试子弹, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C自机基础>()},
		{L"玩家发射.自机", E玩家发射::e自机基础, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C自机基础>()},
		{L"玩家发射.灵梦诱导", E玩家发射::e灵梦诱导, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C灵梦诱导>()},
		{L"玩家发射.灵梦集中", E玩家发射::e灵梦集中, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C灵梦集中>()},
		{L"玩家发射.魔理沙贯穿", E玩家发射::e魔理沙贯穿, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C魔理沙贯穿>()},
		{L"玩家发射.魔理沙范围", E玩家发射::e魔理沙范围, new C简单工厂<C玩家子弹发射器, 玩家子弹发射::C魔理沙范围>()},
		{L"玩家发射.全屏清弹", E玩家发射::e全屏清弹, new C简单工厂<C玩家子弹发射器, C玩家炸弹简单发射器<玩家炸弹::C全屏清弹>>()},
		{L"玩家发射.测试炸弹", E玩家发射::e测试炸弹, new C简单工厂<C玩家子弹发射器, C玩家炸弹简单发射器<玩家炸弹::C风神录>>()},
	};
	auto &va玩家发射 = C游戏::g资源.fg玩家发射();
	for (auto &v : v玩家发射表) {
		C全局名称标识::f创建(v.m名称, (int)v.m标识);
		va玩家发射.f添加((int)v.m标识, v.m发射对象);
	}
}
void C内部载入::f动画() {
	struct S内置动画属性 {
		E动画 m动画标识;
		I工厂<I动画> *m动画对象;
	};
	const S内置动画属性 v内置动画表[] = {
		{E动画::e静态, new C简单工厂<I动画>},
		{E动画::e道具, new C简单工厂<I动画, C道具动画>},
	};
	auto &va动画扩展 = C游戏::g资源.fg动画();
	for (auto &v : v内置动画表) {
		va动画扩展.f添加((int)v.m动画标识, v.m动画对象);
	}
}
void C内部载入::f模型() {
	auto &v名称标识 = C游戏::fg资源().fg名称标识();
	//纹理
	纹理::C自定义纹理 v纹理;
	v纹理.f初始化(2, 2);
	v纹理.fg像素(0, 0) = 数学::S颜色(1, 0, 0);
	v纹理.fg像素(0, 1) = 数学::S颜色(0, 1, 0);
	v纹理.fg像素(1, 0) = 数学::S颜色(0, 0, 1);
	v纹理.fg像素(1, 1) = 数学::S颜色(1, 1, 0);
	auto &v图形 = C游戏::fg图形();
	auto &v纹理工厂 = v图形.fg纹理工厂();
	v纹理工厂.f创建纹理((int)E纹理::e测试, v纹理);
	v名称标识[L"纹理.微软"] = 计算::fc随机标识();
	//模型
	auto &v模型工厂 = v图形.fg模型工厂();
	int v标识 = 计算::fc随机标识();
	const std::wstring c标识名称 = L"模型.平面.";
	const uint16_t c平面索引[] = {
		0, 1, 2,
		1, 3, 2
	};
	//平面模型
	for (int x = 1; x < 8; ++x) {
		for (int y = 1; y < 8; ++y) {
			const float v宽 = powf(2, x);
			const float v高 = powf(2, y);
			const std::wstring v名称 = c标识名称 + std::to_wstring((int)v宽) + L"x" + std::to_wstring((int)v高);
			const int v标识0 = (v标识++);
			v名称标识[v名称] = v标识0;
			const float v半宽 = v宽 / 2;
			const float v半高 = v高 / 2;
			const S三维顶点 v顶点[] = {
				{{-v半宽, v半高, 0}, {0, 0}},
				{{v半宽, v半高, 0}, {0, 1}},
				{{-v半宽, -v半高, 0}, {1, 0}},
				{{v半宽, -v半高, 0}, {1, 1}}
			};
			v模型工厂.m参数.fs顶点(v顶点, _countof(v顶点));
			v模型工厂.m参数.fs索引(c平面索引, _countof(c平面索引));
			v模型工厂.f创建模型(v标识0);
		}
	}
}
//==============================================================================
// 总载入
//==============================================================================
void f载入() {
	const std::filesystem::path v载入文件 = c启动文件;
	boost::property_tree::wptree v根树;
	C读json文件::f读取(v根树, v载入文件);
	C载入::f汇总({v根树 , v载入文件});
	C内部载入::f图形管线();
	//C内部载入::f子机();
	//C内部载入::f玩家子弹();
	C内部载入::f玩家子弹发射();
	C内部载入::f道具();
	C内部载入::f动画();
	C内部载入::f模型();
	C程序::fs游戏标志((int)E游戏标志::e载入0);
}
}	//namespace 东方山寨