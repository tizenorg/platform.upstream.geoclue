libexec_PROGRAMS = geoclue-manual

noinst_DATA = \
	geoclue-manual.xml

nodist_geoclue_manual_SOURCES = \
	geoclue-manual-glue.h

BUILT_SOURCES =			\
	$(nodist_geoclue_manual_SOURCES)

geoclue_manual_SOURCES = 	\
	geoclue-manual.c

geoclue_manual_CFLAGS = \
	-I$(top_srcdir)     \
	-I$(top_builddir)   \
	$(GEOCLUE_CFLAGS)

geoclue_manual_LDADD = \
	$(GEOCLUE_LIBS)    \
	$(top_builddir)/geoclue/libgeoclue.la


providersdir = $(datadir)/geoclue-providers
providers_DATA = geoclue-manual.provider

servicedir = $(DBUS_SERVICES_DIR)
service_in_files = org.freedesktop.Geoclue.Providers.Manual.service.in
service_DATA = $(service_in_files:.service.in=.service)

$(service_DATA): $(service_in_files) Makefile
	@sed -e "s|\@libexecdir\@|$(libexecdir)|" $< > $@

CLEANFILES = \
	stamp-geoclue-manual-glue.h

EXTRA_DIST = 			\
	$(service_in_files)	\
	$(providers_DATA)	\
	$(noinst_DATA)

DISTCLEANFILES = 	\
	$(service_DATA)	\
	$(nodist_geoclue_manual_SOURCES)

%-glue.h: stamp-%-glue.h
	@true

stamp-geoclue-manual-glue.h: geoclue-manual.xml
	$(DBUS_BINDING_TOOL) --prefix=geoclue_manual --mode=glib-server $< > xgen-$(@F) \
	&& (cmp -s xgen-$(@F) $(@F:stamp-%=%) || cp xgen-$(@F) $(@F:stamp-%=%)) \
	&& rm -f xgen-$(@F) \
	&& echo timestamp > $(@F)
