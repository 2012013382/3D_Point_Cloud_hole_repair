#include "stdafx.h"
#include "PointCloudData.h"


PointCloudData::PointCloudData()
{
	m_PointSumNumber = 0;
	b_OneStepMode = false;
	b_AllPoint = false;
}


PointCloudData::~PointCloudData()
{
}

//��ȡ��������
int PointCloudData::GetPointSumNumber()
{
	return m_PointSumNumber;
}

//���õ�������
void PointCloudData::SetPointSumNumber(int number)
{
	m_PointSumNumber = number;
}

//��ȡ��������
PCPoint* PointCloudData::GetPointCloud()
{
	return m_PointCloud;
}
//��ʼ����������
void PointCloudData::InitPointCloud(PCPoint* pointCloud)
{
	m_PointCloud = (PCPoint*)new PCPoint[m_PointSumNumber];//��������
	m_OriginPointCloud = (PCPoint*)new PCPoint[m_PointSumNumber];//��λ����ĵ�������
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		//��ʼ�������������ɫ
		for (int i = 0; i < 3; i++)
		{
			m_PointCloud[num].m_Coordinate[i] = pointCloud[num].m_Coordinate[i];
			m_PointCloud[num].m_Color[i] = pointCloud[num].m_Color[i];
		}
		m_PointCloud[num].m_ID = num;
	}
	PointMoveToOrigin(pointCloud);//��ģ��������ʾ����
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_OriginPointCloud[num].m_Coordinate[j] = pointCloud[num].m_Coordinate[j];
			m_OriginPointCloud[num].m_Color[j] = pointCloud[num].m_Color[j];
		}
		//��ʼ��ID
		m_OriginPointCloud[num].m_ID = num;
	}
	//��ʼ��PCL kd��
	cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
	cloud->width = m_PointSumNumber;//��ʼ�� PCL ����
	cloud->height = 1;
	cloud->points.resize(cloud->width * cloud->height);
	int cloudCount = 0;
	for (int num = 0; num < m_PointSumNumber; num++)
	{
			cloud->points[cloudCount].x = m_OriginPointCloud[num].m_Coordinate[0];
			cloud->points[cloudCount].y = m_OriginPointCloud[num].m_Coordinate[1];
			cloud->points[cloudCount].z = m_OriginPointCloud[num].m_Coordinate[2];
			cloudCount++;
	}
	kdtree.setInputCloud(cloud);
}
//��ȡ�ƶ���ԭ���ĵ�������
PCPoint* PointCloudData::GetOriginPointCloud()
{
	return m_OriginPointCloud;
}
//���ļ��ж�ȡ��������
bool PointCloudData::ReadPointCloudFile(char* fileName)
{
	m_MaxX = -10000000.0;//������һ���ǳ�С�ĳ�ʼֵ
	m_MaxY = -10000000.0;//������һ���ǳ�С�ĳ�ʼֵ
	m_MaxZ = -10000000.0;//������һ���ǳ�С�ĳ�ʼֵ

	m_MinX = DBL_MAX;//���������ֵ
	m_MinY = DBL_MAX;//���������ֵ
	m_MinZ = DBL_MAX;//���������ֵ

	char str[256];
	int i = 0;
	FILE *fp;
	PCPoint sumPoint;
	PCPoint* tempPointData;//����������ʱ�洢��
	//��ȡ����ģ�͵�����
	if (fopen_s(&fp, fileName, "r") == 0)
	{
		while (fscanf_s(fp, "%s", str, 256) != EOF)
		{
			fscanf_s(fp, "%s", str, 256);
			fscanf_s(fp, "%s", str, 256);
			m_PointSumNumber++;
		}
		fclose(fp);
	}
	//��ʼ����ʱ��������
	tempPointData = (PCPoint*) new PCPoint[m_PointSumNumber];
	sumPoint.m_Coordinate[0] = 0.0;
	sumPoint.m_Coordinate[1] = 0.0;
	sumPoint.m_Coordinate[2] = 0.0;

	if (fopen_s(&fp, fileName, "r") == 0)
	{
		while (fscanf_s(fp, "%s", str, 256) != EOF)
		{
			//���ļ��ж�ȡ���ݵ����Ϣ����������
			double v[3];
			int c[3];
			int index;

			v[2] = (double)atof(str);
			fscanf_s(fp, "%s", str, 256);
			v[0] = (double)atof(str);
			fscanf_s(fp, "%s", str, 256);
			v[1] = (double)atof(str);
			c[0] = 0.0; c[1] = 0.0; c[2] = 0.0;//���ó�ʼ��ɫΪ��ɫ
			index = i++;
			for (int j = 0; j<3; j++)//���ļ��еĵ��������RangeData��
			{
				tempPointData[index].m_Coordinate[j] = v[j];
				tempPointData[index].m_Color[j] = c[j];
				sumPoint.m_Coordinate[j] += v[j];
			}
			if (v[0] > m_MaxX)
			{
				m_MaxX = v[0];//�õ�����x����ֵ
			}
			if (v[1] > m_MaxY)
			{
				m_MaxY = v[1];//�õ�����y����ֵ
			}
			if (v[2] > m_MaxZ)
			{
				m_MaxZ = v[2];//�õ�����z����ֵ
			}
			if (v[0] < m_MinX)
			{
				m_MinX = v[0];//�õ���С��x����ֵ
			}
			if (v[1] < m_MinY)
			{
				m_MinY = v[1];//�õ���С��y����ֵ
			}
			if (v[2] < m_MinZ)
			{
				m_MinZ = v[2];//�õ���С��z����ֵ
			}
		}
		fclose(fp);
		//��ȡģ�͵����ĵ�
		m_MidPoint.m_Coordinate[0] = sumPoint.m_Coordinate[0] / m_PointSumNumber;
		m_MidPoint.m_Coordinate[1] = sumPoint.m_Coordinate[1] / m_PointSumNumber;
		m_MidPoint.m_Coordinate[2] = sumPoint.m_Coordinate[2] / m_PointSumNumber;

		InitPointCloud(tempPointData);//��ʼ����������
		delete[] tempPointData;//�ͷ��ڴ�
		return 1;//�ļ���ÿ��򷵻�1
	}
	else
	{
		return 0;//�ļ��򲻿��򷵻�0
	}
}
void PointCloudData::PointMoveToOrigin(PCPoint* & pointCloud)//��ģ��������ʾ����
{
	m_MaxX -= m_MidPoint.m_Coordinate[0];
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		pointCloud[num].m_Coordinate[0] -= m_MidPoint.m_Coordinate[0];
		pointCloud[num].m_Coordinate[1] -= m_MidPoint.m_Coordinate[1];
		pointCloud[num].m_Coordinate[2] -= m_MidPoint.m_Coordinate[2];
	
		pointCloud[num].m_Coordinate[0] = (pointCloud[num].m_Coordinate[0])
			/ (m_MaxX);
		pointCloud[num].m_Coordinate[1] = (pointCloud[num].m_Coordinate[1])
			/ (m_MaxX);
		pointCloud[num].m_Coordinate[2] = (pointCloud[num].m_Coordinate[2])
			/ (m_MaxX);
	} 
}
//���Ʋ�����PCL kdtree k��������
void  PointCloudData::PCLCoefficientsKDtreeNKSearch(PCPoint lpoint, int Knum, pcl::PointCloud<pcl::PointXYZ>::Ptr coeCloud
	, pcl::KdTreeFLANN<pcl::PointXYZ> coeKdtree)
{
	pcl::PointXYZ searchPoint;//��ʼ�� ������
	searchPoint.x = lpoint.m_Coordinate[0];
	searchPoint.y = lpoint.m_Coordinate[1];
	searchPoint.z = lpoint.m_Coordinate[2];
	std::vector<int> pointIdxNKNSearch(Knum);
	std::vector<float> pointNKNSquaredDistance(Knum);
	PCPoint Ptemp;
	if (coeKdtree.nearestKSearch(searchPoint, Knum, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
	{
		for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
		{
			Ptemp.m_Coordinate[0] = coeCloud->points[pointIdxNKNSearch[i]].x;
			Ptemp.m_Coordinate[1] = coeCloud->points[pointIdxNKNSearch[i]].y;
			Ptemp.m_Coordinate[2] = coeCloud->points[pointIdxNKNSearch[i]].z;
			RkNearestPoints.push_back(Ptemp);
		}
	}
}
//PCL KDtree k��������
void PointCloudData::PCLKDtreeNKSearch(PCPoint lpoint, int Knum)
{
	pcl::PointXYZ searchPoint;//��ʼ�� ������
	searchPoint.x = lpoint.m_Coordinate[0];
	searchPoint.y = lpoint.m_Coordinate[1];
	searchPoint.z = lpoint.m_Coordinate[2];
	std::vector<int> pointIdxNKNSearch(Knum);
	std::vector<float> pointNKNSquaredDistance(Knum);
	PCPoint Ptemp;
	if (kdtree.nearestKSearch(searchPoint, Knum, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
	{
		for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i)
		{
			Ptemp.m_Coordinate[0] = cloud->points[pointIdxNKNSearch[i]].x;
			Ptemp.m_Coordinate[1] = cloud->points[pointIdxNKNSearch[i]].y;
			Ptemp.m_Coordinate[2] = cloud->points[pointIdxNKNSearch[i]].z;
			RkNearestPoints.push_back(Ptemp);
		}
	}
}
//�߽���
bool PointCloudData::BoundaryCheck(PCPoint lpoint)
{
	double array[BCNum][3], Y[3];
	double array_ML[BCNum][3];
	double A, B, C;
	A = B = C = 0.0;
	ZeroMemory(array, sizeof(array));
	ZeroMemory(Y, sizeof(Y));
	PCLKDtreeNKSearch(lpoint, BCNum);
	for (int i = 0; i < BCNum; i++)
	{
		array_ML[i][0] = array[i][0] = RkNearestPoints[i].m_Coordinate[0];
		array_ML[i][1] = array[i][1] = RkNearestPoints[i].m_Coordinate[1];
		array_ML[i][2] = array[i][2] = RkNearestPoints[i].m_Coordinate[2];
	}
	RkNearestPoints.clear();
	double *Matrix[3], *IMatrix[3];
	for (int i = 0; i < 3; i++)
	{
		Matrix[i] = new double[3];
		IMatrix[i] = new double[3];
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*(Matrix[i] + j) = 0.0;//ȫ����ֵΪ0.0
		}
	}
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < BCNum; i++)
		{
			*(Matrix[0] + j) += array[i][0] * array[i][j];
			*(Matrix[1] + j) += array[i][1] * array[i][j];
			*(Matrix[2] + j) += array[i][2] * array[i][j];
			Y[j] -= array[i][j];
		}
	}
	double d = Determinant(Matrix, 3);
	Inverse(Matrix, IMatrix, 3, d);
	for (int i = 0; i < 3; i++)
	{
		A += *(IMatrix[0] + i)*Y[i];
		B += *(IMatrix[1] + i)*Y[i];
		C += *(IMatrix[2] + i)*Y[i];
	}

	for (int i = 0; i < 3; i++)
	{
		delete[] Matrix[i];
		delete[] IMatrix[i];
	}
	for (int i = 0; i<BCNum; i++){
		double t = (A*array[i][0] + B*array[i][1] + C*array[i][2] + 1) / (A*A + B*B + C*C);
		array[i][0] = array[i][0] - A*t;
		array[i][1] = array[i][1] - B*t;
		array[i][2] = array[i][2] - C*t;
	}
	double t = (A*lpoint.m_Coordinate[0] + B*lpoint.m_Coordinate[1] + C*lpoint.m_Coordinate[2] + 1) / (A*A + B*B + C*C);
	lpoint.m_Coordinate[0] = lpoint.m_Coordinate[0] - A*t;
	lpoint.m_Coordinate[1] = lpoint.m_Coordinate[1] - B*t;
	lpoint.m_Coordinate[2] = lpoint.m_Coordinate[2] - C*t;

	PCPoint* pt3d = new PCPoint[BCNum];
	// 	Point* pt2d = new Point[10];
	PCPoint averagePoint; // average point.
	averagePoint.m_Coordinate[0] = 0;
	averagePoint.m_Coordinate[1] = 0;
	averagePoint.m_Coordinate[2] = 0;
	for (int i = 0; i < BCNum; i++)
	{
		pt3d[i].m_Coordinate[0] = array[i][0];
		pt3d[i].m_Coordinate[1] = array[i][1];
		pt3d[i].m_Coordinate[2] = array[i][2];
		averagePoint.m_Coordinate[0] += array[i][0];//get averagePoint
		averagePoint.m_Coordinate[1] += array[i][1];
		averagePoint.m_Coordinate[2] += array[i][2];
	}
	averagePoint.m_Coordinate[0] = averagePoint.m_Coordinate[0] / BCNum;
	averagePoint.m_Coordinate[1] = averagePoint.m_Coordinate[1] / BCNum;
	averagePoint.m_Coordinate[2] = averagePoint.m_Coordinate[2] / BCNum;

	int side1 = 0;
	int side2 = 0;
	PCPoint s;
	s.m_Coordinate[0] = averagePoint.m_Coordinate[0] - lpoint.m_Coordinate[0];
	s.m_Coordinate[1] = averagePoint.m_Coordinate[1] - lpoint.m_Coordinate[1];
	s.m_Coordinate[2] = averagePoint.m_Coordinate[2] - lpoint.m_Coordinate[2];
	for (int i = 0; i < BCNum; i++)
	{
		double t = s.m_Coordinate[0] * (pt3d[i].m_Coordinate[0] - lpoint.m_Coordinate[0])
			+ s.m_Coordinate[1] * (pt3d[i].m_Coordinate[1] - lpoint.m_Coordinate[1])
			+ s.m_Coordinate[2] * (pt3d[i].m_Coordinate[2] - lpoint.m_Coordinate[2]);
		if (t > 0)
		{
			side1++;
		}
		else
		{
			side2++;
		}
	}
	if (abs(((double)side1 - (double)side2) / BCNum) > Threadshold)
	{
		return true;
	}
	return false;
}
//���п׶��޲�
bool PointCloudData::HoleRepair()
{
	//���������
	vector<PCPoint> m_SelectedPoint;//��ѡ�е�Լ����
	vector<PCPoint> newSelectedPoint;//��������Լ����
	vector<PCPoint> m_SelectedBoundaryPoint;//��ѡ�еı߽��
	
	//�µ��޲��㼯��
	vector<PCPoint> repairedPoint;
	//��ȡѡ�еı߽�㼯��
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		if (m_OriginPointCloud[num].b_Selected &&
			m_OriginPointCloud[num].b_BoundaryPoint)
		{
			m_SelectedBoundaryPoint.push_back(m_OriginPointCloud[num]);
		}
	}
	//��ѡ�еı߽������Χ�������䣬����ĵ㼴ΪԼ���㣬ÿ����������Χ����
	//�µ�knum����
	int knum = 15;
	for (int num = 0; num < m_SelectedBoundaryPoint.size(); num++)
	{
		PCLKDtreeNKSearch(m_SelectedBoundaryPoint[num], knum);
		for (int i = 1; i < knum; i++)
		{
			if (NotIn(RkNearestPoints[i], m_SelectedBoundaryPoint,m_SelectedPoint))
			{
				m_SelectedPoint.push_back(RkNearestPoints[i]);
				newSelectedPoint.push_back(RkNearestPoints[i]);
			}
		}
		RkNearestPoints.clear();
	}

	gProgress = 10;//������ʾ������
	//��ȡ��ʽ���淽�̵�ϵ��
	double* coefficients = GetRBFCoefficients(m_SelectedPoint);
	//test begin
	for (int i = 0; i < m_SelectedPoint.size(); i++)
	{
		m_TestSeletedPointCloud.push_back(m_SelectedPoint[i]);
	}
	//test end
	gProgress = 30;//������ʾ������
	//�����µĿ׶��޲��㣬�����޲������λ�õĵ���
	bool repairingResult = InsertRepairPoint(coefficients, repairedPoint, m_SelectedBoundaryPoint, m_SelectedPoint);
	gProgress = 90;//������ʾ������

	//�����е��������õ���ʼ��δѡ��״̬	
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		m_OriginPointCloud[num].b_Selected = false;
	}
	gProgress = 95;//������ʾ������

	//��������ͶƱ��������
	//TensorVoting(repairedPoint);
	//������в����µ��޲���
	for (int num = 0; num < repairedPoint.size(); num++)
	{
		/*if (num % 2 == 0 && repairedPoint[num].b_TVPoint == false && num != 0)
		{
			continue;
		}*/
		m_AddedPoingCLoud.push_back(repairedPoint[num]);
	}
	gProgress = -1;//���ٽ�����
	if (repairingResult)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//�Ƿ���ѡ�еı߽缯����
