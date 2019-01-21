#include "CSVRow.h"

CSVRow::~CSVRow()
{
}

void CSVRow::readNextRow(istream& str)
{
	string line;
	getline(str, line);
	stringstream lineStream(line);
	string cell;
	m_data.clear();
	while (getline(lineStream, cell, ','))
	{
		m_data.push_back(cell);
		//cout << "Read: " << cell << endl;
	}
	// This checks for a trailing comma with no data after it
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element
		m_data.push_back("");
	}
}

size_t CSVRow::size() const 
{ 
	return m_data.size();
}

string const& CSVRow::operator[](size_t index) const
{ 
	return m_data[index];
}

//This function allows you to just do "file >> row" to read a
//row from a file and uses the CSVRow class to split it into a
//vector of strings
istream& operator>>(istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}