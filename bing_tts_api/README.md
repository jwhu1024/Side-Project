# bing TTS REST api                                                                                                                                                    
# Before compile
```
change the api key in bing_tts.c
static const char *azure_api_key_1     = "";    // put your api key1 here
static const char *azure_api_key_2     = "";    // put your api key2 here
```

- cmake .
- make
- ./bin/bing_tts -t "This program demonstrates the use of the bing tts via REST API" -o /tmp/test.wav

```
Usage: bing_tts [-v] [-o <output>] [-t <input>] [--help] [--version]
This program demonstrates the use of the bing tts via REST API
  -o <output>               output file (default is "-")
  -t <input>                input text (default is "Microsoft Bing Voice Output API")
  -v, --verbose, --debug    verbose messages
  --help                    print this help and exit
  --version                 print version information and exit
```
