module;
#include "程序.h"
#include "游戏.h"
#include "标识.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
#include "游戏_名称标识.h"
export module 东方山寨.载入.纹理;
import 东方山寨.载入.xml;
import 东方山寨.xml.解析;
import 东方山寨.文件系统;
export namespace 东方山寨::xml {
struct S解析纹理 {
	operator bool() const;
	const t向量2 &fg尺寸() const;
	const std::wstring &fg路径() const;
	const S纹理 *m纹理 = nullptr;
	std::wstring m路径;	//全路径
};
class C解析纹理 {
public:
	C解析纹理(const S载入参数 &);
	S解析纹理 f解析纹理(int 标识, const t节点 &) const;
	const S载入参数 &m载入参数;
	const C纹理工厂 &m纹理工厂;
};
}	//namespace 东方山寨::xml
module: private;
namespace 东方山寨::xml {
//==============================================================================
// 解析纹理节点
//==============================================================================
S解析纹理::operator bool() const {
	return m纹理;
}
const t向量2 &S解析纹理::fg尺寸() const {
	return m纹理->m尺寸;
}
const std::wstring &S解析纹理::fg路径() const {
	return m路径;
}
//解析纹理
C解析纹理::C解析纹理(const S载入参数 &a参数) :
	m载入参数(a参数),
	m纹理工厂(C程序::fg图形().fg纹理工厂()) {
}
S解析纹理 C解析纹理::f解析纹理(int a标识, const t节点 &a纹理节点) const {
	S解析纹理 v返回;
	v返回.m路径 = 解析::f路径(m载入参数, a纹理节点.child(L"路径"));
	if (!v返回.m路径.empty()) {
		v返回.m纹理 = m纹理工厂.f创建纹理(a标识, v返回.m路径);
	}
	return v返回;
}
//==============================================================================
// 解析纹理xml
//==============================================================================
void C载入::f纹理(const S载入参数 &a参数) {
	const t节点 &v节点 = a参数.m根.child(L"头部");
	const int v全局标识 = v节点.attribute(L"标识").as_int(计算::fc随机标识());
	const std::wstring v全局名称 = std::wstring(L"纹理.") + v节点.attribute(L"名称").as_string();
	auto &v纹理工厂 = C程序::fg图形().fg纹理工厂();
	C名称标识组 v名称标识组;
	const C名称标识 v名称标识0 = v名称标识组.f创建层(v全局名称, v全局标识);
	int v主标识 = -1;
	for (const auto &v纹理节点 : a参数.m根.child(L"数据").children(L"纹理")) {
		const std::wstring v纹理名称 = v纹理节点.attribute(L"名称").as_string();
		const C名称标识 v名称标识1 = v名称标识0.f创建层(v纹理名称, ++v主标识, true);
		const std::wstring_view &v纹理路径 = v纹理节点.text().as_string();
		v纹理工厂.f创建纹理(v名称标识1, 文件系统::f计算路径(v纹理路径, a参数.m路径).native());
	}
}
}	//namespace 东方山寨::xml