#include "zlog.h"
zlog_category_t *c;
int init_zlog(void)
{
	int rc;


	rc = zlog_init("/opt/zlog.conf");
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	c = zlog_get_category("my_cat");
	if (!c) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

//	zlog_fini();
	return 0;
}
