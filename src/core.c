#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 


/* anskabot alpha 1
 * [X] receive text from user as parameter
 * [X] send a answer to the user as return 
 * [ ] save the user requests
 * [ ] learn to use a data response
 * [ ] make a DB
 * [ ] online connection
 * [ ] better text search reference
 * [X] functions
 * [ ] intercept functions inside of messages
 * [ ] can edit the messages through the bot
 * [ ] use threads to make schedules list
 * [ ] can create and save system variables
 * [ ] kwownledge to learn what means the questions  (what is, looking for, search, tell me)
 * [ ] make titles for each topic
 * [ ] create categories
 * [ ] add todo list, manage todo with searches and commands
 * [ ] make it restful API server and return must be in json
 * [ ] individual use with token
 * [ ] add news search
 * [ ] video youtube downloader
 * [ ] make it an audio reader
 * [ ] make the answer in audio
 * [x] use linux to develop (test only)
  
 * gcc -w -o bot core.c
 * .\bot.exe 


training mode ON
 human: what is your birthdate?
 bot: @emocionalSorry, I can't answer that, can you help me [Y/N] @askYesNo ?
 human: y
 bot: @emotionalThanks! so, what sould I answer for your question?
 human: I was born in november, 17 of 2018
 bot: @emocionalOk so, if someone asks to me "what is your birthdate?" @trainingQuestion i should tell him "I was born in november, 17 of 2018" @trainingAnswer, I'll remember that on our next talk!
 bot: did you have another answer-type for this question for me [Y/N] @askYesNo ?
 human: y
 bot: thank you! so, what should I answer for your question?
 human: 17 11 2018
 bot: @emocionalOk so, if someone asks to me "what is your birthdate?" @trainingQuestion I should tell him "17 11 2018" trainingAnswer, I'll remember that on our next talk!
 bot: did you have another answer-type for this question for me [Y/N] @askYesNo ?
 human: n
 bot: @emocionalOk, i have the right answer now, you rock! so, what kind of category you recommend to I record this type of request? @breakLine @categoryList @breakline [X] - New One
 human: x
 bot: understood! tell me what is the name of this new category
 human: personal info
 bot: @emocionalOk now tell me what means this question?
 human: birthdate
 bot: @emocionalOk i've saved every data into my memory, @emotionalThanks once again, you doing a great job, training me!


"tell me about <topic>"
https://simple.wikipedia.org/wiki/<topic>

continuous topic https://simple.wikipedia.org/wiki/Dog
human: topic
bot: @emotionalOk, type what a kind of topic you want to know
human: dog
bot: Dogs (Canis lupus familiaris) are domesticated mammals, not natural wild animals. They were originally bred from wolves.\n
They have been bred by humans for a long time, and were the first animals ever to be domesticated.\n
Today, some dogs are used as pets, others are used to help humans do their work. They are a popular pet because they are usually playful, friendly, loyal and listen to humans.\n
Dogs eat both meat and vegetables, often mixed together and sold in stores as dog food.\n
Dogs often have jobs, including as police dogs, army dogs, assistance dogs, fire dogs, messenger dogs, hunting dogs, herding dogs, or rescue dogs.\n
They are sometimes called "canines" from the Latin word for dog - canis. Sometimes people also use "dog" to describe other canids, such as wolves.\n
A baby dog is called a pup or puppy. A dog is called a puppy until it is about one year old.\n
Dogs are sometimes referred to as "man's best friend" because they are kept as domestic pets and are usually loyal and like being around humans.\n\n
[1] - Appearance and behaviour
[2] - Lifespan
[3] - Origin of dogs
[4] - Dogs and humans
[5] - Dog breeds
[6] - References
[X] - I'm done
@topicListOptions
human: life
bot: Different dog breeds have different lifespans.\n
In general, smaller dogs live longer than bigger ones.\n
The size and the breed of the dog change how long the dog lives, on average.\n
Breeds such as the Dachshund usually live for fifteen years, Chihuahuas can reach age twenty.\n
The Great Dane, on the other hand has an average lifespan of six to eight years; some Great Danes have lived for ten years.\n\n
[0] - Description
[1] - Appearance and behaviour
[3] - Origin of dogs
[4] - Dogs and humans
[5] - Dog breeds
[6] - References
[X] - I'm done
@topicListOptions
human: x
bot: @emocionalOk, no more talk about @topicName
human: topic
bot: @emotionalOk, type what a kind of topic you want to know
human: cat
bot: @emotionalSorry, I don't know about it, can you teach me this topic @yesno?
human: yes
bot: @emotionalOk So, I need that you tell me about the description of topic
human: !load file.txt
bot: @emotionalOk Do you have any extra itens to complement this topic @yesno?
human: y
bot: @emotionalOk Inform the name of the item please
human: Communication
bot: @emotionalOk Send me info about the current item description 
human: Cats use many different sounds for communication, including meowing, purring, trilling, hissing, growling, squeaking, chirping, clicking and grunting.
bot: @emotionalOk Do you have any extra itens to complement this topic @yesno?
human: no
bot: @emotionalThanks, try to talk with me the @topic that we've created and see the results!

human: name
bot: "@requestText"? What means it? I've a lot of options, please be more specific\n
[0] - What's your name?
[1] - What's my author name?
[X] - Nothing
human: your name
bot: my name is @botName

functions
@emocionalOk = [
Got it!
Great!
Understood!
Okay!
I understand it!
Right!
]

@emocionalSorry = [
Oh no
Sorry
Excuse me, but...
Pardon me
My apologies @name
]

@emotionalThanks = [
Thanks
Thank you
]

@emocionalWhat = [
What
]

@yesno= [
[Y/N]
]

 */

