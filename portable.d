# This file is included by other makefiles

QUEUE=						\
	$(PORTABLE_PATH)/queue_init.c		\
	$(PORTABLE_PATH)/queue_deq.c		\
	$(PORTABLE_PATH)/queue_enq.c		\
	$(PORTABLE_PATH)/queue_flush.c		\
	$(PORTABLE_PATH)/queue_init.c		\
	$(PORTABLE_PATH)/queue_isempty.c	\
	$(PORTABLE_PATH)/queue_isfull.c		\
	$(PORTABLE_PATH)/queue_ocupied.c	\
	$(PORTABLE_PATH)/queue_peekfirst.c	\
	$(PORTABLE_PATH)/queue_peeklast.c	\
	$(PORTABLE_PATH)/queue.h
