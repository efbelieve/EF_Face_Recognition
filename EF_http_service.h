#ifndef __EF_HTTP_SERVICE_H
#define __EF_HTTP_SERVICE_H

#include <string>

class EF_http_service
{
public:
	EF_http_service();
	~EF_http_service();
	
	bool set_url(const std::string &url_addr);
	bool add_request_head(std::string name, std::string value);
	bool http_post();
private:
	int socket_fd;
	std::string m_message;
	std::string m_request_line;
	std::string m_request_head;
	std::string m_url_host;
	std::string m_url_path;
};


#endif