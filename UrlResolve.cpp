#include "UrlResolve.h"
#include <iostream>
using namespace std;

UrlResolve::UrlResolve()
{
	//set regular expressions!
	regular_expressions[SCHEME] = "^([a-zA-Z]+):(/{0,3})";
	regular_expressions[HOST]   = "^([0-9A-Za-z.-]+)";
	regular_expressions[PORT]   = "^(:([0-9]+))*";
	regular_expressions[PATH]   = "^([^#|\?|\n]+)?";
}

void UrlResolve::set_url(const string &url)
{
	this->m_url = url;
}

bool UrlResolve::url_resolve(url_st &url_resolve)
{
	string url_result;

	for(int i = MIN_URL_STRUCTURE; i < MAX_URL_STRUCTURE; i++)
	{
		if(url_resolve_step(m_url,url_result,regular_expressions[i]) == false)
		{
			cout << "url_resolve error!" << endl;
			return false;
		}
		url_resolve_result[i] = url_result;
	}
	url_resolve.scheme = url_resolve_result[SCHEME];
	url_resolve.host   = url_resolve_result[HOST];
	url_resolve.port   = url_resolve_result[PORT];
	url_resolve.path   = url_resolve_result[PATH];

	return true;
}
bool UrlResolve::url_resolve_step(string &url,string &url_result,const string &regular_expressions)
{
	int stauts;
	regex_t reg;
	regmatch_t regmatch;

	stauts =  regcomp(&reg, regular_expressions.c_str(), REG_EXTENDED);
	if(stauts != 0)
	{
		goto error;
	}

	stauts =  regexec(&reg, url.c_str(), 1, &regmatch, 0);
	if(stauts != 0)
	{
		goto error;
	}else
	{
		url_result = url.substr(regmatch.rm_so,regmatch.rm_eo-regmatch.rm_so);
		url = url.substr(regmatch.rm_eo);
		regfree(&reg);
		return true;
	}

error:
	cout << "url_resolve_step error!can't match!" << endl;
	regfree(&reg);
	return false;
}