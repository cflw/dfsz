#include "����.h"
#include "��Ϸ.h"
#include "ͼ��.h"
#include "���ӵ�.h"
namespace ����ɽկ {
void f����_���ӵ�() {
	auto vͼ�� = C����::fͼ��();
	std::pair<E���ӵ�, I���ӵ�*> v���ӵ���[] = {
		{E���ӵ�::e����, new C���ӵ�_����(vͼ��->v��ά)},
		{E���ӵ�::e����, new C���ӵ�_����(vͼ��->v��ά)},
	};
	auto &va���ӵ� = C��Ϸ::fa���ӵ��ӿ�();
	for (auto &v : v���ӵ���) {
		va���ӵ�.f���((int)v.first, v.second);
	}
}
}
