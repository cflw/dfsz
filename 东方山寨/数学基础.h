#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
//=============================================================================
// �߽��ж�
//=============================================================================
class C�߽� {
public:
	static const C�߽� c�߿�, c����, c�Ի�;
	C�߽�() = default;
	C�߽�(float, float, float, float);
	static C�߽� fc���ľ���(float, float);
	//����
	float fg���() const;
	float fg�߶�() const;
	float fgб��() const;
	float fg����() const;
	float fg��߶�() const;
	float fg��б��() const;
	//�����ж�
	bool f����ж�(const t����2 &, float) const;
	bool f�ұ��ж�(const t����2 &, float) const;
	bool f�ϱ��ж�(const t����2 &, float) const;
	bool f�±��ж�(const t����2 &, float) const;
	bool f����ж�(const t����2 &, float) const;
	//�߽�����
	bool f�������(t����2 &, float) const;
	bool f�ұ�����(t����2 &, float) const;
	bool f�ϱ�����(t����2 &, float) const;
	bool f�±�����(t����2 &, float) const;
	bool f��������(t����2 &, float) const;
	bool f��������(t����2 &, float) const;
	bool f�߽�����(t����2 &, float) const;
	//�߽練��
	bool f��߷���(t����2 &, float) const;
	bool f�ұ߷���(t����2 &, float) const;
	bool f�ϱ߷���(t����2 &, float) const;
	bool f�±߷���(t����2 &, float) const;
	bool f���ҷ���(t����2 &, float) const;
	bool f���·���(t����2 &, float) const;
	bool f�߽練��(t����2 &, float) const;
public:
	float m�� = 0, m�� = 0, m�� = 0, m�� = 0;
};
//=============================================================================
// ������״
//=============================================================================
class C������״ {
public:
	C������״(const t����2 &, const t����2 &, float);
	C������״(const t����2 &, float);
	static C������״ fc�Զ�(const t����2 &����, const t����2 &ԭʼ�ж�, const t����2 &����, float ����);
	static C������״ fc���Բ(const t����2 &����, const t����2 &ԭʼ�ж�, const t����2 &����);
	static C������״ fc��СԲ(const t����2 &����, const t����2 &ԭʼ�ж�, const t����2 &����);
	bool f�ཻ�ж�(const tԲ�� &) const;
	bool fiԲ��() const;
	bool fi����() const;
	tԲ�� fgԲ��() const;
	t��ת���� fg��ת����() const;
public:
	t����2 m����;
	t����2 m��ߴ�;
	float m����;
	bool mi����;
};
}