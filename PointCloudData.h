#pragma once
#include"Guass.h"
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/search/kdtree.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/poisson.h>
#include<pcl/features/boundary.h>
#define BCNum 30
#define NORMAL_VECTOR_NUM 5
using namespace std;
class PointCloudData
{
public:
	PointCloudData();
	~PointCloudData();
private://����
	int m_PointSumNumber;//��������
	PCPoint m_MidPoint;//ģ�͵��е�
	PCPoint* m_PointCloud;//�洢��������
	PCPoint* m_OriginPointCloud;//������ʾ���ĺ�ĵ�������
	PCPoint* m_AddedRepairingPointCloud;//�����޲���֮��ĵ�������
	double m_MaxX;//��������������xֵ
	double m_MinX;//������������С��xֵ
	double m_MaxY;//��������������yֵ
	double m_MinY;//������������С��yֵ
	double m_MaxZ;//��������������zֵ
	double m_MinZ;//������������С��zֵ
	vector<PCPoint> RkNearestPoints;//���ڴ洢k���ڵ�
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud; // PCL ���ƴ洢�ռ�
	pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
	int m_CloudClusterNum;//�������
	vector<PCPoint>* m_BoundaryPointClusters;//�洢�߽���༯��
	vector<PCPoint> m_AddedPoingCLoud;//�������޲���
public:
	pcl::PolygonMesh triangles;//���ǻ����ģ��
	double  Threadshold;//�߽籣������
	double m_clusterDistace;//��С�������
	double m_clusterNum;//��С�������
	double m_trianMaxDistace;//������Ӿ���
	double m_trianMaxAngle;//����
	double m_trianMinAngle;//��С��
	double m_trianMaxSAngle;//��Զ��������
	vector<PCPoint> m_TestSeletedPointCloud;//test
	vector<PCPoint> m_SelectedPointsNormalPoints;//������ʾ���ݵ�ķ�ʸ��
	vector<PCPoint> m_SelectedPointsNormalPoints2;//������ʾ���ݵ�ķ�ʸ��
	//һ���޸�ģʽ
	bool b_OneStepMode;
	//һ���޲�����������
	bool b_AllPoint;
public://����
	int GetPointSumNumber();//��ȡģ�͵ĵ�������
	void SetPointSumNumber(int number);//����ģ�͵ĵ�������
	PCPoint* GetPointCloud();//��ȡ��������
	void InitPointCloud(PCPoint* pointCloud);//��ʼ����������
	PCPoint* GetOriginPointCloud();//��ȡ������ʾ���ĺ�ĵ�������
	PCPoint* GetAddedRepairingPointCloud();//��ȡ�޲�֮���ģ�͵�������
	bool ReadPointCloudFile(char* fileName);//���ļ��ж�ȡ��������
	void PointMoveToOrigin(PCPoint*& pointCloud);//��ģ��������ʾ����
	void PCLKDtreeNKSearch(PCPoint lpoint, int Knum);//PCL KDtree k��������
	bool BoundaryCheck(PCPoint lpoint);//�߽���
	bool HoleRepair();//�׶��޲�
	double* GetRBFCoefficients(vector<PCPoint>& m_SelectedPoint);//��ȡ�����������ϵ��
	void RectifyNormals(PCPoint* additionalPoint, int RBFNum);//�������
	double* GetNormalVector(PCPoint lpoint);//��ȡ���ݵ�ķ�ʸ��
	void GetAdditionalPoint(PCPoint* lpoint);//��ȡ����Լ�����ֵ
	double GetTwoPointsDistance(PCPoint p,PCPoint q);//��ȡ�������ݵ�֮��ľ���
	bool InsertRepairPoint(double* coefficients, vector<PCPoint> & repairedPoint, vector<PCPoint> m_SelectedBoundaryPoint, vector<PCPoint> m_SelectedPoint);//�����µ��޲���
	PCPoint GetInsertPoint(PCPoint p, PCPoint q, double l);//��ȡ�µĲ����޲���
	vector<PCPoint>* GetNewAddedPoint();//��ȡ�޲��㼯��
	//vector<PCPoint>* GetSelectedPoint();//��ȡԼ���㼯��
	void RepairedPointDisjust(double* coefficients, PCPoint& repairedPoint, vector<PCPoint> m_SelectedPoint);//�����׶��޲���
	void BoundaryClustering();//�߽����
	int GetCloudClusterNum();//��ȡ��������
	vector<PCPoint>* GetBoundaryPointClusters();//��ȡ�߽���༯��
	void AutomaticHoleRepair();//�Զ����п׶��޲�
	bool NotIn(PCPoint lpoint, vector<PCPoint> m_SelectedBoundaryPoint, vector<PCPoint> m_SelectedPoint);//�Ƿ���ѡ�еı߽缯����
	void SurfaceGenerating();//�������ǻ�
	void GetSelectedPointsNormalVectors();//��ȡѡȡ���ݵ�ķ�ʸ��
	void PCLBoundaryKeep();//PCL�еı߽籣���㷨
	void TensorVoting(vector<PCPoint>& repairedPoint);//����ͶƱ�㷨
	void PCLCoefficientsKDtreeNKSearch(PCPoint lpoint, int Knum, pcl::PointCloud<pcl::PointXYZ>::Ptr coeCloud
		, pcl::KdTreeFLANN<pcl::PointXYZ> coeKdtree);//��������PCL��������
	double* GetTVNormalVector(PCPoint lpoint, pcl::PointCloud<pcl::PointXYZ>::Ptr coeCloud
		, pcl::KdTreeFLANN<pcl::PointXYZ> coeKdtree);//�������ͶƱ�㷨�������㷨ʸ��
};

