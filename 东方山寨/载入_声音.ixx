module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "游戏_名称标识.h"
#include "音频引擎.h"
export module 东方山寨.载入.声音;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import 东方山寨.文件系统;
namespace 东方山寨::xml {
void C载入::f音效(const S载入参数 &a参数) {	//音效
	const t节点 &v头部节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v头部节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"声音.") + v头部节点.attribute(L"名称").as_string();
	auto &v声音工厂 = C游戏::fg音频().fg声音工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const t节点 &v音效节点 : a参数.m根.child(L"数据").children(L"音效")) {
		const std::wstring v音效名称 = v音效节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v音效名称, ++v主标识, true);
		v声音工厂.f创建声音(v名称标识1, 文件系统::f计算路径(v音效节点.text().as_string(), a参数.m路径));
	}
}
void C载入::f音乐(const S载入参数 &) {	//音乐

}
}	//namespace 东方山寨::xml