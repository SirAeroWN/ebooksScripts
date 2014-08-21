#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	cout << "make sure that you have read the readme and How-to at siraero.weebly.com/"
	system("python varGet.py");
	cout << "you will be prompted for your password, enter it to avoid a failed install of ruby" << endl;
	system("chmod +x rvmInstall.sh");
	system("./rvmInstall.sh");
	system("sudo gem install twitter_ebooks -v 2.2.6");
	string botName;
	string APIKey;
	string APISecret;
	string AccessToken;
	string AccessTokenSecret;
	botVars = fopen("botVars.txt", "r");
	if (botVars == NULL)
	{
		printf("The file containing your app information has something wrong with it, please try again\n");
	}
	int n = fscanf(botVars, "%s", &botName);
	n = fscanf(botVars, "%s", &APIKey);
	n = fscanf(botVars, "%s", &APISecret);
	n = fscanf(botVars, "%s", &AccessToken);
	n = fscanf(botVars, "%s", &AccessTokenSecret);
	fclose(botVars);
	string systemCommand = "ebooks new " + botName;
	system(systemCommand);
	systemCommand = "mv tweets.csv " + botName + "/corpus/" + botName + ".csv";
	system(systemCommand);
	systemCommand = "cd " + botName + "/";
	system(systemCommand);
	systemCommand = "ebooks consume corpus/" + botName + ".csv";
	system(systemCommand);
	FILE *f;
	char firstFileName[40];
	sprintf(firstFileName, "run.rb");
	f = fopen(firstFileName, "w");
	fprintf(f, "#!/usr/bin/env ruby\n\n#####################################################################\n# Hacky BS for Ruby SSL issue on Windows                            #\n# Based on:                                                         # \n# https://gist.github.com/fnichol/867550#file-win_fetch_cacerts-rb  #\n#####################################################################\nrequire 'shell'\n");
    fprintf(f, "require 'net/http'\n\npwd = Shell.new.pwd\nunless pwd[0] == '/'\n  cacert_file = File.join(pwd, 'cacert.pem')\n  ENV[\"SSL_CERT_FILE\"] = cacert_file\n  unless File.exists?(cacert_file)\n    Net::HTTP.start(\"curl.haxx.se\") do |http|\n      resp = http.get(\"/ca/cacert.pem\")");
    fprintf(f, "      if resp.code == \"200\"\n        open(cacert_file, \"wb\") { |file| file.write(resp.body) }\n      else\n        p \"There was a problem downloading cacert.pem\"\n        p \"Please save this file into your #{pwd} directory:\"\n        p \"\thttp://curl.haxx.se/ca/cacert.pem\"\n      end\n    end\n  end\nend\n\n");
   	fprintf(f, "##########################################\n# The actual script                      #\n##########################################\nrequire_relative 'bots'\nif ARGV[0] && ARGV[0] != 'start'\n  Ebooks::Bot.get(ARGV[0]).start\nelse\n  EM.run do\n   Ebooks::Bot.all.each do |bot|\n      bot.start\n    end\n  end\nend\n");
   	fclose(f);
   	FILE *k;
   	char secondFileName[40];
   	sprintf(secondFileName, "bots.rb");
   	f = fopen(firstFileName, "w");
   	fprintf(f, "#!/usr/bin/env ruby\n\nrequire 'twitter_ebooks'\ninclude Ebooks\n\nCONSUMER_KEY = \"");
   	fprintf(f, "%s\"\n", APIKey);
   	fprintf(f, "CONSUMER_SECRET = \"%s\"\n", APISecret);
   	fprintf(f, "OATH_TOKEN = \"%s\"\n", AccessToken);
   	fprintf(f, "OAUTH_TOKEN_SECRET = \"%s\"\n", AccessTokenSecret);
   	fprintf(f, "\nROBOT_ID = "ebooks" # Avoid infinite reply chains\n");
   	fprintf(f, "TWITTER_USERNAME = \"%s\"\n", botName);
   	fprintf(f, "TEXT_MODEL_NAME = \"%s\"\n", botName);
   	system("python read_write.py");
}