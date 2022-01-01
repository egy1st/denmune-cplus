#include "stdafx.h"
#include<stack>
#include<fstream>
#include<iostream>
#include <iomanip>
#include "Find.h"
#include <limits>
#include <string>
#include <algorithm>
#include <time.h>
#include <vector>
#include "Tree.h"
#include "similarity.h"
#include <sstream>
#include <set>
#include <assert.h>

//const string DATA_PATH  = "D:/PhD/TiRaNN/Data/" ;
const string DATA_PATH  = "../Data/" ;
int dim_num = 50;


int itration_to_stop_at = 0 ;
double tot_time = 0.00 ;
double time_exec = 0.00 ;
bool stopClustering = false ;
int strong_points = 0 ;
int weak_points_phase1 = 0 ;
int weak_points_phase2 = 0 ;

map<int, set<int> > weight_class;
string Prog_State = "";
string FILE_NAME = "";
string filename = "";
vector<DataPoint> DataPoints, Miss_Points;
int dp_count = 0;
multiset<pair<double, int>, Cmp> Kernel_Pts;
multiset<pair<int, int>, Cmp2> Overlap_Pts;
multimap<int, int> Pass_Points;
multiset<pair<int, int>, Cmp5> Print_Points;
typedef Tree<int> TreeCls;
TreeCls g_tree;
vector<TreeCls::Node*> Class_Points;
int _num_dimentional = 0;
double _best_value = 0.0;
double TP_BEST = 0.0;
ofstream Out;
string st1;
int tot_refsize = 0;
stringstream weightno_stream;
string weightno_str = "";
int strength_multiple = 0.0;
int steps_increment = 0;
double REF_COUNT = 0.0;
double GravityMultiplier = 0.5;
bool Two_D = false;
bool ValidateIt = false;
int INTERSECT = 1;
double CLASS_STRENGTH = 0.01;
int tot_Noises = 0;
bool printIt = false;

int basic_guide[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int basic_count[30] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int chars_guide[10] = { 554, 1125, 1682, 2254, 2822, 3380, 3938, 4504, 5058,
		5620 };
int chars_count[10] = { 554, 571, 557, 572, 568, 558, 558, 566, 554, 562 };

int mnist_guide[10] = { 6903,  14780, 21770, 28911, 35735, 42048, 48924, 56217, 63042, 70000};
int mnist_count[10] = { 6903, 7877, 6990, 7141, 6824, 6313, 6876, 7293, 6825, 6958 };

int digits_guide[10] = { 1143, 2286, 3430, 4485, 5629, 6684, 7740, 8882, 9937,
		10992 };
int digits_count[10] = { 1143, 1143, 1144, 1055, 1144, 1055, 1056, 1142, 1055,
		1055 };
int ecoli_guide[8] = { 143, 220, 222, 224, 259, 279, 284, 336 };
int ecoli_count[8] = { 143, 77, 2, 2, 35, 20, 5, 52 };
int breast_guide[2] = { 444, 683 };
int breast_count[2] = { 444, 239 };
int wdbc_guide[2] = { 357, 569 };
int wdbc_count[2] = { 357, 212 };
int wpbc_guide[2] = { 148, 194 };
int wpbc_count[2] = { 148, 46 };
int spect_guide[2] = { 55, 267 };
int spect_count[2] = { 55, 212 };
int cardio3_guide[3] = { 1655, 1950, 2126 };
int cardio3_count[3] = { 1655, 295, 176 };
int cardio10_guide[10] = { 384, 963, 1016, 1097, 1169, 1501, 1753, 1860, 1929,
		2126 };
int cardio10_count[10] = { 384, 579, 53, 81, 72, 332, 252, 107, 69, 197 };
int parkin_guide[2] = { 48, 195 };
int parkin_count[2] = { 48, 147 };
int robot2_guide[4] = { 2205, 4302, 4630, 5456 };
int robot2_count[4] = { 2205, 2097, 328, 826 };
int robot4_guide[4] = { 2205, 4302, 4630, 5456 };
int robot4_count[4] = { 2205, 2097, 328, 826 };
int robot24_guide[4] = { 2205, 4302, 4630, 5456 };
int robot24_count[4] = { 2205, 2097, 328, 826 };
int yeast_guide[10] = { 463, 468, 503, 547, 598, 761, 1005, 1434, 1454, 1484 };
int yeast_count[10] = { 463, 5, 35, 44, 51, 163, 244, 429, 20, 30 };
int iris_guide[3] = { 50, 100, 150 };
int iris_count[3] = { 50, 50, 50 };
int time_guide[6] = { 100, 200, 300, 400, 500, 600 };
int time_count[6] = { 100, 100, 100, 100, 100, 100 };
int letters_guide[26] = { 789, 1555, 2291, 3096, 3864, 4639, 5412, 6146, 6901,
		7648, 8387, 9148, 9940, 10723, 11476, 12279, 13062, 13820, 14568, 15364,
		16177, 16941, 17693, 18480, 19266, 20000 };
int letters_count[26] = { 789, 766, 736, 805, 768, 775, 773, 734, 755, 747, 739,
		761, 792, 783, 753, 803, 783, 758, 748, 796, 813, 764, 752, 787, 786,
		734 };

int glass_guide[6] = { 70, 146, 159, 188, 197, 214 };
int glass_count[6] = { 70, 76, 13, 29, 9, 17 };

int move_guide[15] = { 24, 48, 72, 96, 120, 144, 168, 192, 216, 240, 264, 288,
		312, 336, 360 };
int move_count[15] = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
		24 };

int arcene_guide[2] = { 112, 200 };
int arcene_count[2] = { 112, 88 };

int madelon_guide[2] = { 1300, 2600 };
int madelon_count[2] = { 1300, 1300 };

int gisette_guide[2] = { 3500, 7000 };
int gisette_count[2] = { 3500, 3500 };

int dorothea_guide[2] = { 1038, 1150 };
int dorothea_count[2] = { 1038, 112 };

int corel_guide[18] = { 167, 267, 352, 447, 554, 652, 752, 850, 1050, 1210,
		1360, 1520, 1584, 1684, 1774, 1874, 1974, 2074 };
int corel_count[18] = { 167, 100, 85, 95, 107, 98, 100, 98, 200, 160, 150, 160,
		64, 100, 90, 100, 100, 100 };

int compound_guide[6] = { 50, 142, 181, 225, 383, 399 };
int compound_count[6] = { 50, 92, 39, 44, 158, 16 };

DBSCAN ds;
bool act_class = false;
//        string f_names[] = {"time" , "ecoli"  , "breast" , "wdbc" , "gisette", "corel", "madelon", "arcene" , "chars" , "digits"} ;
string f_names[] = { "iris", "time", "arcene", "madelon", "chars",  "digits" , "mnist", "gisette", "dorothea"};
//int count_k =0 ;
//int  count_z = 0 ;
//int count_c = 0 ;
//int Prog_Step = 1 ;

