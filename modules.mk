mod_process_name.la: mod_process_name.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_process_name.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_process_name.la