typedef struct replyMessage {;
	char message[255];
} replyMessage;

int APPLICATION_VERSION_NUMBER = 1;
char APPLICATION_VERSION_TYPE[] = "alpha";
char DEFAULT_ANSWER[] = "Answer not found!"; 
struct replyMessage replyFinal;

int checkRequest(char *request[]);
int checkReply(int category);
int checkFunction(char *text[]);

int main(int argc, char *argv[]){

	char *userRequest = strdup(argv[1]);
	char *answer[255];
	
	int category = checkRequest(userRequest);
	
	int status = checkReply(category);

	if (status != 0){
		sprintf(replyFinal.message, "%s", DEFAULT_ANSWER);
	}

	strtok(replyFinal.message, "\n");
	
	printf("%s\n", replyFinal.message);

	return 0;
}

int checkRequest(char *request[]){
	FILE *fileRequests;
	fileRequests = fopen("../data/requests", "r");

	char *stringLine[255];
	int category = -1, selectedCategory = -1;

	if (fileRequests == NULL){
		perror("Error while opening the requests file.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(stringLine, sizeof(stringLine), fileRequests)) {
		if(strstr(stringLine,"&") != 0) {
			category++; 
		} else if (strstr(stringLine,request) != 0) {
			selectedCategory = category;	
			break;	
		}
	}

	fclose(fileRequests);
	return selectedCategory;
}

int checkReply(int category){
	char answer[255];
	sprintf(answer, "%d", category);
	char *stringLine[255];
	int selectedCategory = -1, repliesListCount = -1, chooseMessage = 0;
	struct replyMessage repliesMessageList[255];

	FILE *fileReplies;
	fileReplies = fopen("../data/replies", "r");
	
	if (fileReplies == NULL){
		perror("Error while opening the replies file.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(stringLine, sizeof(stringLine), fileReplies)) {
		if(strstr(stringLine,"&") != 0) {
			selectedCategory++; 
		} else if (selectedCategory == category){
			repliesListCount++;	
			strcpy(repliesMessageList[repliesListCount].message,stringLine);
		} else if (selectedCategory > category){
			break;
		}
	}

	fclose(fileReplies);

	if (repliesListCount > 0){
		srand(time(NULL));
		chooseMessage = rand() % (repliesListCount + 1);
	}

	if (repliesListCount >= 0){
		if(strstr(repliesMessageList[chooseMessage].message,"@") != 0){
			return checkFunction(repliesMessageList[chooseMessage].message);
		} else {
			replyFinal = repliesMessageList[chooseMessage]; 
			return 0;	
		}	
	} else {
		return 1;
	}
	
}

int checkFunction(char *text[]){
	strtok(text, "\n");
	if (strcmp("@random", text) == 0) {
		srand(time(NULL));
		sprintf(replyFinal.message, "%d",  rand() % 100);
		return 0;
	} else if (strcmp("@version", text) == 0) {
		sprintf(replyFinal.message, "%s - compilation %d", APPLICATION_VERSION_TYPE, APPLICATION_VERSION_NUMBER);	
		return 0;
	} else if (strcmp("@datetime", text) == 0) {
		time_t timeManager = time(NULL);
		struct tm timelocal = *localtime(&timeManager);
		sprintf(replyFinal.message, "now is %d-%d-%d %d:%d:%d", timelocal.tm_year + 1900, timelocal.tm_mon + 1, timelocal.tm_mday, timelocal.tm_hour, timelocal.tm_min, timelocal.tm_sec);	
		return 0;
	}

	return 1;
}