int main(int argc, char* argv[]) {
	vector<double> Dim;

	Prog_State = ""; // sd  oc    Save Dis //   // Output Classes
	if (Prog_State == "")
		ValidateIt = true;

	//ifstream lastrun("last_run.txt");
	//if(lastrun.is_open())
	{
		//lastrun>>Prog_Step>>count_k>>count_z>>count_c ;
		//lastrun.close()

	}

	for (int Prog_Step = 6; Prog_Step <= 6; Prog_Step++)

	{

		
		if (Prog_Step == 6) dim_num = 200 ;
		else dim_num = 50 ;

		TP_BEST = 0.0;
		ds.file_name = f_names[Prog_Step] ;
		string unique_fileName = ds.file_name;
		_best_value = 0;

		int _step1 = 39;  //dim_num ;
		//string unique_fileName = "mnist";
		int int_dim = 2;
		printIt = false;

		ds.file_name = unique_fileName;
		FILE_NAME = ds.file_name;

		ds.dis_type = 1;

		stringstream stream_dim;
		stream_dim << int_dim;
		string str_dim = stream_dim.str();
		// FILE_NAME = ds.file_name  + str_dim;
		// ds.file_name = unique_fileName ;
		if (int_dim != 0)
			ds.file_name = unique_fileName + str_dim;

		string _pre_file_name1 = "Data_";
		string _pre_file_name2 = "Dis_";
		string _pre_file_name3 = "DisMatrix_";
		string _post_file_name1 = ".txt";
		stringstream _post_file_name2;
		string _post_file_name3 = ".txt";

		if (unique_fileName == "iris") {
			ds.step_count = 3;
			ds.num_dimentional = (int_dim == 0) ? 4 : int_dim;
			ds.records_num = 150;
		} else if (unique_fileName == "letters") {
			ds.step_count = 26;
		} else if (unique_fileName == "time") {
			ds.step_count = 6;
			ds.num_dimentional = (int_dim == 0) ? 60 : int_dim;
			ds.records_num = 600;
		} else if (unique_fileName == "move") {
			ds.step_count = 15;
			ds.num_dimentional = 90;
			ds.records_num = 360;
		} else if (unique_fileName == "digits") {
			ds.step_count = 10;
			ds.num_dimentional = (int_dim == 0) ? 16 : int_dim;
			ds.records_num = 10992;
		} else if (unique_fileName == "chars") {
			ds.step_count = 10;
			ds.num_dimentional = (int_dim == 0) ? 64 : int_dim;
			;
			ds.records_num = 5620;
		} else if (unique_fileName == "spect") {
			ds.step_count = 2;
		} else if (unique_fileName == "breast") {
			ds.step_count = 2;
			ds.num_dimentional = 9;
			ds.records_num = 683;
		} else if (unique_fileName == "wdbc") {
			ds.step_count = 2;
			ds.num_dimentional = 30;
			ds.records_num = 569;
		} else if (unique_fileName == "wpbc") {
			ds.step_count = 2;
		} else if (unique_fileName == "ecoli") {
			ds.step_count = 8;
			ds.num_dimentional = 7;
			ds.records_num = 336;
		} else if (unique_fileName == "cardio3") {
			ds.step_count = 3;
		} else if (unique_fileName == "cardio10") {
			ds.step_count = 10;
		} else if (unique_fileName == "parkin") {
			ds.step_count = 2;
		} else if (unique_fileName == "robot2") {
			ds.step_count = 4;
		} else if (unique_fileName == "robot4") {
			ds.step_count = 4;
		} else if (unique_fileName == "robot24") {
			ds.step_count = 4;
			ds.num_dimentional = (int_dim == 0) ? 24 : int_dim;
			ds.records_num = 5456;
		} else if (unique_fileName == "yeast") {
			ds.step_count = 10;
			ds.num_dimentional = 8;
			ds.records_num = 1484;
		}

		else if (unique_fileName == "arcene") {
			ds.step_count = 2;
			ds.num_dimentional = (int_dim == 0) ? 10000 : int_dim;
			ds.records_num = 200;
		} else if (unique_fileName == "madelon") {
			ds.step_count = 2;
			ds.num_dimentional = (int_dim == 0) ? 500 : int_dim;
			ds.records_num = 2600;
		} else if (unique_fileName == "dorothea") {
			ds.step_count = 2;
			ds.num_dimentional = (int_dim == 0) ? 100000 : int_dim;
			ds.records_num = 1150;
		} else if (unique_fileName == "gisette") {
			ds.step_count = 2;
			ds.num_dimentional = (int_dim == 0) ? 5000 : int_dim;
			ds.records_num = 7000;
		} else if (unique_fileName == "cham_01") {
			ds.step_count = 0;
			ds.num_dimentional = 2;
			ds.records_num = 8000;
		} else if (unique_fileName == "cham_02") {
			ds.step_count = 0;
			ds.num_dimentional = 2;
			ds.records_num = 8000;
		} else if (unique_fileName == "cham_03") {
			ds.step_count = 0;
			ds.num_dimentional = 2;
			ds.records_num = 8000;
		} else if (unique_fileName == "cham_04") {
			ds.step_count = 0;
			ds.num_dimentional = 2;
			ds.records_num = 10000;
		} else if (unique_fileName == "compound") {
			ds.step_count = 6;
			ds.num_dimentional = 2;
			ds.records_num = 399;
		} else if (unique_fileName == "mnist") {
			ds.step_count = 10;
			ds.num_dimentional = (int_dim == 0) ? 784 : int_dim;
			ds.records_num = 70000;
		}


		if (Prog_State == "oc")  // Output_Classes
				{
			ds.Output_Classes();
			return 0;
		}

		if (ds.num_dimentional == 2)
			Two_D = true;
		else
			Two_D = false;

		if (ds.file_name.substr(0, 4) == "cham")
			ValidateIt = false;

		if (ds.dis_type == 1) {
			_post_file_name2 << "_" << dim_num << "_euc.txt";
			_post_file_name3 = "_euc.txt";
		} else if (ds.dis_type == 2) {
			_post_file_name2 << "_" << dim_num << "_cor.txt";
			_post_file_name3 = "_cor.txt";
		} else if (ds.dis_type == 3) {
			_post_file_name2 << "_" << dim_num << "_cos.txt";
			_post_file_name3 = "_cos.txt";
		}

		string _File_Data = DATA_PATH + _pre_file_name1 + ds.file_name + _post_file_name1;
		string _File_Dis = DATA_PATH + _pre_file_name2 + ds.file_name
				+ _post_file_name2.str();
		string _File_Matrix = DATA_PATH + _pre_file_name3 + ds.file_name + _post_file_name3;

		const char* c_File_Data = _File_Data.c_str();
		const char* c_File_Dis = _File_Dis.c_str();
		const char* c_File_Matrix = _File_Matrix.c_str();

		DataPoints.clear();
		Kernel_Pts.clear();
		Print_Points.clear();

		ifstream Records(c_File_Data);
		if (Records.is_open()) {
			//The first line is assumed tods contain eps, min_pts,no_columns and no_recods
			//Records>>ds.records_num>>ds.num_dimentional>>ds.k_nearst>>ds.noise_threshold>>ds.link_strength;
//		Records>>ds.records_num>>ds.num_dimentional;
			//Once we know the number of records we will simly read it from the text file and insert it in
			//our list by using the AddDataPoint function
			Dim.resize(ds.num_dimentional);
		 if (Prog_State == "" && Two_D == false ) 
        {
        	 Dim.resize(0);
        }

        int c_cls = 0 ; 	
		

		DBSCAN::Set_Guide(ds.file_name);
		for(int i=0;i<ds.records_num;i++)
        {
           


        if (Prog_State == ""  && Two_D == true ) 
        {
           for(int n=0;n<ds.num_dimentional;n++)
              {  
			   Records>>Dim[n];
              			
			 }
		}   
		   
		   if (act_class == true)
		   {
			   Records>> c_cls ; 			
		   }
	      	  
               ds.AddDataPoint(DataPoint(Dim), c_cls );
        }
		Records.close();

		}
	else
	{
		cout<<"Can't Open Data.txt"<<endl;
	}


		//calculate distance matrix
		if (Prog_State == "sd") // Save_Dis
				{
			Two_D = true;
			ValidateIt = false;
			ds.Save_DataPoints(c_File_Dis);
			return 0;
		}

		///////////ds.Load_Mitosis("dat1.txt" , "solution.txt");

///*

		//ds.Load_DisMatrix(c_File_Matrix);

		int _old_TP_c = 0;
		int _old_TP_z = 0;
		int TP_freq_c = 0;
		int TP_freq_z = 0;
		bool _first_c = false;
		bool _first_z = false;
		int _link_threshold = 0;
		int _noise_threshold = 0;

		//int _step1 = 36;  //dim_num ;
		strength_multiple = 2.50;
		GravityMultiplier = 1.00;
		steps_increment = 8000;  //6990
		REF_COUNT = 2.8;
		double _step2 = 1;
		int _step3 = 0;

		st1 = "Para_Set_ho_" + ds.file_name + ".txt"; // _post_file_name2 ;
		const char* st1_c = st1.c_str();
		remove(st1_c);
		Out.open(st1_c, ios_base::app);
		Out << "k_nearst" << "\t" << "n_noises" << "\t" << "n_cls" << "\t"
				<< "real_cls" << "\t" "itration_to_stop_at" << "\t" << "strong-points" << "\t" << "weak-phase1" << "\t" << "weak-phase2" << "\t" <<  "time_exec" << "\t" << "VMeasure" << "\t" << "FMeasure"
				<< "\t" << "AdjustedRandIndex" << "\t" << "Jaccard" << "\t"
				<< "Purity" << "\t" << "Entropy" << "\t" << "Fowlkes" << "\t"
				<< "Gamma" << "\t" << "MI" << "\t" << "VI" << "\t" << "Q0"
				<< "\t" << "Q2" << "\t" << "RandIndex" << "\t" << "Mirkin"
				<< "\t" << "InvariantMirkin" << "\n";
		Out.close();

		int my_step11 = 0 ;
		int  my_step12 = 0;

		if (printIt == true)
			ValidateIt = false;

		if (Two_D && !ValidateIt) {
			my_step11 = _step1;
			my_step12 = _step1;
		} else {
			my_step11 = 1;
			my_step12 = dim_num;
		} //dim_num  dim_num-50+

		//for (int count_k = my_step11; count_k <= my_step12; count_k++) {
		for (int count_k = 93; count_k <= 93; count_k++) {

			ds.k_nearst = count_k;
			//ds.Mark_DensePoints(c_File_Dis);
			ds.Load_DataPoints(c_File_Dis);
			weightno_str = "";
			weightno_stream.str("");

			//for (double count_z = _step2; count_z <= _step2; count_z += 1) // count_k/
			for (double count_z = 1000; count_z <= 70000; count_z += 1000) // count_k/
					{
				// ds.noise_threshold = count_z ;
				itration_to_stop_at = count_z;
				
				strength_multiple = count_z;
				//INTERSECT = count_z;
				//CLASS_STRENGTH = count_z;

				//for (int count_c = _step3  ; count_c <= count_k   ; count_c++ ) // count_k
				{

					//ds.link_strength = count_c ;

					//ofstream last_run;
					//last_run.open("last_run.txt");
					//last_run<<Prog_Step<<count_k<<count_z<<count_c<<endl;
					//last_run.close();

					//usleep(100000); // wait 0.001 second

					//ds.Save_DataPoints(c_File_Dis);
                    clock_t start = clock();
                    
					ds.Semi_Init_DataPoints(); // phd maa
					ds.Find_Noise();   // phd maa
					ds.Sort_DataPoints();
					ds.Prepare_Clusters();
					//ds.Prepare_Clusters2 () ;

					time_exec = ((double)clock() - start) / CLOCKS_PER_SEC ;
					tot_time += time_exec ;
					printf("%f\n",time_exec);


					ds.Print_Clusters();
				}





weight_class.clear();
Miss_Points.clear();
Kernel_Pts.clear();
Overlap_Pts.clear();
Pass_Points.clear();
Print_Points.clear();
Class_Points.clear();
Out.clear();


			}
//	Out.close() ;
		}

		int yu = 0;


	} // for Prog_Step

	// Plotting Program
	//remove("points.m") ;
	//Plot_Rectangle(DataPoint(0,0) , 100 , 100 , 6 , 0 ) ;
	//Plot_Rectangle(DataPoint(90,90) , 100 , 100 , 3  , 1) ;

	return 0;
}

