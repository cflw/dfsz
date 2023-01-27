#include <string>
#include <map>
#include "载入.h"
#include "载入解析.h"
#include "标识.h"
#include "图形_对话立绘.h"
#include "图形_静态立绘.h"
#include "游戏.h"
using namespace std::literals;
namespace 东方山寨::载入 {
E立绘表情 f字符串到立绘表情(const std::wstring &a字符串) {
	static const std::map<std::wstring, E立绘表情> ca表情 = {
		{L"无", E立绘表情::e无},
		{L"正常", E立绘表情::e正常},
		{L"高兴", E立绘表情::e高兴},
		{L"伤心", E立绘表情::e伤心},
		{L"愤怒", E立绘表情::e愤怒},
	};
	if (auto v找 = ca表情.find(a字符串); v找 != ca表情.end()) {
		return v找->second;
	}
	return E立绘表情::e无;
}
void C载入::f立绘列表1(const S载入参数 &a) {
	//由多张图片拼成的静态立绘
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	auto &v静态立绘管理 = C游戏::fg资源().fg静态立绘();
	//数据
	C解析纹理 v解析纹理{a};
	const auto &va数据 = a.m树.get_child(L"数据");
	int v主标识 = -1;
	float v缩放 = 1;
	std::vector<S静态立绘组件> va组件;
	std::vector<int> va组件标识;
	for (const auto &[v名称0_, v树0] : va数据) {
		const std::wstring v名称0 = v树0.get<std::wstring>(L"名称");
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识, true);
		S静态立绘属性 &v属性 = v静态立绘管理.ma属性.f取空(v名称标识1);
		v缩放 = v属性.m缩放 = v树0.get<float>(L"缩放", 1);
		const int v方向 = v树0.get<int>(L"方向", 0);
		v属性.m方向 = (E对话方向)v方向;
		int v组件标识 = -1;
		//读取组件
		for (const auto &[v名称1_, v树1] : v树0.get_child(L"组件")) {
			const std::wstring v名称1 = L"组件."s + v树1.get<std::wstring>(L"名称");
			v组件标识 = v树1.get<int>(L"标识", v组件标识 + 1);
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v名称1, v组件标识, true);
			va组件标识.push_back(v名称标识2);
			S静态立绘组件 &v组件 = va组件.emplace_back();
			if (const S解析纹理 v纹理 = v解析纹理.f解析纹理(v名称标识2, v树1.get_child(L"纹理"))) {
				v组件.m纹理 = v名称标识2;
				const t向量2 &v纹理尺寸 = v纹理.fg尺寸();
			}
			if (const auto &v树2 = v树1.get_child_optional(L"偏移")) {
				v组件.m偏移 = C解析助手::f获取向量2(*v树2);
			}
		}
		//读取表情
		int v表情标识 = -1;
		for (const auto &[v名称1_, v树1] : v树0.get_child(L"表情")) {
			const std::wstring v名称1 = L"表情."s + v名称1_;
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v名称1, ++v表情标识, true);
			S静态立绘属性::S表情映射 v表情映射;
			int j = 0;
			for (const auto &[v名称2_, v树2] : v树1.get_child(L"")) {
				int v子标识 = v树2.get_value<int>();
				int v计算标识 = 计算::f标识(v全局标识, v主标识, v子标识);
				v表情映射.ma组件[j] = v计算标识;
				++j;
			}
			const E立绘表情 v表情 = f字符串到立绘表情(v名称1_);
			v属性.ma表情映射.emplace(v表情, v表情映射);
		}
	}
	//创建矩形&添加组件
	assert(va组件.size() == va组件标识.size());
	auto &va纹理 = C游戏::fg图形().fg纹理();
	C顶点矩形工厂 &v顶点工厂 = C游戏::g资源.fg顶点工厂();
	auto vp组件标识 = va组件标识.begin();
	for (S静态立绘组件 &v组件 : va组件) {
		va纹理.f编译(v组件.m纹理);	//载入时数据地址会变,之后还要再编译一次
		const t向量2 v纹理尺寸 = v组件.m纹理->m尺寸;
		v顶点工厂.m参数.fs裁剪尺寸(v纹理尺寸);
		v顶点工厂.m参数.fs纹理尺寸(v纹理尺寸);
		v顶点工厂.m参数.fs矩形坐标(v组件.m偏移);
		v顶点工厂.m参数.fs裁剪坐标({});
		v顶点工厂.m参数.fs相对原点缩放(t向量2::fc相同(v缩放));
		const int v组件标识 = *vp组件标识;
		v组件.m矩形 = v组件标识;
		v顶点工厂.f创建矩形(v组件标识);
		v静态立绘管理.ma组件.f添加(v组件标识, v组件);
		++vp组件标识;
	}
}
}	//namespace 东方山寨::载入