bool PointCloudData::NotIn(PCPoint lpoint, vector<PCPoint> m_SelectedBoundaryPoint, vector<PCPoint> m_SelectedPoint)
{
	for (int num = 0; num < m_SelectedBoundaryPoint.size(); num++)
	{
		if (fabs(lpoint.m_Coordinate[0] - m_SelectedBoundaryPoint[num].m_Coordinate[0]) < 0.0001
			&& fabs(lpoint.m_Coordinate[1] - m_SelectedBoundaryPoint[num].m_Coordinate[1]) < 0.0001
			&& fabs(lpoint.m_Coordinate[2] - m_SelectedBoundaryPoint[num].m_Coordinate[2]) < 0.0001)
		{
			return false;
		}
	}
	for (int num = 0; num < m_SelectedPoint.size(); num++)
	{
		if (fabs(lpoint.m_Coordinate[0] - m_SelectedPoint[num].m_Coordinate[0]) < 0.0001
			&& fabs(lpoint.m_Coordinate[1] - m_SelectedPoint[num].m_Coordinate[1]) < 0.0001
			&& fabs(lpoint.m_Coordinate[2] - m_SelectedPoint[num].m_Coordinate[2]) < 0.0001)
		{
			return false;
		}
	}
	return true;
}
//��ȡ�����������ϵ��
double*  PointCloudData::GetRBFCoefficients(vector<PCPoint>& m_SelectedPoint)
{
	//���帽��Լ����
	int RBFNum = m_SelectedPoint.size();
	PCPoint* additionalPoint = new PCPoint[RBFNum];
	//����ѡ���Լ�����ȡ����Լ����
	for (int num = 0; num < m_SelectedPoint.size(); num++)
	{
		//��ȡÿ�����ݵ�ķ�ʸ��ֵ������ֵ
		additionalPoint[num].m_Normal = GetNormalVector(m_SelectedPoint[num]);
		additionalPoint[num].m_Coordinate[0] = m_SelectedPoint[num].m_Coordinate[0];
		additionalPoint[num].m_Coordinate[1] = m_SelectedPoint[num].m_Coordinate[1];
		additionalPoint[num].m_Coordinate[2] = m_SelectedPoint[num].m_Coordinate[2];
	}

	//���з�ʸ���ķ������
	RectifyNormals(additionalPoint, RBFNum);

	for (int num = 0; num < RBFNum; num++)
	{
		//��ȡ����Լ�����ֵ
		GetAdditionalPoint(&additionalPoint[num]);
		//Ϊ�˷���ֱ�ӽ��õ��ĸ���Լ�������Լ���㼯����
		m_SelectedPoint.push_back(additionalPoint[num]);
	}
	//RBF����Ĵ�С
	int newRBFNum = 2 * RBFNum;
	//��ʼ��RBFԪ��ֵ
	double** RBFValue = new double*[newRBFNum];
	for (int num = 0; num < newRBFNum; num++)
	{
		RBFValue[num] = new double[newRBFNum];
	}
	for (int i = 0; i < newRBFNum; i++)
	{
		for (int j = 0; j < newRBFNum; j++)
		{
			RBFValue[i][j] = GetRBFValue(GetTwoPointsDistance(m_SelectedPoint[i],m_SelectedPoint[j]));
		}
	}
	//��ʼ��RBF����
	double** RBFMatrix = new double*[newRBFNum + 4];
	for (int num = 0; num < newRBFNum + 4; num++)
	{
		RBFMatrix[num] = new double[newRBFNum + 5];
	}
	for (int i = 0; i < newRBFNum; i++)
	{
		for (int j = 0; j < newRBFNum; j++)
		{
			RBFMatrix[i][j] = RBFValue[i][j];
		}
	}
	for (int num = 0; num < newRBFNum; num++)
	{
		RBFMatrix[num][newRBFNum] = 1;
		RBFMatrix[num][newRBFNum + 1] = m_SelectedPoint[num].m_Coordinate[0];
		RBFMatrix[num][newRBFNum + 2] = m_SelectedPoint[num].m_Coordinate[1];
		RBFMatrix[num][newRBFNum + 3] = m_SelectedPoint[num].m_Coordinate[2];
	}
	for (int num = 0; num < newRBFNum; num++)
	{
		RBFMatrix[newRBFNum][num] = 1;
		RBFMatrix[newRBFNum + 1][num] = m_SelectedPoint[num].m_Coordinate[0];
		RBFMatrix[newRBFNum + 2][num] = m_SelectedPoint[num].m_Coordinate[1];
		RBFMatrix[newRBFNum + 3][num] = m_SelectedPoint[num].m_Coordinate[2];
	}
	for (int i = newRBFNum; i < newRBFNum + 4; i++)
	{
		for (int j = newRBFNum; j < newRBFNum + 4; j++)
		{
			RBFMatrix[i][j] = 0;
		}
	}
	for (int num = 0; num < RBFNum; num++)
	{
		RBFMatrix[num][newRBFNum + 4] = 0;
	}
	for (int num = RBFNum; num < newRBFNum; num++)
	{
		RBFMatrix[num][newRBFNum + 4] = 1;
	}
	for (int num = newRBFNum; num < newRBFNum + 4; num++)
	{
		RBFMatrix[num][newRBFNum + 4] = 0;
	}
	double* coefficients = new double[newRBFNum + 4];
	//��������Ԫ��˹��ȥ���Ծ�����м��㣬�õ���ʽ���淽�̵�ϵ��
	colunmPrincipleGauss(newRBFNum + 4, RBFMatrix);
	//��ȡ��ʽ���淽�̵�ϵ��
	for (int num = 0; num < newRBFNum + 4; num++)
	{
		coefficients[num] = RBFMatrix[num][newRBFNum + 4];
	}
	return coefficients;
}
//�������
void PointCloudData::RectifyNormals(PCPoint* additionalPoint, int RBFNum)
{
	for (int num = 0; num < RBFNum; num++)
	{
		if (additionalPoint[0].m_Normal[0] * additionalPoint[num].m_Normal[0]
			+ additionalPoint[0].m_Normal[1] * additionalPoint[num].m_Normal[1]
			+ additionalPoint[0].m_Normal[2] * additionalPoint[num].m_Normal[2]
			< 0)
		{
			additionalPoint[num].m_Normal[0] = -additionalPoint[num].m_Normal[0];
			additionalPoint[num].m_Normal[1] = -additionalPoint[num].m_Normal[1];
			additionalPoint[num].m_Normal[2] = -additionalPoint[num].m_Normal[2];
		}
	}
	for (int num = 0; num < RBFNum; num++)
	{
		int knum = 10;
		PCLKDtreeNKSearch(additionalPoint[num],knum);
		for (int i = 1; i < knum; i++)
		{
			for (int j = 0; j < RBFNum; j++)
			{
				if (fabs(RkNearestPoints[i].m_Coordinate[0] - additionalPoint[j].m_Coordinate[0]) < 0.0001
					&& fabs(RkNearestPoints[i].m_Coordinate[1] - additionalPoint[j].m_Coordinate[1]) < 0.0001
					&& fabs(RkNearestPoints[i].m_Coordinate[2] - additionalPoint[j].m_Coordinate[2]) < 0.0001)
				{//�ҵ��ý��ڵ�
					if (additionalPoint[num].m_Normal[0] * additionalPoint[j].m_Normal[0]
						+ additionalPoint[num].m_Normal[1] * additionalPoint[j].m_Normal[1]
						+ additionalPoint[num].m_Normal[2] * additionalPoint[j].m_Normal[2]
						< 0)
					{//�������ʸ��֮��ļнǴ���90�ȣ���ı䷨ʸ���ķ���
						additionalPoint[j].m_Normal[0] = -additionalPoint[j].m_Normal[0];
						additionalPoint[j].m_Normal[1] = -additionalPoint[j].m_Normal[1];
						additionalPoint[j].m_Normal[2] = -additionalPoint[j].m_Normal[2];
					}
					break;
				}
			}
		}
		RkNearestPoints.clear();
	}
}
//��ȡ���ݵ�ķ�ʸ��
double* PointCloudData::GetNormalVector(PCPoint lpoint)
{
	/*double* normalVector = new double[3];//�����淨����
	//���·�������������ʽ����õ�
	//lpoint��x1,y1,z1��
	//nearest(x2,y2,z2)
	//nearest2(x3,y3,z3)
	//o(0,0,0)��a(a1,a2,a3)��b(b1,b2,b3)
	//x=a2b3-a3b2,y=a3b1-a1b3,z=a1b2-a2b1
	PCLKDtreeNKSearch(lpoint,10);
	double a1, a2, a3, b1, b2, b3;
	a1 = RkNearestPoints[3].m_Coordinate[0] - lpoint.m_Coordinate[0];
	a2 = RkNearestPoints[3].m_Coordinate[1] - lpoint.m_Coordinate[1];
	a3 = RkNearestPoints[3].m_Coordinate[2] - lpoint.m_Coordinate[2];

	b1 = RkNearestPoints[5].m_Coordinate[0] - lpoint.m_Coordinate[0];
	b2 = RkNearestPoints[5].m_Coordinate[1] - lpoint.m_Coordinate[1];
	b3 = RkNearestPoints[5].m_Coordinate[2] - lpoint.m_Coordinate[2];
	normalVector[0] = a2 * b3 - a3 * b2;
	normalVector[1] = a3 * b1 - a1 * b3;
	normalVector[2] = a1 * b2 - a2 * b1;
	RkNearestPoints.clear();
	return normalVector;*/
	//�������ݵ��������С����ƽ�棬����С����ƽ��ķ�ʸ�������ķ�ʸ��
	double* normalVector = new double[3];
	double array[NORMAL_VECTOR_NUM][3], Y[3];
	double array_ML[NORMAL_VECTOR_NUM][3];
	double A, B, C;
	A = B = C = 0.0;
	ZeroMemory(array, sizeof(array));
	ZeroMemory(Y, sizeof(Y));
	PCLKDtreeNKSearch(lpoint, NORMAL_VECTOR_NUM);
	for (int i = 0; i < NORMAL_VECTOR_NUM; i++)
	{
		array_ML[i][0] = array[i][0] = RkNearestPoints[i].m_Coordinate[0];
		array_ML[i][1] = array[i][1] = RkNearestPoints[i].m_Coordinate[1];
		array_ML[i][2] = array[i][2] = RkNearestPoints[i].m_Coordinate[2];
	}
	RkNearestPoints.clear();
	double *Matrix[3], *IMatrix[3];
	for (int i = 0; i < 3; i++)
	{
		Matrix[i] = new double[3];
		IMatrix[i] = new double[3];
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*(Matrix[i] + j) = 0.0;//ȫ����ֵΪ0.0
		}
	}
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < NORMAL_VECTOR_NUM; i++)
		{
			*(Matrix[0] + j) += array[i][0] * array[i][j];
			*(Matrix[1] + j) += array[i][1] * array[i][j];
			*(Matrix[2] + j) += array[i][2] * array[i][j];
			Y[j] -= array[i][j];
		}
	}
	double d = Determinant(Matrix, 3);
	Inverse(Matrix, IMatrix, 3, d);
	for (int i = 0; i < 3; i++)
	{
		A += *(IMatrix[0] + i)*Y[i];
		B += *(IMatrix[1] + i)*Y[i];
		C += *(IMatrix[2] + i)*Y[i];
	}

	normalVector[0] = A;
	normalVector[1] = B;
	normalVector[2] = C;
	return normalVector;
}
//�������ͶƱ�㷨�������㷨ʸ��
double* PointCloudData::GetTVNormalVector(PCPoint lpoint, pcl::PointCloud<pcl::PointXYZ>::Ptr coeCloud
	, pcl::KdTreeFLANN<pcl::PointXYZ> coeKdtree)
{
	double* normalVector = new double[3];
	double array[NORMAL_VECTOR_NUM][3], Y[3];
	double array_ML[NORMAL_VECTOR_NUM][3];
	double A, B, C;
	A = B = C = 0.0;
	ZeroMemory(array, sizeof(array));
	ZeroMemory(Y, sizeof(Y));
	PCLCoefficientsKDtreeNKSearch(lpoint, NORMAL_VECTOR_NUM, coeCloud, coeKdtree);
	for (int i = 0; i < NORMAL_VECTOR_NUM; i++)
	{
		array_ML[i][0] = array[i][0] = RkNearestPoints[i].m_Coordinate[0];
		array_ML[i][1] = array[i][1] = RkNearestPoints[i].m_Coordinate[1];
		array_ML[i][2] = array[i][2] = RkNearestPoints[i].m_Coordinate[2];
	}
	RkNearestPoints.clear();
	double *Matrix[3], *IMatrix[3];
	for (int i = 0; i < 3; i++)
	{
		Matrix[i] = new double[3];
		IMatrix[i] = new double[3];
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			*(Matrix[i] + j) = 0.0;//ȫ����ֵΪ0.0
		}
	}
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < NORMAL_VECTOR_NUM; i++)
		{
			*(Matrix[0] + j) += array[i][0] * array[i][j];
			*(Matrix[1] + j) += array[i][1] * array[i][j];
			*(Matrix[2] + j) += array[i][2] * array[i][j];
			Y[j] -= array[i][j];
		}
	}
	double d = Determinant(Matrix, 3);
	Inverse(Matrix, IMatrix, 3, d);
	for (int i = 0; i < 3; i++)
	{
		A += *(IMatrix[0] + i)*Y[i];
		B += *(IMatrix[1] + i)*Y[i];
		C += *(IMatrix[2] + i)*Y[i];
	}

	normalVector[0] = A;
	normalVector[1] = B;
	normalVector[2] = C;
	return normalVector;
}
//��ȡ����Լ�����ֵ
void PointCloudData::GetAdditionalPoint(PCPoint* lpoint)
{
	double l = 0.1;
	double pNormal[3];
	double temp[3];
	for (int num = 0; num < 3; num++)
	{
		pNormal[num] = lpoint->m_Normal[num];
	}
	temp[0] = l * pNormal[0] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + lpoint->m_Coordinate[0];

	temp[1] = l * pNormal[1] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + lpoint->m_Coordinate[1];

	temp[2] = l * pNormal[2] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + lpoint->m_Coordinate[2];

	lpoint->m_Coordinate[0] = temp[0];
	lpoint->m_Coordinate[1] = temp[1];
	lpoint->m_Coordinate[2] = temp[2];
}
//��ȡ�������ݵ�֮��ľ���
double PointCloudData::GetTwoPointsDistance(PCPoint p, PCPoint q)
{
	double result = sqrt((p.m_Coordinate[0] - q.m_Coordinate[0]) * (p.m_Coordinate[0] - q.m_Coordinate[0])
		+ (p.m_Coordinate[1] - q.m_Coordinate[1]) * (p.m_Coordinate[1] - q.m_Coordinate[1])
		+ (p.m_Coordinate[2] - q.m_Coordinate[2]) * (p.m_Coordinate[2] - q.m_Coordinate[2]));
	return result;
}
//�����µ��޲���
bool PointCloudData::InsertRepairPoint(double* coefficients, vector<PCPoint> & repairedPoint, vector<PCPoint> m_SelectedBoundaryPoint, vector<PCPoint> m_SelectedPoint)
{
	PCPoint midPoint;//��ѡԼ��������ĵ㣬����������Լ����
	for (int num = 0; num < m_SelectedBoundaryPoint.size(); num++)
	{
		midPoint.m_Coordinate[0] += m_SelectedBoundaryPoint[num].m_Coordinate[0];
		midPoint.m_Coordinate[1] += m_SelectedBoundaryPoint[num].m_Coordinate[1];
		midPoint.m_Coordinate[2] += m_SelectedBoundaryPoint[num].m_Coordinate[2];
	}
	//������ĵ�
	midPoint.m_Coordinate[0] /= (m_SelectedBoundaryPoint.size());
	midPoint.m_Coordinate[1] /= (m_SelectedBoundaryPoint.size());
	midPoint.m_Coordinate[2] /= (m_SelectedBoundaryPoint.size());
	
	//��ȡ�������֮��ľ���
	PCLKDtreeNKSearch(m_SelectedBoundaryPoint[0], 2);
	double dp =  GetTwoPointsDistance(m_SelectedBoundaryPoint[0], RkNearestPoints[1]);
	RkNearestPoints.clear();
	//�е�
	repairedPoint.push_back(midPoint);
	//������ʽ���淽�̵����׶��޲����λ��
	RepairedPointDisjust(coefficients, repairedPoint[repairedPoint.size() - 1], m_SelectedPoint);
	//���в�����
	for (int num = 0; num < m_SelectedBoundaryPoint.size(); num++)
	{
		if (gProgress > 0)
		{
			gProgress = 30 + 60 * ((double)num / (double)m_SelectedBoundaryPoint.size());//������ʾ������
		}
		if (true)
		{
			//��ȡ����֮��ľ���
			double distance = GetTwoPointsDistance(midPoint, m_SelectedBoundaryPoint[num]);
			//��ȡ�����ĸ���
			int pointNum = distance / dp;

			for (int i = 1; i <= pointNum; i++)
			{
				double l = ((double)i / (double)pointNum) * distance;
				PCPoint tempPoint = GetInsertPoint(midPoint, m_SelectedBoundaryPoint[num], l);
				repairedPoint.push_back(tempPoint);
				if (i != 1 && GetTwoPointsDistance(repairedPoint[repairedPoint.size() - 1], repairedPoint[repairedPoint.size() - 2]) > 4.5 * dp)
				{
				    //��ʾ�ÿ׶������þ����������ϣ���˲����Զ��޲�
					repairedPoint.clear();
				    return false;
				}
				else
				{
					//������ʽ���淽�̵����׶��޲����λ��
					RepairedPointDisjust(coefficients, repairedPoint[repairedPoint.size() - 1], m_SelectedPoint);
				}
			}
		}
	}
	return true;
}
//��ȡ�²�����޲���
PCPoint PointCloudData::GetInsertPoint(PCPoint p, PCPoint q, double l)
{
	//��ȡ����ķ�������
	double normal[3];
	normal[0] = q.m_Coordinate[0] - p.m_Coordinate[0];
	normal[1] = q.m_Coordinate[1] - p.m_Coordinate[1];
	normal[2] = q.m_Coordinate[2] - p.m_Coordinate[2];
	//�²�����޲���
	PCPoint repairedPoint;
	repairedPoint.m_Coordinate[0] = l * normal[0] / sqrt(normal[0] * normal[0]
		+ normal[1] * normal[1] + normal[2] * normal[2]) + p.m_Coordinate[0];

	repairedPoint.m_Coordinate[1] = l * normal[1] / sqrt(normal[0] * normal[0]
		+ normal[1] * normal[1] + normal[2] * normal[2]) + p.m_Coordinate[1];

	repairedPoint.m_Coordinate[2] = l * normal[2] / sqrt(normal[0] * normal[0]
		+ normal[1] * normal[1] + normal[2] * normal[2]) + p.m_Coordinate[2];
	//��Ϊ
	repairedPoint.m_Color[0] = 1.0;
	repairedPoint.m_Color[1] = 0.0;
	repairedPoint.m_Color[2] = 1.0;
	return repairedPoint;
}