void DBSCAN::Sort_DataPoints() {

	vector<DataPoint>::iterator pos = DataPoints.begin();
	vector<int>::iterator pos2;
	Kernel_Pts.clear();
	pos = DataPoints.begin();
	while (pos != DataPoints.end()) {
		if (pos->class_id != -1) {

			pos2 = DataPoints[pos->point_id].reference.begin();
			while (pos2 != DataPoints[pos->point_id].reference.end()) {
				if (DataPoints[*pos2].class_id != -1) {
					pos->strength++; // maa we can not ignore noises and work on reference as it // (2) we can neglect any point that has any noises
				}
				pos2++;
			}
			//    Kernel_Pts.insert(make_pair( ((double)pos->reference.size()*10000.00)+(double)pos->strength*100.00+(100.00/pos->homogenity),pos->point_id));
			//Kernel_Pts.insert(make_pair( ((double)pos->reference.size()+(pos->homogenity) ),pos->point_id));  // *(pos->homogenity) removed for now phd maa // maa supposed * not +  //(2) it worked on refernce.size not on pos->strength
			Kernel_Pts.insert(make_pair((pos->homogenity), pos->point_id));

		} else {
			int ty = 0;
		}
		pos++;
	}

}

int tot_kernalpoints = 0;
void DBSCAN::Find_Noise() {
	int p_nosie = 0;
	int p_outliers = 0;
	int tot_kernalpoints = 0;
	int tot_dense = 0;
	tot_refsize = 0;
//   DataPoint *dp ;

	Class_Points.clear();
	Class_Points.resize(dp_count + 1); //   Class_Points.resize(dp_count+1) ;

	for (int i = 0; i < dp_count; i++) {
		//      dp = &DataPoints[i] ;

		//int refcount = DataPoints[i].reference.size() ;
		if (DataPoints[i].is_dense == 1)
			tot_dense++;
		//if ( (int) DataPoints[i].reference.size() < noise_threshold )     //  this never will happen in TIRAN
		if ((int) DataPoints[i].reference.size() < 1) //  this never will happen in TIRAN
				{
			DataPoints[i].class_id = -1;
			DataPoints[i].is_noise = 1;
			Class_Points[i] = new TreeCls::Node(-1);
			p_nosie++;

		} else if (DataPoints[i].reference.size() == 0) {
			DataPoints[i].class_id = -1;
			DataPoints[i].is_noise = 1;
			DataPoints[i].is_isolated = 1;
			Class_Points[i] = new TreeCls::Node(-1);
			p_outliers++;
		} else {
			Class_Points[i] = new TreeCls::Node(0);
			tot_kernalpoints++;
			tot_refsize += DataPoints[i].reference.size();

		}

		if ((int) DataPoints[i].reference.size() >= 0) {
			Pass_Points.insert(
					make_pair(DataPoints[i].point_id,
							(int) DataPoints[i].reference.size()));
		}

	}

	//cout << p_nosie << " Noises and " << p_outliers << " Outliers  and " << tot_kernalpoints << " kernal " << tot_dense << " dense points " << endl ;
	//cout   << p_outliers << " Outliers  and " << tot_kernalpoints << " kernal " << tot_dense << " dense points " << endl ;
	cout << endl;
}

bool value_comparer(map<int, int>::value_type &i1,
		map<int, int>::value_type &i2) {
	return i1.second < i2.second;
}

int get_Root(int x) {
	TreeCls::Node* t;

	if (x == 0) {
		return 0;
	}

	if (x == -1) {
		return -1;
	}

	do {
		t = Class_Points[x]->parent();
		if (t != NULL) {
			x = t->data();
		}

	} while (t != NULL /* && x != t->data()  */); // phd maa

	return x;
}

bool AreSame(double a, double b, double eps) {
	return fabs(a - b) < eps;
}

//This function is going to prepare data points in each cluster
map<int, int> weight_map;
map<int, int> weight_map_parent;


