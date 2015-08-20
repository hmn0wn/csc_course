#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include <algorithm>

class point {
public:
	int x;
	int y;
	double len;
	point(int x_, int y_);

};

point::point(int x_, int y_) :x(x_), y(y_), len(std::sqrt(x*x + y*y)){};

bool special_sort_function(const point& left, const point& right){
	return (left.len < right.len);
}

int main(){

	int n;
	int x, y;
	std::vector<point> point_vec;
	//point *point_tmp;

	std::cin >> n;
	for (int i = 0; i < n; i++){
		std::cin >> x >> y;
		//point_tmp = new point(x, y);
		point_vec.push_back(*new point(x, y));
	}
		
	std::sort(point_vec.begin(), point_vec.end(), std::ptr_fun(special_sort_function));

	
	for (int i = 0; i < n; i++)
		std::cout << point_vec[i].x << ' ' << point_vec[i].y << std::endl;
	
	return 0;
}