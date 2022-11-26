module;
#include "程序实现.h"
export module 东方山寨.游戏输入控制;
export import cflw.工具.单例;
import 东方山寨.图形_帧速率;
export import 东方山寨.游戏输入;
import 东方山寨.游戏输入_录像;
import 东方山寨.游戏录像管理;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
class C游戏输入控制 : public 工具::C弱单例<C游戏输入控制> {
public:
	C游戏输入控制(C程序实现 &a实现, C输入引擎 &a输入):
		mp实现(&a实现),
		mp输入(&a输入) {
	}
	C游戏输入 &fc直接() {
		if (!m游戏输入_直接) {
			m游戏输入_直接 = std::make_unique<C游戏输入>(*mp输入);
		}
		return *m游戏输入_直接;
	}
	C游戏输入_录像 &fc录像(C录像机 &a录像机) {
		if (!m游戏输入_录像) {
			m游戏输入_录像 = std::make_unique<C游戏输入_录像>(*mp输入, mp实现->m画帧速率->m计算);
		}
		m游戏输入_录像->mp录像 = &a录像机;
		return *m游戏输入_录像;

	}
	C游戏输入_回放 &fc回放(C回放机 &a回放机) {
		if (!m游戏输入_回放) {
			m游戏输入_回放 = std::make_unique<C游戏输入_回放>(*mp输入);
		}
		m游戏输入_回放->mp回放 = &a回放机;
		return *m游戏输入_回放;
	}
	C程序实现 *mp实现 = nullptr;
	C输入引擎 *mp输入 = nullptr;
	std::unique_ptr<C游戏输入> m游戏输入_直接;
	std::unique_ptr<C游戏输入_录像> m游戏输入_录像;
	std::unique_ptr<C游戏输入_回放> m游戏输入_回放;
};
}	//namespace 东方山寨