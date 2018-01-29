#pragma once
#include <iostream>
class CHttp
{
public:
	CHttp();
	virtual ~CHttp();
	virtual void initialize() = 0;
	virtual std::string get(const std::string& url) const = 0;
private:

};
