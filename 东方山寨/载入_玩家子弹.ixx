module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "玩家子弹基础.h"
export module 东方山寨.载入.玩家子弹;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
namespace 东方山寨::xml {
void C载入::f玩家子弹(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const int v全局顶点引用 = v头部节点.child(L"顶点").text().as_int();
	const int v全局纹理引用 = v头部节点.child(L"纹理").text().as_int();
	auto &va玩家子弹属性 = C游戏::fg资源().fg玩家子弹属性();
	int v主标识 = -1;
	for (const t节点 &v玩家子弹节点 : a参数.m根.child(L"数据").children(L"玩家子弹")) {
		v主标识 = v玩家子弹节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v玩家子弹名称 = v玩家子弹节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v玩家子弹名称, v主标识, true);
		const int v玩家子弹标识 = v名称标识1;
		S玩家子弹属性 &v玩家子弹属性 = va玩家子弹属性.f取空(v玩家子弹标识);
		//图形
		解析::f引用赋值(v玩家子弹属性.m纹理, v全局纹理引用, v玩家子弹节点.child(L"纹理"));
		解析::f引用赋值(v玩家子弹属性.m顶点, v全局顶点引用, v玩家子弹节点.child(L"顶点"));
		//消失纹理
		const t节点 &v消失纹理节点 = v玩家子弹节点.child(L"消失纹理");
		const std::wstring_view v消失纹理类型 = v消失纹理节点.attribute(L"类型").as_string();
		if (v消失纹理类型 == L"引用") {
			解析::f引用赋值(v玩家子弹属性.m消失纹理, v全局纹理引用, v消失纹理节点);
		} else {
			v玩家子弹属性.m消失纹理 = v玩家子弹属性.m纹理;
		}
		//消失顶点
		const t节点 &v消失顶点节点 = v玩家子弹节点.child(L"消失顶点");
		const std::wstring_view v消失顶点类型 = v消失顶点节点.attribute(L"类型").as_string();
		if (v消失顶点类型 == L"引用") {
			解析::f引用赋值(v玩家子弹属性.m消失顶点, v全局顶点引用, v消失顶点节点);
		} else {
			v玩家子弹属性.m消失顶点 = v玩家子弹属性.m顶点;
		}
		//动画
		v玩家子弹属性.m动画帧数 = v玩家子弹节点.child(L"动画帧数").text().as_int();
		v玩家子弹属性.m消失帧数 = v玩家子弹节点.child(L"消失帧数").text().as_int();
		//伤害
		const t节点 &v伤害节点 = v玩家子弹节点.child(L"伤害");
		v玩家子弹属性.m伤害 = v伤害节点.text().as_float(10);
		const std::wstring_view v伤害度量 = v伤害节点.attribute(L"度量").as_string();
		v玩家子弹属性.mi秒伤 = v伤害度量 == L"每秒";
		if (v玩家子弹属性.mi秒伤) {
			v玩家子弹属性.m伤害 /= c计算频率<float>;
		}
		//判定
		const t节点 &v判定节点 = v玩家子弹节点.child(L"判定");
		if (!v判定节点.empty()) {
			const std::wstring_view v判定类型 = v判定节点.attribute(L"类型").as_string();
			if (v判定类型 == L"圆形") {
				v玩家子弹属性.m判定.x = v判定节点.text().as_float();
			} else if (v判定类型 == L"矩形") {
				v玩家子弹属性.m判定 = 解析::f向量2(v判定节点, {4, 4});
			} else {
				v玩家子弹属性.m判定.x = 4;
			}
		}
	}
}
}	//namespace 东方山寨::xml