#include "CSVRow.h"

CSVRow::~CSVRow()
{
}

CSVRow::CSVRow()
{
	debug = false;
}

void CSVRow::readNextRow(istream& str)
{
	//if (debug) { cout << "readNextRow called" << endl; }
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
	//if (debug) { cout << "size gotten" << endl; }
	return m_data.size();
}

string const& CSVRow::operator[](size_t index) const
{ 
	//if (debug) { cout << "operator[] called" << endl; }
	return m_data[index];
}

istream& operator>>(istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}