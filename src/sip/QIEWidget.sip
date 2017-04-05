%Module QIEWidget
%Import QtWidgets/QtWidgetsmod.sip
%Import QtCore/QtCoremod.sip
%Import QAxContainer/QAxContainermod.sip
%Import QtGui/QtGuimod.sip

class QIEWidget : QWidget
{
%TypeHeaderCode
#include "../qiewidget.h"
#include "../webaxwidget.h"
//#include "windows.h"
%End

public:

    %Property(name=title, get=locationName)
    %Property(name=url, get=locationUrl)
    
    enum tagREADYSTATE
    {
        READYSTATE_UNINITIALIZED    = 0,
        READYSTATE_LOADING          = 1,
        READYSTATE_LOADED           = 2,
        READYSTATE_INTERACTIVE      = 3,
        READYSTATE_COMPLETE         = 4
    };

    explicit QIEWidget(QWidget *parent /TransferThis/ = 0);
    virtual ~QIEWidget();
    
    //debug
    bool isDebug();
    void setDebug(bool debug);

    //是否拦截导航
    bool isBlockBeforeNavigate();
    void setBlockBeforeNavigate(bool blockBeforeNavigate);
    //是否拦截框架导航
    bool isBlockFrameBeforeNavigate();
    void setBlockFrameBeforeNavigate(bool blockFrameBeforeNavigate);
    //是否拦截框架新窗口
    bool isBlockFrameNewWindow();
    void setBlockFrameNewWindow(bool blockFrameNewWindow);
    //是否拦截导航错误
    bool isBlockNavigateError();
    void setBlockNavigateError(bool blockNavigateError);
    //是否拦截新进程
    bool isBlockNewProcess();
    void setBlockNewProcess(bool blockNewProcess);
    //是否拦截新窗口
    bool isBlockNewWindow();
    void setBlockNewWindow(bool blockNewWindow);
    //是否拦截退出
    bool isBlockQuit();
    void setBlockQuit(bool blockQuit);
    
    bool busy();
    QAxObject* document();
    QVariant execScript(QString);
    void goBack();
    void goForward();
    void goHome();
    void goSearch();
    void load(QString url);
    QString locationName();
    QString locationUrl();
    void navigate(QString url, int flags /TransferThis/ = 0, QString targetFrameName /TransferThis/ = "", QVariant& postData /TransferThis/ = QVariant(""), QString headers /TransferThis/ = "");
    void navigate2(QString url, int flags /TransferThis/ = 0, QString targetFrameName /TransferThis/ = "", QVariant& postData /TransferThis/ = QVariant(""), QString headers /TransferThis/ = "");
    void quit();
    void refresh();
    void refresh2(int level /TransferThis/ = 0);
    void setStatusText(QString statusText);
    QString statusText();
    void stop();

    //为浏览器自带的信号绑定槽
    //导航
    void onBeforeNavigate(QString,int,QString,QVariant&,QString,bool&);
    //导航2
    //void onBeforeNavigate2(IDispatch*, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, bool&);
    //命令的启用状态更改
    void onCommandStateChange(int, bool);
    //加载网页完成1
    //void onDocumentComplete(IDispatch*, QVariant&);
    //加载网页开始
    void onDownloadBegin();
    //加载网页完成2
    void onDownloadComplete();
    //文件下载
    void onFileDownload(bool, bool&);
    //框架导航
    void onFrameBeforeNavigate(QString, int, QString, QVariant&, QString, bool&);
    //框架导航完成
    void onFrameNavigateComplete(QString);
    //框架新建窗口
    void onFrameNewWindow(QString, int, QString, QVariant&, QString, bool&);
    //导航完成
    void onNavigateComplete(QString);
    //导航完成2
    //void onNavigateComplete2(IDispatch*, QVariant&);
    //导航错误
    //void onNavigateError(IDispatch*, QVariant&, QVariant&, QVariant&, bool&);
    //新进程
    //void onNewProcess(int, IDispatch*, bool&);
    //新窗口
    void onNewWindow(QString, int, QString, QVariant&, QString, bool&);
    //新窗口2
    //void onNewWindow2(IDispatch**, bool&);
    //新窗口3
    //void onNewWindow3(IDispatch**, bool&, uint, QString, QString);
    //浏览器退出
    void onOnQuit();
    //进度
    void onProgressChange(int, int);
    //属性变化
    void onPropertyChange(QString);
    //退出
    void onQuit(bool&);
    //准备状态
    void onReadyStateChanged(tagREADYSTATE);
    //状态文字改变
    void onStatusTextChange(QString);
    //标题改变
    void onTitleChange(QString);
    //更新页面状态
    //void onUpdatePageStatus(IDispatch*, QVariant&, QVariant&);
    //异常
    void onException(int, QString, QString, QString);
    //属性变化
    void onPropertyChanged(QString);

signals:
    //导航
    void SignalBeforeNavigate(QString, int, QString, QVariant, QString);
    //导航2
    void SignalBeforeNavigate2(QString, int, QString, QVariant, QString);
    //命令的启用状态更改
    void SignalCommandStateChange(int, bool);
    //加载网页完成1
    void SignalDocumentComplete(QString);
    //加载网页开始
    void SignalDownloadBegin();
    //加载网页完成2
    void SignalDownloadComplete();
    //文件下载
    void SignalFileDownload(bool);
    //框架导航
    void SignalFrameBeforeNavigate(QString, int, QString, QVariant, QString);
    //框架导航完成
    void SignalFrameNavigateComplete(QString);
    //框架新建窗口
    void SignalFrameNewWindow(QString, int, QString, QVariant, QString);
    //导航完成
    void SignalNavigateComplete(QString);
    //导航完成2
    void SignalNavigateComplete2(QString);
    //导航错误
    void SignalNavigateError(QString, QString, int);
    //新进程
    void SignalNewProcess(int);
    //新窗口
    void SignalNewWindow(QString, int, QString, QVariant, QString);
    //新窗口2
    void SignalNewWindow2();
    //新窗口3
    void SignalNewWindow3(uint, QString, QString);
    //浏览器退出
    void SignalOnQuit();
    //进度
    void SignalProgressChange(int, int);
    //属性变化
    void SignalPropertyChange(QString);
    //退出
    void SignalQuit();
    //准备状态
    void SignalReadyStateChanged(int);
    //状态文字改变
    void SignalStatusTextChange(QString);
    //标题改变
    void SignalTitleChange(QString);
    //更新页面状态
    void SignalUpdatePageStatus(QVariant, QVariant);
    //异常
    void SignalException(int, QString, QString, QString);
    //属性变化
    void SignalPropertyChanged(QString);

};