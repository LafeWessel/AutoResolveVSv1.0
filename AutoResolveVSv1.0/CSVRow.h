#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
using namespace std;

//This class is setup to read a line from a CSV file, split
//the line by commas, and put each string into a vector of strings
class CSVRow
{
private:
	vector<string> m_data;
	bool debug;
public:
	~CSVRow();
	CSVRow();
	string const& operator[](size_t index) const;
	size_t size() const;
	void readNextRow(istream& str);
	//friend istream& operator>>(istream& str, CSVRow& data);

	void setDebug(bool debugI) { debug = debugI; };
};

istream& operator>>(istream& str, CSVRow& data);
