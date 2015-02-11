/*
 * Stats.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: davew
 */

#include "Stats.h"
#include <algorithm>
#include <iostream>
#include <numeric>

Stats::Stats() {
	// TODO Auto-generated constructor stub

}

Stats::~Stats() {
	// TODO: Auto-generated stub
}

void Stats::addPoint(float x, float y) {
	this->x.push_back(x);
	this->y.push_back(y);
}

float Stats::slope(void) {
    const auto n    = x.size();
    const auto s_x  = std::accumulate(x.begin(), x.end(), 0.0);
    const auto s_y  = std::accumulate(y.begin(), y.end(), 0.0);
    const auto s_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    const auto s_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    const auto a    = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
    return a;
}
