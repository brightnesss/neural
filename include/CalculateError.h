#ifndef NEURAL_CALCULATEERROR_H
#define NEURAL_CALCULATEERROR_H

#include <vector>

namespace neural {

	/**
	 * Calculate error rate in Test-Data and the index of Data which predict wrong
	 * @Param:
	 * truth: groundtruth label of Test-Data
	 * predict: predict label of Test-Data
	 * badNum: the index of wrongly predict Data
	 */
	double CalculateError(std::vector< std::vector<double> > &truth, std::vector< std::vector<double> > &predict, std::vector<unsigned int，double> &badNum);
}

#endif // !NEURAL_CALCULATEERROR_H