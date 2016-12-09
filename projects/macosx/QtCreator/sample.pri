########################################################################
# Copyright (c) 1988-2016 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: sample.pri
#
# Author: $author$
#   Date: 12/7/2016
########################################################################

QMAKE_CXXFLAGS += -std=c++11

########################################################################
# xos
XOS_BLD = ../$${XOS_PKG}/build/macosx/QtCreator/$${SAMPLE_BLD_CONFIG}
XOS_LIB = $${XOS_BLD}/lib

########################################################################
# sample
sample_LIBS += \
-L$${XOS_LIB}/libxosnadir \
-lxosnadir \
-lpthread \
-ldl \
