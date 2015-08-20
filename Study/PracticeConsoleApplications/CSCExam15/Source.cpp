#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <stack> 
#include <vector>
using namespace std;

struct point{
	int val;
	bool left;
	int seg;
};

bool special_sort_function(const point& left, const point& right){
	if (left.val == right.val) return (!left.left < !right.left);
	return (left.val < right.val);
}

int main(){
	ifstream in("input.ini");
	int n;
	point point_tmp;
	vector<point> point_vect;
	stack<int> seg_stack;
	in >> n;
	for (int i = 1; i < n+1; i++){
		in >> point_tmp.val;
		point_tmp.left = true;
		point_tmp.seg = i;
		point_vect.push_back(point_tmp);

		in >> point_tmp.val;
		point_tmp.left = false;
		point_tmp.seg = i;
		point_vect.push_back(point_tmp);
	}

	sort(point_vect.begin(), point_vect.end(), ptr_fun(special_sort_function));
	/*cout << "#########################################################" << endl;
	for (int i = 0; i < n * 2; i++){
		cout << "seg: " << point_vect[i].seg << endl;
		cout << "left: " << point_vect[i].left << endl;
		cout << "val: " << point_vect[i].val << endl << endl;
	}*/

	bool *covered = new bool[n+1];
	for (int i = 1; i < n + 1; i++)
		covered[i] = 0;

	vector<int> ans;
	

	for (int i = 0; i < 2 * n; i++){
		if (point_vect[i].left) seg_stack.push(point_vect[i].seg);
		else if (!covered[point_vect[i].seg]){ 
			//cout << point_vect[i].val << endl;
			ans.push_back(point_vect[i].val);
			
			while (!seg_stack.empty()){
				covered[seg_stack.top()] = true;
				seg_stack.pop();
			}
		}
	}

	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
	
	return 0;
}