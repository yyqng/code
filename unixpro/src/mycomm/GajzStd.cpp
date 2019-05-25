#include "GajzStd.h"


SINGLETON_CLASS_INIT(GajzStd)


GajzStd::GajzStd()
{
    Init();
}

GajzStd::~GajzStd()
{

}


void GajzStd::Init()
{
    BuildProductTable();

    return;
}


void GajzStd::BuildProductTable()
{
    m_productTable[PRODUCT_TEST] = PRODUCT_NAME_TEST;
    m_productTable[PRODUCT_XICIPROXY] = PRODUCT_NAME_XICIPROXY;
    m_productTable[PRODUCT_89PROXY] = PRODUCT_NAME_89PROXY;
    m_productTable[PRODUCT_KUAIPROXY] = PRODUCT_NAME_KUAIPROXY;
    m_productTable[PRODUCT_QQ] = PRODUCT_NAME_QQ;
    m_productTable[PRODUCT_VOXER] = PRODUCT_NAME_VOXER;
    m_productTable[PRODUCT_TAOBAO] = PRODUCT_NAME_TAOBAO;
    m_productTable[PRODUCT_JINGDONG] = PRODUCT_NAME_JINGDONG;
    m_productTable[PRODUCT_MEITUAN] = PRODUCT_NAME_MEITUAN;
    m_productTable[PRODUCT_QQMAIL] = PRODUCT_NAME_QQMAIL;
    m_productTable[PRODUCT_126MAIL] = PRODUCT_NAME_126MAIL;
    m_productTable[PRODUCT_163MAIL] = PRODUCT_NAME_163MAIL;
    m_productTable[PRODUCT_SINAWEIBO] = PRODUCT_NAME_SINAWEIBO;
    m_productTable[PRODUCT_DIDI] = PRODUCT_NAME_DIDI;
    m_productTable[PRODUCT_360CAMERA] = PRODUCT_NAME_360CAMERA;
    m_productTable[PRODUCT_YSYCAMERA] = PRODUCT_NAME_YSYCAMERA;
    m_productTable[PRODUCT_YOUKU] = PRODUCT_NAME_YOUKU;
    m_productTable[PRODUCT_DOUYIN] = PRODUCT_NAME_DOUYIN;
    m_productTable[PRODUCT_MAIMAI] = PRODUCT_NAME_MAIMAI;


    return;
}


std::string GajzStd::GetProductName(const std::string& productId)
{
    return m_productTable[productId];
}

