#include<iostream>
#include"PCPoint.h"
#define MAX 10
extern int gProgress;
extern int gProgressAu;
extern bool b_Saved;//�����ж�
extern bool b_FIP;//�ļ������ж�
void Inverse(double *matrix1[], double *matrix2[], int n, double d);
double Determinant(double* matrix[], int n);
double AlCo(double* matrix[], int jie, int row, int column);
double Cofactor(double* matrix[], int jie, int row, int column);
void colunmPrincipleGauss(int N, double** a);//����Ԫ��˹��ȥ��
double GetRBFValue(double a);//�򵥾����������ֵ
double GetDistance(double* q, double* p);//��ȡ����֮��ľ���
bool ThreePointsCollinear(PCPoint p1,PCPoint p2,PCPoint p3);//�ж������Ƿ���
double Guss(double s, double x);
void sortValue(double &value1, double &value2, double &value3);