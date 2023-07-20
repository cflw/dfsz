module;
#include <string>
#include "程序设置.h"
export module 东方山寨.界面语言;
import 东方山寨.设置管理;
export namespace 东方山寨 {
//跟踪语言设置并触发相应事件的类. 没有跟踪游戏中语言的功能,因为游戏中不能修改语言
class I跟踪界面语言 {
public:
	virtual void f事件_刷新文本() = 0;
};
}	//namespace 东方山寨
