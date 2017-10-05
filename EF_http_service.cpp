#include "EF_http_service.h"
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include "UrlResolve.h"

EF_http_service::EF_http_service()
{
	socket_fd = -1;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		cout << "socket error!" << endl;
		return false;
	}
}

EF_http_service::~EF_http_service()
{
	close(socket_fd);
}

bool EF_http_service::set_url(const string &url_addr)
{
	url_st url_temp;
	UrlResolve urlresolve;
	urlresolve.set_url(url_addr);
	if(urlresolve.url_resolve(url_temp))
	{
		cout << "EF_http_service::set_url error!\n" << endl;
		return false;
	}
	m_url_host = url_temp.HOST;
	m_url_path = url_temp.PATH;

	m_request_line = "POST " + m_url_path + " HTTP/1.1\r\n";

	return true;
}

bool EF_http_service::add_request_head(string name, string value)
{
	m_request_head += name + ": " + value;
	return true;
}

bool EF_http_service::http_post()
{
	if(m_url_host.empty())
	{
		cout << "please set url!" << endl;
		return false;
	}
	
	struct hostent * hostaddr;
	hostaddr = gethostbyname(m_url_host);

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("203.195.192.24");
    serv_addr.sin_port = htons((short)80);

}