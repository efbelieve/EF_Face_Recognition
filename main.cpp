#include <iostream>
#include "UrlResolve.h"
using namespace std;

int main(int argc, char** argv)
{
	url_st test;
	UrlResolve haha;
	haha.set_url("https://api-cn.faceplusplus.com:8800/facepp/v3/detect");
	haha.url_resolve(test);
	cout << test.scheme << endl;
	cout << test.host << endl;
	cout << test.port << endl;
	cout << test.path << endl;

    return 0;
}
