#pragma once
#include <map>
#include "����.h"
#include "����.h"
#include "�Ի�����.h"
namespace ����ɽկ {
class C�ؿ�����;
class C�Ի���;
class I�Ի�����;
class C�Ի����� {
public:
	static constexpr float c������� = 0.1f;
	static constexpr float c��סȷ�������ĵȴ�ʱ�� = 1;
	void f��ʼ��_����(C�ؿ����� &);
	void f����();
	void f���밴��(const ����::C������ &);
	void f��ʼ(tp�Ի��ű�);
	void f����();
	void f��������_��һ��();	//��zʱ����
	void f��������_����();	//��ctrl,�������zʱ����
	t��־::reference fg�Ի����();
	bool fg�Ի����() const;
	bool fi�Ի���() const;
	bool fw����() const;
	//����
	void f����_�¶Ի���(const S�Ի�����_�Ի� &);
	void f����_��ʾ����(const S�Ի�����_��ʾ���� &);
	void f����_����״̬(const S�Ի�����_����״̬ &);
	void f����_�ȴ�();	//�ͼ�������
	void f����_����();	//����ִ����һ���¼�,�͵ȴ�����
private:
	void f�ڲ�_ִ�жԻ��¼�();
	void f�ڲ�_�����Ի���();
	void f�ڲ�_���潹��(I�Ի����� *);
	tp�Ի��ű� m�Ի��ű�;
	ta�Ի��¼�::const_iterator m��ǰ�Ի�;
	std::shared_ptr<C�Ի���> m��ǰ�Ի���;
	std::map<int, std::shared_ptr<I�Ի�����>> ma�Ի�����;
	I�Ի����� *m��ǰ���� = nullptr;
	C�ؿ����� *m�ؿ�;
	float m�����ȴ� = 0;	//��
	float m�Զ��ȴ� = 0;	//��,û�в���ʱ��һ��ʱ���Զ���һ���Ի�
	float m�Զ���� = 10;	//ʱ������ַ�������
	float m����_ȷ��ʱ�� = 0;	//��סz��ʱ��
	bool m�ȴ� = false;
};
class C�Ի��ű� {
public:
	operator tp�Ի��ű�() const;
	C�Ի��ű� &f�Ի�(const std::wstring &, bool = false);
	C�Ի��ű� &f��ʾ����(const I����<I�Ի�����> &, int ��ʶ, bool ����);	//��Ҫ������ʱ��������
	C�Ի��ű� &f����۽�(int ��ʶ);
	C�Ի��ű� &f������ʧ(int ��ʶ);
	std::shared_ptr<ta�Ի��¼�> ma�Ի��¼� = std::make_shared<ta�Ի��¼�>();
};
class I�Ի��¼� {
public:
	virtual void f�ӿ�_����(C�Ի����� &) = 0;
};
namespace �Ի��¼� {
class C�Ի� : public I�Ի��¼� {
public:
	C�Ի�(S�Ի�����_�Ի� &&);
	void f�ӿ�_����(C�Ի����� &) override;
	S�Ի�����_�Ի� m����;
};
class C��ʾ���� : public I�Ի��¼� {
public:
	C��ʾ����(S�Ի�����_��ʾ���� &&);
	void f�ӿ�_����(C�Ի����� &) override;
	S�Ի�����_��ʾ���� m����;
};
class C����״̬ : public I�Ի��¼� {
public:
	C����״̬(S�Ի�����_����״̬ &&);
	void f�ӿ�_����(C�Ի����� &) override;
	S�Ի�����_����״̬ m����;
};
}	//namespace �Ի��¼�
}	//namespace ����ɽկ