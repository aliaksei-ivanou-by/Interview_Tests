#pragma once
#ifndef HTTP_PARSER_LIB_H_
#define HTTP_PARSER_LIB_H_

//#define DEBUG

enum HTTP_Method
{
	GET,
	POST,
	CONNECT,
	PUT,
	HEAD
};

std::ostream& operator<<(std::ostream& out, const HTTP_Method& method);

struct Header
{
    char* name;
    char* value;
    struct Header* next;
};

struct Request
{
    enum HTTP_Method method;
    char* url;
    char* version;
    struct Header* headers;
};

struct Request* request_parse(const char* raw);

void header_clear(struct Header* header);

void request_clear(struct Request* request);

#endif
