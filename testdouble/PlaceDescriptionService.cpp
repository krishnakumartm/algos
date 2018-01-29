#include "stdafx.h"
#include "PlaceDescriptionService.h"
#include "CurlHttp.h"
PlaceDescriptionService::PlaceDescriptionService(std::shared_ptr<CHttpFactory> httpFactory):
	_httpFactory(httpFactory)
{
}

PlaceDescriptionService::~PlaceDescriptionService()
{
}

std::string PlaceDescriptionService::summaryDescription(const std::string & lattitude, const std::string & longitude)
{
	auto getRequestURL = createGetRequestURL(lattitude, longitude);
	return get(getRequestURL);
}

std::string PlaceDescriptionService::createGetRequestURL(const std::string & latitude, const std::string & longitude)
{
	std::string server("http://open.mapquestapi.com/");
	std::string document{ "nominatim/v1/reverse" };
	return server + document + "?" +
		keyValue("format", "json") + "&" +
		keyValue("lat", latitude) + "&" +
		keyValue("lon", longitude);
}

std::string PlaceDescriptionService::keyValue(const std::string & key, const std::string & value)
{
	return key + "=" + value;
}

std::string PlaceDescriptionService::get(const std::string & url)
{
	auto http = httpService();
	http->initialize();
	return http->get(url);
}

std::shared_ptr<CHttp> PlaceDescriptionService::httpService() const
{
	return std::make_shared<CCurlHttp>();
}
