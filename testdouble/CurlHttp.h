#pragma once
#include "Http.h"

class CCurlHttp: public CHttp
{
public:
	CCurlHttp();
	~CCurlHttp();
	virtual void initialize() override;
	virtual std::string get(const std::string& url) const override;
private:

};
