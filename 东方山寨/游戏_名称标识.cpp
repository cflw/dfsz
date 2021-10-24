#include <cassert>
#include "游戏_名称标识.h"
#include "游戏.h"
#include "标识.h"
namespace 东方山寨 {
//==============================================================================
// 名称标识引用
//==============================================================================
C名称标识::C名称标识(C名称标识组 &a标识组, const S名称标识层 &a标识层):
	m标识层(&a标识层),
	m标识组(&a标识组) {
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
S名称标识层::S名称标识层() {
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
	m当前标识 = a标识;
	mi可创建 = a上一层.mi可创建 && !a名称.empty();
}
void S名称标识层::f清空() {
	m当前标识 = -1;
}
//==============================================================================
// 名称标识组
//==============================================================================
C名称标识组::C名称标识组():
	ma标识{} {
}
S名称标识层 &C名称标识组::operator [](int a层) {
	return ma标识[a层];
}
C名称标识 C名称标识组::f创建层(const std::wstring &a名称, int a标识) {
	//创建层
	if (m当前层数 == 0) {
		ma标识[0].f重置0(a名称, a标识);
	} else {	//m层数 >= 1
		ma标识[m当前层数].f重置1(ma标识[m当前层数 - 1], a名称, a标识);
	}
	S名称标识层 &v当前层 = ma标识[m当前层数];
	++m当前层数;
	//创建名称标识
	v当前层.m计算标识 = fg计算标识();
	C全局名称标识::f创建(v当前层.m计算名称, v当前层.m计算标识);
	return C名称标识(*this, v当前层);
}
int C名称标识组::fg当前层号() const {
	return m当前层数 - 1;
}
int C名称标识组::fg当前层数() const {
	return m当前层数;
}
void C名称标识组::f弹出层() {
	--m当前层数;	//不需要清理无效的层
}
int C名称标识组::fg计算标识() const {
	switch (m当前层数) {
	case 0:	//不应该在0层时调用
		return 0;
	case 1:
		return 计算::f标识(fg层标识(0), 0);
	case 2:
		return 计算::f标识(fg层标识(0), fg层标识(1));
	case 3:
		return 计算::f标识(fg层标识(0), fg层标识(1), fg层标识(2));
	case 4:
		return 计算::f标识(fg层标识(0), fg层标识(1), fg层标识(2), fg层标识(3));
	default:	//不应该有其它情况
		__debugbreak();
		return 0;
	}
}
int C名称标识组::fg层标识(int a层) const {
	return ma标识[a层].m当前标识;
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