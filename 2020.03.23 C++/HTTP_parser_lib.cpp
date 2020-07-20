#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "HTTP_parser_lib.h"


struct Request* request_parse(const char *raw)
{
	// General
    struct Request* request = NULL;
    request = static_cast<Request*>(malloc(sizeof(struct Request)));
    if (!request)
    {
        return NULL;
    }
    memset(request, 0, sizeof(struct Request)); // заполнение памяти под размер структуры

    // Поиск HTTP_Method
    size_t meth_len = strcspn(raw, " "); // поиск до первого пробела
#ifdef DEBUG
    std::cout << "HTTP_Method - meth_len = " << meth_len << '\n';
#endif
    if (strncmp(raw, "CONNECT", strlen("CONNECT")) == 0) // проверка на равенство строк
    {
    	request->method = HTTP_Method::CONNECT;
    }
    else
    {
    	if (strncmp(raw, "GET", strlen("GET")) == 0) // проверка на равенство строк
    	{
    		request->method = HTTP_Method::GET;
    	}
    	else
    	{
    		if (strncmp(raw, "HEAD", strlen("HEAD")) == 0) // проверка на равенство строк
    		{
    			request->method = HTTP_Method::HEAD;
    		}
    		else
    		{
    			if (strncmp(raw, "POST", strlen("POST")) == 0) // проверка на равенство строк
    			{
    				request->method = HTTP_Method::POST;
    			}
    			else
    			{
    				request->method = HTTP_Method::PUT;
    			}
    		}
    	}
    }
    raw += meth_len + 1;

    // Поиск Request-URI
    size_t url_len = strcspn(raw, " "); // поиск до первого пробела
#ifdef DEBUG
    std::cout << "Request-URI - url_len = " << url_len << '\n';
#endif
    request->url = static_cast<char*>(malloc(url_len + 1));

    if (!request->url)
    {
        request_clear(request); // освобождение памяти
        return NULL;
    }
    memcpy(request->url, raw, url_len); // копирование из raw в url
    request->url[url_len] = '\0';
    raw += url_len + 1;

    // Поиск HTTP-Version
    size_t ver_len = strcspn(raw, "\r\n"); // поиск до \r\n
#ifdef DEBUG
    std::cout << "HTTP-Version - ver_len = " << ver_len << '\n';
#endif
    request->version = static_cast<char*>(malloc(ver_len + 1));
    if (!request->version)
    {
        request_clear(request); // освобождение памяти
        return NULL;
    }
    memcpy(request->version, raw, ver_len); // копирование из raw в version
    request->version[ver_len] = '\0';
    raw += ver_len + 2;

    // Header
    struct Header *header = NULL;
    struct Header *last = NULL;
    while (raw[0] != '\r' || raw[1] != '\n')
    {
        last = header;
        header = static_cast<Header*>(malloc(sizeof(Header)));
        if (!header)
        {
            request_clear(request); // освобождение памяти
            return NULL;
        }

        // name
        size_t name_len = strcspn(raw, ":"); // поиск до :
#ifdef DEBUG
        std::cout << "name - name_len = " << name_len << '\n';
#endif
        header->name = static_cast<char*>(malloc(name_len + 1));
        if (!header->name)
        {
            request_clear(request); // освобождение памяти
            return NULL;
        }
        memcpy(header->name, raw, name_len); // копирование из raw в name
        header->name[name_len] = '\0';
        raw += name_len + 1;
        while (*raw == ' ')
        {
            raw++;
        }

        // value
        size_t value_len = strcspn(raw, "\r\n"); // поиск до символа \r\n
#ifdef DEBUG
        std::cout << "value - value_len = " << value_len << '\n';
#endif
        header->value = static_cast<char*>(malloc(value_len + 1));
        if (!header->value)
        {
            request_clear(request); // освобождение памяти
            return NULL;
        }
        memcpy(header->value, raw, value_len); // копирование из raw в value
        header->value[value_len] = '\0';
        raw += value_len + 2;

        // next
        header->next = last;
    }
    request->headers = header;
    raw += 2;
    return request;
}

// Освобождение памяти
void header_clear(struct Header* header)
{
    if (header != nullptr)
    {
        free(header->name);
        free(header->value);
        header_clear(header->next);
        free(header);
    }
}

// Освобождение памяти
void request_clear(struct Request* request)
{
	free(request->url);
    free(request->version);
    header_clear(request->headers);
    free(request);
}

// Печать HTTP_Method
std::ostream& operator<<(std::ostream& out, const HTTP_Method& method)
{
	switch(method)
	{
	case HTTP_Method::GET:
		return (out << "GET");
	case HTTP_Method::POST:
		return (out << "POST");
	case HTTP_Method::CONNECT:
		return (out << "CONNECT");
	case HTTP_Method::PUT:
		return (out << "PUT");
	case HTTP_Method::HEAD:
		return (out << "HEAD");
	}
}
