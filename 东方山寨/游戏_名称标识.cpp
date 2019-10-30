#include "游戏_名称标识.h"
#include "游戏.h"
#include "标识.h"
namespace 东方山寨 {
int C名称标识::f解析名称(const std::wstring &a名称) {
	const auto &v名称标识 = C游戏::g资源.fg名称标识();
	if (auto v = v名称标识.find(a名称); v != v名称标识.end()) {
		return v->second;
	} else {
		return 0;
	}
}
void C名称标识::f复制名称标识(const std::wstring &a入, const std::wstring &a出) {
	auto &v名称标识 = C游戏::g资源.fg名称标识();
	v名称标识[a出] = v名称标识[a入];
}
C名称标识::C名称标识(const std::wstring &a名称, int a标识):
	m名称(a名称),
	m层(0),
	m标识(std::make_shared<std::vector<int>>(3)),
	mi可创建(!a名称.empty()) {
	m标识->at(0) = a标识;
}
C名称标识::C名称标识(const std::wstring &a名称, int a标识, C名称标识 const *a上一层) :
	m名称(a名称),
	m层(a上一层->m层 + 1),
	m标识(a上一层->m标识),
	mi可创建(a上一层->mi可创建 && !a名称.empty()) {
	if (m层 == m标识->size()) {	//更小的层
		m标识->push_back(a标识);
	} else {
		if (a标识) {
			m标识->at(m层) = a标识;
		}
	}
	switch (m层) {
	case 0:	//同时清空1,2层
		m标识->at(1) = 0;
	case 1:
		m标识->at(2) = 0;
	}
}
C名称标识::C名称标识(C名称标识 &&a标识) :
	m名称(std::move(a标识.m名称)),
	m层(a标识.m层),
	m标识(std::move(a标识.m标识)),
	mi可创建(a标识.mi可创建){
	a标识.m层 = -1;	//只是为了确定是临时值
}
C名称标识::~C名称标识() {
	//目前的标识只有2层,如果存在更小的层则把更小层加到更大层中
	if (m层 <= 0) {
		//0层和临时值不自增
	} else if (m层 < 2) {
		++m标识->at(m层);
	} else {	//层>=2
		if (m层 == m标识->size() - 1) {	//最后一层,自增
			++m标识->at(m层);
		} else {	//倒数第二层,[-1]加到[-2]中,删除[-1],不自增
			m标识->at(m层) += m标识->back();
			m标识->pop_back();
		}
	}
}
void C名称标识::fs名称(const std::wstring &a名称) {
	m名称 = a名称;
}
C名称标识 C名称标识::f创建层(const std::wstring &a名称, int a标识) const {
	C名称标识 v(m名称 + L"." + a名称, a标识, this);
	if (v.mi可创建) {
		v.f创建名称标识();
	}
	return v;
}
int C名称标识::fg标识() const {
	auto &v名称标识 = C游戏::g资源.fg名称标识();
	if (auto v找 = v名称标识.find(m名称); v找 != v名称标识.end()) {
		return v找->second;
	} else {
		return 0;
	}
}
int C名称标识::fg计算标识() const {
	return 计算::f标识(m标识->at(0), m标识->at(1), fg子标识());
}
int C名称标识::fg主标识() const {
	return  m标识->at(1);
}
int C名称标识::fg子标识() const {
	int v和 = 0;
	for (auto i = m标识->begin() + 2; i < m标识->end(); ++i) {
		v和 += *i;
	}
	return v和;
}
void C名称标识::f创建名称标识() const {
	auto &v名称标识 = C游戏::g资源.fg名称标识();
	if (v名称标识.find(m名称) == v名称标识.end()) {
		v名称标识[m名称] = fg计算标识();
	}
}
}	//namespace 东方山寨