#pragma once
class PCPoint
{
public:
	PCPoint();
	~PCPoint();
public: //����
	double m_Coordinate[3];//����ֵ
	double m_Color[3];//��ɫ
	double* m_Normal;//��ʸ��
	int m_ID;//���
	bool b_Selected;//�Ƿ�ѡ��
	bool b_BoundaryPoint;//�Ƿ�Ϊ�߽��
	bool b_TVPoint;//����ͶƱ������
};

