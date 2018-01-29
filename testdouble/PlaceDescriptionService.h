#pragma once
#include <iostream>
#include <memory>
#include "HttpFactory.h"

class PlaceDescriptionService
{
public:
	PlaceDescriptionService(std::shared_ptr<CHttpFactory> httpFactory);
	~PlaceDescriptionService();
	std::string summaryDescription(const std::string& lattitude, const std::string& longitude);
	std::string createGetRequestURL(const std::string& latitude, const std::string& longitude);
	std::string keyValue(const std::string& key, const std::string& value);
	std::string get(const std::string& url);
private:
	std::shared_ptr<CHttpFactory> _httpFactory;
protected:
	virtual std::shared_ptr<CHttp> httpService() const;
};

