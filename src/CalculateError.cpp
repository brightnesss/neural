#include "CalculateError.h"
#include <iostream>

namespace neural {
	double CalculateError(std::vector<std::vector<double>> &truth_label, std::vector<std::vector<double>> &output_label, std::vector<unsigned int> &bad_number)
	{
		if (truth_label.size() != output_label.size())
		{
			std::cerr << "Error to have different number of instances between predicted label and groudtruth label";
			return -1;
		}

		std::vector<double>::size_type instanceNum = truth_label.size();
		std::vector<double>::size_type featureNum = truth_label[0].size();
		unsigned int badNum = 0;
		for (std::vector<double>::size_type ins = 0;ins != instanceNum;++ins)
		{
			unsigned int count = 0;
			for (std::vector<double>::size_type num = 0;num != featureNum;++num)
			{
				//通过位与运算判断预测类标是否与真值类标相同
				count += (unsigned int(truth_label[ins][num]) & unsigned int(output_label[ins][num]));
			}
			if (count == 1)
			{
				continue;
			}
			else
			{
				badNum = badNum + 1; //错误数+1
				bad_number.push_back(ins + 1); //将错误的样本号码输出
			}
		}
		double error = double(badNum) / double(instanceNum);
		return error;
	}
}