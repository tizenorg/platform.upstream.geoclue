noinst_PROGRAMS = \
	position-example \
	position-async-example \
	master-example \
	master-pos-example \
	address-example \
	geocode-example \
	revgeocode-example \
	common-example

position_example_SOURCES = position-example.c
position_async_example_SOURCES = position-async-example.c
master_example_SOURCES = master-example.c
master_pos_example_SOURCES = master-pos-example.c
address_example_SOURCES = address-example.c
geocode_example_SOURCES = geocode-example.c
revgeocode_example_SOURCES = revgeocode-example.c
common_example_SOURCES = common-example.c

AM_CFLAGS = $(GEOCLUE_CFLAGS)
LDADD = \
	$(GEOCLUE_LIBS) \
    $(top_builddir)/geoclue/libgeoclue.la
