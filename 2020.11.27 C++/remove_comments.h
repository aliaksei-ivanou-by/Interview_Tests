#pragma once

#ifndef REMOVE_COMMENTS_H
#define REMOVE_COMMENTS_H

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#ifndef WRITE_STRING_LINE_H
#include "write_string_line.h"
#endif

//#define DEBUG

int remove_comments(const std::string&& fileNameFrom, std::string&& fileNameTo, bool help = true)
try
{
	unsigned int numberOfComments = 0;
	std::ifstream inputFileStream(fileNameFrom.c_str());
	if (!inputFileStream)
	{
		std::cout << "Can't open file " << fileNameFrom << '\n';
		return 1;
	}
	std::ofstream outputFileStream(fileNameTo.c_str());
	if (!outputFileStream)
	{
		std::cout << "Can't create file " << fileNameTo << '\n';
		return 2;
	}
	std::string stringLine;
	char ch;
	while (inputFileStream.get(ch))
	{
		if (ch != '/')
		{
			stringLine += ch;
			if (ch == '\n')
			{
#ifdef DEBUG
				std::cout << stringLine << '\n';
#endif // DEBUG
				write_string_line(outputFileStream, stringLine);
			}
			continue;
		}
		if (!inputFileStream.get(ch))
		{
			break;
		}
		switch (ch)
		{
		case '/':
			{
				auto comment1 = [&inputFileStream]()
				{
					char ch;
					while (inputFileStream.get(ch))
					{
						if (ch == '\n')
						{
							return;
						}
					}
				};
				comment1();
				++numberOfComments;
				stringLine += '\n';
#ifdef DEBUG
				std::cout << stringLine << '\n';
#endif // DEBUG
				write_string_line(outputFileStream, stringLine);
				break;
			}
		case '*':
			{
				auto comment2 = [&inputFileStream]()
				{
					char ch;
					while (inputFileStream.get(ch))
					{
						if (ch == '*')
						{
							if (!inputFileStream.get(ch))
							{
								break;
							}
							if (ch == '/')
							{
								return;
							}
						}
					}
				};
				comment2();
				++numberOfComments;
				stringLine += ' ';
				break;
			}
		default:
			{
				stringLine += '/';
				stringLine += ch;
				break;
			}
		}
	}
#ifdef DEBUG
	std::cout << stringLine << '\n';
#endif // DEBUG
	write_string_line(outputFileStream, stringLine);
	inputFileStream.close();
	outputFileStream.close();
	if (help)
	{
		std::cout << "Comments in file " << fileNameFrom << " were deleted!\n";
		std::cout << "New file without comments is " << fileNameTo << ".\n";
		std::cout << "Number of comments is " << numberOfComments << ".\n";
	}
	return 0;
}
catch (...)
{
	std::cout << "Something went wrong!\n";
	return 3;
}

#endif