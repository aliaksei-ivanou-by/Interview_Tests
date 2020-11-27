#pragma once

#ifndef WRITE_STRING_LINE_H
#define WRITE_STRING_LINE_H

#ifndef STDAFX_H
#include "stdafx.h"
#endif

void write_string_line(std::ofstream& outputFileStream, std::string& stringLine)
{
	static bool previousLineIsEmpty = false;
	for (size_t i = 0; i < stringLine.length(); ++i)
	{
		if (!isspace(stringLine[i]))
		{
			previousLineIsEmpty = true;
			outputFileStream.write(stringLine.c_str(), stringLine.length());
			stringLine = "";
			return;
		}
	}
	if (!previousLineIsEmpty)
	{
		outputFileStream.put('\n');
		previousLineIsEmpty = true;
	}
	stringLine = "";
}

#endif