#pragma once
#include "基础_缓冲数组.h"
namespace 东方山寨 {
class I图形缓冲;
template<typename t类>
class I对象图形 {
public:
	I对象图形(const t类 &a对象):
		m对象(&a对象) {
	}
	virtual void f计算() {}
	virtual void f更新() {}
	virtual I图形缓冲 &fg图形缓冲() const = 0;
	const t类 *m对象 = nullptr;
};
template<typename t类, typename t图形缓冲>
class C对象图形 : public I对象图形<t类> {
public:
	C对象图形(const t类 &a对象, C缓冲数组<I图形缓冲> &aa图形缓冲):	//只是创建缓冲和绑定关系
		I对象图形<t类>(a对象),
		m图形缓冲(aa图形缓冲.f新建<t图形缓冲>()) {
	}
	~C对象图形() {
		m图形缓冲->f对象_销毁();
	}
	I图形缓冲 &fg图形缓冲() const override {
		return *m图形缓冲;
	}
	t图形缓冲 *m图形缓冲 = nullptr;
};
}	//namespace 东方山寨