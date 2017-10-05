#ifndef __EF_HTTP_SERVICE_H
#define __EF_HTTP_SERVICE_H

#include <string.h>

class EF_http_service
{
public:
	EF_http_service();
	~EF_http_service();
	
	bool set_url(const string &url_addr);
	bool add_request_head(string name, string value);
	bool http_post();
private:
	int socket_fd;
	string m_message;
	string m_request_line;
	string m_request_head;
	string m_url_host;
	string m_url_path;
}


#endif