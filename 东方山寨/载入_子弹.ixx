module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "游戏_名称标识.h"
#include "子弹基础.h"
export module 东方山寨.载入.子弹;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
namespace 东方山寨::xml {
void C载入::f子弹(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	assert(c子弹标识 == v全局标识);
	auto &v纹理工厂 = C程序::fg图形().fg纹理工厂();
	auto &v顶点工厂 = C程序::fg图形().fg顶点工厂();
	auto &va子弹属性 = C游戏::g资源.fg子弹属性();
	int v主标识 = -1;
	for (const t节点 &v子弹节点 : a参数.m根.child(L"数据").children(L"子弹")) {
		v主标识 = v子弹节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v子弹名称 = v子弹节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v子弹名称, v主标识, true);
		const int v子弹标识 = v名称标识1;
		//纹理
		const t节点 &v纹理节点 = v子弹节点.child(L"纹理");
		const std::wstring v纹理路径 = 解析::f路径(a参数, v纹理节点.child(L"路径"));
		v纹理工厂.f创建纹理(v子弹标识, v纹理路径);
		//顶点
		const t向量2 v纹理尺寸 = 解析::f向量2(v纹理节点.child(L"尺寸"));
		v顶点工厂.f创建矩形_完整纹理(v子弹标识, v纹理尺寸);
		//属性
		S子弹属性 &v属性 = va子弹属性.f取空(v子弹标识);
		const t节点 &v判定节点 = v子弹节点.child(L"判定");
		const std::wstring v判定类型 = v判定节点.attribute(L"类型").as_string();
		if (v判定类型 == L"圆形") {
			const float v纹理尺寸d = (v纹理尺寸.x + v纹理尺寸.y) / 2;
			const t节点 &v视觉节点 = v判定节点.child(L"视觉");
			const t节点 &v修正节点 = v判定节点.child(L"修正");
			const float v判定r = v视觉节点.text().as_float(v纹理尺寸d / 2);
			const float v修正r = v修正节点.text().as_float(v纹理尺寸d / 4);
			v属性.m判定 = t向量2{v判定r, 0};
			v属性.m判定修正 = t向量2{v修正r, v修正r};
		} else if (v判定类型 == L"矩形") {
			const t节点 &v视觉节点 = v判定节点.child(L"视觉");
			const t节点 &v修正节点 = v判定节点.child(L"修正");
			v属性.m判定 = 解析::f向量2(v视觉节点, {v纹理尺寸.x / 2, v纹理尺寸.y / 2});
			v属性.m判定修正 = 解析::f向量2(v修正节点, {v纹理尺寸.x / 4, v纹理尺寸.y / 4});
		} else {	//未知类型,取纹理尺寸作为判定尺寸
			v属性.m判定 = t向量2{v纹理尺寸.x / 2, 0};
			v属性.m判定修正 = t向量2{v纹理尺寸.x / 4, v纹理尺寸.y / 4};
		}
		v属性.m纹理 = v子弹标识;
		v属性.m顶点 = v子弹标识;
		v属性.m动画帧数 = 1;
	}
}
}	//东方山寨::xml