void DBSCAN::Prepare_Clusters() {
	multiset<pair<double, int>, Cmp>::iterator pos, back_pos;
	vector<int>::iterator pos2, pos3;
	int center_of_gravity = 10000000;
	bool COG = false; // center-of-gravity is reached FLAG

	int class_id = 0;
	int _cls = 0;
	map<int, int>::iterator weight;
	map<int, int>::iterator found;

	DataPoint *dp_core, *dp_noise;
	int i = 0, i2 = 0;
	int _class_id;

	int iterNum = 0;
	int _refsize = 0;
	int weight_no = 0;
	int link_threshold = 0;
	int max_class = 0;
	int intersect = 0;
	int totcls = 0;
	int class_strength;
	set<int> S;
	int wz = 0;
	strong_points = 0 ;
    stopClustering  = 0 ;

	weight_class.clear();
	pos = Kernel_Pts.begin();
	back_pos = Kernel_Pts.end();

	if (Kernel_Pts.size() > 0) {
		dp_core = &DataPoints[pos->second];
		link_threshold = dp_core->reference.size();
	}

	if (Kernel_Pts.size() > 0) {
		back_pos--;
		dp_noise = &DataPoints[back_pos->second];
		link_threshold = dp_core->reference.size();
	}

	while (stopClustering == false && pos != Kernel_Pts.end()) {
		i++;

		S.clear();

		dp_core = &DataPoints[pos->second];
		Pass_Points.erase(dp_core->point_id);
		weight_map.clear();
		weight_map_parent.clear();

		
        /* 
		/////// begin Dummy Code for Titann

		_refsize += dp_core->reference.size();

        // here in tirann as GravityMultiplier is set to 1, the following condition will always be happen
		if (_refsize <= (GravityMultiplier * tot_refsize)) {  
			link_threshold = dp_core->reference.size();
			center_of_gravity = i;
		}

		else {
			// in tirann this COG will never set to true, as it is not used here in this Algorithm
			COG = true;  
		}

        /////// End Dummy Code for Titann
		// if (AreSame(dp_core->D[0], 485.1 , 0.1 && AreSame(dp_core->D[1], 360.9 , 0.1) ) ) {
		//	   int yui = 0 ;

		//   }

		*/
		
		iterNum++;

		if (iterNum >= itration_to_stop_at ) {
						stopClustering = true;
		}

		// remember no strong points & weak points in Tirann
		//  all points with at least one refernce are considered  (ignore noises)
		if (dp_core->reference.size() > 0

			    // notice we consider referred_by points as much as we can, as there no link thrthold L param
			// points with [[ referred_by.size() >= dp_core->refer_to.size())]] have higher weight than others and are considered strong points

				&& dp_core->referred_by.size() >= dp_core->refer_to.size() ) 
				//if (  ) // for propagation purpose
						{
                     strong_points++ ;							
			//iterNum++;

			class_id++;
			S.clear();
			//S.insert(pos->second);  // 3M

			pos2 = dp_core->reference.begin();
			dp_core->visited = true;
			dp_core->class_id = class_id;
			Class_Points[class_id] = new TreeCls::Node(class_id);
			max_class = -1;
			intersect = 0;

			while (pos2 != dp_core->reference.end()) {

				if (DataPoints[*pos2].visited // visited was tested not to affect on results, so you can ommit it
				       &&  DataPoints[*pos2].class_id > 0  // this condition is a must, as some points may be visited but not classified yet
						&& DataPoints[*pos2].referred_by.size()
								>= DataPoints[*pos2].refer_to.size()) // maa we may neglect is noise as long as it is in our refernce points
								{
					_cls = DataPoints[*pos2].class_id;
					//S.insert(*pos2);  // 3M
					_class_id = get_Root(_cls);
					weight_map[_class_id] += 1;
					intersect++;

					//_class_id = DataPoints[*pos2].class_id ;
					//weight_map_parent[_class_id] += 1 ;

				} else if (DataPoints[*pos2].visited == false) {
					// never un-comment this again DataPoints[*pos2].class_id = class_id ; //maa phd
					//DataPoints[*pos2].class_id = class_id ;
					//S.insert(*pos2);  // 3M
					DataPoints[*pos2].visited = true;  // this point is visited but not classified yet
				}
				pos2++;
			} // end inner while

			/// weight_class[class_id] = S ;    // 3M

			// maa you should check that set parent class work correctly

			if (weight_map.size() > 0 /* && intersect >= INTERSECT*/) {
				weight = max_element(weight_map.begin(), weight_map.end(),
						value_comparer);
				weight_no = weight->second;
				max_class = weight->first;

				int wz = weight_map.size();
				int _wz = wz - 1;
				while ((weight_map.size() > 0 /*  && weight_no >= strength_multiple */)) {

					_class_id = weight->first;
					class_strength = weight->second;

					if (_class_id != -1 & _class_id != class_id) {

						Class_Points[_class_id]->set_parent(
								new TreeCls::Node(class_id));

					}

					weight_map.erase(weight);
					weight = max_element(weight_map.begin(), weight_map.end(),
							value_comparer); // merge with all connected regions that have the same class
					// if (_wz > 0 )   weight_no = weight->second ;

				} // end while

			} // end if

		} // end main if

		passit: pos++;

	} // end outer while

	

	int gh = 0;
	int no = 0;


    iterNum = 0 ;
	

	for (i = 0; i < dp_count; i++) {
		DataPoints[i].class_id = get_Root(DataPoints[i].class_id);
		if (DataPoints[i].class_id == 0)
			gh++;
	
	}

	int NO = -1;
	no = 0;
	iterNum = 0 ;
	stopClustering = false ;

	//while (no != NO)

	 {

		NO = no;
		no = 0;

		pos = Kernel_Pts.begin();
        iterNum++;
		if (iterNum >= itration_to_stop_at ) {
						stopClustering = true;
		}
		while (stopClustering == false && pos != Kernel_Pts.end()) {
			i = pos->second;

			if (DataPoints[i].class_id == 0) {
				DataPoints[i].class_id = Attach_Point(i);
				no++;

			}

			pos++;
		}

		int yuu = 0;
	}

   weak_points_phase1 = no ;
	//*
	NO = -1;
	no = 0;
    iterNum = 0 ;
	stopClustering = false ;
	//while ( no != NO ) 
	//{

	//	NO = no ;
	//	no = 0 ;

	iterNum++;
		if (iterNum >= itration_to_stop_at ) {
						stopClustering = true;
		}
	pos = Kernel_Pts.begin();
	while (stopClustering == false && pos != Kernel_Pts.end() ) {
		i = pos->second;

		if (DataPoints[i].class_id == 0) {
			DataPoints[i].class_id = Attach_Weak_Point(i);
			no++;
		}

		pos++;
	}

 weak_points_phase2 = no ;
	//}

	//*/

	tot_Noises = 0;
	for (i = 0; i < dp_count; i++) {
		if (DataPoints[i].class_id == 0)
			tot_Noises++;
	}

	cout << endl;

}

int DBSCAN::Attach_Point(int point_id) {
	multiset<pair<double, int>, Cmp>::iterator pos, back_pos;
	vector<int>::iterator pos2, pos3;

	//int class_id = 0 ;
	int _cls = 0;
	map<int, int>::iterator weight;
	DataPoint *dp_core;
	int _class_id;
	int max_class = 0;
	int weight_no = 0;

	weight_map.clear();
	dp_core = &DataPoints[point_id];

	if (dp_core->reference.size() > 0) {
		pos2 = dp_core->reference.begin();
		dp_core->visited = true;
		//dp_core->class_id = class_id ;
		//Class_Points[class_id] = new TreeCls::Node (class_id);
		max_class = -1;

		while (pos2 != dp_core->reference.end()) {

			if (DataPoints[*pos2].visited == true
					&& DataPoints[*pos2].referred_by.size()
							>= DataPoints[*pos2].refer_to.size()) {
				_cls = DataPoints[*pos2].class_id;
				_class_id = get_Root(_cls);
				weight_map[_class_id] += 1;

			}
			pos2++;
		} // end inner while

		if (weight_map.size() > 0) {
			weight = max_element(weight_map.begin(), weight_map.end(),
					value_comparer);
			weight_no = weight->second;
			max_class = weight->first;
			return max_class; // this will return get_Root(max_class) as we computed earlier _class_id = get_Root(_cls) ;
			//return get_Root(max_class);
		}

	}

}

