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
#   File: ls.pri
#
# Author: $author$
#   Date: 12/7/2016
########################################################################

########################################################################
ls_HEADERS += \
$${SAMPLE_SRC}/sample/app/ls/tree/main.hpp \
$${SAMPLE_SRC}/sample/app/ls/main.hpp \

ls_SOURCES += \
$${SAMPLE_SRC}/sample/app/ls/tree/main.cpp \
$${XOS_SRC}/xos/base/main_main.cpp \
$${XOS_SRC}/xos/base/getopt/main_opt.cpp \

########################################################################
