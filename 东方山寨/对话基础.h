#pragma once
#include "����.h"
namespace ����ɽկ {
enum class E����״̬ {
	e�۽�,
	e��ʧ,
};
//ͼ��
class I�Ի�����;
//����
class C�Ի�����;
class C�Ի��ű�;
class I�Ի��¼�;
using ta�Ի��¼� = std::vector<std::unique_ptr<I�Ի��¼�>>;
using tp�Ի��ű� = std::shared_ptr<const ta�Ի��¼�>;
struct S�Ի�����_�Ի� {
	std::wstring m�ı�;
	bool m����;
};
struct S�Ի�����_��ʾ���� {
	const I����<I�Ի�����> *m���湤��;
	int m��ʶ;
	bool m����;
};
struct S�Ի�����_����״̬ {
	int m��ʶ;
	E����״̬ m״̬;
};
}