//��ȡ�޲��㼯��
vector<PCPoint>* PointCloudData::GetNewAddedPoint()
{
	return &m_AddedPoingCLoud;
}
/*
//��ȡԼ���㼯��
vector<PCPoint>* PointCloudData::GetSelectedPoint()
{
	return &m_SelectedPoint;
}*/
//�����׶��޲���
void PointCloudData::RepairedPointDisjust(double* coefficients, PCPoint& repairedPoint, vector<PCPoint> m_SelectedPoint)
{

		double lastFr = DBL_MAX;//��Ϊ����doubleֵ
		while (true)
		{
			double frPoint[3];
			double frX = 0;
			double frY = 0;
			double frZ = 0;
			for (int i = 0; i < m_SelectedPoint.size(); i++)
			{
				frX += coefficients[i] * (repairedPoint.m_Coordinate[0] - m_SelectedPoint[i].m_Coordinate[0])
					* GetTwoPointsDistance(repairedPoint, m_SelectedPoint[i]);

				frY += coefficients[i] * (repairedPoint.m_Coordinate[1] - m_SelectedPoint[i].m_Coordinate[1])
					* GetTwoPointsDistance(repairedPoint, m_SelectedPoint[i]);

				frZ += coefficients[i] * (repairedPoint.m_Coordinate[2] - m_SelectedPoint[i].m_Coordinate[2])
					* GetTwoPointsDistance(repairedPoint, m_SelectedPoint[i]);
			}
			frX = 3 * frX + coefficients[m_SelectedPoint.size() + 1];
			frY = 3 * frY + coefficients[m_SelectedPoint.size() + 2];
			frZ = 3 * frZ + coefficients[m_SelectedPoint.size() + 3];
			frPoint[0] = frX;
			frPoint[1] = frY;
			frPoint[2] = frZ;

			double Fr = 0;
			for (int i = 0; i < m_SelectedPoint.size(); i++)
			{
				Fr += coefficients[i] * GetRBFValue(GetTwoPointsDistance(repairedPoint, m_SelectedPoint[i]));
			}
			Fr = Fr + coefficients[m_SelectedPoint.size()] + repairedPoint.m_Coordinate[0] * coefficients[m_SelectedPoint.size() + 1]
				+ repairedPoint.m_Coordinate[1] * coefficients[m_SelectedPoint.size() + 2]
				+ repairedPoint.m_Coordinate[2] * coefficients[m_SelectedPoint.size() + 3];
			double tempFr = Fr / (frPoint[0] * frPoint[0]
				+ frPoint[1] * frPoint[1] + frPoint[2] * frPoint[2]);
			if (fabs(Fr) < fabs(lastFr))
			{
				lastFr = Fr;
				repairedPoint.m_Coordinate[0] = repairedPoint.m_Coordinate[0] - tempFr * frPoint[0];
				repairedPoint.m_Coordinate[1] = repairedPoint.m_Coordinate[1] - tempFr * frPoint[1];
				repairedPoint.m_Coordinate[2] = repairedPoint.m_Coordinate[2] - tempFr * frPoint[2];
			}
			else
			{
				break;
			}
		}
}
//���б߽����
void PointCloudData::BoundaryClustering()
{
	//��ȡѡ�еı߽�㼯��
	vector<PCPoint> m_SelectedBoundaryPoint;
	for (int num = 0; num < m_PointSumNumber; num++)
	{
		if (m_OriginPointCloud[num].b_Selected &&
			m_OriginPointCloud[num].b_BoundaryPoint)
		{
			m_SelectedBoundaryPoint.push_back(m_OriginPointCloud[num]);
		}
	}
	//����PCL�еľ��ຯ���Եõ��ı߽����о������
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr boundarycloud(new pcl::PointCloud<pcl::PointXYZ>);
	for (int num = 0; num < m_PointSumNumber; num++)
	{//��ȡ�߽�㼯��
		if (m_OriginPointCloud[num].b_BoundaryPoint)
		{
			m_SelectedBoundaryPoint.push_back(m_OriginPointCloud[num]);
		}
		m_OriginPointCloud[num].m_Color[0] = 0.0;//ȫ����Ϊ��ɫ
		m_OriginPointCloud[num].m_Color[1] = 0.0;//ȫ����Ϊ��ɫ
		m_OriginPointCloud[num].m_Color[2] = 1.0;//ȫ����Ϊ��ɫ
	}
	boundarycloud->width = m_SelectedBoundaryPoint.size();//��ʼ�� PCL ����
	boundarycloud->height = 1;
	boundarycloud->points.resize(boundarycloud->width * boundarycloud->height);
	//��ʼ������
	int cloudCount = 0;
	for (int num = 0; num < m_SelectedBoundaryPoint.size(); num++)
	{
		boundarycloud->points[cloudCount].x = m_SelectedBoundaryPoint[num].m_Coordinate[0];
		boundarycloud->points[cloudCount].y = m_SelectedBoundaryPoint[num].m_Coordinate[1];
		boundarycloud->points[cloudCount].z = m_SelectedBoundaryPoint[num].m_Coordinate[2];
		cloudCount++;
	}
	tree->setInputCloud(boundarycloud);
	//��ʼ��������������о���
	vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
	ec.setClusterTolerance(m_clusterDistace);
	ec.setMinClusterSize(m_clusterNum);
	ec.setMaxClusterSize(5000);
	ec.setSearchMethod(tree);
	ec.setInputCloud(boundarycloud);
	ec.extract(cluster_indices);
	//��ȡ������ɵĸ������Ƽ���
	
	m_CloudClusterNum = cluster_indices.size();
	pcl::PointCloud<pcl::PointXYZ>::Ptr* cloud_cluster; //(new pcl::PointCloud<pcl::PointXYZ>);
	cloud_cluster = new pcl::PointCloud<pcl::PointXYZ>::Ptr[m_CloudClusterNum];
	for (int num = 0; num < m_CloudClusterNum; num++)
	{
		cloud_cluster[num] = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
	}
	int i = 0;
	for (vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin();
		it != cluster_indices.end(); i++, it++)
	{
		for (vector<int>::const_iterator pit = it->indices.begin();
			pit != it->indices.end(); pit++)
		{
			cloud_cluster[i]->points.push_back(boundarycloud->points[*pit]);
		}
		cloud_cluster[i]->width = cloud_cluster[i]->points.size();
		cloud_cluster[i]->height = 1;
		cloud_cluster[i]->is_dense = true;
	}
	//���õ��ľ��໮�ֺõĵ��Ƽ��ϴ洢����
	m_BoundaryPointClusters = new vector<PCPoint>[m_CloudClusterNum];
	for (int i = 0; i < m_CloudClusterNum; i++)
	{
		for (int num = 0; num < cloud_cluster[i]->points.size(); num++)
		{
			PCPoint tempPoint;
			tempPoint.m_Color[0] = ((double)i / double(m_CloudClusterNum)) * 1.0;
			tempPoint.m_Color[1] = 1.0 - ((double)i / double(m_CloudClusterNum)) * 1.0;
			tempPoint.m_Color[2] = 0.5;
			tempPoint.m_Coordinate[0] = cloud_cluster[i]->points[num].x;
			tempPoint.m_Coordinate[1] = cloud_cluster[i]->points[num].y;
			tempPoint.m_Coordinate[2] = cloud_cluster[i]->points[num].z;
			m_BoundaryPointClusters[i].push_back(tempPoint);
		}
	}
}

