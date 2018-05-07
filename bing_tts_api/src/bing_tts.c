#include <stdio.h>
#include <string.h>
#include <utils.h>

#define API_TOK_BUF_MAX_SZ		521+1
#define API_TOK_CMD_LENGTH		169+1
#define SSML_MAXIMAL_BYTES		1024
#define VOICE_CMD_MAX_LENGTH	153+API_TOK_BUF_MAX_SZ+2+219+SSML_MAXIMAL_BYTES

static const char *azure_api_key_1	   = "";	// put your api key1 here
static const char *azure_api_key_2	   = "";	// put your api key2 here
static const char *azure_api_key_host  = "https://api.cognitive.microsoft.com/sts/v1.0/issueToken";

typedef struct _S_BING_TTS_LANG_
{
	char *lang;
	char *gender;
} S_BING_TTS_LANG, *PS_BING_TTS_LANG;

static S_BING_TTS_LANG lang_property[] =
{
	{"ar_EG*", 	"Female"},	// Microsoft Server Speech Text to Speech Voice (ar-EG, Hoda)
	{"ar-SA",	"Male" 	},	// Microsoft Server Speech Text to Speech Voice (ar-SA, Naayf)
	{"bg-BG",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (bg-BG, Ivan)"	},
	{"ca-ES",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ca-ES, HerenaRUS)
	{"cs-CZ",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (cs-CZ, Jakub)
	{"da-DK",	"Female"},	// Microsoft Server Speech Text to Speech Voice (da-DK, HelleRUS)
	{"de-AT",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (de-AT, Michael)
	{"de-CH",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (de-CH, Karsten)
	{"de-DE",	"Female"},	// Microsoft Server Speech Text to Speech Voice (de-DE, Hedda)
	{"de-DE",	"Female"},	// Microsoft Server Speech Text to Speech Voice (de-DE, HeddaRUS)
	{"de-DE",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (de-DE, Stefan, Apollo)
	{"el-GR",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (el-GR, Stefanos)
	{"en-AU",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-AU, Catherine)
	{"en-AU",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-AU, HayleyRUS)
	{"en-CA",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-CA, Linda)
	{"en-CA",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-CA, HeatherRUS)
	{"en-GB",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-GB, Susan, Apollo)
	{"en-GB",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-GB, HazelRUS)
	{"en-GB",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (en-GB, George, Apollo)
	{"en-IE",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (en-IE, Sean)
	{"en-IN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-IN, Heera, Apollo)
	{"en-IN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-IN, PriyaRUS)
	{"en-IN",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (en-IN, Ravi, Apollo)
	{"en-US",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-US, ZiraRUS)
	{"en-US",	"Female"},	// Microsoft Server Speech Text to Speech Voice (en-US, JessaRUS)
	{"en-US",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (en-US, BenjaminRUS)
	{"es-ES",	"Female"},	// Microsoft Server Speech Text to Speech Voice (es-ES, Laura, Apollo)
	{"es-ES",	"Female"},	// Microsoft Server Speech Text to Speech Voice (es-ES, HelenaRUS)
	{"es-ES",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (es-ES, Pablo, Apollo)
	{"es-MX",	"Female"},	// Microsoft Server Speech Text to Speech Voice (es-MX, HildaRUS)
	{"es-MX",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (es-MX, Raul, Apollo)
	{"fi-FI",	"Female"},	// Microsoft Server Speech Text to Speech Voice (fi-FI, HeidiRUS)
	{"fr-CA",	"Female"},	// Microsoft Server Speech Text to Speech Voice (fr-CA, Caroline)
	{"fr-CA",	"Female"},	// Microsoft Server Speech Text to Speech Voice (fr-CA, HarmonieRUS)
	{"fr-CH",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (fr-CH, Guillaume)
	{"fr-FR",	"Female"},	// Microsoft Server Speech Text to Speech Voice (fr-FR, Julie, Apollo)
	{"fr-FR",	"Female"},	// Microsoft Server Speech Text to Speech Voice (fr-FR, HortenseRUS)
	{"fr-FR",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (fr-FR, Paul, Apollo)
	{"he-IL",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (he-IL, Asaf)
	{"hi-IN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (hi-IN, Kalpana, Apollo)
	{"hi-IN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (hi-IN, Kalpana)
	{"hi-IN",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (hi-IN, Hemant)
	{"hr-HR",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (hr-HR, Matej)
	{"hu-HU",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (hu-HU, Szabolcs)
	{"id-ID",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (id-ID, Andika)
	{"it-IT",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (it-IT, Cosimo, Apollo)
	{"ja-JP",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ja-JP, Ayumi, Apollo)
	{"ja-JP",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ja-JP, Ichiro, Apollo)
	{"ja-JP",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ja-JP, HarukaRUS)
	{"ja-JP",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ja-JP, LuciaRUS)
	{"ja-JP",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ja-JP, EkaterinaRUS)
	{"ko-KR",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ko-KR, HeamiRUS)
	{"ms-MY",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ms-MY, Rizwan)
	{"nb-NO",	"Female"},	// Microsoft Server Speech Text to Speech Voice (nb-NO, HuldaRUS)
	{"nl-NL",	"Female"},	// Microsoft Server Speech Text to Speech Voice (nl-NL, HannaRUS)
	{"pl-PL",	"Female"},	// Microsoft Server Speech Text to Speech Voice (pl-PL, PaulinaRUS)
	{"pt-BR",	"Female"},	// Microsoft Server Speech Text to Speech Voice (pt-BR, HeloisaRUS)
	{"pt-BR",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (pt-BR, Daniel, Apollo)
	{"pt-PT",	"Female"},	// Microsoft Server Speech Text to Speech Voice (pt-PT, HeliaRUS)
	{"ro-RO",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ro-RO, Andrei)
	{"ru-RU",	"Female"},	// Microsoft Server Speech Text to Speech Voice (ru-RU, Irina, Apollo)
	{"ru-RU",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ru-RU, Pavel, Apollo)
	{"sk-SK",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (sk-SK, Filip)
	{"sl-SI",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (sl-SI, Lado)
	{"sv-SE",	"Female"},	// Microsoft Server Speech Text to Speech Voice (sv-SE, HedvigRUS)
	{"ta-IN",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (ta-IN, Valluvar)
	{"th-TH",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (th-TH, Pattara)
	{"tr-TR",	"Female"},	// Microsoft Server Speech Text to Speech Voice (tr-TR, SedaRUS)
	{"vi-VN",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (vi-VN, An)
	{"zh-CN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-CN, HuihuiRUS)
	{"zh-CN",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-CN, Yaoyao, Apollo)
	{"zh-CN",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (zh-CN, Kangkang, Apollo)
	{"zh-HK",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-HK, Tracy, Apollo)
	{"zh-HK",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-HK, TracyRUS)
	{"zh-HK",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (zh-HK, Danny, Apollo)
	{"zh-TW",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-TW, Yating, Apollo)
	{"zh-TW",	"Female"},	// Microsoft Server Speech Text to Speech Voice (zh-TW, HanHanRUS)
	{"zh-TW",	"Male"	},	// Microsoft Server Speech Text to Speech Voice (zh-TW, Zhiwei, Apollo)
};

int voice_synthesis_request (char *api_token)
{
	char sc[API_TOK_CMD_LENGTH] = {0};
	
	snprintf(sc, API_TOK_BUF_MAX_SZ,
			"curl -X POST --header \"Content-Length: 0\" \
			--header \"Ocp-Apim-Subscription-Key:%s\" \"%s\"" \
			, azure_api_key_1, azure_api_key_host);

#ifdef _DEBUG_
	printf("cmd: %s\n\n", sc);
#endif

	return p_run_command(sc, api_token);
}

/*curl -X POST --header "X-Microsoft-OutputFormat: riff-8khz-8bit-mono-mulaw" --header "Content-Type: application/ssml+xml" --header "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJ1cm46bXMuY29nbml0aXZlc2VydmljZXMiLCJleHAiOiIxNTI1NjU4Mzk4IiwicmVnaW9uIjoiZ2xvYmFsIiwic3Vic2NyaXB0aW9uLWlkIjoiYWNlNWI5OWY0MGYyNDY1NTkwMzk5YmFkZjhhZGJmZjIiLCJwcm9kdWN0LWlkIjoiQmluZy5TcGVlY2guUHJldmlldyIsImNvZ25pdGl2ZS1zZXJ2aWNlcy1lbmRwb2ludCI6Imh0dHBzOi8vYXBpLmNvZ25pdGl2ZS5taWNyb3NvZnQuY29tL2ludGVybmFsL3YxLjAvIiwiYXp1cmUtcmVzb3VyY2UtaWQiOiIiLCJzY29wZSI6Imh0dHBzOi8vc3BlZWNoLnBsYXRmb3JtLmJpbmcuY29tIiwiYXVkIjoidXJuOm1zLnNwZWVjaCJ9.FWYvXrynOK52MVuzyIcs1kr4y7EpfNISj2ScWFj-lsc" -d "<speak version='1.0' xml:lang='en-US'><voice xml:lang='en-US' xml:gender='Female' name='Microsoft Server Speech Text to Speech Voice (en-US, ZiraRUS)'>Microsoft Bing Voice Output API</voice></speak>" "https://speech.platform.bing.com/synthesize"*/
int voice_output_request(const char *intext, const char *outfile, char *jwt_tok)
{
	char szTemp[1] = {0};
	char sc[VOICE_CMD_MAX_LENGTH] = {0};
	
	snprintf(sc, VOICE_CMD_MAX_LENGTH,
			"curl -X POST --header \"X-Microsoft-OutputFormat: riff-8khz-8bit-mono-mulaw\" \
			--header \"Content-Type: application/ssml+xml\" \
			--header \"Authorization: Bearer %s\" \
			-d \"<speak version='1.0' xml:lang='en-US'><voice xml:lang='en-US' xml:gender='Female' name='Microsoft Server Speech Text to Speech Voice (en-US, ZiraRUS)'>%s</voice></speak>\" \
			\"https://speech.platform.bing.com/synthesize\" \
			> %s", jwt_tok, intext, outfile);

#ifdef _DEBUG_
	printf("cmd: %s\n", sc);
#endif

	return p_run_command(sc, szTemp);
}

int bing_tts(const char *outfile, const char *intext, int verbose)
{
	int len;

#ifdef _DEBUG_
	printf("output file is \"%s\"\n", outfile);
	printf("input text is \"%s\"\n", intext);

	if (verbose > 0)
		printf("verbose is enabled (-v)\n");
#endif

	// Voice synthesis request
	char jwt_tok[API_TOK_BUF_MAX_SZ] = {0};
	len = voice_synthesis_request(jwt_tok);

#ifdef _DEBUG_
	printf("len: %d\n", len);
	printf("api_tok: %s\n", jwt_tok);
#endif

	//  Voice output request
	len = voice_output_request(intext, outfile, jwt_tok);

	if (is_file_exist(outfile) == 0)
	{
		printf("Error, please retry...\n");
		return 0;
	}

	return 1;
}
