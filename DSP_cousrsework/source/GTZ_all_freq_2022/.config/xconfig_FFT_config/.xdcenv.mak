#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_35_04_50/packages;C:/ti/ccsv5/ccs_base;C:/ti/uia_1_03_01_08/packages;C:/2021/C_Code/GTZ/GTZ/.config
override XDCROOT = C:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_35_04_50/packages;C:/ti/ccsv5/ccs_base;C:/ti/uia_1_03_01_08/packages;C:/2021/C_Code/GTZ/GTZ/.config;C:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
