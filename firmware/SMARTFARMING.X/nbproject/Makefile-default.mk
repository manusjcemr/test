#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/driver/usart/src/drv_usart.c ../src/config/default/peripheral/can/plib_can0.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rtc/plib_rtc_clock.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/config/default/peripheral/tc/plib_tc3.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/tasks.c ../src/main.c ../src/myapp.c ../src/app.c ../src/at_engine.c ../src/at_parser.c ../src/dev_adapter.c ../src/dev_hal.c ../src/dev_timer.c ../src/gsm_gps.c ../src/app2.c ../src/app3.c ../src/ext_flash.c ../src/app4.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/869808652/drv_usart.o ${OBJECTDIR}/_ext/60165182/plib_can0.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/829342655/plib_tc3.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/myapp.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/at_engine.o ${OBJECTDIR}/_ext/1360937237/at_parser.o ${OBJECTDIR}/_ext/1360937237/dev_adapter.o ${OBJECTDIR}/_ext/1360937237/dev_hal.o ${OBJECTDIR}/_ext/1360937237/dev_timer.o ${OBJECTDIR}/_ext/1360937237/gsm_gps.o ${OBJECTDIR}/_ext/1360937237/app2.o ${OBJECTDIR}/_ext/1360937237/app3.o ${OBJECTDIR}/_ext/1360937237/ext_flash.o ${OBJECTDIR}/_ext/1360937237/app4.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/869808652/drv_usart.o.d ${OBJECTDIR}/_ext/60165182/plib_can0.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/60167341/plib_eic.o.d ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1865521619/plib_port.o.d ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o.d ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o.d ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d ${OBJECTDIR}/_ext/829342655/plib_tc3.o.d ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/14461671/sys_dma.o.d ${OBJECTDIR}/_ext/1881668453/sys_int.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/tasks.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/myapp.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/at_engine.o.d ${OBJECTDIR}/_ext/1360937237/at_parser.o.d ${OBJECTDIR}/_ext/1360937237/dev_adapter.o.d ${OBJECTDIR}/_ext/1360937237/dev_hal.o.d ${OBJECTDIR}/_ext/1360937237/dev_timer.o.d ${OBJECTDIR}/_ext/1360937237/gsm_gps.o.d ${OBJECTDIR}/_ext/1360937237/app2.o.d ${OBJECTDIR}/_ext/1360937237/app3.o.d ${OBJECTDIR}/_ext/1360937237/ext_flash.o.d ${OBJECTDIR}/_ext/1360937237/app4.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/869808652/drv_usart.o ${OBJECTDIR}/_ext/60165182/plib_can0.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ${OBJECTDIR}/_ext/829342655/plib_tc3.o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/14461671/sys_dma.o ${OBJECTDIR}/_ext/1881668453/sys_int.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/tasks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/myapp.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/at_engine.o ${OBJECTDIR}/_ext/1360937237/at_parser.o ${OBJECTDIR}/_ext/1360937237/dev_adapter.o ${OBJECTDIR}/_ext/1360937237/dev_hal.o ${OBJECTDIR}/_ext/1360937237/dev_timer.o ${OBJECTDIR}/_ext/1360937237/gsm_gps.o ${OBJECTDIR}/_ext/1360937237/app2.o ${OBJECTDIR}/_ext/1360937237/app3.o ${OBJECTDIR}/_ext/1360937237/ext_flash.o ${OBJECTDIR}/_ext/1360937237/app4.o

