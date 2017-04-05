#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Created on 2017年4月4日
@author: Irony."[讽刺]
@site: alyl.vip, orzorz.vip, irony.coding.me , irony.iask.in , mzone.iask.in
@email: 892768447@qq.com
@file: Coding.QIEWidget.examples.testiewidget
@description: 
'''
from PyQt5.QtWidgets import QMainWindow, QLabel

import QIEWidget  # @UnresolvedImport


__Author__ = "By: Irony.\"[讽刺]\nQQ: 892768447\nEmail: 892768447@qq.com"
__Copyright__ = "Copyright (c) 2017 Irony.\"[讽刺]"
__Version__ = "Version 1.0"


class Window(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(Window, self).__init__(*args, **kwargs)
        self.resize(800, 600)
        self.ie = QIEWidget.QIEWidget(self)
        self.ie.setBlockNewWindow(True)  # 拦截新窗口,然后跳转到自己的新标签
        self.setCentralWidget(self.ie)

        # 状态栏
        self._statusBar = self.statusBar()
        self._statusBar.setSizeGripEnabled(True)
        self._statusBar.addPermanentWidget(QLabel(self._statusBar))

        # 信号槽
        self.ie.SignalBeforeNavigate.connect(self._onSignalBeforeNavigate)
        self.ie.SignalBeforeNavigate2.connect(self._onSignalBeforeNavigate2)
        self.ie.SignalCommandStateChange.connect(
            self._onSignalCommandStateChange)
        self.ie.SignalDocumentComplete.connect(self._onSignalDocumentComplete)
        self.ie.SignalDownloadBegin.connect(self._onSignalDownloadBegin)
        self.ie.SignalDownloadComplete.connect(self._onSignalDownloadComplete)
        self.ie.SignalFileDownload.connect(self._onSignalFileDownload)
        self.ie.SignalFrameBeforeNavigate.connect(
            self._onSignalFrameBeforeNavigate)
        self.ie.SignalFrameNavigateComplete.connect(
            self._onSignalFrameNavigateComplete)
        self.ie.SignalFrameNewWindow.connect(self._onSignalFrameNewWindow)
        self.ie.SignalNavigateComplete.connect(self._onSignalNavigateComplete)
        self.ie.SignalNavigateComplete2.connect(
            self._onSignalNavigateComplete2)
        self.ie.SignalNavigateError.connect(self._onSignalNavigateError)
        self.ie.SignalNewProcess.connect(self._onSignalNewProcess)
        self.ie.SignalNewWindow.connect(self._onSignalNewWindow)
        self.ie.SignalNewWindow2.connect(self._onSignalNewWindow2)
        self.ie.SignalNewWindow3.connect(self._onSignalNewWindow3)
        self.ie.SignalOnQuit.connect(self._onSignalOnQuit)
        self.ie.SignalProgressChange.connect(self._onSignalProgressChange)
        self.ie.SignalPropertyChange.connect(self._onSignalPropertyChange)
        self.ie.SignalQuit.connect(self._onSignalQuit)
        self.ie.SignalReadyStateChanged.connect(
            self._onSignalReadyStateChanged)
        self.ie.SignalStatusTextChange.connect(self._onSignalStatusTextChange)
        self.ie.SignalTitleChange.connect(self._onSignalTitleChange)
        self.ie.SignalUpdatePageStatus.connect(self._onSignalUpdatePageStatus)
        self.ie.SignalException.connect(self._onSignalException)
        self.ie.SignalPropertyChanged.connect(self._onSignalPropertyChanged)

        # 方法
        # debug
        print("isDebug", self.ie.isDebug())
        # 是否拦截导航
        print("isBlockBeforeNavigate", self.ie.isBlockBeforeNavigate())
        # 是否拦截框架导航
        print("isBlockFrameBeforeNavigate",
              self.ie.isBlockFrameBeforeNavigate())
        # 是否拦截框架新窗口
        print("isBlockFrameNewWindow", self.ie.isBlockFrameNewWindow())
        # 是否拦截导航错误
        print("isBlockNavigateError", self.ie.isBlockNavigateError())
        # 是否拦截新进程
        print("isBlockNewProcess", self.ie.isBlockNewProcess())
        # 是否拦截新窗口
        print("isBlockNewWindow", self.ie.isBlockNewWindow())
        # 是否拦截退出
        print("isBlockQuit", self.ie.isBlockQuit())
        # 繁忙?
        print("busy", self.ie.busy())
        # 文档对象
        print("document", self.ie.document())
        # 执行js
        print("execScript", self.ie.execScript)
        # 后退
        print("goBack", self.ie.goBack)
        # 前进
        print("goForward", self.ie.goForward)
        # 主页
        print("goHome", self.ie.goHome)
        # 进入搜索？
        print("goSearch", self.ie.goSearch)
        # 加载网址
        print("load", self.ie.load)
        # 标题
        print("locationName", self.ie.locationName)
        # 网址
        print("locationUrl", self.ie.locationUrl)
        # 导航
        print("navigate", self.ie.navigate)
        # 导航2
        print("navigate2", self.ie.navigate2)
        # 退出
        print("quit", self.ie.quit)
        # 刷新1
        print("refresh", self.ie.refresh)
        # 刷新2
        print("refresh2", self.ie.refresh2)
        # 设置状态文字
        print("setStatusText", self.ie.setStatusText)
        # 状态文字
        print("statusText", self.ie.statusText())
        # 停止
        print("stop", self.ie.stop)

    def _onSignalBeforeNavigate(self, URL, Flags, TargetFrameName, PostData, Headers):
        print("_onSignalBeforeNavigate", URL, Flags,
              TargetFrameName, PostData, Headers)

    def _onSignalBeforeNavigate2(self, URL, Flags, TargetFrameName, PostData, Headers):
        print("_onSignalBeforeNavigate2", URL, Flags,
              TargetFrameName, PostData, Headers)

    def _onSignalCommandStateChange(self, command, enable):
        print("_onSignalCommandStateChange", command, enable)

    def _onSignalDocumentComplete(self, url):
        print("_onSignalDocumentComplete", url)

    def _onSignalDownloadBegin(self):
        print("_onSignalDownloadBegin")

    def _onSignalDownloadComplete(self):
        print("_onSignalDownloadComplete")

    def _onSignalFileDownload(self, ActiveDocument):
        print("_onSignalFileDownload", ActiveDocument)

    def _onSignalFrameBeforeNavigate(self, URL, Flags, TargetFrameName, PostData, Headers):
        print("_onSignalFrameBeforeNavigate", URL,
              Flags, TargetFrameName, PostData, Headers)

    def _onSignalFrameNavigateComplete(self, url):
        print("_onSignalFrameNavigateComplete", url)

    def _onSignalFrameNewWindow(self, URL, Flags, TargetFrameName, PostData, Headers):
        print("_onSignalFrameNewWindow", URL, Flags,
              TargetFrameName, PostData, Headers)

    def _onSignalNavigateComplete(self, url):
        print("_onSignalNavigateComplete", url)

    def _onSignalNavigateComplete2(self, url):
        print("_onSignalNavigateComplete2", url)

    def _onSignalNavigateError(self, URL, Frame, StatusCode):
        print("_onSignalNavigateError", URL, Frame, StatusCode)

    def _onSignalNewProcess(self, lCauseFlag):
        print("_onSignalNewProcess", lCauseFlag)

    def _onSignalNewWindow(self, URL, Flags, TargetFrameName, PostData, Headers):
        print("_onSignalNewWindow", URL, Flags,
              TargetFrameName, PostData, Headers)

    def _onSignalNewWindow2(self):
        print("_onSignalNewWindow2")

    def _onSignalNewWindow3(self, dwFlags, bstrUrlContext, bstrUrl):
        print("_onSignalNewWindow3", dwFlags, bstrUrlContext, bstrUrl)

    def _onSignalOnQuit(self):
        print("_onSignalOnQuit")

    def _onSignalProgressChange(self, Progress, ProgressMax):
        print("_onSignalProgressChange", Progress, ProgressMax)

    def _onSignalPropertyChange(self, szProperty):
        print("_onSignalPropertyChange", szProperty)

    def _onSignalQuit(self):
        print("_onSignalQuit")

    def _onSignalReadyStateChanged(self, ReadyState):
        print("_onSignalReadyStateChanged", ReadyState)

    def _onSignalStatusTextChange(self, Text):
        print("_onSignalStatusTextChange", Text)

    def _onSignalTitleChange(self, Text):
        print("_onSignalTitleChange", Text)

    def _onSignalUpdatePageStatus(self, nPage, fDone):
        print("_onSignalUpdatePageStatus", nPage, fDone)

    def _onSignalException(self, code, source, disc, helps):
        print("_onSignalException", code, source, disc, helps)

    def _onSignalPropertyChanged(self, name):
        print("_onSignalPropertyChanged", name)

if __name__ == "__main__":
    import sys
    from PyQt5.QtWidgets import QApplication
    app = QApplication(sys.argv)
    app.setApplicationDisplayName("PyQt IE Webbrowser")
    app.setApplicationVersion("0.0.1")
    w = Window()
    w.show()
    w.ie.load("http://alyl.vip")
    sys.exit(app.exec_())
