#include <cassert>
#include "游戏_名称标识.h"
#include "游戏.h"
#include "标识.h"
namespace 东方山寨 {
//==============================================================================
// 名称标识引用
//==============================================================================
C名称标识::C名称标识(S名称标识层 &a标识层):
	m标识层(&a标识层),
	m标识组(a标识层.m标识组) {
}
C名称标识::C名称标识(C名称标识 &&a):
	m标识层(a.m标识层),
	m标识组(a.m标识组) {
	a.m标识层 = nullptr;
	a.m标识组 = nullptr;
}
C名称标识::~C名称标识() {
	if (m标识组) {
		m标识组->f弹出层();
	}
}
C名称标识::operator int() const {
	return m标识层->m计算标识;
}
C名称标识 C名称标识::f创建层(const std::wstring &a名称, int a标识) const {
	return m标识组->f创建层(a名称, a标识);
}
const std::wstring &C名称标识::fg当前名称() const {
	return m标识层->m当前名称;
}
const std::wstring &C名称标识::fg计算名称() const {
	return m标识层->m当前名称;
}
int C名称标识::fg当前标识() const {
	return m标识层->m计算标识;
}
int C名称标识::fg计算标识() const {
	return m标识层->m计算标识;
}
//==============================================================================
// 名称标识层
//==============================================================================
S名称标识层::S名称标识层(C名称标识组 &a标识组):
	m标识组(&a标识组) {
}
S名称标识层::operator int() const {
	return m计算标识;
}
void S名称标识层::f重置0(const std::wstring &a名称, int a标识) {
	m当前名称 = a名称;
	m计算名称 = a名称;
	m当前标识 = a标识;
	m计算标识 = a标识;
	mi可创建 = !a名称.empty();
}
void S名称标识层::f重置1(const S名称标识层 &a上一层, const std::wstring &a名称, int a标识) {
	m当前名称 = a名称;
	m计算名称 = C全局名称标识::f连接名称(a上一层.m计算名称, a名称);
	if (a标识) {
		m当前标识 = a标识;
	} else {
		++m当前标识;
	}
	mi可创建 = a上一层.mi可创建 && !a名称.empty();
}
void S名称标识层::f清空() {
	m当前标识 = -1;
}
//==============================================================================
// 名称标识组
//==============================================================================
C名称标识组::C名称标识组() {
	ma标识.reserve(4);
	ma标识.emplace_back(*this);
}
S名称标识层 &C名称标识组::operator [](size_t a层) {
	return ma标识[a层];
}
S名称标识层 &C名称标识组::f创建层(const std::wstring &a名称, int a标识) {
	//创建层
	if (m层数量 == 0) {
		ma标识[0].f重置0(a名称, a标识);
	} else {	//m层数 >= 1
		if (m层数量 == ma标识.size()) {	//容器数量达到上限
			ma标识.emplace_back(*this);
		}
		ma标识[m层数量].f重置1(ma标识[m层数量 - 1], a名称, a标识);
	}
	S名称标识层 &v当前层 = ma标识[m层数量];
	++m层数量;
	//创建名称标识
	v当前层.m计算标识 = fg计算标识();
	C全局名称标识::f创建(v当前层.m计算名称, v当前层.m计算标识);
	return v当前层;
}
size_t C名称标识组::fg当前层号() const {
	return m层数量 - 1;
}
size_t C名称标识组::fg当前层数() const {
	return m层数量;
}
void C名称标识组::f弹出层() {
	//目前的标识只有2层,如果存在更小的层则把更小层加到更大层中
	if (m层数量 <= 2) {
		//0层不自增, 1,2层在重置时自增
	} else {//层>=3
		S名称标识层 &v当前层 = ma标识[m层数量 - 1];
		S名称标识层 &v上一层 = ma标识[m层数量 - 2];
		v上一层.m当前标识 += v当前层.m当前标识 + 1;
		v当前层.f清空();
	}
	--m层数量;
}
int C名称标识组::fg计算标识() const {
	switch (m层数量) {
	case 0:
		return 0;
	case 1:
		return 计算::f标识(fg根标识(), 0, 0);
	case 2:
		return 计算::f标识(fg根标识(), fg主标识(), 0);
	default:
		return 计算::f标识(fg根标识(), fg主标识(), fg子标识());
	}
}
int C名称标识组::fg根标识() const {
	return ma标识[0].m当前标识;
}
int C名称标识组::fg主标识() const {
	return ma标识[1].m当前标识;
}
int C名称标识组::fg子标识() const {
	int v和 = 0;
	for (size_t i = 2; i < m层数量; ++i) {
		v和 += ma标识[i].m当前标识;
	}
	return v和;
}
//==============================================================================
// 全局
//==============================================================================
std::map<std::wstring, int> &C全局名称标识::fg映射() {
	return C游戏::g资源.fg名称标识();
}
int C全局名称标识::f解析(const std::wstring &a名称) {
	const auto &v映射 = fg映射();
	if (auto v = v映射.find(a名称); v != v映射.end()) {
		return v->second;
	} else {
		return 0;
	}
}
void C全局名称标识::f复制(const std::wstring &a入, const std::wstring &a出) {
	auto &v映射 = fg映射();
	v映射[a出] = v映射[a入];
}
void C全局名称标识::f创建(const std::wstring &a名称, int a标识) {
	auto &v映射 = fg映射();
	//assert(v映射.find(a名称) == v映射.end());
	v映射[a名称] = a标识;
}
std::wstring C全局名称标识::f连接名称(const std::wstring &a, const std::wstring &b) {
	return a + L"." + b;
}
}	//namespace 东方山寨