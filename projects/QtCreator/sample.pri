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
SAMPLE_PKG = ../../../../..
SAMPLE_BLD = ../..
SAMPLE_PRJ = $${SAMPLE_PKG}
SAMPLE_BIN = $${SAMPLE_BLD}/bin
SAMPLE_LIB = $${SAMPLE_BLD}/lib
SAMPLE_SRC = $${SAMPLE_PKG}/source

CONFIG(debug, debug|release) {
SAMPLE_BLD_CONFIG = Debug
xosnadir_DEFINES += DEBUG_BUILD
} else {
SAMPLE_BLD_CONFIG = Release
xosnadir_DEFINES += RELEASE_BUILD
}

########################################################################
# nadir
NADIR_PKG = $${SAMPLE_PKG}/../nadir
NADIR_PRJ = $${NADIR_PKG}
NADIR_SRC = $${NADIR_PKG}/src

nadir_INCLUDEPATH += \
$${NADIR_SRC} \

xosnadir_DEFINES += \

nadir_DEFINES += \
USE_NADIR_BASE \
$${xosnadir_DEFINES} \

########################################################################
# sample
sample_INCLUDEPATH += \
$${SAMPLE_SRC} \
$${nadir_INCLUDEPATH} \

sample_DEFINES += \
$${xosnadir_DEFINES} \

