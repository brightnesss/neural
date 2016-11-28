#include "Data.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace neural {
	int load_feature(std::string &filename, std::vector< std::vector<double> > &feature) {
		std::ifstream infile(filename.c_str(),std::ios_base::in);
		if (!infile.is_open()) {
			std::cerr << "error: unable to open input file: " << filename << std::endl;
			return -1;
		}
		std::string line;
		double num;
		while (std::getline(infile, line))
		{
			std::vector<double> nums;
			std::istringstream stream(line);
			while (stream >> num) {
				nums.push_back(num);
			}
			feature.push_back(nums);
		}
		infile.close();
		return 0;
	}

	int load_label(std::string &filename, std::vector< std::vector<double> > &label, const std::vector<double>::size_type &num) 
	{
		std::ifstream infile(filename.c_str(),std::ios_base::in);
		if (!infile.is_open()) {
			std::cerr << "error: unable to open input file: " << filename << std::endl;
			return -1;
		}
		std::string line;
		double lab;
		while (std::getline(infile, line))
		{
			std::vector<double> l(num, 0);
			std::istringstream stream(line);
			stream >> lab;
			l[--lab] = 1;
			label.push_back(l);
		}
		return 0;
	}

	 std::vector< std::vector<double> > normalize_trainFeature(std::vector< std::vector<double> > &feature)
	{
		std::vector<double>::size_type instance_num = feature.size();
		std::vector<double>::size_type feature_num = feature[0].size();
		std::vector< std::vector<double> > temp(feature_num);

		for (std::vector<double>::size_type ins = 0;ins != instance_num;++ins)
		{
			for (std::vector<double>::size_type fea = 0;fea != feature_num;++fea)
			{
				temp[fea].push_back(feature[ins][fea]);
			}
		} 

		double min, max;

		for (std::vector<double>::size_type fea = 0;fea != feature_num;++fea)
		{
			std::sort(temp[fea].begin(), temp[fea].end());
			min = *(temp[fea].begin());
			max = *(temp[fea].rbegin());
			temp[fea].clear();
			temp[fea].push_back(min);
			temp[fea].push_back(max);
		} 

		for (std::vector< std::vector<double> >::iterator iter = feature.begin();iter != feature.end();++iter)
		{
			for (std::vector<double>::size_type fea = 0;fea != feature_num;++fea)
			{
				(*iter)[fea] = ((*iter)[fea] - *(temp[fea].begin())) / (*(temp[fea].rbegin()) - *(temp[fea].begin()));
			}
		} 
		return temp;
	}

	 void normalize_testFeature(std::vector<std::vector<double>>& feature, std::vector<std::vector<double>>& para)
	 {
		 std::vector<double>::size_type feature_num = feature[0].size();

		 for (std::vector< std::vector<double> >::iterator iter = feature.begin();iter != feature.end();++iter)
		 {
			 for (std::vector<double>::size_type fea = 0;fea != feature_num;++fea)
			 {
				 (*iter)[fea] = ((*iter)[fea] - *(para[fea].begin())) / (*(para[fea].rbegin()) - *(para[fea].begin()));
			 }
		 } 
	 }

	 std::vector<double>::iterator find_max(std::vector<double>& vec)
	 {
		 std::vector<double>::iterator max, iter;
		 max = iter = vec.begin();
		 while (iter != vec.end())
		 {
			 if (*iter > *max) {
				 max = iter;
			 }
			 ++iter;
		 }
		 return max;
	 }

	 void predictedLabel(std::vector<double>& pre_label)
	 {
		 std::vector<double>::iterator it;
		 it = find_max(pre_label);
		 for (std::vector<double>::iterator my_it = pre_label.begin();my_it != pre_label.end();++my_it) {
			 if (it == my_it) {
				 *my_it = 1;
			 }
			 else *my_it = 0;
		 }
	 }

}