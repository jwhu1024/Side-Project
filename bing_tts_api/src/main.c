#include <stdio.h>
#include <bing_tts.h>
#include <argtable2.h>

#define PROGRAM_NAME		"bing_tts"

/* Example : bing_tts -t "Microsoft Bing Voice Output API" -o /tmp/test.wav */
int main(int argc, char **argv)
{
	struct arg_file *outfile = arg_file0("o", NULL, "<output>", "output file (default is \"-\")");
	struct arg_file *intext  = arg_file0("t", NULL, "<input>", "input text (default is \"Microsoft Bing Voice Output API\")");
	struct arg_lit  *verbose = arg_lit0("v", "verbose,debug", "verbose messages");
	struct arg_lit  *help    = arg_lit0(NULL, "help", "print this help and exit");
	struct arg_lit  *version = arg_lit0(NULL, "version", "print version information and exit");
	struct arg_end  *end     = arg_end(20);

	void* argtable[] = {outfile, intext, verbose, help, version, end};
	int nerrors;
	int exitcode = 0;

	/* verify the argtable[] entries were allocated sucessfully */
	if (arg_nullcheck(argtable) != 0)
	{
		/* NULL entries were detected, some allocations must have failed */
		printf("%s: insufficient memory\n", PROGRAM_NAME);
		exitcode = 1;
		goto exit;
	}

	/* set any command line default values prior to parsing */
	outfile->filename[0] = "/tmp/test.wav";
	intext->filename[0] = "Microsoft Bing Voice Output API";

	/* Parse the command line as defined by argtable[] */
	nerrors = arg_parse(argc, argv, argtable);

	/* special case: '--help' takes precedence over error reporting */
	if (help->count > 0)
	{
		printf("Usage: %s", PROGRAM_NAME);
		arg_print_syntax(stdout,argtable,"\n");
		printf("This program demonstrates the use of the bing tts via REST API\n");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		exitcode=0;
		goto exit;
	}

	/* special case: '--version' takes precedence error reporting */
	if (version->count > 0)
	{
		printf("May 2018 v0.01\n");
		exitcode=0;
		goto exit;
	}

	/* If the parser returned any errors then display them and exit */
	if (nerrors > 0)
	{
		/* Display the error details contained in the arg_end struct.*/
		arg_print_errors(stdout, end, PROGRAM_NAME);
		printf("Try '%s --help' for more information.\n", PROGRAM_NAME);
		exitcode=1;
		goto exit;
	}

	/* special case: uname with no command line options induces brief help */
	if (argc==1)
	{
		printf("Try '%s --help' for more information.\n", PROGRAM_NAME);
		exitcode=0;
		goto exit;
	}

	/* normal case: take the command line options at face value */
	exitcode = bing_tts(outfile->filename[0], intext->filename[0], verbose->count);

exit:
	/* deallocate each non-null entry in argtable[] */
	arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));

	return exitcode;
}

