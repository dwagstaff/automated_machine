/*
 * Stats.h
 *
 *  Created on: Feb 11, 2015
 *      Author: davew
 */

#ifndef STATS_H_
#define STATS_H_

#include <vector>


class Stats {
private:
	std::vector<float> x;
	std::vector<float> y;

public:
	Stats();
	virtual ~Stats();

	void addPoint(float x, float y);
	float slope(void);
};

#endif /* STATS_H_ */
