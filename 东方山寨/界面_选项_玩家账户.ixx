module;
#include "界面包含.h"
export module 东方山寨.界面_选项.玩家账户;
export import 东方山寨.界面_选项.选项列表;
import 用户界面.控件;
export namespace 东方山寨 {
class W玩家帐户 : public W选项列表 {
public:
	W玩家帐户() = default;
	void f响应_载入() override;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void W玩家帐户::f响应_载入() {
	f添加行(L"{option.playername}", std::make_unique<用户界面::W文本框>());
}
}	//namespace 东方山寨