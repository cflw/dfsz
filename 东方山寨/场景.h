#pragma once
#include "ͼ��_��ά.h"
namespace ����ɽկ {
class I���� {
public:
	virtual void f�ӿ�_��ʼ��();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_����();
	virtual void f�ӿ�_��ʾ(C����ά &) const;
};
class C�������� {
public:
	void f��ʼ��_ͼ��(C����ά &);
	void f���ó���(std::shared_ptr<I����>);
	void f����();
	void f����();
	void f��ʾ() const;
private:
	std::shared_ptr<I����> m����, m�³���;
	C����ά *m����ά = nullptr;
};
}