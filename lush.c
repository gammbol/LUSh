#include "include/lush.h"

userinfo ui = {};


int main(void) {
	lush_init();
	printf("\033c");
	printf("LUSh - L.U. Shell\n");
	lush_loop();
	return 0;
}

void lush_init() {
	ui.username[1023] = 0;
	ui.hostname[1023] = 0;

	getlogin_r(ui.username, 1023);
	gethostname(ui.hostname, 1023);
}

void lush_loop() {
	while (1) {
		char *com = lush_input();
		if (strcmp(com, "exit") == 0) {
			free(com);
			exit(EXIT_SUCCESS);
		}
		argsbuf *args = lush_parse(com);
		lush_exec(args);
		ab_free(args);
		free(com);
	}
}

char *lush_input() {
	char c;
	char *com = malloc(BUFSIZE);

	printf("[%s@%s]$ ", ui.username, ui.hostname);

	// getting input from user
	int i = 0;
	while ((c = getchar()) != '\n') com[i++] = c;
	com[i] = 0;

	return com;
}

argsbuf *lush_parse(char *com) {
	// argument buffer initialization
	argsbuf *ab = malloc(sizeof(argsbuf));
	memset(ab, 0, sizeof(*ab));

	char *arg = malloc(BUFSIZE);
	memset(arg, 0, BUFSIZE);

	int i = 0;
	while (*com) {
		if (*com == ' ') {
			arg[i] = 0;
			ab_append(ab, arg);
			memset(arg, 0, BUFSIZE);
			i = 0;
		} else {
			arg[i++] = *com;
		}
		com++;
	}

	arg[i] = 0;
	ab_append(ab, arg);
	free(arg);

	return ab;
}

void lush_exec(argsbuf *args) {
	pid_t pid;
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
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && ! WIFSIGNALED(status));
	}
}
