#include "EF_http_service.h"
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>

EF_http_service::EF_http_service()
{
	m_url_addr = "";
	m_message  = "";

}

EF_http_service::~EF_http_service()
{

}

bool EF_http_service::set_url(const string url_addr)
{
	m_url_addr = url_addr;
}

bool EF_http_service::http_post()
{
	if(m_url_addr == "")
	{
		printf("please set url!\n");
		return FALSE;
	}
	
	m_head  = "POST "+m_url_addr+" HTTP/1.1\r\n";
	m_head += "Connection: Keep-Alive\r\n"

	int socket_fd = 0;
	struct sockaddr_in serv_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		printf("socket error!\n");
		return FALSE;
	}

	memset(&serv_addr, 0, sizeof(struct sockaddr_in));

}