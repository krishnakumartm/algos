#include "stdafx.h"
#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include <memory>
#include "PlaceDescriptionService.h"
#include "HttpFactory.h"

class CHttpStub :public CHttp
{
public:
	CHttpStub();
	~CHttpStub();
	//virtual std::string get(const std::string& url) const override;
	MOCK_CONST_METHOD1(get, std::string(const std::string&));
	//virtual void initialize()
	MOCK_METHOD0(initialize, void(void));
private:
	void verify(const std::string& url) const;
};

CHttpStub::CHttpStub()
{
}

CHttpStub::~CHttpStub()
{
}

class APlaceDescriptionService:public testing::Test
{
public:
	APlaceDescriptionService();
	~APlaceDescriptionService();
	static const std::string ValidLattitude;
	static const std::string ValidLongitude;

	std::shared_ptr<CHttpStub> httpStub;
	std::shared_ptr<CHttpFactory> httpFactory;
	std::shared_ptr<PlaceDescriptionService> service;

	virtual void SetUp() override
	{
		httpFactory = std::make_shared<CHttpFactory>();
		service = std::make_shared<PlaceDescriptionService>(httpFactory);
	}

	void TearDown() override
	{
		httpFactory.reset();
		httpStub.reset();
	}
private:

};

APlaceDescriptionService::APlaceDescriptionService()
{
}

APlaceDescriptionService::~APlaceDescriptionService()
{
}

class APlaceDescriptionService_WithHttpMock:public APlaceDescriptionService
{
public:
	APlaceDescriptionService_WithHttpMock();
	~APlaceDescriptionService_WithHttpMock();
	virtual void SetUp() override
	{
		httpStub = std::make_shared<CHttpStub>();
		httpFactory->setInstance(httpStub);
	}
private:

};

APlaceDescriptionService_WithHttpMock::APlaceDescriptionService_WithHttpMock()
{
}

APlaceDescriptionService_WithHttpMock::~APlaceDescriptionService_WithHttpMock()
{
}

const std::string APlaceDescriptionService::ValidLattitude("38.005");
const std::string APlaceDescriptionService::ValidLongitude("-104.44");

void CHttpStub::verify(const std::string& url) const
{
	std::string urlStart("http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");

	std::string expected(urlStart + "lat=" + APlaceDescriptionService::ValidLattitude + "&" +
		"lon=" + APlaceDescriptionService::ValidLongitude);
	ASSERT_THAT(url, testing::EndsWith(expected));
}


class CPlacementDescriptionService_StubHttpService: public PlaceDescriptionService
{
public:
	CPlacementDescriptionService_StubHttpService(std::shared_ptr<CHttpStub> http);
	~CPlacementDescriptionService_StubHttpService();
protected:
	virtual std::shared_ptr<CHttp> httpService() const override;
private:
	std::shared_ptr<CHttp> _http;
	std::shared_ptr<CHttpFactory> _httpFactory;
};

CPlacementDescriptionService_StubHttpService::CPlacementDescriptionService_StubHttpService(std::shared_ptr<CHttpStub> http) :
	_http(http), PlaceDescriptionService(std::make_shared<CHttpFactory>())
{
}

CPlacementDescriptionService_StubHttpService::~CPlacementDescriptionService_StubHttpService()
{
}

std::shared_ptr<CHttp> CPlacementDescriptionService_StubHttpService::httpService() const
{
	return _http;
}

//TEST_F(APlaceDescriptionService, ReturnDescriptionForValidLocation)
//{
//	CHttpStub httpStub;
//	
//	PlaceDescriptionService service{ &httpStub };
//
//	auto description = service.summaryDescription(ValidLattitude, ValidLongitude);
//	ASSERT_THAT(description, testing::Eq(R"({ "address": {
 //	
 //        "road":"Drury Ln",
 //	
 //        "city":"Fountain",
 //	
 //        "state":"CO",
 //	
 //        "country":"US" }})"));
//}

TEST_F(APlaceDescriptionService, MakeHttpRequestToObtainAddress)
{
	std::shared_ptr<CHttpStub> httpStub = std::make_shared<CHttpStub>();
	std::string urlStart{ "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&" };
	auto expectedUrl = urlStart + "lat=" + ValidLattitude + "&" + "lon=" + ValidLongitude;
	EXPECT_CALL(*httpStub, initialize());
	EXPECT_CALL(*httpStub, get(expectedUrl));

	CPlacementDescriptionService_StubHttpService service{ httpStub };
	service.summaryDescription(ValidLattitude, ValidLongitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription)
{
	CHttpStub httpStub;
	EXPECT_CALL(httpStub, get(testing::_)).WillOnce(testing::Return(R"({ "address": {
 	
         "road":"Drury Ln",
 	
         "city":"Fountain",
 	
         "state":"CO",
 	
         "country":"US" }})"));

	PlaceDescriptionService service{ httpFactory };
	auto description = service.summaryDescription(ValidLattitude, ValidLongitude);
	ASSERT_THAT(description, testing::Eq(R"({ "address": {
 	
         "road":"Drury Ln",
 	
         "city":"Fountain",
 	
         "state":"CO",
 	
         "country":"US" }})"));
}