#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

int is_file_exist (const char *path)
{
	if ( access( path, F_OK ) != -1 )
		return 1;
	else
		return 0;
}

int _system (const char *fmt, ...)
{
	va_list args;
	int i;
	char buf[1024];

	memset(buf, 0x0, 1024);
	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);

	system(buf);
	return i;
}

int p_run_command (char *c, char *v)
{
	FILE *fp = NULL;
	char buf[1024] = {0};

	memset (buf, 0x0, sizeof(buf));
	fp = popen (c, "r");
	fread(buf, sizeof(char), sizeof(buf), fp);
	pclose (fp);
	buf[strlen(buf)] = '\0';
	strncpy(v, buf, strlen(buf) + 1);

	return strlen(v);
}

