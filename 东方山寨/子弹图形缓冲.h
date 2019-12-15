#pragma once
#include "基础.h"
#include "基础_游戏对象.h"
#include "子弹图形接口.h"
namespace 东方山寨 {
class C子弹;
class I画子弹;
class I子弹图形数据;
using tp子弹图形数据 = std::unique_ptr<I子弹图形数据>;
class C子弹图形缓冲 : public C简单游戏对象 {
public:
	C子弹图形缓冲() = default;
	void f显示() const;
	I画子弹 *m绘制 = nullptr;
	tp子弹图形数据 m图形数据 = nullptr;
	int m显示编号 = 0;
	int m图层 = 0;
	bool mi可显示 = false;
};
}	//namespace 东方山寨