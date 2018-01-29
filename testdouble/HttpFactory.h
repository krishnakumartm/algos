#pragma once
#include "Http.h"
#include <memory>

class CHttpFactory
{
public:
	CHttpFactory();
	~CHttpFactory();
	std::shared_ptr<CHttp> get();
	void reset();
	void setInstance(std::shared_ptr<CHttp> newInstance);
private:
	std::shared_ptr<CHttp> instance;
};

