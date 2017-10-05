#include <iostream>
#include "UrlResolve.h"
#include "EF_http_service.h"
using namespace std;

int main(int argc, char** argv)
{
	EF_http_service http_service;
	http_service.set_url("https://api-cn.faceplusplus.com/facepp/v3/detect");
	http_service.http_post();

    return 0;
}
