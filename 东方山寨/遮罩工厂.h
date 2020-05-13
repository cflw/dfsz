#pragma once
#include "基础_对象数组.h"
#include "遮罩基础.h"
namespace 东方山寨 {
class C遮罩工厂 {
public:
	class C实现 {
	public:
		void f初始化_数组(C对象数组<I遮罩> &);
		bool fi有空();
		void f产生遮罩(const std::shared_ptr<I遮罩> &);
		C对象数组<I遮罩> *ma遮罩 = nullptr;
	};
	C遮罩工厂(C实现 &);
	~C遮罩工厂();
	template<typename t, typename...t参数> std::shared_ptr<t> f产生遮罩(t参数 &&...a参数);
	C实现 *m实现 = nullptr;
};
template<typename t, typename...t参数> std::shared_ptr<t> C遮罩工厂::f产生遮罩(t参数 &&...a参数) {
	if (m实现->fi有空()) {
		std::shared_ptr<t> v遮罩 = std::make_shared<t>(a参数...);
		m实现->f产生遮罩(v遮罩);
	}
	return nullptr;
}
}	//namespace 东方山寨