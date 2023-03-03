## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/FFT_config_pe66.oe66

linker.cmd: package/cfg/FFT_config_pe66.xdl
	$(SED) 's"^\"\(package/cfg/FFT_config_pe66cfg.cmd\)\"$""\"C:/2021/C_Code/GTZ/GTZ/.config/xconfig_FFT_config/\1\""' package/cfg/FFT_config_pe66.xdl > $@
