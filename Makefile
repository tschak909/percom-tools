
##
## FujiNet tools Master Make file.
## Hack-o-matic, for sure, it will get better.
##

.PHONY: all mostlyclean clean install zip

.SUFFIXES:

all mostlyclean clean install zip:
	@$(MAKE) -C pbget   --no-print-directory $@	
	@$(MAKE) -C pbset   --no-print-directory $@	

dist: all
	mkdir -p dist
	cp pbget/pbget.com dist/
	cp pbset/pbset.com dist/
	cp doc/pbget.doc dist/
	cp doc/pbset.doc dist/
	dir2atr 720 pbtools.atr dist/
