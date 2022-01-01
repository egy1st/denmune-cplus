#ifndef __DBSCAN_H__
#define __DBSCAN_H__



//Uncomment this line for compiling in vs
//#include "stdafx.h"
#include<cmath>
#include<vector>
#include<list>
#include <utility>
#include<map>
#include<iterator>
#include<set>
using namespace std;

struct Cmp
{
	bool operator () (const pair <double, int> &a, const pair <double, int> &b)
	{
		return a.first > b.first ;
	}
};

struct Cmp2
{
	bool operator () (const pair <double, int> &a, const pair <double, int> &b)
	{
		return a.second < b.second ;
	}
};

struct Cmp3
{
	bool operator () (const pair <double, int> &a, const pair <double, int> &b)
	{
		return a.first < b.first ;
	}
};

struct Cmp4
{
	bool operator () (const pair <int, double> &a, const pair <int, double> &b)
	{
		return a.second < b.second ;
	}
};

struct Cmp5
{
	bool operator () (const pair <int, int> &a, const pair <int, int> &b)
	{
		return a.first < b.first ;
	}
};


int parsingInput(int argc, char *argv[]);
string Print_Pattern(int i);
void tokenizer(const string& str, vector<string>& tokens, const string& delimiters = " \t") ;



class DataPoint
{
public:
	                     // 3 for noise
	int     point_id ;
	int     class_id ; 
    double homogenity ;
	double diameter ;
	double minimeter ;
	double range;
	double average ;
	double std;
	double ref_std;
	int ref_range;
	double inner_dis ;
	double inner_ratio;
	vector<int> reference;
	multiset<pair<int, int>,Cmp> intensity;
	multimap<int, int> correlation;
	int     is_noise ;    // 1 indicate NOISE
	int     is_isolated ;    // 1 indicate has no references at all
	int     is_dense ;    // 1 indicates it has one  refence  point at k =1 
	int     act_class ;    
	bool    visited ;
	int     visit_count;
  	int strength ;
	int ref_count ;
	double ref_correlation;
	bool intact;
	
	
		
	multiset<pair<int ,double>, Cmp4> referred_by ;
	multiset<pair<double, int>, Cmp3> refer_to;
	
	

	//pair<double, int> refer_to ;

	//double d1;    // dimension x-axis
	//double d2;    // dimension y-axis
	vector<double> D ;
	
public:
	DataPoint(vector<double> );
	double Compute_Distance(DataPoint& dp , int T);
	double Compute_AllDistance(DataPoint& dp , int T);
	
	
};

void Plot_Rectangle(DataPoint start_point , int width ,int height , int step , int cluster_no);

class DBSCAN
{
public:
//	vector<DataPoint> DataPoints;
    const char* filename  ;
    int mydim_num;
    int records_num ;
    int k_nearst ;
    int link_strength ;
	int noise_threshold;
	int num_dimentional;
	int dis_type;
	int step_count ;
    double TP;
	string file_name ;

private:
//

public:
	DBSCAN();
	void AddDataPoint(DataPoint dp);
	void AddMissPoint(DataPoint dp);
	void Prepare_DataPoints();
	void Save_DataPoints(const char* _file);
	void Save_DisMatrix(const char* _file);
	void Load_DataPoints(const char* _file);
	void Load_DisMatrix(const char* _file);
	void Load_ParaSet(const char* _file);
	void Mark_DensePoints(const char*  _file );
	void static Set_Guide(string _file);
	void static Compute_Overlap();
	void static Compute_Intensity();
	void static Compute_Correlation();
	int static Attach_Point(int point_id);
	int static Attach_Weak_Point(int point_id);
	//void Load_Mitosis(const char* _file1 , const char* _file2);
	

	multimap<double,int> Compute_Distance(DataPoint& dp);
	vector<double> Compute_AllDistance(DataPoint& dp);
	void Init_DataPoints();
	void Semi_Init_DataPoints();
	void Print_Clusters();
	void Sort_DataPoints();
	void pre_Sort_DataPoints();
	void Compute_Links();
    void Prepare_Clusters();
	void Prepare_Clusters2();
	void Merge_Clusters();
	void Find_Noise();
	void Find_Dense();
	void Output_Classes();
	void Swap_2Sets(int a, int b);
	
    		
private:
	//void CorePointCluster(int dp_pos, int core_class_id);
	
};

#endif
