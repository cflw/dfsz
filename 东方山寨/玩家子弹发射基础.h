#pragma once
#include "����.h"
#include "����ӵ������.h"
namespace ����ɽկ {
class I��ҷ��价�� {
public:
	virtual C��� &fg���() const = 0;
	virtual t����2 fg��������() const = 0;
	virtual t����2 fg��������() const = 0;	//�Ի�������
	virtual t����2 fg�������() const;
	virtual float fg��Է���r() const;
	virtual const C��Ϸ�ٶ� &fg��Ϸ�ٶ�() const;
	virtual const float &fg���ٽ���() const;
};
class C��ҷ��价�� : public I��ҷ��价�� {
public:
	C��ҷ��价��(C��� &);
	C��� &fg���() const override;
	t����2 fg��������() const override;
	t����2 fg��������() const override;
	const C��Ϸ�ٶ� &fg��Ϸ�ٶ�() const override;
	t����2 fg�������() const override;
	float fg��Է���r() const override;
	const float &fg���ٽ���() const override;
	C��� *m��� = nullptr;
};
class C����ӵ������� {
public:
	static constexpr float cǰ���� = ��ѧ::c���<float>;
	static constexpr float c����ʱ�� = 0.2f;
	static constexpr float c������ = 0.05f;
	static constexpr float c�ٶȴ�С = 2000;
	C����ӵ�������();
	//��ʼ��
	void f��ʼ��_���价��(std::shared_ptr<I��ҷ��价��>);
	void f��ʼ��_ʱ�����();
	//����
	void f����_һ������(float = c������);	//�� f�ӿ�_���� �е���
	void f����_����ʱ��();
	void f����_������(float);	//�ڷ����ӵ������
	bool f����_i�ɷ���() const;
	bool f����_i������() const;
	bool f����_i������() const;
	void f����_��λ();
	void f����_s�ӵ�����(const S����ӵ����� *);
	void f����_s������(float);
	//�ӿ�
	virtual void f�ӿ�_��ʼ��();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_��λ();
	virtual void f�ӿ�_�����ӵ�();	//��"f�ӿ�_����"����, �����ӵ�
	//�ⲿ����
	void f����();
	void f����();
protected:
	//����
	std::shared_ptr<I��ҷ��价��> m���价��;
	std::shared_ptr<C����ӵ������> m�ӵ������;
	//����
	float mʣ��ʱ�� = 0;	//ʣ�෢��ʱ��
	float m���ʱ�� = 0;	//������
	float m����ʱ�� = 0;	//�ѷ���ʱ��
	float m������ = c������;
};
}	//namespace ����ɽկ