int DBSCAN::Attach_Weak_Point(int point_id) {
	multiset<pair<double, int>, Cmp>::iterator pos, back_pos;
	vector<int>::iterator pos2, pos3;

	//int class_id = 0 ;
	int _cls = 0;
	map<int, int>::iterator weight;
	DataPoint *dp_core;
	int _class_id;
	int max_class = 0;
	int weight_no = 0;

	weight_map.clear();
	dp_core = &DataPoints[point_id];

	if (dp_core->reference.size() > 0) {
		pos2 = dp_core->reference.begin();
		dp_core->visited = true;
		//dp_core->class_id = class_id ;
		//Class_Points[class_id] = new TreeCls::Node (class_id);
		max_class = -1;

		while (pos2 != dp_core->reference.end()) {

			if (DataPoints[*pos2].visited == true)
					{
						_cls = DataPoints[*pos2].class_id;
						_class_id = get_Root(_cls);
						weight_map[_class_id] += 1;

					}
					pos2++;
				} // end inner while

				if (weight_map.size() > 0) {
					weight = max_element(weight_map.begin(), weight_map.end(),
							value_comparer);
					weight_no = weight->second;
					max_class = weight->first;
					return max_class; // this will return get_Root(max_class) as we computed earlier _class_id = get_Root(_cls) ;
					//return get_Root(max_class);
				}

			}

		}

		void DBSCAN::Compute_Overlap() {
			multiset<pair<int, int>, Cmp2>::iterator pos;
			vector<int>::iterator pos2, pos3;

			int class_id = 0;

			DataPoint *dp_core;
			int i = 0;

			for (i = 0; i < dp_count; i++) {
				dp_core = &DataPoints[i];

				if (dp_core->reference.size() > 0) {

					pos2 = dp_core->reference.begin();
					dp_core->visit_count += 1;

					while (pos2 != dp_core->reference.end()) {

						DataPoints[*pos2].visit_count += 1;

						pos2++;
					} // end while
				} // end if

			} // end for

			Overlap_Pts.clear();
			for (i = 0; i < dp_count; i++) {
				Overlap_Pts.insert(make_pair(i, DataPoints[i].visit_count));
			}

			pos = Overlap_Pts.end();
			pos--;

			int yuio = 0;

		}

// this function computes both overlap & intensity
		void DBSCAN::Compute_Intensity() {

			vector<int>::iterator pos;
			int ref_count = 0;

			DataPoint *dp_core;
			int i = 0;
			int max = 0;
			int min = 100000;
			double ref_std = 0.00;
			int ref_range = 0;
			double homogenity = 0.0;

			for (i = 0; i < dp_count; i++) {

				vector<double> std_vector;

				dp_core = &DataPoints[i];

				if (dp_core->reference.size() > 0) {

					pos = dp_core->reference.begin();
					dp_core->visit_count += 1;
					ref_count = dp_core->reference.size();
					dp_core->ref_count = ref_count;
					dp_core->intensity.insert(make_pair(ref_count, i));
					max = min = ref_count;
					std_vector.push_back(ref_count);
					while (pos != dp_core->reference.end()) {

						DataPoints[*pos].visit_count += 1;
						ref_count = DataPoints[*pos].reference.size();
						std_vector.push_back(ref_count);
						dp_core->ref_count += ref_count;
						dp_core->intensity.insert(
								make_pair(ref_count,
										DataPoints[*pos].point_id));
						if (max < ref_count)
							max = ref_count;
						if (min > ref_count)
							min = ref_count;

						pos++;
					} // end while
					ref_std = Stats::GetStdev(std_vector);
					dp_core->ref_std = ref_std;
					ref_range = max - min;
					dp_core->ref_range = ref_range;
					homogenity = (100.00 * (double) std_vector.size())
							+ (1.00 / ref_std);
					dp_core->homogenity = homogenity;

				} // end if

			} // end for

		}

		void DBSCAN::Compute_Links() {

			multiset<pair<double, int>, Cmp3>::iterator pos, pos3;
			multiset<pair<int, double>, Cmp4>::iterator pos2;
			vector<int>::iterator pos4, pos5;
			bool found = 0;
			multimap<double, int> dis;
			int i_count = 0;
			int c_cls1, c_cls2, i_diff = 0;
			bool diff = false;

// find symetric similarity distances
			//printf("Find Symtrics\n");

			for (int i = 0; i < dp_count; i++) {
//    	dp = &DataPoints[i] ;
				diff = false;
				c_cls1 = c_cls2 = 0;

				pos = DataPoints[i].refer_to.begin();
				c_cls1 = DataPoints[i].act_class;
				double dia = 0.00;
				double avg = 0.00;
				double minimeter = 10000000.0;
				double range = 0.00;
				vector<double> std_vector;
				double std = 0.00;
				double homogenity = 0.00;
				double inner_dis = 0.00;
				double tmp_dis = 0.00;
				double inner_avg = 0.0;
				double inner_tot = 0.0;
				bool found = false;

				while (pos != DataPoints[i].refer_to.end()) {

					found = false;
					pos2 = DataPoints[i].referred_by.begin();
					while (pos2 != DataPoints[i].referred_by.end()
							&& found == false) {

						if (pos2->first == pos->second) {
							found = true;
							DataPoints[i].reference.push_back(pos->second);

							c_cls2 = DataPoints[pos->second].act_class;
							if (c_cls1 != c_cls2) {
								i_count++;
								diff = true;
							}
							std_vector.push_back(pos->first);
							if (dia < pos->first)
								dia = pos->first;
							if (minimeter > pos->first)
								minimeter = pos->first;
						}
						pos2++;
					}
					pos++;
				}

				if (std_vector.size() >= 2) {
					for (int v = 1; v < (int) std_vector.size(); v++) {
						tmp_dis = std_vector[v] - std_vector[v - 1];
						inner_tot += tmp_dis;
						if (inner_dis < tmp_dis)
							inner_dis = tmp_dis;
					}
				} else
					inner_dis = 100000;

				inner_avg = inner_tot / ((double) (std_vector.size() - 1));
				double inner_ratio = inner_dis / inner_avg;
				DataPoints[i].inner_ratio = inner_ratio;
				DataPoints[i].diameter = dia;
				avg = Stats::GetAverage(std_vector);
				DataPoints[i].average = avg;
				DataPoints[i].minimeter = minimeter;
				range = dia - minimeter;
				DataPoints[i].range = range;
				std = Stats::GetStdev(std_vector);
				DataPoints[i].std = std;
				DataPoints[i].inner_dis = inner_dis;
				;
				//homogenity =   avg ;
				// homogenity =  (1000.00 * (double) std_vector.size()) + (1.00 / inner_avg) ; // last used one
				// homogenity =    (double)DataPoints[i].reference.size() + ((double) DataPoints[i].refer_to.size() /  (double)DataPoints[i].referred_by.size())/ 10.0 ;
				//homogenity =  100.0 * (double) DataPoints[i].referred_by.size() + (1.00 / inner_avg) ;
				//homogenity =  1.0 / (100.0 * (double) DataPoints[i].referred_by.size() + (1.00 / inner_avg)) ;

				homogenity = 100 * (double) DataPoints[i].referred_by.size()
						+ (double) DataPoints[i].reference.size();
				// homogenity =  1.0 / (100 * (double) DataPoints[i].referred_by.size() + (double)DataPoints[i].reference.size()) ;
				//homogenity =  100 * (double) DataPoints[i].reference.size() + (double) DataPoints[i].referred_by.size();
				// homogenity = 1.0 / ( 100 * (double) DataPoints[i].reference.size() + (double) DataPoints[i].referred_by.size());
				DataPoints[i].homogenity = homogenity;

				std_vector.clear();
				if (diff == true) {
					i_diff++;
					DataPoint miss_point = DataPoints[i];
					ds.AddMissPoint(miss_point);
				}

			}

			//Compute_Overlap();
			//Compute_Correlation();
			//Compute_Intensity();

		}

		void DBSCAN::Compute_Correlation() {

			multiset<pair<double, int>, Cmp3>::iterator pos, pos3;
			multiset<pair<int, double>, Cmp4>::iterator pos2;
			multimap<int, int>::iterator pos4;
			int to_rank, by_rank;
			DataPoint *dp;

			for (int i = 0; i < dp_count; i++) {

				dp = &DataPoints[i];
				pos = DataPoints[i].refer_to.begin();
				to_rank = 0;

				while (pos != DataPoints[i].refer_to.end()) {
					to_rank++;
					pos2 = DataPoints[i].referred_by.begin();
					by_rank = 0;
					while (pos2 != DataPoints[i].referred_by.end()) {
						by_rank++;
						if (pos->second == pos2->first) {
							DataPoints[i].correlation.insert(
									make_pair(to_rank, by_rank));
							goto get_out_loop;

						}
						pos2++;
					}
					get_out_loop:

					pos++;
				} // end outer while
			} // end for

			vector<double> cor1, cor2;
			for (int i = 0; i < dp_count; i++) {
				cor1.clear();
				cor2.clear();
				dp = &DataPoints[i];
				pos4 = DataPoints[i].correlation.begin();

				DataPoints[i].intact = true;
				int it = 0;
				while (pos4 != DataPoints[i].correlation.end()) {
					cor1.push_back(pos4->first);
					cor2.push_back(pos4->second);
					if (pos4->first != pos4->second)
						it++;
					if (it == 2)
						DataPoints[i].intact = false;

					pos4++;
				}
				double cor = Stats::GetCorrelation(cor1, cor2);
				dp->ref_correlation = cor;

			}

		}

