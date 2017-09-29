#ifndef __EF_HTTP_SERVICE_H
#define __EF_HTTP_SERVICE_H

#include <string.h>

class EF_http_service
{
public:
	EF_http_service();
	~EF_http_service();
	
	bool set_url(const string url_addr);
	bool http_post();
private:
	string m_url_addr;
	string m_message;
	string m_head;
}


#endif