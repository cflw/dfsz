#pragma once
#include "����.h"
#include "ͼ��_ͼƬ.h"
#include "�����ӿ�.h"
namespace ����ɽկ {
struct S�������;
class C��Ϸ�ٶ�;
class C�������;
struct S�л�����;
//==============================================================================
// �л���
//==============================================================================
class C�л� : public I�¼�, public C����ͼƬ���� {
public:
	static constexpr float c�ж��뾶 = 16.f;
	using tf�˶� = std::function<t����2(const C�л� &)>;
	enum E��־ {
		eʹ��,
		e�޶���,
		e��,
	};
	C�л�() = default;
	C�л�(int p����ֵ);
	void f����_ʹ��();
	void f����_����();
	bool f����_iʹ��() const;
	void f��ʼ��();
	void f����();
	void f����();
	void f��ʾ() const override;
	void f�е�(int �˺�);
	//����
	const t����2 &fg����() const;
	const SͼƬ�������� &fgͼƬ��������() const;
	float fg�ж��뾶() const;
	tԲ�� fg�ж���() const;
	bool fi�ڴ�����() const;
	bool fi����() const;
	bool fi��() const;
	const S������� &fg�������() const;
	float fg�ƶ�����x() const;
	float fg�ƶ�����y() const;
	void fs����ֵ(int = 1, float �޵� = 1);
	bool fi�˶�ʱ����(float) const;
	float fʣ���˶�ʱ��(float) const;
	//�˶�
	void fs�ٶ�(const t����2 &);
	void fs�˶�(const tf�˶� &);
	void f�˶�_�ٶ�(const t����2 &�ٶ�, float ʱ�� = 0);
	void f�˶�_��ʱ�ƶ���(const t����2 &, float ʱ��, float ƽ����ʼʱ�� = 0, float ƽ������ʱ�� = 0);
	void f�˶�_�����ƶ���(const t����2 &, float �ٶ�, float ƽ����ʼʱ�� = 0, float ƽ������ʱ�� = 0);
	void f�˶�_��ʱ�ƶ���(const t����2 &, float ʱ��, float ƽ����ʼʱ�� = 0);
	void f�˶�_�����ƶ���(const t����2 &, float �ٶ�, float ƽ����ʼʱ�� = 0);
	void f�˶�_ƽ���ƶ���(const t����2 &, float ��ʱ��, float ƽ����ʼʱ�� = 0.5f, float ƽ������ʱ�� = 0.5f);
	void f�˶�_ƽ���ƶ���(const t����2 &, float ��ʱ��, float ƽ����ʼʱ�� = 0.5f);
	void f�˶�_��Ժ���������ƶ�(float ������, float ��ƽ��, float �ḡ��, float ��ƽ�� = 100, float �ݸ��� = 5);
	//����
	void f����_����();
	void f����_����();	//ǿ������,������������,����û����¼�
private:
	void f�����˶�();
	void fֱ���ƶ�(const t����2 &aĿ��, float aʱ��);
public:
	t����2 m����;
	t����2 m�ٶ�;
	int m��� = 0;
	t��־ m��־;
	float m�˶�ʱ�� = 0;
	tf�˶� mf�˶�;
	const C��Ϸ�ٶ� *m��Ϸ�ٶ� = nullptr;
	C������� *m����ָ�� = nullptr;
	const S�л����� *m�л����� = nullptr;
	��ѧ::S����ֵ<int> m����ֵ = {1};
	float m�޵�ʱ�� = 0;
};
//==============================================================================
// �л�ʹ�õĽṹ
//==============================================================================
struct S�л����� : public SͼƬ�������� {
	float m�ж��뾶;
};
//==============================================================================
// �л��˶�
//==============================================================================
C�л�::tf�˶� F�л��˶�_ֱ���ٶ�(const t����2 &�ٶ�, float ʱ��);
C�л�::tf�˶� F�л��˶�_Ŀ������(const t����2 &Ŀ��, float ʱ��);
C�л�::tf�˶� F�л��˶�_ƽ���ƶ���(const t����2 &����ٶ�, float ��ʱ��, float ƽ����ʼ, float ƽ������);
C�л�::tf�˶� F�л��˶�_ƽ���ƶ���(const t����2 &Ŀ��, float ��ʱ��, float ƽ����ʼ);
}