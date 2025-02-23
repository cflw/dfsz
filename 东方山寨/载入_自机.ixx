module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "游戏_名称标识.h"
#include "自机.h"
export module 载入.自机;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import 东方山寨.文件系统;
namespace 东方山寨::xml {
void C载入::f自机(const S载入参数 &a参数) {
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = v头部节点.attribute(L"名称").as_string();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	const int v全局发射引用 = v头部节点.child(L"发射").text().as_int();
	const int v全局动画引用 = v头部节点.child(L"动画").text().as_int();
	const int v全局顶点引用 = v头部节点.child(L"顶点").text().as_int();
	const int v全局子弹引用 = {v头部节点.child(L"子弹").text().as_int()};
	auto &v纹理工厂 = C程序::fg图形().fg纹理工厂();
	auto &va自机属性 = C游戏::g资源.fg自机属性();
	int v主标识 = -1;
	for (const auto &v自机节点 : a参数.m根.child(L"数据").children(L"玩家飞机")) {
		v主标识 = v自机节点.attribute(L"标识").as_int(v主标识 + 1);
		const std::wstring v自机名称 = v自机节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v自机名称, v主标识, true);
		const int v自机标识 = v名称标识1;
		auto &v属性 = va自机属性.f取空(v自机标识);
		//纹理
		const t节点 &v纹理节点 = v自机节点.child(L"纹理");
		const std::wstring v纹理路径 = v纹理节点.child(L"路径").text().as_string();
		if (!v纹理路径.empty()) {
			v纹理工厂.f创建纹理(v自机标识, 文件系统::f计算路径(v纹理路径, a参数.m路径).native());
			v属性.m纹理 = v自机标识;
		} else {
			v属性.m纹理 = nullptr;
		}
		//属性
		v属性.m判定半径 = v自机节点.child(L"判定").text().as_float(C自机::c判定半径);
		v属性.m擦弹半径 = v自机节点.child(L"擦弹").text().as_float(C自机::c擦弹半径);
		v属性.m道具半径 = v自机节点.child(L"道具").text().as_float(C自机::c道具半径);
		v属性.m移动速度 = v自机节点.child(L"移动速度").text().as_float(C自机::c移动速度);
		解析::f引用赋值(v属性.m动画, v全局动画引用, v自机节点.child(L"动画"));
		解析::f引用赋值(v属性.m顶点, v全局顶点引用, v自机节点.child(L"顶点"));
		解析::f引用赋值(v属性.m发射子弹, v全局发射引用, v自机节点.child(L"发射"));
		解析::f引用赋值(v属性.m子弹属性, v全局子弹引用, v自机节点.child(L"子弹"));
	}
}
}	//namespace 东方山寨::xml