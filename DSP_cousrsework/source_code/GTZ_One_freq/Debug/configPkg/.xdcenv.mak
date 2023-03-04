#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/Software/CCS_5.5/bios_6_35_04_50/packages;D:/Software/CCS_5.5/ccsv5/ccs_base;D:/Software/CCS_5.5/uia_1_03_01_08/packages
override XDCROOT = D:/Software/CCS_5.5/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/Software/CCS_5.5/bios_6_35_04_50/packages;D:/Software/CCS_5.5/ccsv5/ccs_base;D:/Software/CCS_5.5/uia_1_03_01_08/packages;D:/Software/CCS_5.5/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
