################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/linker.cmd: ../Sys_BIOs_config.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/Software/CCS_5.5/xdctools_3_25_03_72/xs" --xdcpath="D:/Software/CCS_5.5/bios_6_35_04_50/packages;D:/Software/CCS_5.5/ccsv5/ccs_base;D:/Software/CCS_5.5/uia_1_03_01_08/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platforms.simTCI6608 -r release -c "D:/Software/CCS_5.5/ccsv5/tools/compiler/c6000_7.4.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd

main_gtz.obj: ../main_gtz.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/Software/CCS_5.5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O3 -g --include_path="D:/Software/CCS_5.5/ccsv5/tools/compiler/c6000_7.4.4/include" --display_error_number --diag_warning=225 --diag_wrap=off --no_bad_aliases --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="main_gtz.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util.obj: ../util.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/Software/CCS_5.5/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O3 -g --include_path="D:/Software/CCS_5.5/ccsv5/tools/compiler/c6000_7.4.4/include" --display_error_number --diag_warning=225 --diag_wrap=off --no_bad_aliases --debug_software_pipeline -k --preproc_with_compile --preproc_dependency="util.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


