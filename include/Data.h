#ifndef NEURAL_LOADDATA_H
#define NEURAL_LOADDATA_H

#include <vector>
#include <string>

	/**
	 * Load feature data and label data from .txt files and save them into std::vector
	 * Each instance in feature.txt should be in a line, which means different features should be in different column
	 * Multi-class classification is allowed, and the different label in label.txt should be different number
	 * But in memory, different label is stored in different bit
	 * For example: class one(1000), class two(0100), class three(0010), class(0001) if totally have 4 different class
	 * Pre-process data if needed, including normalize train data and use the same parameters to normalize test data
	 */

namespace neural {
	/** 
	 * @Param:
	 * add : a reference of feature.txt's address
	 * feature : a reference of the vector to save the features
	 */
	int load_feature(std::string &add, std::vector< std::vector<double> > &feature);

	/** 
	 * @Param:
	 * add : a reference of label.txt's address
	 * label : a reference of the vector to save the labels
	 * num: number of classes
	 */
	int load_label(std::string &add, std::vector< std::vector<double> > &label, const std::vector<double>::size_type &num);

	/** 
	 * Normalize each kind of features to [0,1] in Train-Data
	 * Return the MEAN and the VARIANCE of each kind of features to normalize Test-Data
	 * @Param:
	 * feature : Train-Data need to normalize
	 */
	std::vector< std::vector<double> > normalize_trainFeature(std::vector< std::vector<double> > &feature);

	/**
	 * Normalize Test-Data using the same parameters in Train-Data
	 * @Param:
	 * feature: Test-Data need to normalize
	 * param: MEAN and VARIANCE which the return of neural::normalize_trainFeature
	 */
	void normalize_testFeature(std::vector< std::vector<double> > &feature, std::vector< std::vector<double> > &param);

	/**
	 * Find Max score in the result of classification
	 * Make Max to 1 and all other 0
	 * @Param:
	 * vec: Scores of classification result
	 */
	std::vector<double>::iterator find_max(std::vector<double>& vec);

	void predictedLabel(std::vector<double> &pre_label);
}

#endif // !NERUAL_LOADDATA_H