#pragma once
#include "��ѧ����.h"
namespace ����ɽկ {
namespace ���� {
//�ӻ�
float f��ֵ(const std::pair<float, float> &, float);
//ʱ��
bool f��ʱ(float &��ʱ, float a);
//�仯
float f�ӱ仯(float �仯, float ʱ�� = 1);
float f�˱仯(float �仯, float ʱ�� = 1);
//ͼ��
float f����͸����(float ԭ͸��, float ����);
//�˶�
void f�����˶�����(t����2 &, const t����2 &, float);
float f��Ŀ��ʱ��(const t����2 &ԭ, const t����2 &Ŀ��, float �ٶ�);
t����2 f��Ŀ���ٶ�(const t����2 &ԭ, const t����2 &Ŀ��, float ʱ��);
}}