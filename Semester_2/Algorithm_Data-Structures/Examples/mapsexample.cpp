#include <map>
#include <iostream>
#include <cstring>

using namespace std;

class LessThanStr {
public:
	bool operator()(const char* s1, const char* s2) const
	{
		return (strcmp(s1, s2) < 0);
	}
};

int main()
{
	map<const char*, int, LessThanStr> months;
  
	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;
	
	cout << "june -> " << months["june"] << endl;
	
	map<const char*, int, LessThanStr>::iterator cur = months.find("june");
	map<const char*, int, LessThanStr>::iterator prev = cur;
	map<const char*, int, LessThanStr>::iterator next = cur;

	++next;
	--prev;
	cout << "Previous (in alphabetical order) is " << (*prev).first << endl;
	cout << "Next (in alphabetical order) is " << (*next).first << endl;
}
