#include "stdafx.h"
#include "HttpFactory.h"
#include "CurlHttp.h"

CHttpFactory::CHttpFactory()
{
}


CHttpFactory::~CHttpFactory()
{
}

std::shared_ptr<CHttp> CHttpFactory::get()
{
	return instance;
}
void CHttpFactory::reset()
{
	instance = std::make_shared<CCurlHttp>();
}
void CHttpFactory::setInstance(std::shared_ptr<CHttp> newInstance)
{
	instance = newInstance;
}
