#include "qiewidget.h"
#include <QDebug>

QIEWidget::QIEWidget(QWidget *parent) :
    QWidget(parent)
  , _debug(false)
  , _title("")
  , _blockBeforeNavigate(false)
  , _blockFrameBeforeNavigate(false)
  , _blockFrameNewWindow(false)
  , _blockNavigateError(false)
  , _blockNewProcess(false)
  , _blockNewWindow(false)
  , _blockQuit(false)
{
    //QAXWidget COM控件
    axWidget = new WebAxWidget(this);
    //布局
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(axWidget);

    //绑定信号槽
    //导航
    connect(axWidget, SIGNAL(BeforeNavigate(QString, int, QString, QVariant&, QString, bool&)),
            this, SLOT(onBeforeNavigate(QString,int,QString,QVariant&,QString,bool&)));
    //导航2
    connect(axWidget, SIGNAL(BeforeNavigate2(IDispatch*, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, bool&)),
            this, SLOT(onBeforeNavigate2(IDispatch*, QVariant&, QVariant&, QVariant&, QVariant&, QVariant&, bool&)));
    //命令的启用状态更改
    connect(axWidget, SIGNAL(CommandStateChange(int, bool)),
            this, SLOT(onCommandStateChange(int, bool)));
    //加载网页完成1
    connect(axWidget, SIGNAL(DocumentComplete(IDispatch*, QVariant&)),
            this, SLOT(onDocumentComplete(IDispatch*, QVariant&)));
    //加载网页开始
    connect(axWidget, SIGNAL(DownloadBegin()),
            this, SLOT(onDownloadBegin()));
    //加载网页完成2
    connect(axWidget, SIGNAL(DownloadComplete()),
            this, SLOT(onDownloadComplete()));
    //文件下载
    connect(axWidget, SIGNAL(FileDownload(bool, bool&)),
            this, SLOT(onFileDownload(bool, bool&)));
    //框架导航
    connect(axWidget, SIGNAL(FrameBeforeNavigate(QString, int, QString, QVariant&, QString, bool&)),
            this, SLOT(onFrameBeforeNavigate(QString, int, QString, QVariant&, QString, bool&)));
    //框架导航完成
    connect(axWidget, SIGNAL(FrameNavigateComplete(QString)),
            this, SLOT(onFrameNavigateComplete(QString)));
    //框架新建窗口
    connect(axWidget, SIGNAL(FrameNewWindow(QString, int, QString, QVariant&, QString, bool&)),
            this, SLOT(onFrameNewWindow(QString, int, QString, QVariant&, QString, bool&)));
    //导航完成
    connect(axWidget, SIGNAL(NavigateComplete(QString)),
            this, SLOT(onNavigateComplete(QString)));
    //导航完成2
    connect(axWidget, SIGNAL(NavigateComplete2(IDispatch*, QVariant&)),
            this, SLOT(onNavigateComplete2(IDispatch*, QVariant&)));
    //导航错误
    connect(axWidget, SIGNAL(NavigateError(IDispatch*, QVariant&, QVariant&, QVariant&, bool&)),
            this, SLOT(onNavigateError(IDispatch*, QVariant&, QVariant&, QVariant&, bool&)));
    //新进程
    connect(axWidget, SIGNAL(NewProcess(int, IDispatch*, bool&)),
            this, SLOT(onNewProcess(int, IDispatch*, bool&)));
    //新窗口
    connect(axWidget, SIGNAL(NewWindow(QString, int, QString, QVariant&, QString, bool&)),
            this, SLOT(onNewWindow(QString, int, QString, QVariant&, QString, bool&)));
    //新窗口2
    connect(axWidget, SIGNAL(NewWindow2(IDispatch**, bool&)),
            this, SLOT(onNewWindow2(IDispatch**, bool&)));
    //新窗口3
    connect(axWidget, SIGNAL(NewWindow3(IDispatch**, bool&, uint, QString, QString)),
            this, SLOT(onNewWindow3(IDispatch**, bool&, uint, QString, QString)));
    //浏览器退出
    connect(axWidget, SIGNAL(OnQuit()),
            this, SLOT(onOnQuit()));
    //进度
    connect(axWidget, SIGNAL(ProgressChange(int, int)),
            this, SLOT(onProgressChange(int, int)));
    //属性变化
    connect(axWidget, SIGNAL(PropertyChange(QString)),
            this, SLOT(onPropertyChange(QString)));
    //退出
    connect(axWidget, SIGNAL(Quit(bool&)),
            this, SLOT(onQuit(bool&)));
    //准备状态
    connect(axWidget, SIGNAL(ReadyStateChanged(tagREADYSTATE)),
            this, SLOT(onReadyStateChanged(tagREADYSTATE)));
    //状态文字改变
    connect(axWidget, SIGNAL(StatusTextChange(QString)),
            this, SLOT(onStatusTextChange(QString)));
    //标题改变
    connect(axWidget, SIGNAL(TitleChange(QString)),
            this, SLOT(onTitleChange(QString)));
    //更新页面状态
    connect(axWidget, SIGNAL(UpdatePageStatus(IDispatch*, QVariant&, QVariant&)),
            this, SLOT(onUpdatePageStatus(IDispatch*, QVariant&, QVariant&)));
    //异常
    connect(axWidget, SIGNAL(exception(int, QString, QString, QString)),
            this, SLOT(onException(int, QString, QString, QString)));
    //属性变化
    connect(axWidget, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

QIEWidget::~QIEWidget()
{
    quit();
}

//获取浏览器是否在繁忙
bool QIEWidget::busy()
{
    return axWidget->dynamicCall("Busy()").toBool();
}

//获取浏览器的Document
QAxObject *QIEWidget::document()
{
    return axWidget->querySubObject("Document()");
}

//执行js
QVariant QIEWidget::execScript(QString javaScript)
{
    QAxObject *document = axWidget->querySubObject("Document");
    if(document == NULL || document->isNull())
        return "";
    //qDebug() << "execScript document" << document;
    QAxObject *parentWindow = document->querySubObject("parentWindow");
    if(parentWindow == NULL || parentWindow->isNull())
        return "";
    //qDebug() << "execScript parentWindow" << parentWindow;

//    IHTMLDocument2 *doc2;
//    document->queryInterface(QUuid(IID_IHTMLDocument2), (void**)&doc2);
//    CComDispatchDriver script;
//    doc2->get_Script(&script);
//    CComVariant var(static_cast<IDispatch*>(this->axWidget));
//    script.Invoke1(L"SaveCppObject", &var);

    //run js
//     if (doc2)
//     {
//      IHTMLWindow2 *win2 = NULL;
//      if (doc2->get_parentWindow(&win2) == S_OK)
//      {
//       BSTR s1 = SysAllocString(L"test()");
//       BSTR s2 = SysAllocString(L"JavaScript");
//       VARIANT ret;
//       win2->execScript(s1, s2, &ret);
//       SysFreeString(s2);
//       SysFreeString(s1);
//      }
//     }

    return  parentWindow->dynamicCall("execScript(QString,QString)",javaScript,"JavaScript");
}

//后退
void QIEWidget::goBack()
{
    axWidget->dynamicCall("GoBack()");
}

//前进
void QIEWidget::goForward()
{
    axWidget->dynamicCall("GoForward()");
}

//返回主页
void QIEWidget::goHome()
{
    axWidget->dynamicCall("GoHome()");
}

//进入搜索页面
void QIEWidget::goSearch()
{
    axWidget->dynamicCall("GoSearch()");
}

//加载网页
void QIEWidget::load(QString url)
{
    axWidget->dynamicCall("Navigate(const QString&)", url);
}

//获取名字
QString QIEWidget::locationName()
{
    return _title;
//    QAxObject *document = axWidget->querySubObject("Document");
//    if(document == NULL || document->isNull())
//        return axWidget->dynamicCall("LocationName()").toString(); //这里可能获取为空或者是很长的网址
//    QVariant title;
//    title = document->property("nameProp");
//    if(title.isNull() || title.toString() == "")
//        title = document->property("title");
//    if(title.isNull() || title.toString() == "")
//        title = document->dynamicCall("LocationName()");
//    return title.toString();
}

//获取网址
QString QIEWidget::locationUrl()
{
    return axWidget->dynamicCall("LocationURL()").toString();
}

//加载网页
void QIEWidget::navigate(QString url, int flags, QString targetFrameName, QVariant &postData, QString headers)
{
    axWidget->dynamicCall("Navigate(QString, QVariant&, QVariant&, QVariant&, QVariant&)", url, flags, targetFrameName, postData, headers);
}

//加载网页2
void QIEWidget::navigate2(QString url, int flags, QString targetFrameName, QVariant &postData, QString headers)
{
    axWidget->dynamicCall("Navigate2(QVariant&, QVariant&, QVariant&, QVariant&, QVariant&)", url, flags, targetFrameName, postData, headers);
}

//退出
void QIEWidget::quit()
{
    if(axWidget != NULL)
    {
        axWidget->dynamicCall("Quit()");
        axWidget = NULL;
    }
}

//刷新
void QIEWidget::refresh()
{
    axWidget->dynamicCall("Refresh()");
}

//刷新2
void QIEWidget::refresh2(int level)
{
    axWidget->dynamicCall("Refresh2(QVariant&)", level);
}

//设置状态文字
void QIEWidget::setStatusText(QString statusText)
{
    axWidget->dynamicCall("SetStatusText(QString)", statusText);
}

//获取状态文字
QString QIEWidget::statusText()
{
    return axWidget->dynamicCall("StatusText()").toString();
}

//停止加载
void QIEWidget::stop()
{
    axWidget->dynamicCall("Stop()");
}

void QIEWidget::onBeforeNavigate(QString URL, int Flags, QString TargetFrameName, QVariant& PostData, QString Headers, bool& Cancel)
{
    emit SignalBeforeNavigate(URL, Flags, TargetFrameName, PostData, Headers);
    if(_blockBeforeNavigate)
        Cancel = true;//阻止打开
    if(_debug)
    {
        qDebug() << "onBeforeNavigate URL:" << URL;
        qDebug() << "onBeforeNavigate Flags:" << Flags;
        qDebug() << "onBeforeNavigate TargetFrameName:" << TargetFrameName;
        qDebug() << "onBeforeNavigate PostData:" << PostData.toString();
        qDebug() << "onBeforeNavigate Headers:" << Headers;
        qDebug() << "onBeforeNavigate Cancel:" << Cancel;
    }
}

void QIEWidget::onBeforeNavigate2(IDispatch*, QVariant& URL, QVariant& Flags, QVariant& TargetFrameName, QVariant& PostData, QVariant& Headers, bool& Cancel)
{
    emit SignalBeforeNavigate2(URL.toString(), Flags.toInt(), TargetFrameName.toString(), PostData, Headers.toString());
    if(_blockBeforeNavigate)
        Cancel = true;//阻止打开
    if(_debug)
    {
        qDebug() << "onBeforeNavigate2 URL:" << URL.toString();
        qDebug() << "onBeforeNavigate2 Flags:" << Flags.toInt();
        qDebug() << "onBeforeNavigate2 TargetFrameName:" << TargetFrameName.toString();
        qDebug() << "onBeforeNavigate2 PostData:" << PostData.toString();
        qDebug() << "onBeforeNavigate2 Headers:" << Headers.toString();
        qDebug() << "onBeforeNavigate2 Cancel:" << Cancel;
    }
}

//命令的启用状态更改
void QIEWidget::onCommandStateChange(int command, bool enable)
{
    emit SignalCommandStateChange(command, enable);
    if(_debug)
    {
        qDebug() << "onCommandStateChange command:" << command;
        qDebug() << "onCommandStateChange enable:" << enable;
    }
}

//加载网页完成
void QIEWidget::onDocumentComplete(IDispatch*, QVariant& URL)
{
    emit SignalDocumentComplete(URL.toString());
    if(_debug)
        qDebug() << "onDocumentComplete URL:" << URL.toString();
}

//加载网页开始
void QIEWidget::onDownloadBegin()
{
    emit SignalDownloadBegin();
    if(_debug)
        qDebug() << "onDownloadBegin";
}

//加载网页完成
void QIEWidget::onDownloadComplete()
{
    emit SignalDownloadComplete();
    if(_debug)
        qDebug() << "onDownloadComplete";
}

//文件下载
void QIEWidget::onFileDownload(bool ActiveDocument, bool& Cancel)
{
    emit SignalFileDownload(ActiveDocument);
    if(_debug)
    {
        qDebug() << "FileDownload ActiveDocument:" << ActiveDocument;
        qDebug() << "FileDownload Cancel:" << Cancel;
    }
}

//框架导航
void QIEWidget::onFrameBeforeNavigate(QString URL, int Flags, QString TargetFrameName, QVariant& PostData, QString Headers, bool& Cancel){
    emit SignalFrameBeforeNavigate(URL, Flags, TargetFrameName, PostData, Headers);
    if(_blockFrameBeforeNavigate)
        Cancel = true;
    if(_debug)
    {
        qDebug() << "onFrameBeforeNavigate URL:" << URL;
        qDebug() << "onFrameBeforeNavigate Flags:" << Flags;
        qDebug() << "onFrameBeforeNavigate TargetFrameName:" << TargetFrameName;
        qDebug() << "onFrameBeforeNavigate PostData:" << PostData.toString();
        qDebug() << "onFrameBeforeNavigate Headers:" << Headers;
        qDebug() << "onFrameBeforeNavigate Cancel:" << Cancel;
    }
}

//框架导航完成
void QIEWidget::onFrameNavigateComplete(QString URL){
    emit SignalFrameNavigateComplete(URL);
    if(_debug)
        qDebug() << "onFrameNavigateComplete URL:" << URL;
}

//框架新建窗口
void QIEWidget::onFrameNewWindow(QString URL, int Flags, QString TargetFrameName, QVariant& PostData, QString Headers, bool& Processed){
    emit SignalFrameNewWindow(URL, Flags, TargetFrameName, PostData, Headers);
    if(_blockFrameNewWindow)
        Processed = true;
    if(_debug)
    {
        qDebug() << "onFrameNewWindow URL:" << URL;
        qDebug() << "onFrameNewWindow Flags:" << Flags;
        qDebug() << "onFrameNewWindow TargetFrameName:" << TargetFrameName;
        qDebug() << "onFrameNewWindow PostData:" << PostData.toString();
        qDebug() << "onFrameNewWindow Headers:" << Headers;
        qDebug() << "onFrameNewWindow Processed:" << Processed;
    }
}

//导航完成
void QIEWidget::onNavigateComplete(QString URL){
    emit SignalNavigateComplete(URL);
    if(_debug)
        qDebug() << "onNavigateComplete URL:" << URL;
}

//导航完成2
void QIEWidget::onNavigateComplete2(IDispatch*, QVariant& URL){
    emit SignalNavigateComplete2(URL.toString());
    if(_debug)
        qDebug() << "onNavigateComplete2 URL:" << URL.toString();
}

//导航错误
void QIEWidget::onNavigateError(IDispatch*, QVariant& URL, QVariant& Frame, QVariant& StatusCode, bool& Cancel){
    emit SignalNavigateError(URL.toString(), Frame.toString(), StatusCode.toInt());
    if(_blockNavigateError)
        Cancel = true;
    if(_debug)
    {
        qDebug() << "onNavigateError URL:" << URL;
        qDebug() << "onNavigateError Frame:" << Frame.toString();
        qDebug() << "onNavigateError StatusCode:" << StatusCode.toString();
        qDebug() << "onNavigateError Cancel:" << Cancel;
    }
}

//新进程
void QIEWidget::onNewProcess(int lCauseFlag, IDispatch*, bool& Cancel){
    emit SignalNewProcess(lCauseFlag);
    if(_blockNewProcess)
        Cancel = true;
    if(_debug)
    {
        qDebug() << "onNewProcess lCauseFlag:" << lCauseFlag;
        qDebug() << "onNewProcess Cancel:" << Cancel;
    }
}

//新窗口
void QIEWidget::onNewWindow(QString URL, int Flags, QString TargetFrameName, QVariant& PostData, QString Headers, bool& Processed){
    emit SignalNewWindow(URL, Flags, TargetFrameName, PostData, Headers);
    if(_blockNewWindow)
        Processed = true;
    if(_debug)
    {
        qDebug() << "onNewWindow URL:" << URL;
        qDebug() << "onNewWindow Flags:" << Flags;
        qDebug() << "onNewWindow TargetFrameName:" << TargetFrameName;
        qDebug() << "onNewWindow PostData:" << PostData.toString();
        qDebug() << "onNewWindow Headers:" << Headers;
        qDebug() << "onNewWindow Processed:" << Processed;
    }
}

//新窗口2
void QIEWidget::onNewWindow2(IDispatch**, bool& Cancel){
    emit SignalNewWindow2();
//    if(_blockNewWindow)
//        Cancel = true;
    if(_debug)
        qDebug() << "onNewWindow2 Cancel:" << Cancel;
}

//新窗口3
void QIEWidget::onNewWindow3(IDispatch**, bool& Cancel, uint dwFlags, QString bstrUrlContext, QString bstrUrl){
    emit SignalNewWindow3(dwFlags, bstrUrlContext, bstrUrl);
//    if(_blockNewWindow)
//        Cancel = true;
    if(_debug)
    {
        qDebug() << "onNewWindow3 Cancel:" << Cancel;
        qDebug() << "onNewWindow3 dwFlags:" << dwFlags;
        qDebug() << "onNewWindow3 bstrUrlContext:" << bstrUrlContext;
        qDebug() << "onNewWindow3 bstrUrl:" << bstrUrl;
    }
}

//浏览器退出
void QIEWidget::onOnQuit(){
    emit SignalOnQuit();
    if(_debug)
        qDebug() << "onOnQuit";
}

//进度
void QIEWidget::onProgressChange(int Progress, int ProgressMax){
    emit SignalProgressChange(Progress, ProgressMax);
    if(_debug)
    {
        qDebug() << "onProgressChange Progress:" << Progress;
        qDebug() << "onProgressChange ProgressMax:" << ProgressMax;
    }
}

//属性变化
void QIEWidget::onPropertyChange(QString szProperty){
    emit SignalPropertyChange(szProperty);
    if(_debug)
        qDebug() << "onPropertyChange szProperty:" << szProperty;
}

//退出
void QIEWidget::onQuit(bool& Cancel){
    emit SignalQuit();
    if(_blockQuit)
        Cancel = true;
    if(_debug)
        qDebug() << "onQuit Cancel:" << Cancel;
}

//准备状态
void QIEWidget::onReadyStateChanged(tagREADYSTATE ReadyState){
    emit SignalReadyStateChanged((int)ReadyState);
    if(_debug)
        qDebug() << "onReadyStateChanged ReadyState:" << (int)ReadyState;
}

//状态文字改变
void QIEWidget::onStatusTextChange(QString Text){
    emit SignalStatusTextChange(Text);
    if(_debug)
        qDebug() << "onStatusTextChange Text:" << Text;
}

//标题改变
void QIEWidget::onTitleChange(QString Text){
    _title = Text;
    emit SignalTitleChange(Text);
    if(_debug)
        qDebug() << "onTitleChange Text:" << Text;
}

//更新页面状态
void QIEWidget::onUpdatePageStatus(IDispatch*, QVariant& nPage, QVariant& fDone){
    emit SignalUpdatePageStatus(nPage, fDone);
    if(_debug)
    {
        qDebug() << "onUpdatePageStatus nPage:" << nPage.toString();
        qDebug() << "onUpdatePageStatus fDone:" << fDone.toString();
    }
}

//异常
void QIEWidget::onException(int code, QString source, QString disc, QString help){
    emit SignalException(code, source, disc, help);
    if(_debug)
    {
        qDebug() << "onException code:" << code;
        qDebug() << "onException source:" << source;
        qDebug() << "onException disc:" << disc;
        qDebug() << "onException help:" << help;
    }
}

//属性变化
void QIEWidget::onPropertyChanged(QString name){
    emit SignalPropertyChanged(name);
    if(_debug)
        qDebug() << "onPropertyChanged name:" << name;
}

//debug
bool QIEWidget::isDebug(){
    return _debug;
}
void QIEWidget::setDebug(bool debug){
    _debug = debug;
}

//是否拦截导航
bool QIEWidget::isBlockBeforeNavigate(){
    return _blockBeforeNavigate;
}

void QIEWidget::setBlockBeforeNavigate(bool blockBeforeNavigate){
    _blockBeforeNavigate = blockBeforeNavigate;
}

//是否拦截框架导航
bool QIEWidget::isBlockFrameBeforeNavigate(){
    return _blockFrameBeforeNavigate;
}

void QIEWidget::setBlockFrameBeforeNavigate(bool blockFrameBeforeNavigate){
    _blockFrameBeforeNavigate = blockFrameBeforeNavigate;
}

//是否拦截框架新窗口
bool QIEWidget::isBlockFrameNewWindow(){
    return _blockFrameNewWindow;
}

void QIEWidget::setBlockFrameNewWindow(bool blockFrameNewWindow){
    _blockFrameNewWindow = blockFrameNewWindow;
}

//是否拦截导航错误
bool QIEWidget::isBlockNavigateError(){
    return _blockNavigateError;
}

void QIEWidget::setBlockNavigateError(bool blockNavigateError){
    _blockNavigateError = blockNavigateError;
}

//是否拦截新进程
bool QIEWidget::isBlockNewProcess(){
    return _blockNewProcess;
}

void QIEWidget::setBlockNewProcess(bool blockNewProcess){
    _blockNewProcess = blockNewProcess;
}

//是否拦截新窗口
bool QIEWidget::isBlockNewWindow(){
    return _blockNewWindow;
}

void QIEWidget::setBlockNewWindow(bool blockNewWindow){
    _blockNewWindow = blockNewWindow;
}

//是否拦截退出
bool QIEWidget::isBlockQuit(){
    return _blockQuit;
}

void QIEWidget::setBlockQuit(bool blockQuit){
    _blockQuit = blockQuit;
}
