#pragma once
#include "�ӻ��ƶ��ӿ�.h"
#include "����.h"
namespace ����ɽկ {
namespace �ӻ��ƶ� {
//λ��
class Cλ�� : public I�ӻ��ƶ� {
public:
	static const int c���� = 10;	//1+2+3+4=10	�������ɵ��������
	enum E���� {
		e����,
	};
	struct S���� {
		t����2 v����[c����];
		t����2 v����[c����];
		S����(const t����2 *);
		const t����2 *fg����(int p���) const;
		const t����2 *fg����(int p���) const;
	};
	class Cȡ���� {
	public:
		Cȡ����(const S���� &, int);
		const t����2 &fg����(int) const;
		const t����2 &fg����(int) const;
		t����2 fg��ֵ(int, float) const;
	private:
		int v����;
		int v���;
		const t����2 *v����;
		const t����2 *v����;
	};
	class C���� : public I����<I�ӻ��ƶ�> {
	public:
		C����(const std::initializer_list<t����2> &);
		C����(const std::shared_ptr<S����> &);
		I�ӻ��ƶ� *f�ӿ�_�½�() const override;
		std::shared_ptr<S����> v����;
	};
	static int f�������(int p);	//���ݻ����������鿪ʼ���
	Cλ��(const std::shared_ptr<S����> &);
	void f�ӿ�_����() override;
	void f�ӿ�_��λ(int) override;
	Cȡ���� fȡ����() const;
private:
	std::shared_ptr<S����> v����;
};
//�����ռ����
}	//namespace �ӻ��ƶ�

}