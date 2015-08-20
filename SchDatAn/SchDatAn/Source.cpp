#include <iostream>
#include <string>


int _(){

	std::string s;
	std::cin >> s;
	bool l = 0, L = 0, N = 0;
	if (s.length() < 8) std::cout << "no" << std::endl;
	else{
		for (int i = 0; i < s.length(); i++){
			if (s[i] >= 'a' && s[i] <= 'z') l = 1;
			if (s[i] >= 'A' && s[i] <= 'Z') L = 1;
			if (s[i] >= '0' && s[i] <= '9') N = 1;
		}
		if (l*L*N) std::cout << "yes" << std::endl;
		else std::cout << "no" << std::endl;
	}

	
	return 0;
}