#pragma once
#include "Include/FTPluginCore.h"
#include "Include/FTPluginQuoteInterface.h"
#include "Include/FTPluginTradeInterface.h"
#include "Protocol/ProtoDataStruct.h"
#include "JsonCpp/json.h"
#include "PluginBasicPrice.h"
#include "PluginGearPrice.h"
#include "PluginRTData.h"
#include "PluginKLData.h"
#include "PluginStockSub.h"
#include "PluginStockUnSub.h"
#include "PluginQueryStockSub.h"
#include "PluginTradeDate.h"
#include "PluginStockList.h"
#include "PluginBatchBasic.h"
#include "PluginTickerPrice.h"
#include "PluginSnapshot.h"
#include "PluginHistoryKL.h"
#include "PluginExRightInfo.h"
#include "PluginPushStockData.h"
#include "PluginPushBatchBasic.h"
#include "PluginPushGearPrice.h"
#include "PluginPushTickerPrice.h"
#include "PluginPushKLData.h"
#include "PluginPushRTData.h"

class CPluginNetwork;

enum QuoteServerType
{
	QuoteServer_BasicPrice = 1,
	QuoteServer_GearPrice = 2,
	QuoteServer_RTData = 3,
	QuoteServer_KLData = 4,
	QuoteServer_StockSub = 5,
	QuoteServer_StockUnSub = 6,
	QuoteServer_QueryStockSub = 7,
	QuoteServer_BatchBasic = 8,
	QuoteServer_TickerPrice = 9,
	QuoteServer_Snapshot = 10,
	QuoteServer_HistoryKL = 11,
	QuoteServer_ExRightInfo = 12,
	QuoteServer_PushStockData = 13,
	QuoteServer_PushBatchBasic = 14,
	QuoteServer_PushGearPrice = 15,
	QuoteServer_PushKLData = 16,
	QuoteServer_PushRTData = 17,
	QuoteServer_PushTickerPrice = 18,
};

class CPluginQuoteServer: 	
	public IQuoteInfoCallback,
	public IQuoteKLCallback
{
public:
	CPluginQuoteServer();
	virtual ~CPluginQuoteServer();
	
	void InitQuoteSvr(IFTPluginCore* pPluginCore, CPluginNetwork *pNetwork);
	void UninitQuoteSvr();	
	void SetQuoteReqData(int nCmdID, const Json::Value &jsnVal, SOCKET sock);
	void ReplyQuoteReq(int nCmdID, const char *pBuf, int nLen, SOCKET sock);

	StockSubErrCode SubscribeQuote(const std::string &strCode, StockMktType nMarketType,  StockSubType eStockSubType, bool bSubOrUnsub);
	QueryDataErrCode QueryStockRTData(DWORD* pCookie, const std::string &strCode, StockMktType nMarketType, QuoteServerType type);
	QueryDataErrCode QueryStockKLData(DWORD* pCookie, const std::string &strCode, StockMktType nMarketType, QuoteServerType type, int nKLType);
	void CloseSocket(SOCKET sock);
protected:
	//IQuoteInfoCallback
	virtual void  OnChanged_PriceBase(INT64  ddwStockHash); 
	virtual void  OnChanged_OrderQueue(INT64 ddwStockHash); 
	virtual void  OnChanged_RTData(INT64 ddwStockHash);
	virtual void  OnChanged_KLData(INT64 ddwStockHash, int nKLType);
	virtual void  OnReqStockSnapshot(DWORD dwCookie, PluginStockSnapshot *arSnapshot, int nSnapshotNum);

	virtual void  OnPushPriceBase(INT64 ddwStockHash, SOCKET sock);
	virtual void  OnPushGear(INT64 ddwStockHash, SOCKET sock);
	virtual void  OnPushTicker(INT64 ddwStockHash, SOCKET sock, INT64 nSequence);
	virtual void  OnPushKL(INT64  ddwStockHash, SOCKET sock, StockSubType eStockSubType, DWORD dwTime);
	virtual void  OnPushRT(INT64  ddwStockHash, SOCKET sock, DWORD dwTime);

	//IQuoteKLCallback
	virtual void  OnQueryStockRTData(DWORD dwCookie, int nCSResult);
	virtual void  OnQueryStockKLData(DWORD dwCookie, int nCSResult);

protected:
	IFTPluginCore		*m_pPluginCore;
	IFTQuoteData		*m_pQuoteData;
	IFTQuoteOperation	*m_pQuoteOp;
	IFTDataReport		*m_pDataReport;
	CPluginNetwork		*m_pNetwork;

	CPluginBasicPrice	m_BasicPrice;
	CPluginGearPrice	m_GearPrice;
	CPluginRTData		m_RTData;
	CPluginKLData		m_KLData;
	CPluginStockSub		m_StockSub;
	CPluginStockUnSub	m_StockUnSub;
	CPluginQueryStockSub m_QueryStockSub;
	CPluginTradeDate	m_TradeDate;
	CPluginStockList	m_StockList;
	CPluginBatchBasic   m_BatchBasic;
	CPluginTickerPrice  m_TickerPrice;
	CPluginSnapshot		m_Snapshot;
	CPluginHistoryKL	m_HistoryKL;
	CPluginExRightInfo  m_ExRightInfo;
	CPluginPushStockData m_PushStockData;
	CPluginPushBatchBasic m_PushBatchBasic;
	CPluginPushGearPrice m_PushGearPrice;
	CPluginPushTickerPrice m_PushTickerPrice;
	CPluginPushKLData	m_PushKLData;
	CPluginPushRTData	m_PushRTData;
};