//Copyright (c) 2019-2020 The Hush developers
//Copyright 2020 Safecoin Developers
//Released under the GPLv3

#ifndef SETTINGS_H
#define SETTINGS_H

#include "precompiled.h"

struct Config {
    QString host;
    QString port;
    QString rpcuser;
    QString rpcpassword;
};

struct ToFields;
struct Tx;

struct PaymentURI {
    QString addr;
    QString amt;
    QString memo;

    // Any errors are stored here
    QString error;
};

class Settings
{
public:
    static  Settings* init();
    static  Settings* getInstance();

    Config  getSettings();
    void    saveSettings(const QString& host, const QString& port, const QString& username, const QString& password);

    bool    isTestnet();
    void    setTestnet(bool isTestnet);
            
    bool    isSaplingAddress(QString addr);
    bool    isSproutAddress(QString addr);
            
    bool    isValidSaplingPrivateKey(QString pk);

    bool    isSyncing();
    void    setSyncing(bool syncing);

    int     getZcashdVersion();
    void    setZcashdVersion(int version);
    
    void    setUseEmbedded(bool r) { _useEmbedded = r; }
    bool    useEmbedded() { return _useEmbedded; }

    void    setHeadless(bool h) { _headless = h; }
    bool    isHeadless() { return _headless; }

    int     getBlockNumber();
    void    setBlockNumber(int number);
            
    bool    getSaveZtxs();
    void    setSaveZtxs(bool save);

    bool    getAutoShield();
    void    setAutoShield(bool allow);

    bool    getAllowCustomFees();
    void    setAllowCustomFees(bool allow);

    bool    getAllowFetchPrices();
    void    setAllowFetchPrices(bool allow);

    bool    getCheckForUpdates();
    void    setCheckForUpdates(bool allow);

    bool    isSaplingActive();
    
    QString get_theme_name();
    void set_theme_name(QString theme_name);

    std::string get_currency_name();
    void set_currency_name(std::string currency_name);


    void    setUsingZcashConf(QString confLocation);
    const   QString& getZcashdConfLocation() { return _confLocation; }


    void    setZECPrice(double p)       { zecPrice = p;   }
    void    set_fiat_price(double p)    { fiat_price = p; }
    void    setBTCPrice(unsigned int p) { btcPrice = p;   }
    double  getZECPrice();
    double  get_fiat_price();
    unsigned int  getBTCPrice();
    double get_price(std::string currency);
    double get_marketcap(std::string currency);
    void   set_price(std::string currency, double price);
    double get_volume(std::string ticker);


    void    setPeers(int peers);
    int     getPeers();
       
    // Static stuff
    static const QString txidStatusMessage;
    
    static void saveRestore(QDialog* d);
    static void saveRestoreTableHeader(QTableView* table, QDialog* d, QString tablename) ;

    static void openAddressInExplorer(QString address);
    static void openTxInExplorer(QString txid);

    static PaymentURI parseURI(QString paymentURI);
    static QString    paymentURIPretty(PaymentURI);

    static bool    isZAddress(QString addr);
    static bool    isTAddress(QString addr);

    static QString getDecimalString(double amt);
    static QString getUSDFormat(double bal);
    static QString getDisplayFormat(double bal);

    static QString getZECUSDDisplayFormat(double bal);

    static QString getTokenName();
    static QString getDonationAddr();

    static double  getMinerFee();
    static double  getZboardAmount();
    static QString getZboardAddr();

    static int     getMaxMobileAppTxns() { return 30; }
    
    static bool    isValidAddress(QString addr);

    static bool    addToZcashConf(QString confLocation, QString line);
    static bool    removeFromZcashConf(QString confLocation, QString option);

    static const QString labelRegExp;

    static const int     updateSpeed         = 10 * 1000;        // 10 sec
    static const int     quickUpdateSpeed    = 3  * 1000;        // 3 sec
    static const int     priceRefreshSpeed   = 15 * 60 * 1000;   // 15 mins

private:
    // This class can only be accessed through Settings::getInstance()
    Settings() = default;
    ~Settings() = default;

    static Settings* instance;

    QString _confLocation;
    QString _executable;
    bool    _isTestnet        = false;
    bool    _isSyncing        = false;
    int     _blockNumber      = 0;
    int     _zcashdVersion    = 0;
    bool    _useEmbedded      = false;
    bool    _headless         = false;
    int     _peerConnections  = 0;
    
    double  zecPrice          = 0.0;
    double  fiat_price        = 0.0;
    unsigned int  btcPrice    = 0;
    std::map<std::string, double> prices;
    std::map<std::string, double> volumes;
    std::map<std::string, double> marketcaps;
};

#endif // SETTINGS_H
