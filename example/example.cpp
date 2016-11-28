#include "Layer.h"
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "CalculateError.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace neural;

int main()
{
	string train_feature_add = "..\\data\\train_feature.txt";
	string train_label_add = "..\\data\\train_label.txt";
	vector< vector<double> > feature;
	vector< vector<double> > label;
	load_feature(train_feature_add, feature);
	load_label(train_label_add, label, 5);

	vector<int> hidden_layer;
	hidden_layer.push_back(8);
	Network nn(feature[0].size(),label[0].size(),hidden_layer);

	vector< vector<double> > param;
	param = neural::normalize_trainFeature(feature);

	size_t times = 0;
	vector<double>::size_type instanceNum = feature.size();
	while (times != 500)
	{
		for (vector<double>::size_type i = 0;i != instanceNum;++i)
		{
			nn.trainSingle(feature[i], label[i], 0.01);
		}
		cout << times++ << " ";
	}
	cout << endl;

	string test_feature_add = "..\\data\\test_feature.txt";
	string test_label_add = "..\\data\\test_label.txt";
	vector< vector<double> > test_feature;
	vector< vector<double> > test_label;
	load_feature(test_feature_add, test_feature);
	load_label(test_label_add, test_label, 5);

	neural::normalize_testFeature(test_feature, param);

	vector<double> pre_label;
	vector<double>::iterator iter;
	vector< vector<double> > preLabels;
	vector<double>::size_type testNum = test_feature.size();
	for (vector<double>::size_type i = 0;i != testNum;++i)
	{
		pre_label = nn.run(test_feature[i]);
		predictedLabel(pre_label);
		preLabels.push_back(pre_label);

		iter = pre_label.begin();
		while (iter != pre_label.end())
		{
			cout << *iter << " ";
			++iter;
		}
		cout << endl;
	}
	
	double error;
	map<unsigned int, double> bad_num;
	error = CalculateError(test_label, preLabels, bad_num);
	cout << "The Error is: " << error << endl;
	for (map<unsigned int,double>::const_iterator new_it = bad_num.begin();new_it != bad_num.end();++new_it)
	{
		cout << "Wrongly predicted data's index is : " << new_it->first << ", its predicted label is : " << new_it->second << endl;
	}
	cout << endl;
}