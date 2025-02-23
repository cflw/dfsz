module;
export module 东方山寨.载入.图形;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import "程序.h";
import "标识.h";
import "图形引擎.h";
import "图形资源工厂.h";
namespace 东方山寨::xml {
void C载入::f图形(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const auto &v纹理工厂 = C程序::fg图形().fg纹理工厂();
	const auto &v顶点工厂 = C程序::fg图形().fg顶点工厂();
	t顶点矩形参数 v顶点参数;
	int v主标识 = -1;
	for (const t节点 &v图形节点 : a参数.m根.child(L"数据").children(L"图形")) {
		v主标识 = v图形节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v默认图形名称 = std::wstring(L"图形") + std::to_wstring(v主标识);
		const std::wstring v图形名称 = v图形节点.attribute(L"名称").as_string(v默认图形名称.c_str());
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v图形名称, v主标识, true);
		//纹理
		const t节点 &v纹理节点 = v图形节点.child(L"纹理");
		const std::wstring_view v纹理类型 = v纹理节点.attribute(L"类型").as_string(L"文件");
		if (v纹理类型 == L"文件") {
			if (const t节点 &v纹理路径节点 = v纹理节点.child(L"路径"); !v纹理路径节点.empty()) {
				if (const std::wstring &v纹理路径 = 解析::f路径(a参数, v纹理路径节点); !v纹理路径.empty()) {
					v纹理工厂.f创建纹理(v名称标识1, v纹理路径);
				}
			}
		}
		const t向量2 v纹理尺寸 = 解析::f向量2(v纹理节点.child(L"尺寸"));
		v顶点参数.fs纹理尺寸(v纹理尺寸);
		//顶点
		int v顶点矩形标识 = 0;
		for (const t节点 &v顶点节点 : v图形节点.children(L"顶点")) {
			const std::wstring v默认顶点名称 = std::wstring(L"顶点") + std::to_wstring(v顶点矩形标识);
			const std::wstring v顶点名称 = v顶点节点.attribute(L"名称").as_string(v默认顶点名称.c_str());
			const C名称标识 v名称标识2 = v名称标识1.f创建层(v顶点名称, v顶点矩形标识);
			++v顶点矩形标识;
			const auto [x, y] = 解析::f二元组<float, float>(v顶点节点.child(L"裁剪坐标"), {0, 0});
			const auto [v宽, v高] = 解析::f二元组<float, float>(v顶点节点.child(L"裁剪尺寸"), {v纹理尺寸.x - x, v纹理尺寸.y - y});
			const auto [v行数, v列数] = 解析::f二元组<int, int>(v顶点节点.child(L"顶点细分"), {1, 1});
			const auto [v偏移x, v偏移y] = 解析::f二元组<float, float>(v顶点节点.child(L"顶点偏移"), {0, 0});
			const float v分宽 = v宽 / (float)v列数;
			const float v分高 = v高 / (float)v行数;
			//创建矩形
			const t向量2 v顶点尺寸{v分宽, v分高};
			v顶点参数.fs裁剪坐标({x, y});
			v顶点参数.fs裁剪尺寸(v顶点尺寸);
			v顶点参数.fs矩形坐标({v偏移x, v偏移y});
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
}	//namespace 东方山寨::xml