//��ȡ�߽�ľ�������
int PointCloudData::GetCloudClusterNum()
{
	return m_CloudClusterNum;
}
//��ȡ�߽���༯��
vector<PCPoint>* PointCloudData::GetBoundaryPointClusters()
{
	return m_BoundaryPointClusters;
}
//�Զ����п׶��޲�
void  PointCloudData::AutomaticHoleRepair()
{
	m_AddedPoingCLoud.clear();
    //�Ծ�����Ŀ׶��߽缯�Ϸֱ���п׶��޲��Ĺ���
	//���жϳ��������޲��Ŀ׶�
	//�洢�жϾ���
	double distance = m_MaxX - m_MinX;
	if (distance < m_MaxY - m_MinY)
	{
		distance = m_MaxY - m_MinY;
	}
	if (distance < m_MaxZ - m_MinZ)
	{
		distance = m_MaxZ - m_MinZ;
	}
	//�洢�������޲��Ŀ׶����
	vector<int> NotRepair;
	for (int num = 0; num < m_CloudClusterNum; num++)
	{
		//�Ƚ�����Ϊ0
		double maxDistance = 0.0;
		for (int i = 0; i < m_BoundaryPointClusters[num].size(); i++)
		{//��ȡ������
			double tempDistance = GetTwoPointsDistance(m_BoundaryPointClusters[num][0], m_BoundaryPointClusters[num][i]);
			if (tempDistance > maxDistance)
			{
				maxDistance = tempDistance;
			}
		}
		if (maxDistance > distance / 2)
		{//������ڸþ����򲻽����޲�
			NotRepair.push_back(num);
		}
	}
	if (b_OneStepMode)
	{
		gProgressAu = 10;//������ʾ������
	}
	else
	{
		gProgressAu = 5;//������ʾ������
	}

	//���ڴ洢ÿ���׶���Լ���㼯��
	vector<PCPoint> selectedPoint;
	//�µ��޲��㼯��
	vector<PCPoint> repairedPoint;
	//�����ж��Ƿ��޲�
	bool flag = false;
	for (int num = 0; num < m_CloudClusterNum; num++)
	{
		if (b_OneStepMode)
		{
			gProgressAu = 10 + 20 * ((double)num / (double)m_CloudClusterNum);//������ʾ������
		}
		else
		{
			gProgressAu = 5 + 45 * ((double)num / (double)m_CloudClusterNum);//������ʾ������
		}
		//���ж��Ƿ�����޲�
		for (int i = 0; i < NotRepair.size(); i++)
		{
			if (NotRepair[i] == num)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{//�ÿ׶������޲���������һ���׶�����
			flag = false;
			continue;
		}
		//���selected,repair
		selectedPoint.clear();
		repairedPoint.clear();
		//��ѡ�еı߽������Χ�������䣬����ĵ㼴ΪԼ���㣬ÿ����������Χ����
		//�µ�knum����
		int knum = 15;
		for (int i = 0; i < m_BoundaryPointClusters[num].size(); i++)
		{
			PCLKDtreeNKSearch(m_BoundaryPointClusters[num][i], knum);
			for (int j = 1; j < knum; j++)
			{
				if (NotIn(RkNearestPoints[j], m_BoundaryPointClusters[num], selectedPoint))
				{
					selectedPoint.push_back(RkNearestPoints[j]);
				}
			}
			RkNearestPoints.clear();
		}
		//��ȡ��ʽ���淽�̵�ϵ��
		double* coefficients = GetRBFCoefficients(selectedPoint);
		//�����µĿ׶��޲��㣬�����޲������λ�õĵ���
		bool repairingResult = InsertRepairPoint(coefficients, repairedPoint, m_BoundaryPointClusters[num], selectedPoint);
		//�����е��������õ���ʼ��δѡ��״̬	
		for (int num = 0; num < m_PointSumNumber; num++)
		{
			m_OriginPointCloud[num].b_Selected = false;
		}
		//������в����µ��޲���
		for (int num = 0; num < repairedPoint.size(); num++)
		{
			if (b_AllPoint)
			{
				if (num % 2 == 0 && repairedPoint[num].b_TVPoint == false && num != 0)
				{
					continue;
				}
			}
			m_AddedPoingCLoud.push_back(repairedPoint[num]);
		}
	}
}

//���е������ǻ�
void PointCloudData::SurfaceGenerating()
{
	//�Ȼ�ȡ���е���Ҫ���ǻ��ĵ���
	vector<PCPoint> pointSurfaceCloud;
	//��ʼ����ʾ�õĵ���
	m_AddedRepairingPointCloud = new PCPoint[m_PointSumNumber + m_AddedPoingCLoud.size()];

	for (int num = 0; num < m_PointSumNumber; num++)
	{
		if (b_OneStepMode)
		{
			gProgressAu = 30 + 5 * ((double)num / (double)m_PointSumNumber);//������ʾ������
		}
		else
		{
			gProgressAu = 10 * (double)num / (double)m_PointSumNumber;//��ʾ������
		}
		pointSurfaceCloud.push_back(m_OriginPointCloud[num]);
		m_AddedRepairingPointCloud[num].m_Coordinate[0] = m_OriginPointCloud[num].m_Coordinate[0];
		m_AddedRepairingPointCloud[num].m_Coordinate[1] = m_OriginPointCloud[num].m_Coordinate[1];
		m_AddedRepairingPointCloud[num].m_Coordinate[2] = m_OriginPointCloud[num].m_Coordinate[2];
	}

	for (int num = 0; num < m_AddedPoingCLoud.size(); num++)
	{
		pointSurfaceCloud.push_back(m_AddedPoingCLoud[num]);
		m_AddedRepairingPointCloud[num + m_PointSumNumber].m_Coordinate[0] = m_AddedPoingCLoud[num].m_Coordinate[0];
		m_AddedRepairingPointCloud[num + m_PointSumNumber].m_Coordinate[1] = m_AddedPoingCLoud[num].m_Coordinate[1];
		m_AddedRepairingPointCloud[num + m_PointSumNumber].m_Coordinate[2] = m_AddedPoingCLoud[num].m_Coordinate[2];
	}
	//��ʼ������
	pcl::PointCloud<pcl::PointXYZ>::Ptr surfaceCloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;//���㷨ʸ��
	//�洢���Ƶķ�ʸ��
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	//����kdtree
	pcl::search::KdTree<pcl::PointXYZ>::Ptr surfaceTree(new pcl::search::KdTree<pcl::PointXYZ>);
	//��ʼ�� PCL ����
	surfaceCloud->width = m_PointSumNumber + m_AddedPoingCLoud.size();
	surfaceCloud->height = 1;
	surfaceCloud->points.resize(surfaceCloud->width * surfaceCloud->height);
	int cloudCount = 0;
	for (int num = 0; num <m_PointSumNumber + m_AddedPoingCLoud.size(); num++)
	{
		if (b_OneStepMode)
		{
			gProgressAu = 35 + 5 * ((double)num / (double)(m_PointSumNumber + m_AddedPoingCLoud.size()));//������ʾ������
		}
		else
		{
			gProgressAu = 10 + 10 * (double)num / (double)(m_PointSumNumber + m_AddedPoingCLoud.size());
		}
		surfaceCloud->points[cloudCount].x = pointSurfaceCloud[num].m_Coordinate[0];
		surfaceCloud->points[cloudCount].y = pointSurfaceCloud[num].m_Coordinate[1];
		surfaceCloud->points[cloudCount].z = pointSurfaceCloud[num].m_Coordinate[2];
		cloudCount++;
	}
	
	//��cloud����tree����
	surfaceTree->setInputCloud(surfaceCloud);
    //Ϊ���߹��ƶ��������������
	n.setInputCloud(surfaceCloud);
	n.setSearchMethod(surfaceTree);
	n.setKSearch(20);
	n.compute(*normals);
	//���е��Ƶ����ǻ�
	pcl::PointCloud<pcl::PointNormal>::Ptr surfaceCloudWithNormals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*surfaceCloud, *normals, *surfaceCloudWithNormals);
	//�����ǻ���صı������ж���
	pcl::search::KdTree<pcl::PointNormal>::Ptr surfaceTreeWithNormals(new pcl::search::KdTree<pcl::PointNormal>);
	surfaceTreeWithNormals->setInputCloud(surfaceCloudWithNormals);
	pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
	
	gp3.setSearchRadius(m_trianMaxDistace);//���ǻ���õ���ÿ�������ε������ܱ߳�
	gp3.setMu(m_trianMaxAngle);//���ý�����������Զ����
	gp3.setMaximumNearestNeighbors(100);//�����������������������
	gp3.setMaximumSurfaceAngle(M_PI / 4);//��Ƕ�Ϊ45��
	gp3.setMinimumAngle(M_PI * m_trianMinAngle);//�������ǻ���õ��������ڽ���С�Ƕ�
	gp3.setMaximumAngle(M_PI * m_trianMaxSAngle);//�������ǻ���õ��������ڽ����Ƕ�
	gp3.setNormalConsistency(false);//ʹ�÷�ʸ������һ��

	gp3.setInputCloud(surfaceCloudWithNormals);
	gp3.setSearchMethod(surfaceTreeWithNormals);
	if (b_OneStepMode)
	{
		gProgressAu = 40;
	}
	else
	{
		gProgressAu = 30;
	}
	gp3.reconstruct(triangles);

	/*pcl::Poisson<pcl::PointNormal> pn;
	pn.setConfidence(false);
	pn.setIsoDivide(2);
	pn.setInputCloud(surfaceCloudWithNormals);
	pn.setSearchMethod(surfaceTreeWithNormals);
	pn.reconstruct(triangles);
	*/
	gProgressAu = 50;
	gProgressAu = -1;
	
	/*
	// Additional vertex information
	std::vector<int> parts = gp3.getPartIDs();
	std::vector<int> states = gp3.getPointStates();
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPolygonMesh(triangles, "my");

	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();
	// ��ѭ��
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	*/
}

