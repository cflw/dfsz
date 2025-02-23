module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "游戏_名称标识.h"
#include "子机.h"
#include "子机移动接口.h"
#include "子机移动_位置.h"
export module 东方山寨.载入.子机;
import 东方山寨.载入.内部;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
namespace 东方山寨::载入 {
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
}	//namespace 东方山寨::载入
namespace 东方山寨::xml {
class C解析子机移动 {
public:
	using t返回值 = std::unique_ptr<I工厂<I子机移动>> ;
	using tf解析 = std::unique_ptr<I工厂<I子机移动>>(*)(int, const t节点 &);
	static std::unique_ptr<I工厂<I子机移动>> f位置(int a子机数, const t节点 &a移动节点) {
		const int v数量 = (1 + a子机数) * a子机数 / 2;//=1+2+..+子机数
		const int v总数量 = v数量 * 2;	//高速+低速
		std::vector<t向量2> v数组;
		for (const t节点 &v位置节点 : a移动节点.children(L"位置")) {
			const t向量2 &v位置 = 解析::f向量2(v位置节点);
			v数组.emplace_back(v位置);
		}
		assert(v数组.size() <= v总数量);
		auto va属性 = std::make_shared<子机移动::C位置::S属性>(v数组.data());	//没有排序,所以xml<位置>要先排好序
		return std::make_unique<子机移动::C位置::C工厂>(va属性);
	}
};
void C载入::f子机(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	assert(c子机标识 == v全局标识);
	const int v全局纹理引用 = v头部节点.child(L"纹理").text().as_int();
	const int v全局顶点引用 = v头部节点.child(L"顶点").text().as_int();
	const int v全局移动引用 = v头部节点.child(L"移动").text().as_int();
	const int v全局发射引用 = v头部节点.child(L"发射").text().as_int();
	const int v全局子弹引用 = v头部节点.child(L"子弹").text().as_int();
	auto &va子机 = C游戏::g资源.fg子机属性();
	auto &va子机移动 = C游戏::g资源.fg子机移动();
	int v主标识 = -1;
	for (const auto &v子机节点 : a参数.m根.child(L"数据").children(L"玩家子机")) {
		v主标识 = v子机节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v子机名称 = v子机节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v子机名称, v主标识, true);
		const int v子机标识 = v名称标识1;
		S子机属性 &v子机属性 = va子机.f取空(v子机标识);
		//子机数
		const int v子机数 = v子机节点.child(L"子机数").text().as_int();
		v子机属性.m数量上限 = v子机数;
		解析::f引用赋值(v子机属性.m纹理, v全局纹理引用, v子机节点.child(L"纹理"));
		解析::f引用赋值(v子机属性.m顶点, v全局顶点引用, v子机节点.child(L"顶点"));
		解析::f引用赋值(v子机属性.m发射, v全局发射引用, v子机节点.child(L"发射"));
		解析::f引用赋值(v子机属性.m子弹属性, v全局子弹引用, v子机节点.child(L"子弹"));
		//移动
		const t节点 &v子机移动节点 = v子机节点.child(L"移动");
		if (!v子机移动节点.empty()) {
			const std::wstring_view v类型 = v子机移动节点.attribute(L"类型").as_string();
			if (v类型 == L"引用") {
				解析::f引用赋值(v子机属性.m移动, v全局移动引用, v子机移动节点);
			} else if (v类型 == L"位置") {
				v子机属性.m移动 = v子机标识;
				va子机移动.f添加(v子机标识, C解析子机移动::f位置(v子机数, v子机移动节点).release());
			} else {
				v子机属性.m移动 = v全局移动引用;
			}
		} else {
			v子机属性.m移动 = v全局移动引用;
		}
	}
}
}	//东方山寨::xml