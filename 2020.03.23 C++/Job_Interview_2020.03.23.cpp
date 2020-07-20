#include <stdio.h>
#include <iostream>
#include "HTTP_parser_lib.h"

int main()
{
	char* request_raw =
			"GET /wiki/http HTTP/1.1\r\n"
            "Host: ru.wikipedia.org\r\n"
            "Connection: close\r\n"
            "Accept: text/html\r\n"
            "User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5\r\n"
            "\r\n"
			;
    struct Request* request = request_parse(request_raw);
    if (request)
    {
    	std::cout << "Method: " << request->method << '\n';
    	std::cout << "Request-URI: " << request->url << '\n';
    	std::cout << "HTTP-Version: " << request->version << '\n';
    	std::cout << "Headers:\n";
        struct Header* header;
        for (header = request->headers; header; header = header->next)
        {
        	std::cout << "\t\t" << header->name << ": " << header->value << "\n";
        }
    }
    request_clear(request);
    return 0;
}
