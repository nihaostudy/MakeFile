#-C指定工作目录

.PHONY: 001 002 clean

DIR = 001 002

all: $(DIR)

$(DIR):
	make -C $@

clean: 
	make -C ./001 clean
	make -C ./002 clean

all-v1:
	make -C ./001
	make -C ./002

clean-v1:
	make -C ./001 clean
	make -C ./002 clean