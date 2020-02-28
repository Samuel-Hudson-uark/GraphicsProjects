#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <sstream>
using namespace std;

//constants
const int GRAPH_RANGE = 460;
const int GRAPH_START = 16;
const int THICCNESS = 6;

//Input: This function takes an int and the max range of that int
//Output: An int within the boundries of the graph [16, 476]
int ScaleInt(int oldValue, int max) {
	return ((oldValue*GRAPH_RANGE)/max) + GRAPH_START;
}

int main() {
	//User input
	cout << "Input data file name: ";
	string fileName, input;
	cin >> fileName;
	while (input != "Column" && input != "Point" && input != "Line" && input != "Area")
	{
		cout << "Which type of chart to create? (Column, Point, Line, Area): ";
		cin >> input;
	}
	
    //File reading
	std::list <int> list;
	std::list<int>::iterator it;
	int tempInt;
	stringstream ss; // this stringstream stores the commands to later be put into output.txt.
	ifstream file(fileName.c_str());
	if(file.is_open())
	{
		file >> tempInt;
		int max = tempInt;
		while(file.eof() == false)
		{
			list.push_back(tempInt);
			file >> tempInt;
			if(tempInt > max)
				max = tempInt;
		}
		file.close();
		ss << "draw_line 1 10 16 484 16\ndraw_line 1 10 62 484 62\ndraw_line 1 10 108 484 108\ndraw_line 1 10 154 484 154\ndraw_line 1 10 200 484 200\ndraw_line 1 10 246 484 246\ndraw_line 1 10 292 484 292\ndraw_line 1 10 338 484 338\ndraw_line 1 10 384 484 384\ndraw_line 1 10 430 484 430\ndraw_line 1 10 476 484 476\ndraw_line 1 16 10 16 484\ndraw_line 1 62 10 62 16\ndraw_line 1 108 10 108 16\ndraw_line 1 154 10 154 16\ndraw_line 1 200 10 200 16\ndraw_line 1 246 10 246 16\ndraw_line 1 292 10 292 16\ndraw_line 1 338 10 338 16\ndraw_line 1 384 10 384 16\ndraw_line 1 430 10 430 16\ndraw_line 1 476 10 476 16\nset_color 1.0 0.5 1.0";
        //add graph data to ss
		int i = GRAPH_START;
		int interval = GRAPH_RANGE/list.size();
		for(it = list.begin(); it != list.end(); it++) 
		{
			i = i + interval;
			if(input == "Column") //draw_polygon 4 x1 y1 x2 y2 x3 y3 x4 y4
			{
				ss << "\ndraw_polygon 4 "
				<< (i - 11) << " " << (ScaleInt(*it, max)) << " "
				<< (i + 11) << " " << (ScaleInt(*it, max)) << " "
				<< (i + 11) << " " << (GRAPH_START) << " "
				<< (i - 11) << " " << (GRAPH_START);
			}
			else if(input == "Point") //draw_point size x1 y1
			{
				ss << "\ndraw_point " << (THICCNESS) << " "
				<< (i) << " " << (ScaleInt(*it, max));
			}
			else if(input == "Line") //draw_line width x1 y1 x2 y2
			{
				if(it != list.begin()) {
					ss << "\ndraw_line " << (THICCNESS) << " "
					<< (i - interval) << " " << (ScaleInt(tempInt, max)) << " "
					<< (i) << " " << (ScaleInt(*it, max));
				}
				tempInt = *it;
			}
			else if(input == "Area") //draw_polygon 4 x1 y1 x2 y2 x3 y3 x4 y4
			{
				if(it != list.begin()) {
					ss << "\ndraw_polygon 4 "
					<< (i - interval) << " " << (GRAPH_START) << " "
					<< (i - interval) << " " << (ScaleInt(tempInt, max)) << " "
					<< (i) << " " << (ScaleInt(*it, max)) << " "
					<< (i) << " " << (GRAPH_START);
				}
				tempInt = *it;
			}
		}
	}
	else {cout << "unable to open file.";}
	
    //File output
	string s;
	string fileStr = "set_color 1.0 1.0 1.0";
	while(ss >> s) {
		if(s[0] >= 'a' && s[0] <= 'z')
			fileStr += "\n";
		fileStr += s + " ";
	}
	ofstream outFile("output.txt");
	if(outFile.is_open())
	{
		outFile << fileStr;
		outFile.close();
	}
	else {cout << "unable to open file.";}
	return 0;
}
