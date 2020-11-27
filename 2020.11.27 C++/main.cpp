#ifdef STDAFX_H
#include "stdafx.h"
#endif

#ifndef REMOVE_COMMENTS_H
#include "remove_comments.h"
#endif

#ifndef WRITE_STRING_LINE_H
#include "write_string_line.h"
#endif

int main(int argc, char** argv)
try
{
	remove_comments("input.txt", "output.txt");
	return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
	std::cout << "Exception occured: " << e.what() << ".\n";
	return EXIT_SUCCESS;
	// return EXIT_FAILURE;
}
catch (...)
{
	std::cout << "Unknown exception.\n";
	return EXIT_SUCCESS;
	// return EXIT_FAILURE;
}