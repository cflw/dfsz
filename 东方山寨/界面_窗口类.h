#pragma once
#include <�û�����_�ؼ�.h>
namespace ����ɽկ {
class W���˵� : public �û�����::W���� {
public:
	enum E��ʶ {
		e��ʼ��Ϸ,
		e¼��ط�,
		e����,
		e�˳�,
	};
	W���˵�();
	void f�¼�_����(�û�����::W���� &, const �û�����::S�������� &) override;
	void f��Ӧ_��ʼ��() override;
	std::vector<std::unique_ptr<�û�����::W��ť>> ma��ť;
};
class Wѡ��ģʽ : public �û�����::W���� {
public:
	enum E��ʶ {
		e��ͳģʽ,
		e���ӹؿ�,
		e�ؿ���ϰ,
		e������ϰ,
	};
};
class Wѡ���Ѷ� : public �û�����::W���� {
public:
	Wѡ���Ѷ�();
	void f�¼�_����(�û�����::W���� &, const �û�����::S�������� &) override;
	void f��Ӧ_��ʼ��() override;
	std::vector<std::unique_ptr<�û�����::W��ť>> ma��ť;
};
class Wѡ���Ի� : public �û�����::W���� {
public:
	enum E��ʶ {
		e����,
		e�����յ�,
		e���μ���,
		eħ��ɳ�ᴩ,
		eħ��ɳ��Χ,
	};
	Wѡ���Ի�();
	void f�¼�_����(�û�����::W���� &, const �û�����::S�������� &) override;
	void f��Ӧ_��ʼ��() override;
	void f�������(int, int, int);
	std::vector<std::unique_ptr<�û�����::W��ť>> ma��ť;
};
class W���� : public �û�����::W���� {
public:
	enum E��ʶ {
		e��Ϸ,
		eͼ��,
		e����,
		e�ֱ�,
		e����,
	};
};
class W������ : public �û�����::W���� {
public:
};
class W�������� : public �û�����::W���� {

};
class Wͼ������ : public �û�����::W���� {
public:
};
class W�������� : public �û�����::W���� {
public:
};
class W�ֱ��豸 : public �û�����::W���� {
public:

};
class W�����豸 : public �û�����::W���� {
public:

};

}