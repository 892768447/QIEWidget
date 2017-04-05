#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Created on 2017年4月4日
@author: Irony."[讽刺]
@site: alyl.vip, orzorz.vip, irony.coding.me , irony.iask.in , mzone.iask.in
@email: 892768447@qq.com
@file: webbrowser
@description: 
'''
from PyQt5.QtCore import QRect, Qt
from PyQt5.QtGui import QFont, QPainter
from PyQt5.QtWidgets import QMainWindow, QTabWidget, QAction, QToolBar,\
    QLineEdit, QLabel, QProgressBar

import QIEWidget  # @UnresolvedImport


__Author__ = "By: Irony.\"[讽刺]\nQQ: 892768447\nEmail: 892768447@qq.com"
__Copyright__ = "Copyright (c) 2017 Irony.\"[讽刺]"
__Version__ = "Version 1.0"


class Webbrowser(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(Webbrowser, self).__init__(*args, **kwargs)
        self.resize(800, 600)
        self.tabWidget = QTabWidget(
            self, tabsClosable=True, movable=True,
            tabCloseRequested=self.onTabCloseRequested,
            currentChanged=self.onCurrentChanged)  # 标签页
        self.setCentralWidget(self.tabWidget)
        self._init()
        self._initTab()

    def paintEvent(self, event):
        painter = QPainter(self)
        self._addRect = QRect(self.width() - 30,
                              self.tabWidget.y(), 30,
                              self.tabWidget.tabBar().height())
        painter.fillRect(self._addRect, Qt.white)
        painter.drawRect(self._addRect)
        painter.drawText(self.width() - 16, self.tabWidget.y() + 18, "+")
        super(Webbrowser, self).paintEvent(event)

    def mousePressEvent(self, event):
        super(Webbrowser, self).mousePressEvent(event)
        if self._addRect.x() <= event.pos().x() <= self.width() and \
                self._addRect.y() <= event.pos().y() <= self._addRect.y() + 30:
            self.addTab("about:Tabs", "about:Tabs")

    def _initTab(self):
        self.addTab("http://alyl.vip", "Blog")
        self.addTab(
            "https://coding.net/u/892768447/project", "Coding/892768447")
        self.addTab(
            "https://github.com/892768447?tab=repositories", "Github/892768447")

    def addTab(self, url, title=""):
        w = QIEWidget.QIEWidget(self.tabWidget)
        w.setBlockNewWindow(True)  # 拦截新窗口,然后跳转到自己的新标签
        # 绑定信号槽
        # 跳转到自己的新标签，注意不能用onSignalNewWindow，否则会覆盖窗口函数
        w.SignalNewWindow.connect(self._onSignalNewWindow)
        w.SignalNavigateComplete.connect(
            self._onSignalNavigateComplete)  # 导航完成
        self.tabWidget.addTab(w, title)
        w.load(url)

    def load(self, url):
        w = self.tabWidget.currentWidget()
        if w:
            w.load(url)

    def _init(self):
        # 后退 前进 刷新 停止
        self.backAction = QAction(
            "3", self, triggered=self.actionBack, statusTip="后退", font=QFont("webdings", 16))
        self.forwardAction = QAction(
            "4", self, triggered=self.actionForward, statusTip="前进", font=QFont("webdings", 16))
        self.refreshAction = QAction(
            "q", self, triggered=self.actionRefresh, statusTip="刷新", font=QFont("webdings", 16))
        self.stopAction = QAction(
            "r", self, triggered=self.actionStop, visible=False, statusTip="停止", font=QFont("webdings", 16))
        toolBar = QToolBar(self, movable=False, windowTitle="工具栏")
        self.addToolBar(toolBar)
        toolBar.addAction(self.backAction)
        toolBar.addAction(self.forwardAction)
        toolBar.addAction(self.refreshAction)
        toolBar.addAction(self.stopAction)

        # 地址栏
        self.searchEdit = QLineEdit(
            self, returnPressed=self.actionGo, minimumHeight=28, clearButtonEnabled=True)
        toolBar.addWidget(self.searchEdit)

        # 状态栏
        self._statusBar = self.statusBar()
        self._statusBar.setSizeGripEnabled(True)
        self._statusBar.addPermanentWidget(QLabel(self._statusBar))

        # 进度条
        self.progressBar = QProgressBar(self._statusBar)
        self.progressBar.setTextVisible(False)
        self.progressBar.hide()
        self._statusBar.addPermanentWidget(self.progressBar)

    def actionBack(self):
        # 后退
        self.tabWidget.currentWidget().goBack()

    def actionForward(self):
        # 前进
        self.tabWidget.currentWidget().goForward()

    def actionRefresh(self):
        # 刷新
        self.refreshAction.setVisible(False)
        self.stopAction.setVisible(True)
        self.tabWidget.currentWidget().refresh()

    def actionStop(self):
        # 停止
        self.stopAction.setVisible(False)
        self.refreshAction.setVisible(True)
        self.tabWidget.currentWidget().stop()

    def actionGo(self):
        # 输入网址后回车
        url = self.searchEdit.text()
        if not url:
            return
        self.load(url)  # 加载url

    def onTabCloseRequested(self, index):
        # tab关闭请求
        if self.tabWidget.count() > 1:
            self.tabWidget.removeTab(index)

    def onCurrentChanged(self, index):
        # 当前标签变化
        # 更改地址栏地址
        self.searchEdit.setText(self.tabWidget.widget(index).url)
        self.tabWidget.setTabText(
            index, self.tabWidget.widget(index).title)
        self.setWindowTitle(self.tabWidget.widget(index).title)

    def _onSignalNavigateComplete(self, url):
        self.searchEdit.setText(url)  # 设置地址栏地址
        self.tabWidget.setTabText(
            self.tabWidget.currentIndex(), self.tabWidget.currentWidget().title)
        self.setWindowTitle(self.tabWidget.currentWidget().title)

    def _onSignalNewWindow(self, url, flags, targetFrameName, postData, headers):
        # 新窗口拦截
        print("_onSignalNewWindow", url, flags,
              targetFrameName, postData, headers)
        self.addTab(url, "加载中")


class Label(QLabel):

    def paintEvent(self, event):
        painter = QPainter(self)
        rect = QRect(self.width() - 30, 0, 30, self.height())
        painter.fillRect(rect, Qt.white)
        painter.drawRect(rect)
        painter.drawText(self.width() - 15, self.height() / 2 + 5, "+")
        super(Label, self).paintEvent(event)

if __name__ == "__main__":
    import sys
    from PyQt5.QtWidgets import QApplication
    app = QApplication(sys.argv)
    app.setStyleSheet("QTabBar::tab {max-width: 100px;}")
    app.setApplicationDisplayName("PyQt IE Webbrowser")
    app.setApplicationVersion("0.0.1")
    w = Webbrowser()
    w.show()
    sys.exit(app.exec_())
