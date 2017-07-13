#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;




int main() {
	std::map< std::string,std::map<std::string,std::string> > map_data;
	std::map<std::string, std::string> data;
	
	std::string val1 = "foo";
	std::string val2 = "bar";
	std::string val3 = "baz";

	data.emplace(val2,val3);
	map_data.emplace(val1,data);
		
	std::map<std::string, std::string> data2;
	data2 = map_data.find(val1)->second;
	cout << "value = " << data2.find(val2)->second << endl;
	
	data.erase(val1);
	data2["crew"]="cruz";
	
	map_data[val1] = data2;
	
	data2.clear();

	data2 = map_data.find(val1)->second;
	cout << "value = " << data2.find("crew")->second << endl;
	cout << "value = " << data2.find("bar")->first << endl;

	data2.clear();
	
	data2["bug"] = "bugz";
	map_data["swarm"] = data2;

	data2.clear();

	data2 = map_data.find("swarm")->second;
	cout << "value = " << data2.find("bug")->second << endl;
	
	
	
	return 0;
}
