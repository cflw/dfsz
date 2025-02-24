﻿export module 东方山寨.载入.立绘;
import <string>;
import <map>;
import <experimental/generator>;
import "载入.h";
import "标识.h";
import "程序.h";
import "图形引擎.h";
import "图形资源工厂.h";
import "游戏.h";
import cflw.字符串;
import cflw.字符串.数字;
import 东方山寨.载入.xml;
import 东方山寨.载入.纹理;
import 东方山寨.图形.对话立绘;
import 东方山寨.图形.静态立绘;
using namespace std::literals;
namespace 字符串 = cflw::字符串;
namespace 东方山寨::xml {
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
void C载入::f立绘(const S载入参数 &a参数) {
	//由多张图片拼成的静态立绘
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	auto &v静态立绘管理 = C游戏::fg资源().fg静态立绘();
	//数据
	C解析纹理 v解析纹理{a参数};
	int v主标识 = -1;
	float v缩放 = 1;
	std::vector<S静态立绘组件> va组件;
	std::vector<int> va组件标识;
	for (const t节点 &v立绘节点 : a参数.m根.child(L"数据").children(L"立绘")) {
		const std::wstring v名称0 = v立绘节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, ++v主标识, true);
		S静态立绘属性 &v属性 = v静态立绘管理.ma属性.f取空(v名称标识1);
		v缩放 = v属性.m缩放 = v立绘节点.child(L"缩放").text().as_float(1);
		const std::wstring_view v方向 = v立绘节点.child(L"方向").text().as_string();
		if (v方向 == L"从右向左") {
			v属性.m方向 = E对话方向::e从右向左;
		} else if (v方向 == L"从左向右") {
			v属性.m方向 = E对话方向::e从左向右;
		}
		int v组件标识 = -1;
		//读取组件
		for (const t节点 &v组件节点 : v立绘节点.children(L"组件")) {
			const std::wstring v名称1 = L"组件."s + v组件节点.attribute(L"名称").as_string();
			v组件标识 = v组件节点.attribute(L"标识").as_int(v组件标识 + 1);
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v名称1, v组件标识, true);
			va组件标识.push_back(v名称标识2);
			S静态立绘组件 &v组件 = va组件.emplace_back();
			if (const S解析纹理 &v纹理 = v解析纹理.f解析纹理(v名称标识2, v组件节点.child(L"纹理"))) {
				v组件.m纹理 = v名称标识2;
				const t向量2 &v纹理尺寸 = v纹理.fg尺寸();
			}
			if (const t节点 &v偏移节点 = v组件节点.child(L"偏移")) {
				v组件.m偏移 = 解析::f向量2(v偏移节点);
			}
		}
		//读取表情
		int v表情标识 = -1;
		for (const t节点 &v表情节点 : v立绘节点.children(L"表情")) {
			const std::wstring v名称1_ = v表情节点.attribute(L"名称").as_string();
			const std::wstring v名称1 = L"表情."s + v名称1_;
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v名称1, ++v表情标识, true);
			S静态立绘属性::S表情映射 v表情映射;
			int j = 0;
			const std::wstring_view &v值 = v表情节点.text().as_string();
			for (const std::wstring_view &v子标识s : 字符串::fe分离(v值, L',')) {
				const int v子标识 = 字符串::f到数字<int>(v子标识s);
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
	const C顶点矩形工厂 &v顶点工厂 = C程序::fg图形().fg顶点工厂();
	t顶点矩形参数 v顶点参数;
	auto vp组件标识 = va组件标识.begin();
	for (S静态立绘组件 &v组件 : va组件) {
		va纹理.f编译(v组件.m纹理);	//载入时数据地址会变,之后还要再编译一次
		const t向量2 v纹理尺寸 = v组件.m纹理->m尺寸;
		v顶点参数.fs裁剪尺寸(v纹理尺寸);
		v顶点参数.fs纹理尺寸(v纹理尺寸);
		v顶点参数.fs矩形坐标(v组件.m偏移);
		v顶点参数.fs裁剪坐标({});
		v顶点参数.fs相对原点缩放(t向量2::fc相同(v缩放));
		const int v组件标识 = *vp组件标识;
		v组件.m矩形 = v组件标识;
		v顶点工厂.f创建矩形(v组件标识, v顶点参数);
		v静态立绘管理.ma组件.f添加(v组件标识, v组件);
		++vp组件标识;
	}
}
}	//namespace 东方山寨::xml