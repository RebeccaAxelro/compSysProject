#include "csapp.h"
/*
http://www.recipepuppy.com/about/api/

> telnet www.recipepuppy.com 80
> GET /api?q=salad HTTP/1.1
  Host: www.recipepuppy.com
  -- blank line --

- The Tiny web server is going to run our “website.” Tiny can receive HTTP requests and handle them.

- We can send a GET request to Tiny that tells it to open recipe.c, like we told it to run adder.c
by doing GET /cgi-bin/adder?1500&1400 HTTP/1.0. Instead of 1500 and 1400, it would contain the
parameters for the recipe search (like q=salad).

- recipe.c would then be run and it would connect to the recipepuppy API, send the request, and
receive the response data and deal with it
- then Tiny displays everything on browser

**recipepuppy.com (and most APIs) uses HTTP 1.1, NOT HTTP 1.0. So the request looks like this:
	GET /api HTTP/1.1
	Host: www.recipepuppy.com

(requires a host header)


  REQUEST TO API:


        GET /api?q=arg1... HTTP/1.1
        Host: www.recipepuppy.com
        blank line

       i.e. --> "GET /api?q=salad HTTP/1.1\r\nHost: www.recipepuppy.com\r\n\r\n"

 */

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], arg3[MAXLINE], content[MAXLINE];
            // ----- will the args come in as "cookie" or "recipe=cookie"? (html form) -----
            //  (just parse if necessary)

    char buffer[MAXLINE];
    char buffer2[MAXLINE];

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
      p = strchr(buf, '&');
    	*p = '\0';
    	 strcpy(arg1, buf);
    	 strcpy(arg2, p+1);
    	 n1 = atoi(arg1);
    	 n2 = atoi(arg2);
       n3 = atoi(arg3);

       // ----- add error handling for if there is only 1 arg -----
       // (because they just search for a recipe)
    }

    char *host, *port;
    rio_t rio;
    host = "www.recipepuppy.com"
    port = "80";

    /* establish connection with API */
    int clientfd = open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);


    if (clientfd == -1) {                                                   // if it couldn't establish connect
      printf("ERROR: connection could not be established.");
    }

    // if they search for a certain recipe
    /*
    char *arg1 = arg1;
    char *recipe = "recipe";
    char *arg = strstr(arg1, recipe);
    if (arg) { ... }
    */
    sprintf(buffer, "GET http://www.recipepuppy.com/api/?q=%s\n", arg1);       // save to buffer

    // if they search for ingredients
            // ----- ADD CODE ------

    Rio_writen(clientfd, buffer, MAXLINE);    // send request to server
    Rio_readlineb(&rio, buffer2, MAXLINE);    // read response
    Close(clientfd);





    /*  echoclient.c:
          after establishing a connection with the server, the client enters a loop
          that repeatedly
            1) reads a text line from standard input (stdin),             while (Fgets(buf, MAXLINE, stdin) != NULL) {
            2) sends the text line to the server,                           Rio_writen(clientfd, buf, strlen(buf));
            3) reads the echo line from the server,                         Rio_readlineb(&rio, buf, MAXLINE);
            4) and prints the result to standard output (stdout)            Fputs(buf, stdout);
                                                                          }
    */



    /* Make the response body */
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
	    content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    /* Generate the HTTP response */
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    Close(clientfd);
    exit(0);
}
/* $end adder */
