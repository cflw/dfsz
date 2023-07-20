#include "载入解析.h"
#include "程序.h"
#include "图形引擎.h"
#include "图形资源工厂.h"
namespace 东方山寨::载入 {
//==============================================================================
// 纹理
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
C解析纹理::C解析纹理(const S载入参数 &a) :
	m载入参数(a),
	m纹理工厂(C程序::fg图形().fg纹理工厂()) {
}
S解析纹理 C解析纹理::f解析纹理(int a标识, const t属性树 &a树) const {
	S解析纹理 v返回;
	v返回.m路径 = C解析助手::f获取路径(m载入参数, a树);
	if (!v返回.m路径.empty()) {
		v返回.m纹理 = m纹理工厂.f创建纹理(a标识, v返回.m路径);
	}
	return v返回;
}
S解析纹理 C解析纹理::f解析纹理(int a标识, const t可选属性树 &a树) const {
	if (a树) {
		return f解析纹理(a标识, *a树);
	} else {
		return {};
	}
}
}	//namespace 东方山寨::载入