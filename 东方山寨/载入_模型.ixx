module;
export module 东方山寨.载入.模型;
import 东方山寨.载入.内部;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import "程序.h";
import "游戏.h";
import "标识.h";
import "图形引擎.h";
import "图形资源工厂.h";
import "游戏_名称标识.h";
namespace 东方山寨::载入 {
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
}	//namespace 东方山寨::载入
namespace 东方山寨::xml {
void C载入::f模型(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const std::wstring c模型名称 = L"模型";
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"模型.") + v头部节点.attribute(L"名称").as_string();
	auto &v模型工厂 = C游戏::fg图形().fg模型工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const t节点 &v模型节点 : a参数.m根.child(L"数据").children(L"模型")) {
		const std::wstring v默认名称 = c模型名称 + std::to_wstring(++v主标识);
		const std::wstring &v名称0 = v模型节点.attribute(L"名称").as_string(v默认名称.c_str());
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v名称0, v主标识, true);
		std::vector<S三维顶点> va顶点;
		for (const t节点 &v顶点节点 : v模型节点.children(L"顶点")) {
			S三维顶点 v顶点;
			v顶点.m坐标 = 解析::f向量3(v顶点节点.child(L"几何坐标"));
			v顶点.m纹理 = 解析::f向量2(v顶点节点.child(L"纹理坐标"));
			va顶点.push_back(v顶点);
		}
		std::vector<三维::t索引> va索引;
		for (const t节点 &v面节点 : v模型节点.children(L"面")) {
			const auto &[i, j, k] = 解析::f三元组<三维::t索引, 三维::t索引, 三维::t索引>(v面节点);
			va索引.push_back(i);
			va索引.push_back(j);
			va索引.push_back(k);
		}
		v模型工厂.m参数.fs顶点(va顶点.data(), va顶点.size());
		v模型工厂.m参数.fs索引(va索引.data(), va索引.size());
		v模型工厂.f创建模型(v名称标识1);
	}
}
}	//namespace 东方山寨::xml