//This is our default constructor which is simply going to initialize all the member variables.
		DataPoint::DataPoint(vector<double> dim)

		{

			if (!ValidateIt || Two_D) // we want to print it
					{
				D = dim; // php maa // for cham only
			}

		}

//This function is going to calculate the distance between two DataPoints.
		double DataPoint::Compute_Distance(DataPoint& dp, int T) {
			double _d = 0.0;
			double sum = 0.0;
			double sq = 0.0;

			switch (T) {
			case 1:
				;
				if (this != &dp)

				{
					for (int n = 0; n < _num_dimentional; n++) {
						sq = (this->D[n] - dp.D[n]) * (this->D[n] - dp.D[n]);
						sum += sq;
					}

					return sqrt(sum);
				} else
					return numeric_limits<float>::infinity();

			case 2:
				;

				if (this != &dp) {
					_d = Stats::GetCorrelation(this->D, dp.D);

					if (_d >= 1) {
						return 0;
					} else
						return sqrt(1 - _d);

				} else
					return numeric_limits<float>::infinity();

			case 3:
				;

				if (this != &dp) {
					_d = Stats::GetCosine(this->D, dp.D);

					if (_d >= 1) {
						return 0;
					} else
						return (1 - _d);
				} else
					return numeric_limits<float>::infinity();

			}

		}

//This is the default constructor for our DBSAN class.
		DBSCAN::DBSCAN() {
			//DataPoints.reserve(1280);
		}

//This function is going to add a datapoint to the list.
		void DBSCAN::AddDataPoint(DataPoint dp, int _act_class) {
			//dp.act_class = _act_class ;
			DataPoints.push_back(dp);
		}

		void DBSCAN::AddMissPoint(DataPoint dp) {
			Miss_Points.push_back(dp);
		}

		void DBSCAN::Prepare_DataPoints() {
			dp_count = DataPoints.size();
			multimap<double, int> dis;
			multimap<double, int>::iterator pos;
			DataPoint *dp;

			// initialize datapoints to its default values
			Init_DataPoints();

			for (int i = 0; i < dp_count; i++) {

				//printf("dis %d \n", i);
				int k = 0;
				dp = &(DataPoints[i]);
				dis.clear();
				dis = Compute_Distance(*dp);

				pos = dis.begin();

				do {

					dp->refer_to.insert(make_pair(pos->first, pos->second));
					DataPoints[pos->second].referred_by.insert(
							make_pair(i, pos->first));
					pos++;
					k++;

				} while (k < k_nearst);

			} // end outer loop

			Compute_Links();

		}

		multimap<double, int> dis;
		ifstream Records;
//This is going to create our DBSCAn table containing n sorted lists for each DataPoint.
		void DBSCAN::Load_DataPoints(const char* _file) {

			dp_count = DataPoints.size();
//	multimap<double,int> dis ;
			multimap<double, int>::iterator pos, pos2;
//        DataPoint *dp;
			double _dis;
			int _point;

			_num_dimentional = num_dimentional;

			ifstream Records(_file);

			// initialize datapoints to its default values
			Init_DataPoints();
			int c_cls = 1;

			for (int i = 0; i < dp_count; i++) {

				//printf("dis %d \n", i);
				int k = 0;

//		dp= &(DataPoints[i]);
				dis.clear();

				while (k < k_nearst) {
					Records >> _dis >> _point;
					DataPoints[i].refer_to.insert(make_pair(_dis, _point));
					DataPoints[_point].referred_by.insert(make_pair(i, _dis));

					k++;
				}

				// now skip the rest of the 50 k-nearset neibours measured earlier in our file

				while (k < dim_num) {
					Records >> _dis >> _point;
					k++;
				}

				if (i == basic_guide[c_cls - 1]) {
					c_cls++;
				}
				DataPoints[i].act_class = c_cls;

			} // end outer loop

//        free(Records) ;
			Records.close();
			Compute_Links();
			//Compute_Corellation();
			//Find_Noise();
		}

		void DBSCAN::Mark_DensePoints(const char* _file) {

			dp_count = DataPoints.size();
//	multimap<double,int> dis ;

//        DataPoint *dp;
			double _dis;
			int _point;

			_num_dimentional = num_dimentional;

			ifstream Records(_file);

			// initialize datapoints to its default values
			Init_DataPoints();

			for (int i = 0; i < dp_count; i++) {

				//printf("dis %d \n", i);
				int k = 0;
//		dp= &(DataPoints[i]);
				dis.clear();

				while (k < 1) {
					Records >> _dis >> _point;
					DataPoints[i].refer_to.insert(make_pair(_dis, _point));
					DataPoints[_point].referred_by.insert(make_pair(i, _dis));
					k++;
				}

				// now skip the rest of the 50 k-nearset neibours measured earlier in our file

				while (k < dim_num) {
					Records >> _dis >> _point;
					k++;
				}

			} // end outer loop

//        free(Records) ;
			Records.close();
			//Find_Noise();
		}

		vector<vector<double> > dis_matrix;
