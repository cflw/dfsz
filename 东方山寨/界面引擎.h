#pragma once
#include <�û�����_����.h>
#include "ͼ�ΰ���.h"
#include "����.h"
namespace ����ɽկ {
enum class E���� {
	e���˵�,
	eѡ���Ѷ�,
	eѡ�����,
};
class C�������� {
public:
	static C�������� *g��;
	C��������();
	~C��������();
	void f��ʼ��(��ά::C��ά &, C�������� &);
	void f����();
	void f����();
	void f��ʾ();
	void fsʱ��Ƶ��(float, float);
	void f�л�����(E����);
	void f�رմ���();
private:
	class Cʵ��;
	std::unique_ptr<Cʵ��> mʵ��;
};
}	//namespace ����ɽկ