# Source Files
SOURCEFILES=../src/config/default/driver/usart/src/drv_usart.c ../src/config/default/peripheral/can/plib_can0.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/rtc/plib_rtc_clock.c ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/tc/plib_tc0.c ../src/config/default/peripheral/tc/plib_tc3.c ../src/config/default/peripheral/wdt/plib_wdt.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/system/dma/sys_dma.c ../src/config/default/system/int/src/sys_int.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/config/default/libc_syscalls.c ../src/config/default/tasks.c ../src/main.c ../src/myapp.c ../src/app.c ../src/at_engine.c ../src/at_parser.c ../src/dev_adapter.c ../src/dev_hal.c ../src/dev_timer.c ../src/gsm_gps.c ../src/app2.c ../src/app3.c ../src/ext_flash.c ../src/app4.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATSAMC21J18A
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\ATSAMC21J18A.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/869808652/drv_usart.o: ../src/config/default/driver/usart/src/drv_usart.c  .generated_files/flags/default/2022d210a4dfd502aec7164de5d01628a25bda4c .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/869808652" 
	@${RM} ${OBJECTDIR}/_ext/869808652/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/869808652/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/869808652/drv_usart.o.d" -o ${OBJECTDIR}/_ext/869808652/drv_usart.o ../src/config/default/driver/usart/src/drv_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can0.o: ../src/config/default/peripheral/can/plib_can0.c  .generated_files/flags/default/8c46570d3fb29e3eaf123b389b45f3fe159812d4 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can0.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can0.o ../src/config/default/peripheral/can/plib_can0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/bef69733bb6d07d7c70b535548309ca714625d21 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/2af5edaa7573ce52ece1384965afdac602686b8 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/52b63a92dcbb164a99dad6210df8d8f994717bd .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/d7e33e1abc7a0507a1eabb8b3fc9ca1490832f40 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/fb4f2c1a3b122fa6537ab5b05b12655e996cebf1 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/f4707ff216ffd31fbdf849476723ab94be598c5 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o: ../src/config/default/peripheral/rtc/plib_rtc_clock.c  .generated_files/flags/default/47a616c3519798bee093cd14db949bdb9315030f .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60180175" 
	@${RM} ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o.d" -o ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o ../src/config/default/peripheral/rtc/plib_rtc_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/8b9cc6a0e8c6269b6c8f43a1a6435903137c5769 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/default/ff0db6899374d7940c45d9423d932a12fb92cc25 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c  .generated_files/flags/default/3c56360ea74bb9cb0c334d842287fa87b9a9c296 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c  .generated_files/flags/default/548a211e1001e8099b56792672a6b519da44556b .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/flags/default/8f7bc8d6b50021937ea1ca60ad502425ac204189 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/99aad8717d85ffed83bfbb9a3a105d5f77d7a663 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/flags/default/77b5a40250c96cdfbc68143943ac59b92d029fb7 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc3.o: ../src/config/default/peripheral/tc/plib_tc3.c  .generated_files/flags/default/fad41096e9b850a8d309629dec592e9d804603f .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc3.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc3.o ../src/config/default/peripheral/tc/plib_tc3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/7c08e74da68173c5e3cb0e211978c91692d9b292 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/dd803084ca804df3a0e02fc858e6d8cb9d439a1 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  .generated_files/flags/default/a357a5008e0b5d61a5ebb4a9b9da801c3f21e33e .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/101bcc0586e24b290121721521701db537209781 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/d694e1013795ca74ee55b22e5e95d913d20d5b39 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/b5a324bd056c0728ea103103dde9909d3660c6e9 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/40523637d6b280b444d694631da3a07c4d31209 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/810a47bb46f25b1676de5890f4369d662922d20a .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/1fb1029c4c923d7dc8c379cb2ad09d7958a17bd0 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/478c1bd0a57d29f97ed2b32e19d110b693d99bc6 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/6e93a173a7ced0adde0fb3b567235bfef2c51b79 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/myapp.o: ../src/myapp.c  .generated_files/flags/default/c29831227669ef684f49268cdd1b83b56ebca8a0 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/myapp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/myapp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/myapp.o.d" -o ${OBJECTDIR}/_ext/1360937237/myapp.o ../src/myapp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/d004046ff2b516a16081ef20cf023eb79fa09f7e .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/at_engine.o: ../src/at_engine.c  .generated_files/flags/default/6ee3af5e7c60e9fc265cb2493b95989e712eb399 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_engine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_engine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/at_engine.o.d" -o ${OBJECTDIR}/_ext/1360937237/at_engine.o ../src/at_engine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/at_parser.o: ../src/at_parser.c  .generated_files/flags/default/e64b1f42d55b738c015b9b6be92e7a9074d12269 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_parser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/at_parser.o.d" -o ${OBJECTDIR}/_ext/1360937237/at_parser.o ../src/at_parser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_adapter.o: ../src/dev_adapter.c  .generated_files/flags/default/4b666d027ad2e5a7d0768141dcb94684d214afc2 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_adapter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_adapter.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_adapter.o ../src/dev_adapter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_hal.o: ../src/dev_hal.c  .generated_files/flags/default/e4e329be425c0bfc0108f4fba634cf00ecc0e841 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_hal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_hal.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_hal.o ../src/dev_hal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_timer.o: ../src/dev_timer.c  .generated_files/flags/default/7798e8cac50c10f1539da1531fe27ff40404a72e .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_timer.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_timer.o ../src/dev_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/gsm_gps.o: ../src/gsm_gps.c  .generated_files/flags/default/9f44f070096f6d576588b1b8f929044b62a93bdb .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gsm_gps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gsm_gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gsm_gps.o.d" -o ${OBJECTDIR}/_ext/1360937237/gsm_gps.o ../src/gsm_gps.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app2.o: ../src/app2.c  .generated_files/flags/default/fb5662d52db926cb077abc07c4cee218bad73f29 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app2.o.d" -o ${OBJECTDIR}/_ext/1360937237/app2.o ../src/app2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app3.o: ../src/app3.c  .generated_files/flags/default/6781a6f1ad5ce28bee177271d72c951b218ca59b .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app3.o.d" -o ${OBJECTDIR}/_ext/1360937237/app3.o ../src/app3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/ext_flash.o: ../src/ext_flash.c  .generated_files/flags/default/49f9aae9f2ef0c9ed34fde2c5c93add2a19e975b .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext_flash.o.d" -o ${OBJECTDIR}/_ext/1360937237/ext_flash.o ../src/ext_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app4.o: ../src/app4.c  .generated_files/flags/default/9baa1f52c52fa808d24fc5fbf2e8fb082ad41a92 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app4.o.d" -o ${OBJECTDIR}/_ext/1360937237/app4.o ../src/app4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/869808652/drv_usart.o: ../src/config/default/driver/usart/src/drv_usart.c  .generated_files/flags/default/2f8288302ec61d6f56726217398f6c76cb0f9015 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/869808652" 
	@${RM} ${OBJECTDIR}/_ext/869808652/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/869808652/drv_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/869808652/drv_usart.o.d" -o ${OBJECTDIR}/_ext/869808652/drv_usart.o ../src/config/default/driver/usart/src/drv_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60165182/plib_can0.o: ../src/config/default/peripheral/can/plib_can0.c  .generated_files/flags/default/ea64c2fd5942328e26f0a8b8c69a6234db7adc9b .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60165182" 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165182/plib_can0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165182/plib_can0.o.d" -o ${OBJECTDIR}/_ext/60165182/plib_can0.o ../src/config/default/peripheral/can/plib_can0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/beea676574338b5541a3f8d8503a6df75cc90a61 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/81c9801cfe1e07a2fa371aa29a8c7fa24f59a9b9 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/8496a9b0e8ce7f41f5907ffeb23730daeb597f9e .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/9eac372175ee1d69cb817fac8dfb98748eb127b2 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/64c2d59dda1755902a16b8acce9e0aff39e6d5af .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/7001ca13317f5133169275860ac8e694fd26d529 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o: ../src/config/default/peripheral/rtc/plib_rtc_clock.c  .generated_files/flags/default/42f10e1fad2f3b748df804d5a2796eb519000e63 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60180175" 
	@${RM} ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o.d" -o ${OBJECTDIR}/_ext/60180175/plib_rtc_clock.o ../src/config/default/peripheral/rtc/plib_rtc_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o: ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c  .generated_files/flags/default/d3e8c419f65d4465c0b8e3640855e5cd5dd34e82 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/17022449" 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o.d" -o ${OBJECTDIR}/_ext/17022449/plib_sercom0_spi_master.o ../src/config/default/peripheral/sercom/spi_master/plib_sercom0_spi_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/default/4bb3b268b848302c83005f34bf073ab148867971 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom3_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c  .generated_files/flags/default/c103d5f940f4306918e5fd44b25302a59e98d1e8 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom4_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom4_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c  .generated_files/flags/default/8a4fb13f5da76d050377644af035c877d2478000 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom2_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom2_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/flags/default/fe31a9d87069de95bfa391550f6ab8d5a7208bf4 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/3eff36db7bde3c31e83746b9255a255224f1a44 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc0.o: ../src/config/default/peripheral/tc/plib_tc0.c  .generated_files/flags/default/31e59b802d0a1837b68e4f3b1bfa776c54e093b3 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc0.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc0.o ../src/config/default/peripheral/tc/plib_tc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc3.o: ../src/config/default/peripheral/tc/plib_tc3.c  .generated_files/flags/default/f60a626c41ceaaf78e1b9566c2fd9bcdd4249256 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc3.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc3.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc3.o ../src/config/default/peripheral/tc/plib_tc3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60184501/plib_wdt.o: ../src/config/default/peripheral/wdt/plib_wdt.c  .generated_files/flags/default/fd25cbe246162d44842732ee38523f1d514d113e .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/60184501" 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/60184501/plib_wdt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60184501/plib_wdt.o.d" -o ${OBJECTDIR}/_ext/60184501/plib_wdt.o ../src/config/default/peripheral/wdt/plib_wdt.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/32997f39f8c1911acfa32e780198c5be877f034d .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/14461671/sys_dma.o: ../src/config/default/system/dma/sys_dma.c  .generated_files/flags/default/ff7886e24fe2c943bb2d4248b35480ef0b811fb6 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/14461671" 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/14461671/sys_dma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/14461671/sys_dma.o.d" -o ${OBJECTDIR}/_ext/14461671/sys_dma.o ../src/config/default/system/dma/sys_dma.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1881668453/sys_int.o: ../src/config/default/system/int/src/sys_int.c  .generated_files/flags/default/b05ee733a86d4098cc7cde43cacb489a00dc8637 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1881668453" 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1881668453/sys_int.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1881668453/sys_int.o.d" -o ${OBJECTDIR}/_ext/1881668453/sys_int.o ../src/config/default/system/int/src/sys_int.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/98bd6cac3a558491728cfb912320316ddc69127b .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/d6c247645e63eb9c3f2d4c74c698863d3861ae79 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/9c0d1ce3f9650c227208583fbc7fa75a2cbfbc41 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/388b9e3a1305afe7dee164e63727311602c7d683 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/34bf736cd0c3aea3d927e629f2c7f0180a5dda0a .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/tasks.o: ../src/config/default/tasks.c  .generated_files/flags/default/b7efdfd153a2e87a50bac0e60107be4b97463ce6 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/tasks.o.d" -o ${OBJECTDIR}/_ext/1171490990/tasks.o ../src/config/default/tasks.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/52811e184d1bed4ef0875bdcf7c0ba066fb68ebc .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/myapp.o: ../src/myapp.c  .generated_files/flags/default/882be6cde7f8503036a7fa30389b22b5216365b4 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/myapp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/myapp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/myapp.o.d" -o ${OBJECTDIR}/_ext/1360937237/myapp.o ../src/myapp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/7a82e48fddf98c59a862ec0fa34eca54a2b71820 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/at_engine.o: ../src/at_engine.c  .generated_files/flags/default/22b07b849d3cde96dc1d948e58dcfaa1f8d86b6c .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_engine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_engine.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/at_engine.o.d" -o ${OBJECTDIR}/_ext/1360937237/at_engine.o ../src/at_engine.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/at_parser.o: ../src/at_parser.c  .generated_files/flags/default/8d5b9f9c1abf7c1d9717a3b3ac0fea538f8cf384 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_parser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/at_parser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/at_parser.o.d" -o ${OBJECTDIR}/_ext/1360937237/at_parser.o ../src/at_parser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_adapter.o: ../src/dev_adapter.c  .generated_files/flags/default/f7f6cf2447c56f2f0d8c1211c388f784244cdfd2 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_adapter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_adapter.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_adapter.o ../src/dev_adapter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_hal.o: ../src/dev_hal.c  .generated_files/flags/default/e1b534dfee7c7f8a5a9d61d25671993505d1fef4 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_hal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_hal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_hal.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_hal.o ../src/dev_hal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/dev_timer.o: ../src/dev_timer.c  .generated_files/flags/default/e24c8b7f626b947bedc216be2b3f6cdd25840234 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/dev_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/dev_timer.o.d" -o ${OBJECTDIR}/_ext/1360937237/dev_timer.o ../src/dev_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/gsm_gps.o: ../src/gsm_gps.c  .generated_files/flags/default/840af68a0f22158f453ddcbae5fcd5162e296ebf .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gsm_gps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gsm_gps.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gsm_gps.o.d" -o ${OBJECTDIR}/_ext/1360937237/gsm_gps.o ../src/gsm_gps.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app2.o: ../src/app2.c  .generated_files/flags/default/f86c9f8cfcfd9f206ade63418ad081b407134df8 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app2.o.d" -o ${OBJECTDIR}/_ext/1360937237/app2.o ../src/app2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app3.o: ../src/app3.c  .generated_files/flags/default/ec2bc14fde12a4bf4807049ef791440bfd1c2c8d .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app3.o.d" -o ${OBJECTDIR}/_ext/1360937237/app3.o ../src/app3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/ext_flash.o: ../src/ext_flash.c  .generated_files/flags/default/1c0f3a990c28655b0e3d75a76a69fa9ab3289f4f .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_flash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ext_flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/ext_flash.o.d" -o ${OBJECTDIR}/_ext/1360937237/ext_flash.o ../src/ext_flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/app4.o: ../src/app4.c  .generated_files/flags/default/d822cb654673b1cc45882642634af7032214f668 .generated_files/flags/default/d58cecf073f007c4eefb026830697b84d2e55eb6
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -I"../src" -I"../src/config/default" -I"../src/packs/ATSAMC21J18A_DFP" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app4.o.d" -o ${OBJECTDIR}/_ext/1360937237/app4.o ../src/app4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/ATSAMC21J18A.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samc21"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/ATSAMC21J18A.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mno-device-startup-code -o dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}/samc21"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SMARTFARMING.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
