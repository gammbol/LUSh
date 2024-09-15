#include "include/lush.h"

int main(void) {
	printf("LUSh - L.U. Shell\n");
	lush_loop();
	return 0;
}

void lush_loop() {
	char *com = lush_input();
	printf("after input!\n");
	argsbuf *args = lush_parse(com);
	printf("after parse!\n");
	lush_exec(args);
	printf("after exec!\n");
}

char *lush_input() {
	char c;
	char *com = malloc(BUFSIZE);

	printf("> ");

	// getting input from user
	int i = 0;
	while ((c = getchar()) != '\n') com[i++] = c;
	com[i] = 0;

	return com;
}

argsbuf *lush_parse(char *com) {
	// argument buffer initialization
	argsbuf *ab = malloc(sizeof(argsbuf));
	memset(ab, 0, sizeof *ab);

	char *arg = malloc(BUFSIZE);
	memset(arg, 0, BUFSIZE);

	int i = 0;
	while (*com) {
		if (*com == ' ') {
			ab_append(ab, arg);
			memset(arg, 0, BUFSIZE);
			i = 0;
		} else {
			arg[i++] = *com;
		}
	}

	ab_append(ab, arg);
	free(arg);

	return ab;
}

void lush_exec(argsbuf *args) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
		// child process
		if (execvp(args->args[0], args->args) == -1) {
			perror("lush");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("lsh");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && ! WIFSIGNALED(status));
	}

	printf("WPID: %d\n", wpid);

}