//��ȡ�޲�֮��ĵ�������
PCPoint* PointCloudData::GetAddedRepairingPointCloud()
{
	return m_AddedRepairingPointCloud;
}
//��ȡѡȡ���ݵ�ķ�ʸ��
void PointCloudData::GetSelectedPointsNormalVectors()
{
	m_SelectedPointsNormalPoints.clear();
	m_SelectedPointsNormalPoints2.clear();
	for (int num = 0; num < m_PointSumNumber; num++)
	{//�õ�ѡ������ݵ㼯
		if (m_OriginPointCloud[num].b_Selected == true)
		{
			m_SelectedPointsNormalPoints.push_back(m_OriginPointCloud[num]);
		}
	}
	//��ȡ��ʸ��
	PCPoint* tempPointCloud = new PCPoint[m_SelectedPointsNormalPoints.size()];
	for (int num = 0; num < m_SelectedPointsNormalPoints.size(); num++)
	{
		m_SelectedPointsNormalPoints[num].m_Normal
			= GetNormalVector(m_SelectedPointsNormalPoints[num]);
		tempPointCloud[num].m_Coordinate[0] = m_SelectedPointsNormalPoints[num].m_Coordinate[0];
		tempPointCloud[num].m_Coordinate[1] = m_SelectedPointsNormalPoints[num].m_Coordinate[1];
		tempPointCloud[num].m_Coordinate[2] = m_SelectedPointsNormalPoints[num].m_Coordinate[2];
		tempPointCloud[num].m_Normal = m_SelectedPointsNormalPoints[num].m_Normal;
	}
	//���з�ʸ���������
	RectifyNormals(tempPointCloud, m_SelectedPointsNormalPoints.size());
	int selectedSize = m_SelectedPointsNormalPoints.size();
	m_SelectedPointsNormalPoints.clear();
	for (int num = 0; num < selectedSize; num++)
	{
		m_SelectedPointsNormalPoints.push_back(tempPointCloud[num]);
	}
	for (int num = 0; num < m_SelectedPointsNormalPoints.size(); num++)
	{
		PCPoint* tempPoint = new PCPoint;
		tempPoint->m_Coordinate[0] = m_SelectedPointsNormalPoints[num].m_Coordinate[0];
		tempPoint->m_Coordinate[1] = m_SelectedPointsNormalPoints[num].m_Coordinate[1];
		tempPoint->m_Coordinate[2] = m_SelectedPointsNormalPoints[num].m_Coordinate[2];
		tempPoint->m_Normal = m_SelectedPointsNormalPoints[num].m_Normal;
		GetAdditionalPoint(tempPoint);
		m_SelectedPointsNormalPoints2.push_back(*tempPoint);
	}
}
//PCL�е�ģ�� �߽籣��
void PointCloudData::PCLBoundaryKeep()
{
	//PCL �еķ��� begin//
	pcl::PointCloud<pcl::Boundary> boundaries;
	pcl::BoundaryEstimation<pcl::PointXYZ, pcl::Normal, pcl::Boundary> boundEst;
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normEst;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr searchTree(new pcl::search::KdTree<pcl::PointXYZ>);
	
	searchTree->setInputCloud(cloud);
	normEst.setInputCloud(cloud);
	//normEst.setRadiusSearch(0.1);
	if (b_OneStepMode)
	{
		gProgressAu = 5 * (10.0 / 50.0);
	}
	else
	{
		gProgressAu = 10;
	}
	normEst.setSearchMethod(searchTree);
	normEst.setKSearch(10);
	normEst.compute(*normals);
	if (b_OneStepMode)
	{
		gProgressAu = 5 * (30.0 / 50.0);
	}
	else
	{
		gProgressAu = 30;
	}

	boundEst.setInputCloud(cloud);
	boundEst.setInputNormals(normals);
	boundEst.setRadiusSearch(Threadshold);
	boundEst.setAngleThreshold(M_PI / 4);
	boundEst.setSearchMethod(pcl::search::KdTree<pcl::PointXYZ>::Ptr(new pcl::search::KdTree<pcl::PointXYZ>));
	boundEst.compute(boundaries);
	if (b_OneStepMode)
	{
		gProgressAu = 5 * (45.0 / 50.0);
	}
	else
	{
		gProgressAu = 45;
	}

	for (int num = 0; num < m_PointSumNumber; num++)
	{
		if (boundaries.points[num].boundary_point == 1)
		{
			m_OriginPointCloud[num].b_BoundaryPoint = true;
			m_OriginPointCloud[num].m_Color[0] = 1.0;
		}
		else
		{
			m_OriginPointCloud[num].m_Color[2] = 1.0;
		}
	}
	if (b_OneStepMode)
	{
		gProgressAu = 5 * (50.0 / 50.0);
	}
	else
	{
		gProgressAu = 50;
	}

	//end//
}
//����ͶƱ�㷨����������
void PointCloudData::TensorVoting(vector<PCPoint>& repairedPoint)
{
	int k = 0;
	double gussValue = 0.5;//the parameter of guss function.
	double eigenvalue1;//define three eigenvalues.
	double eigenvalue2;
	double eigenvalue3;
	double dm;
	double wi;
	double wMax = 1.45;
	double wMin = 1.0;
	//���ڴ洢�޲���ĵ������ݽṹ
	pcl::PointCloud<pcl::PointXYZ>::Ptr coeCloud; // PCL ���ƴ洢�ռ�
	pcl::KdTreeFLANN<pcl::PointXYZ> coeKdtree;
	//��ʼ��kd���͵�������
	coeCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
	coeCloud->width = repairedPoint.size();//��ʼ�� PCL ����
	coeCloud->height = 1;
	coeCloud->points.resize(coeCloud->width * coeCloud->height);
	int cloudCount = 0;
	for (int num = 0; num < repairedPoint.size(); num++)
	{
		coeCloud->points[cloudCount].x = repairedPoint[num].m_Coordinate[0];
		coeCloud->points[cloudCount].y = repairedPoint[num].m_Coordinate[1];
		coeCloud->points[cloudCount].z = repairedPoint[num].m_Coordinate[2];
		cloudCount++;
	}
	coeKdtree.setInputCloud(coeCloud);

	for (int num = 0; num < repairedPoint.size(); num++)
	{

		eigenvalue1 = 0;
		eigenvalue2 = 0;
		eigenvalue3 = 0;
		dm = 0;
	   
		//����k��������
		PCLCoefficientsKDtreeNKSearch(repairedPoint[num], 10,coeCloud, coeKdtree);
		vector<PCPoint>::iterator it = RkNearestPoints.begin() + 1;
		for (int i = 0; i < 9; it++, i++)//use the function to get tensor T.
		{//count the T tensor of RangeData[num].
			dm = (it->m_Coordinate[0] - repairedPoint[num].m_Coordinate[0])*(it->m_Coordinate[0] - repairedPoint[num].m_Coordinate[0])
				+ (it->m_Coordinate[1] - repairedPoint[num].m_Coordinate[1])*(it->m_Coordinate[1] - repairedPoint[num].m_Coordinate[1])
				+ (it->m_Coordinate[2] - repairedPoint[num].m_Coordinate[2])*(it->m_Coordinate[2] - repairedPoint[num].m_Coordinate[2]);
			PCPoint p;
			p.m_Coordinate[0] = it->m_Coordinate[0];
			p.m_Coordinate[1] = it->m_Coordinate[1];
			p.m_Coordinate[2] = it->m_Coordinate[2];
			eigenvalue1 += Guss(GetTwoPointsDistance(p, repairedPoint[num]), gussValue)*(1 - (it->m_Coordinate[0] - repairedPoint[num].m_Coordinate[0])*(it->m_Coordinate[0] - repairedPoint[num].m_Coordinate[0]) / dm);
			eigenvalue2 += Guss(GetTwoPointsDistance(p, repairedPoint[num]), gussValue)*(1 - (it->m_Coordinate[1] - repairedPoint[num].m_Coordinate[1])*(it->m_Coordinate[1] - repairedPoint[num].m_Coordinate[1]) / dm);
			eigenvalue3 += Guss(GetTwoPointsDistance(p, repairedPoint[num]), gussValue)*(1 - (it->m_Coordinate[2] - repairedPoint[num].m_Coordinate[2])*(it->m_Coordinate[2] - repairedPoint[num].m_Coordinate[2]) / dm);
		}
		RkNearestPoints.clear();//clear 
		sortValue(eigenvalue1, eigenvalue2, eigenvalue3);//sort the three values from max to mini.
		wi = (eigenvalue2 + eigenvalue3) / eigenvalue1;// get w.

		if (wi > wMax)
		{
			repairedPoint[num].b_TVPoint = true;
			repairedPoint[num].m_Color[0] = 0.0;
			repairedPoint[num].m_Color[1] = 0.0;
			repairedPoint[num].m_Color[2] = 0.0;
		}
	}
	//�����������λ�õĵ���
	int rpCount = 0;
	for (int i = 0; i < repairedPoint.size(); i++)
	{
		if (repairedPoint[i].b_TVPoint)
		{
			rpCount++;
		}
	}
	//ֻ�г���10�����ʱ��Ž�������ǿ��
	if (rpCount > 10)
	{
			for (int num = 0; num < repairedPoint.size(); num++)
		{
		if (repairedPoint[num].b_TVPoint)
		{//�����������
		//��ȡ���ݵ㷨ʸ��
		repairedPoint[num].m_Normal = GetTVNormalVector(repairedPoint[num], coeCloud, coeKdtree);
		for (int j = 0; j < 3; j++)
		{
		repairedPoint[num].m_Normal[j] = -repairedPoint[num].m_Normal[j];
		}
		PCLKDtreeNKSearch(m_OriginPointCloud[0],2);
		double l = GetTwoPointsDistance(RkNearestPoints[0], RkNearestPoints[1]) / 2;
		RkNearestPoints.clear();
		double pNormal[3];
		double temp[3];
		for (int i = 0; i < 3; i++)
		{
		pNormal[i] = repairedPoint[num].m_Normal[i];
		}
		temp[0] = l * pNormal[0] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + repairedPoint[num].m_Coordinate[0];

		temp[1] = l * pNormal[1] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + repairedPoint[num].m_Coordinate[1];

		temp[2] = l * pNormal[2] / sqrt(pNormal[0] * pNormal[0]
		+ pNormal[1] * pNormal[1] + pNormal[2] * pNormal[2]) + repairedPoint[num].m_Coordinate[2];

		repairedPoint[num].m_Coordinate[0] = temp[0];
		repairedPoint[num].m_Coordinate[1] = temp[1];
		repairedPoint[num].m_Coordinate[2] = temp[2];
		}
		}
	}
}