//This is going to create our DBSCAn table containing n sorted lists for each DataPoint.
		void DBSCAN::Load_DisMatrix(const char* _file) {

			dp_count = DataPoints.size();
			//vector<vector<double>>::iterator pos , pos2 ;
//        DataPoint *dp;
			double _dis;

			_num_dimentional = num_dimentional;

			ifstream Records(_file);

			dis_matrix.resize(dp_count); // HEIGHT
			for (int i = 0; i < dp_count; ++i)
				dis_matrix[i].resize(dp_count); // WIDTH

			for (int i = 0; i < dp_count; i++) //237
					{
				//printf("%d \n", i) ;
				for (int j = 0; j < dp_count; j++) {
					Records >> _dis;
					dis_matrix[i][j] = _dis;

				}

			} // end outer loop

//        free(Records) ;
			Records.close();

		}

		double DataPoint::Compute_AllDistance(DataPoint& dp, int T) {
			double _d = 0.0;
			double sum = 0.0;
			double sq = 0.0;

			switch (T) {
			case 1:
				;
				if (this != &dp)

				{
					for (int n = 0; n < _num_dimentional; n++) {
						sq = (this->D[n] - dp.D[n]) * (this->D[n] - dp.D[n]);
						sum += sq;
					}

					return sqrt(sum);
				} else
					return 0.0;

			case 2:
				;

				if (this != &dp) {
					_d = Stats::GetCorrelation(this->D, dp.D);

					if (_d >= 1) {
						return 0;
					} else
						return sqrt(1 - _d);

				} else
					return 0.0;

			case 3:
				;

				if (this != &dp) {
					_d = Stats::GetCosine(this->D, dp.D);

					if (_d >= 1) {
						return 0;
					} else
						return (1 - _d);
				} else
					return 0.0;

			}

		}

		vector<double> DBSCAN::Compute_AllDistance(DataPoint& dp) {
			vector<double> dis;
			double _dis = 0;

			for (int i = 0; i < dp_count; i++) {

				_dis = dp.Compute_AllDistance(DataPoints[i], dis_type);
				dis.push_back(_dis);

			}

			return dis;

		}

		void DBSCAN::Save_DataPoints(const char* _file) {
			dp_count = DataPoints.size();
			multimap<double, int> dis;
			multimap<double, int>::iterator pos;
			DataPoint *dp;
			ofstream myfile;
			myfile.open(_file);

			// initialize datapoints to its default values
			Init_DataPoints();
			k_nearst = dim_num;
			_num_dimentional = num_dimentional;

			for (int i = 0; i < dp_count; i++) {

				printf("dist %d \n", i);
				int k = 0;
				dp = &(DataPoints[i]);
				dis.clear();

				dis = Compute_Distance(*dp);
				pos = dis.begin();
				myfile << pos->first << "\t" << pos->second << "\t";
				do {
					pos++;
					k++;
					myfile << pos->first << "\t" << pos->second;
					if (k == k_nearst - 1)
						myfile << "\n";
					else
						myfile << "\t";
				} while (k < k_nearst - 1);

			} // end outer loop
			myfile.close();
		}

		void DBSCAN::Save_DisMatrix(const char* _file) {
			dp_count = DataPoints.size();
			vector<double> dis;
			vector<double>::iterator pos;
			DataPoint *dp;
			ofstream myfile;
			myfile.open(_file);

			// initialize datapoints to its default values
			Init_DataPoints();
			_num_dimentional = num_dimentional;

			for (int i = 0; i < dp_count; i++) {

				printf("dist %d \n", i);
				int k = 0;
				dp = &(DataPoints[i]);
				dis.clear();

				dis = Compute_AllDistance(*dp);
				pos = dis.begin();

				myfile << *pos << "\t";
				do {
					pos++;
					k++;
					myfile << *pos;
					if (k == dp_count - 1) {
						myfile << "\n";
					} else
						myfile << "\t";
				} while (k < dp_count - 1);

			} // end outer loop
			myfile.close();
		}

// this function will compute distance for a datapoint and select the most close ones
		multimap<double, int> DBSCAN::Compute_Distance(DataPoint& dp) {
			multimap<double, int> dis;
			double _dis = 0;

			for (int i = 0; i < dp_count; i++) {
				if (dp.point_id != i) {
					_dis = dp.Compute_Distance(DataPoints[i], dis_type);
					dis.insert(make_pair(_dis, i));
				}
			}

			return dis;

		}

// This function is going to initialize all datapoints with its default vlaues.

		void DBSCAN::Init_DataPoints() {

//	DataPoint *dp;
			for (int i = 0; i < dp_count; i++) {
				//dp = &DataPoints[i] ;
				DataPoints[i].class_id = 0;
				DataPoints[i].is_noise = 0;
				//DataPoints[i].is_isolaed = 0 ;
				//DataPoints[i].is_dense = 0 ;
				DataPoints[i].point_id = i;
				DataPoints[i].refer_to.clear();
				DataPoints[i].referred_by.clear();
				DataPoints[i].reference.clear();
				DataPoints[i].visited = false;
				DataPoints[i].visit_count = 0;
				DataPoints[i].strength = 0;
				DataPoints[i].homogenity = 0.0;
				DataPoints[i].diameter = 0.0;
				DataPoints[i].minimeter = 0.0;
				DataPoints[i].range = 0.0;
				DataPoints[i].average = 0.0;
				DataPoints[i].std = 0.0;
				DataPoints[i].ref_std = 0.0;
				DataPoints[i].ref_range = 0.0;
				DataPoints[i].inner_dis = 0.0;
				DataPoints[i].inner_ratio = 0.0;
				DataPoints[i].ref_range = 0.0;
				DataPoints[i].ref_correlation = 0.0;
				DataPoints[i].ref_count = 0.0;
				DataPoints[i].act_class = 0;

			}
		}

		void DBSCAN::Semi_Init_DataPoints() {

//	DataPoint *dp;
			for (int i = 0; i < dp_count; i++) {
				//  	dp = &DataPoints[i] ;
				DataPoints[i].class_id = 0;
				DataPoints[i].is_noise = 0;
				DataPoints[i].is_dense = 0;
				DataPoints[i].is_isolated = 0;
				DataPoints[i].point_id = i;
				//dp->refer_to.clear() ;
				//dp->referred_by.clear() ;
				//dp->reference.clear() ;
				DataPoints[i].visited = false;
			}
		}

// this function will generate differnt pattern colors to use when plotting with matlab 
		string Print_Pattern(int i) {
			i = i * 2;

			string my_color[7] = { "r", "g", "b", "c", "m", "y", "k" }; // w for white
			string pattern[13] = { ".", "o", "x", "+", "*", "s", "d", "v", ">",
					"<", "^", "p", "h" };

			return my_color[i % 7].append(pattern[i % 13]);

		}

