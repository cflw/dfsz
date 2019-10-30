#pragma once
#include <string>
#include <deque>
#include <cflw时间.h>
#include <cflw图形_d2d.h>
namespace 时间 = cflw::时间;
namespace 二维 = cflw::图形::d2d;
namespace 东方山寨 {
class C日志 {
public:
	enum E级别 {
		e错误,
		e警告,
		e调试,
		e消息,
	};
	struct S日志 {
		时间::t时间点 m时间;
		E级别 m级别;
		std::wstring m文本;
		float m出现 = 0;
		float m消失 = 0;
		float fg透明度() const;
	};
	static constexpr float c行距 = 12;
	C日志(二维::C二维 &);
	void f添加(E级别, const std::wstring &);
	void f计算();
	void f显示() const;
	std::deque<S日志> ma日志;
	std::shared_ptr<二维::C画文本> m画文本;
	float m显示位置y = -240;
};
}	//namespace 东方山寨