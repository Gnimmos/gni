##############################################################################
#
#    file                 : Makefile
#    created              : Wed Dec 20 14:31:48 EET 2017
#    copyright            : (C) 2002 George Nicolaou
#
##############################################################################

ROBOT       = gni
MODULE      = ${ROBOT}.so
MODULEDIR   = drivers/${ROBOT}
SOURCES     = ${ROBOT}.cpp driver.cpp learn.cpp gradient_sarsa.cpp

SHIPDIR     = drivers/${ROBOT}
SHIP        = ${ROBOT}.xml 155-DTM.rgb logo.rgb
SHIPSUBDIRS = 

PKGSUBDIRS  = ${SHIPSUBDIRS}
src-robots-gni_PKGFILES = $(shell find * -maxdepth 0 -type f -print)
src-robots-gni_PKGDIR   = ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))LDFLAGS     = -lefence


include ${MAKE_DEFAULT}
