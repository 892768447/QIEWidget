#!/usr/bin/env python
# -*- encoding:utf-8 -*-

import os,sipconfig
from PyQt5.QtCore import PYQT_CONFIGURATION

# The name of the SIP build file generated by SIP and used by the build
# system.
build_file = 'QIEWidget.sbf'

# Get the SIP configuration information.
config = sipconfig.Configuration()
config.platform = "win32-msvc2010"

qt_path = 'D:/Qt/Qt5.5.1/5.5/msvc2010'
print('QT_DIR: %s' % qt_path)

config.sip_bin = "D:/Python34/Lib/site-packages/PyQt5/sip.exe"
config.default_sip_dir = "D:/Python34/Lib/site-packages/PyQt5/sip"

sip_cmd = ' '.join([
    config.sip_bin,
    '-c', "build",
    '-b', "build/" + build_file,
    '-I', config.default_sip_dir + '/PyQt5',
    PYQT_CONFIGURATION.get('sip_flags', ''),
    'QIEWidget.sip',
])

os.makedirs("build", exist_ok=True)
print(sip_cmd)
os.system(sip_cmd)


# Create the Makefile.
makefile = sipconfig.SIPModuleMakefile(
    config, build_file, dir = "build"
)

# Add the library we are wrapping.  The name doesn't include any platform
# specific prefixes or extensions (e.g. the 'lib' prefix on UNIX, or the
# '.dll' extension on Windows).

#添加头文件路径
makefile.extra_include_dirs = [
    '../', '.', 
    os.path.join(qt_path, 'include'),
    os.path.join(qt_path, 'include', 'ActiveQt'),
    os.path.join(qt_path, 'include', 'QtCore'),
    os.path.join(qt_path, 'include', 'QtGui'),
    os.path.join(qt_path, 'include', 'QtWidgets'),
]

#添加用C++编译的库文件路径
makefile.extra_lib_dirs = [
    os.path.join('..', 'Release'),
    os.path.join('..', '..', 'Release'),
    os.path.join('..', 'Release', 'release'),
    os.path.join('..', '..', 'Release', 'release'),
    os.path.join(qt_path, 'lib'),
]
print(makefile.extra_lib_dirs)

makefile.extra_libs = [
    'QIEWidget',
    'Qt5Core',
    'Qt5Gui',
    'Qt5Widgets',
    'Qt5AxBase',
    'Qt5AxContainer',
    'Qt5AxServer',
]
print(makefile.extra_libs)

# Generate the Makefile itself.
makefile.generate()

import shutil
shutil.copy("../Release/release/QIEWidget.dll", "build/QIEWidget.dll")

try:
    os.remove("build/QIEWidget.lib")
except:pass

