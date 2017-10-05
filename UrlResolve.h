#ifndef  __URLSOLVE_H
#define  __URLSOLVE_H
#include <string>
#include <sys/types.h>
#include <regex.h>

typedef enum 
{
	MIN_URL_STRUCTURE = 0,
	SCHEME = 0,
	HOST,
	PORT,
	PATH,
	MAX_URL_STRUCTURE,
}url_structure;

typedef struct 
{
	std::string scheme;
	std::string host;
	std::string port;
	std::string path;
}url_st;

class UrlResolve
{
public:
	UrlResolve();
	~UrlResolve() {};
	void set_url(const std::string &url);
	bool url_resolve(url_st &url_resolve);
private:
	bool url_resolve_step(std::string &url,std::string &url_result,const std::string &regular_expressions);
	std::string regular_expressions[MAX_URL_STRUCTURE];
	std::string url_resolve_result[MAX_URL_STRUCTURE];
	std::string m_url;
};
#endif