//This function is going to print the data points in each cluster
		vector<pair<int, int> > unique_class;
		map<int, int>::iterator _max_weight;
		vector<int> cls;
		vector<map<int, int> > weight;

		void DBSCAN::Print_Clusters() {
			map<int, int> final_classes;
			ofstream Output;
			stringstream ss ;
			ss <<  "output" << itration_to_stop_at << ".m" ;
			string 	file_output = ss.str() ;	
			const char* File_Output = file_output.c_str();
			Output.open("Output.m");
			string _color, pattern;
			vector<DataPoint>::iterator itr;
			multiset<pair<int, int>, Cmp5>::iterator itr3, itr4;
			vector<int>::iterator itr2;
			int old_cluster;
			int y = 0;
			map<int, int>::iterator _pos1;
			vector<pair<int, int> >::iterator _pos2;
			int _step = 0;
			float tp = 0.0f;
			double FC = 0.0;
			bool _found = false;
			const char* st1_c = st1.c_str();

			ofstream Solution;
			//string file_solution = "Solution_" + file_name + ".txt" ;
			string file_solution = "solution.txt";
			const char* File_Solution = file_solution.c_str();
			remove(File_Solution);
			Solution.open(File_Solution);

			Set_Guide(ds.file_name);

			weight.clear();
			weight.resize(step_count);
			cls.clear();
			unique_class.clear();
			unique_class.resize(ds.step_count);
			string str_filename = "Para_Set_";
			if (dis_type == 1)
				str_filename += file_name + "_euc.txt";
			else if (dis_type == 2)
				str_filename += file_name + "_cor.txt";
			else if (dis_type == 3)
				str_filename += file_name + "_cos.txt";
			const char* _filename = str_filename.c_str();

			int io = 0;
			itr = DataPoints.begin();
			Print_Points.clear();
			while (itr != DataPoints.end()) {
				Print_Points.insert(make_pair(itr->class_id, itr->point_id));
				itr++;
				io++;
			}

			int n_cls = 1; // number of generated clusters
			int _cls = 0;

			itr3 = Print_Points.begin();
			_cls = itr3->first;
			int pts_in_cls = 0;
			int real_cls = 1;

			while (itr3 != Print_Points.end()) {

				pts_in_cls++;
				if (_cls != itr3->first) {
					n_cls++;
					_cls = itr3->first;
					if (pts_in_cls > (dp_count / 100))
						real_cls++;
					pts_in_cls = 0;
				}

				DataPoints[itr3->second].class_id = n_cls;
				itr3++;
			}

			//if(!ValidateIt)
			//{
			//goto donotvalidate;
			// }

			int c = 1;
			int i = 1;

			itr = DataPoints.begin();
			while (itr != DataPoints.end()) {
				//itr->act_class = n ;
				Solution << c << "\t" << itr->class_id << endl;
				if (i == basic_guide[c - 1]) {
					c++;
				}

				i++;
				itr++;
			}
			Solution.close();

			Out.open(st1_c, ios_base::app);
			//Out<<k_nearst<<"\t"<<strength_multiple<<"\t"<<tot_kernalpoints<<"\t"<<n<<"\t"<<TP<<"\t";
			Out << k_nearst << "\t" << tot_Noises <<"\t"<< n_cls <<"\t" << real_cls << "\t" << itration_to_stop_at << "\t" << strong_points << "\t" << weak_points_phase1 << "\t" << weak_points_phase2 << "\t" << time_exec << "\t" ;
			Out.close();

			if (1 >= 1)  // maa phd new //&& n < ds.step_count * 10
					{
				string st2 = "java -jar VM.jar ho_" + file_name + ".txt";
				const char* st2_c = st2.c_str();
				system(st2_c);

			} else {
				Out.open(st1_c, ios_base::app);
				Out << "\n";
				Out.close();
			}

			char buff[20];
			FILE *f = fopen("tmp_val.txt", "r");
			fgets(buff, 20, f);
			fclose(f);
			double TP = atof(buff);

			if (TP_BEST < TP)
				TP_BEST = TP;

			//printf("%s %d  %d %d %d %d %f\n" ,file_name.c_str() , ds.k_nearst ,  strength_multiple, tot_kernalpoints, n , TP , (double)TP_BEST/(double) basic_guide[ds.step_count-1]* 100.0 );
			printf("%s %d %d %d %d %d %d %d %d %5.2f %5.2f\n", file_name.c_str(),
					ds.k_nearst, tot_Noises, n_cls , real_cls, itration_to_stop_at, strong_points, weak_points_phase1, weak_points_phase2, TP * 100.0,
					TP_BEST * 100.0);

            Out.clear();
//donotvalidate:

			if (printIt == true)
				ValidateIt = false;
			// do not print
			if (!ValidateIt) // do not print in case any data set rather cham 1-4
			{
				int x = 0;
				if (Output.is_open()) {

					itr3 = Print_Points.begin();
					itr4 = Print_Points.begin();
					while (itr3 != Print_Points.end()) {
						cls.clear();
						old_cluster = itr3->first;
						while (itr3 != Print_Points.end()
								&& itr4->first == old_cluster) {

							cls.push_back(itr4->second);
							itr3++;
							itr4++;
						}

						if (cls.size() >= 1) {
							x++;
							Output << "c" << x << "=[" << endl;
							itr2 = cls.begin();
							while (itr2 != cls.end())

							{
								if (num_dimentional == 2)
									Output << DataPoints[(*itr2)].D[0] << " "
											<< DataPoints[(*itr2)].D[1] << endl;
								else
									Output << x << " "
											<< DataPoints[(*itr2)].point_id + 1
											<< endl;

								itr2++;
							}

							Output << "];" << endl;
							Output << "x = c" << x << "(:,1);" << endl;
							Output << "y = c" << x << "(:,2);" << endl;
							_color = Print_Pattern(x);
							pattern = "plot (x,y,'" + _color + "');";
							Output << pattern << endl;
							Output << "hold on" << endl;
						}
					}

					Output.close();
					Output.clear();

					//Beep(768,500);

				} else {
					cout << "Could not open Output.txt" << endl;
				}

			}

		}

		void DBSCAN::Swap_2Sets(int a, int b) {

			set<int>::iterator pos;

			pos = weight_class[a].begin();

			while (pos != weight_class[a].end()) {

				if (weight_class[b].find(*pos) == weight_class[b].end()) {
					weight_class[b].insert(*pos);
				}
				pos++;
			}

			weight_class[a].clear();

		}

		void DBSCAN::Output_Classes() {
			weightno_stream.str("");
			weightno_str = "";
			int cls = 0;
			Set_Guide(FILE_NAME);
			for (int i = 1; i <= ds.records_num; i++) {
				weightno_stream << cls << "\n";
				weightno_str += weightno_stream.str();
				if (i >= basic_guide[cls])
					cls++;
				weightno_stream.str("");

			}
			remove("myClassws.txt");
			Out.open("myClasses.txt", ios_base::app);
			Out << weightno_str;
			Out.close();
		}

		void DBSCAN::Set_Guide(string file_name) {
			int s;

			if (file_name.substr(0, 4) == "iris") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = iris_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = iris_count[s];
			} else if (file_name.substr(0, 4) == "time") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = time_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = time_count[s];
			} else if (file_name == "letters") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = letters_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = letters_count[s];
			}

			else if (file_name == "ecoli") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = ecoli_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = ecoli_count[s];
			} else if (file_name.substr(0, 5) == "chars") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = chars_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = chars_count[s];
			} else if (file_name.substr(0, 6) == "digits") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = digits_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = digits_count[s];
			} else if (file_name == "breast") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = breast_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = breast_count[s];
			} else if (file_name == "wdbc") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = wdbc_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = wdbc_count[s];
			} else if (file_name == "wpbc") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = wpbc_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = wpbc_count[s];
			} else if (file_name == "spect") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = spect_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = spect_count[s];
			}

			else if (file_name == "cardio3") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = cardio3_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = cardio3_count[s];
			} else if (file_name == "cardio10") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = cardio10_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = cardio10_count[s];
			} else if (file_name == "parkin") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = parkin_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = parkin_count[s];
			} else if (file_name == "robot2") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = robot2_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = robot2_count[s];
			} else if (file_name == "robot4") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = robot4_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = robot4_count[s];
			} else if (file_name == "robot24") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = robot24_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = robot24_count[s];
			} else if (file_name == "yeast") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = yeast_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = yeast_count[s];
			} else if (file_name.substr(0, 6) == "arcene") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = arcene_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = arcene_count[s];
			} else if (file_name.substr(0, 7) == "madelon") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = madelon_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = madelon_count[s];
			} else if (file_name.substr(0, 7) == "gisette") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = gisette_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = gisette_count[s];
			} else if (file_name.substr(0, 8) == "dorothea") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = dorothea_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = dorothea_count[s];
			}

			else if (file_name.substr(0, 5) == "corel") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = corel_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = corel_count[s];
			}

			else if (file_name == "glass") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = glass_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = glass_count[s];
			} else if (file_name == "move") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = move_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = move_count[s];
			} else if (file_name == "cham_01") {
				//goto skipprint;
			} else if (file_name == "cham_02") {
				//goto skipprint;
			} else if (file_name == "cham_03") {
				//goto skipprint;
			} else if (file_name == "cham_04") {
				//goto skipprint;
			} else if (file_name == "compound") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = compound_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = compound_count[s];
			} else if (file_name == "mnist" || file_name == "mnist2") {
				for (s = 0; s < ds.step_count; s++)
					basic_guide[s] = mnist_guide[s];
				for (s = 0; s < ds.step_count; s++)
					basic_count[s] = mnist_count[s];
			}

		}

		/****************************************************************
		 * Name    : parsingInput                                       *
		 * Function: parsing input command line                         *
		 * Input   : argc, argv                                         *
		 * Output  : void                                               *
		 ****************************************************************/
		int parsingInput(int argc, char *argv[]) {

			DBSCAN ds;

			if (argc == 5) {
				//sscanf_s(argv[2], "%s", ds.filename);
				//sscanf_s(argv[3], "%d", &ds.records_num);
				//sscanf_s(argv[1], "%d", &ds.k_nearst);
				//sscanf_s(argv[3], "%d", &ds.link_strength);
				return 1;
			} /* end if */
			else if (argc == 1) {
				printf("argument error \n");
				printf(" Usage of the program should be of the form: \n");
				printf(" Abbas fileName records_num k_nearst link_strength \n");
				filename = "data.txt";
				ds.records_num = 1000;
				ds.k_nearst = 10;
				ds.link_strength = 2;
				return 1;

			}/* end else */
			else {
				return -1;
			}
		}