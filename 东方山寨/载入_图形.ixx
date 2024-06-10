module;
#include "载入.h"
#include "载入解析.h"
#include "程序.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
export module 东方山寨.载入.图形;
namespace 东方山寨::载入 {
void C载入::f图形(const S载入参数 &a) {
	const int v全局标识 = a.m树.get<int>(L"全局.标识", 计算::fc随机标识());
	const std::wstring &v全局名称 = a.m树.get<std::wstring>(L"全局.名称");
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const auto &v纹理工厂 = C程序::fg图形().fg纹理工厂();
	const auto &v顶点工厂 = C程序::fg图形().fg顶点工厂();
	t顶点矩形参数 v顶点参数;
	int v主标识 = -1;
	for (const auto &[v名称0_, v节点0] : a.m树.get_child(L"数据")) {
		v主标识 = v节点0.get<int>(L"标识", v主标识 + 1);
		const std::wstring &v图形名称 = v节点0.get<std::wstring>(L"名称", std::wstring(L"图形") + std::to_wstring(v主标识));
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v图形名称, v主标识, true);
		//纹理
		const t属性树 &v纹理节点 = v节点0.get_child(L"纹理");
		if (const std::wstring v纹理路径 = C解析助手::f获取路径(a, v纹理节点); !v纹理路径.empty()) {
			v纹理工厂.f创建纹理(v名称标识1, v纹理路径);
		}
		const t向量2 v纹理尺寸 = C解析助手::f获取尺寸(v纹理节点.get_child(L"尺寸"));
		v顶点参数.fs纹理尺寸(v纹理尺寸);
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
			const t向量2 v顶点尺寸{ v分宽, v分高 };
			v顶点参数.fs裁剪坐标({ x, y });
			v顶点参数.fs裁剪尺寸(v顶点尺寸);
			v顶点参数.fs矩形坐标({ v偏移x, v偏移y });
			int v切片标识 = 0;
			for (auto &v循环 : v顶点参数.f循环(v列数, v行数)) {
				const C名称标识 v名称标识3 = v名称标识2.f创建层(std::to_wstring(v切片标识), v切片标识, true);
				++v切片标识;
				v循环.f变换_平移(v顶点尺寸);
				v顶点工厂.f创建矩形(v名称标识3, v顶点参数);
			}
		}
	}
}
}	//namespace 东方山寨::载入