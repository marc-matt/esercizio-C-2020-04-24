/*
 * ExOpSys_04_24.c
 *
 *  Created on: 22 mag 2020
 *      Author: M. Marconi
 *      Status: DONE
 *     Version: 1.0.1
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void child_process(char * file_name, char * text_to_write, int text_to_write_len){
	int text_child_len = (text_to_write_len / 2);
	char * partial_string;
	int point = text_child_len + 1;
	partial_string = calloc(text_child_len, sizeof(char));
	for(int i = 0; i < text_child_len + 1 ; i++){
		partial_string[i] = text_to_write[point];
		point++;
	}
    printf("Ciao! Sono [CHILD]\n");
    int fd = open(file_name, O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
    printf("Scrivo %d bytes\n", text_child_len);
	int res = write(fd, text_to_write, text_child_len);
	if(res == -1){
		perror("write()");
		exit(EXIT_FAILURE);
	}
    if (close(fd) == -1) {
			perror("close()");
			exit(EXIT_FAILURE);
		}
		printf("bye!\n");
		exit(EXIT_SUCCESS);
    exit(EXIT_SUCCESS);
}

int main(int argc, char * argv[]){
	char * file_name;
	int text_to_write_len;
	int text_parent_len;
	char * text_to_write = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin malesuada mi eget quam convallis, vel gravida nulla ultrices. Morbi iaculis neque quam, in commodo mauris tincidunt at. Etiam vitae posuere ante. Sed ac lacinia nibh. Quisque cursus consectetur nulla, nec placerat nisi dictum sed. Vivamus maximus interdum libero, vel sollicitudin erat. Donec felis velit, consectetur at arcu vitae, ultricies rutrum massa. Nam cursus justo vitae euismod consectetur. Aenean fermentum mollis lacus, quis convallis sem pellentesque at. Maecenas posuere leo sit amet ultricies sagittis. Pellentesque vel enim at nisl aliquet viverra. Nullam feugiat tincidunt mauris, at tristique diam tincidunt ut. Sed eleifend purus tincidunt tincidunt blandit. Sed imperdiet, massa in faucibus placerat, lacus sapien egestas lectus, in malesuada felis ante eu turpis. Vestibulum ut lectus a elit aliquam ornare. Cras molestie urna ac euismod pulvinar. Morbi dignissim pulvinar tellus, malesuada mattis sem iaculis a. Nullam cursus lorem a ligula dapibus, nec elementum lacus pharetra. Nulla facilisi. Donec aliquam nunc tellus, id interdum nisl rhoncus et. Curabitur hendrerit tempor nibh ut luctus. Nullam ut ante vel tellus tristique porttitor at ut erat. Ut tincidunt mattis odio, non volutpat dolor egestas nec. Duis iaculis, augue at pretium bibendum, orci mauris varius leo, at egestas risus lacus in lorem. Proin elementum, sapien eu sodales lacinia, nulla magna iaculis lorem, et cursus lorem tellus ac felis. Morbi rutrum lorem id ligula aliquet, ut dignissim ligula iaculis. Donec tincidunt ex id nisl interdum vehicula quis vitae lorem. Nunc posuere, eros eu iaculis vulputate, sapien quam commodo nisl, eu consequat diam neque sit amet enim. Suspendisse et nunc luctus, pretium sapien nec, porttitor nulla. Fusce luctus felis eget fringilla facilisis. Donec non luctus velit. Etiam id tincidunt ligula. Nam risus lorem, congue a sagittis quis, mollis vitae lorem. Praesent quis tortor ipsum. Mauris aliquet, sem eu pretium accumsan, lectus nulla tempor odio, sed tristique purus diam quis diam. Proin bibendum commodo dolor vel venenatis. Fusce ac elit id erat sollicitudin convallis. Integer luctus diam non nulla vehicula, ac aliquam velit maximus. Fusce porttitor faucibus magna, nec tempor massa vestibulum vel. Nullam sed vestibulum erat, ut ornare arcu. Nulla id posuere libero, quis finibus elit. Donec nibh augue, maximus sit amet nunc vitae, semper condimentum lorem. Nunc a nisl tellus. Quisque sed erat vel est pellentesque venenatis id nec diam. Nam eleifend tortor non mauris feugiat, eget ullamcorper nulla gravida. Cras id pulvinar tellus, quis lobortis leo. Praesent vitae condimentum risus. Integer sit amet accumsan orci. Aenean quis urna sagittis augue egestas gravida vel quis ex. Morbi quis enim vel erat gravida vulputate at at leo. Nam maximus, nibh nec egestas dignissim, lacus ligula condimentum urna, ac porta risus ligula cursus arcu. Quisque ut varius odio. In tristique ante ac mi posuere, quis accumsan nulla porta. Praesent vel eleifend ex. Pellentesque magna enim, pulvinar nec varius sed, ullamcorper et felis. Pellentesque luctus lectus vel ligula elementum porta. Proin ac felis vestibulum augue aliquam imperdiet et et sem. Fusce cursus arcu nunc, quis venenatis neque varius sit amet. Suspendisse a eleifend eros. Phasellus non odio ut quam condimentum congue. Aliquam lobortis leo felis, eu scelerisque libero facilisis ac. Etiam fringilla molestie justo in facilisis.";
	if (argc == 1) {
		printf("specificare come parametro il nome del file da creare e su cui scrivere\n");
		exit(EXIT_FAILURE);
	}
	file_name = argv[1];
	printf("scrivo nel file %s\n", file_name);
	int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	text_to_write_len = strlen(text_to_write);
	text_parent_len = text_to_write_len / 2;
    printf("Scrivo %d bytes\n", text_parent_len);
	int res = write(fd, text_to_write, text_parent_len);
	if(res == -1){
		perror("write()");
		exit(EXIT_FAILURE);
	}
    switch (fork()){
    case -1:
        perror("fork()");
        exit(EXIT_FAILURE);
        break;
    case 0: 
        child_process(file_name, text_to_write, text_to_write_len);
    default:
        break;
    }
	if (close(fd) == -1) {
		perror("close()");
		exit(EXIT_FAILURE);
	}
	printf("bye!\n");
	exit(EXIT_SUCCESS);
}
