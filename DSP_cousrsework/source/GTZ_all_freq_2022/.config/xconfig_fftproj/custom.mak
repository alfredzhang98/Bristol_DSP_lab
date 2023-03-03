## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/FFTProj_pe66.oe66

linker.cmd: package/cfg/FFTProj_pe66.xdl
	$(SED) 's"^\"\(package/cfg/FFTProj_pe66cfg.cmd\)\"$""\"C:/Users/Scott/Dropbox/CCS5/FFTProj/.config/xconfig_FFTProj/\1\""' package/cfg/FFTProj_pe66.xdl > $@
